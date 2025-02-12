#include "acomplexType.hpp"
#include "view.h"

#include <array>
#include <cassert>
#include <iostream>
#include <vector>

using view::View;

using i3 = AcomplexType<int, 3>;

template <typename T, size_t N>
bool testview_fixed(const std::array<T, N> &arr, View<T, N> view) {
  std::cout << "testview_fixed\n";
  assert(view.size() == N);
  bool success = true;
  for (size_t i = 0; i < arr.size(); i++) {
    if (view[i] != arr[i]) {
      std::cout << i << " " << view[i] << " " << arr[i] << "\n";
      success = false;
    }
  }
  return success;
}

template <size_t N, typename T>
bool testview_fixed(const std::vector<T> &arr, View<T, N> view) {
  std::cout << "testview_fixed\n";
  assert(view.size() == N);
  bool success = true;
  for (size_t i = 0; i < arr.size(); i++) {
    if (view[i] != arr[i]) {
      std::cout << i << " " << view[i] << " " << arr[i] << "\n";
      success = false;
    }
  }
  return success;
}

template <typename T>
bool testview_subarray(const std::vector<T> &arr, size_t sub, View<T> view) {
  std::cout << "testview_nonfixed (+" << sub << ", " << view.size() << ")\n";
  //   assert(view.size() == 10 - sub);
  bool success = true;
  for (size_t i = 0; i < view.size(); i++) {
    assert(i + sub < arr.size());
    if (view[i] != arr[i + sub]) {
      std::cout << i << " " << view[i] << " " << arr[i + sub] << "\n";
      success = false;
    }
  }
  return success;
}

bool testview_subarray(const std::array<int, 10> &arr, size_t sub,
                       View<int> view) {
  std::cout << "testview_nonfixed (+" << sub << ", " << view.size() << ")\n";
  bool success = true;
  for (size_t i = 0; i < view.size(); i++) {
    if (view[i] != arr[i + sub]) {
      std::cout << i << " " << view[i] << " " << arr[i + sub] << "\n";
      success = false;
    }
  }
  return success;
}
int main() {
  {
    std::cout << "# with std::array<int,N> \n";
    std::array<int, 10> arr = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    assert(testview_fixed(arr, {arr.data()}));
    assert(testview_subarray(arr, 4, {arr.data() + 4, 6}));
    assert(testview_subarray(arr, 5, {arr.data() + 5, 3}));
  }
  ////
  {
    std::cout << "# with std::vector<int> \n";
    std::vector<int> arr = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    assert(testview_fixed<3>(arr, {arr.data()}));
  }

  {
    std::cout << "# with std::vector<AcomplexType> \n";
    std::vector<i3> arr = {{1, 2, 3},    {4, 5, 6},    {7, 8, 9},
                           {10, 11, 12}, {13, 14, 15}, {16, 17, 18},
                           {19, 20, 21}};

    assert(testview_fixed<3>(arr, {arr.data()}));

    assert(testview_subarray(arr, 1, {arr.data() + 1, 2}));
    // Is upt to the user to give a valid size
    assert(testview_subarray(arr, 2, {arr.data() + 2, 4}));
  }

  return 0;
}
