#include "acomplexType.hpp"
#include "mdview.h"
#include "view.h"

#include <array>
#include <cassert>
#include <iostream>
#include <vector>

using view::mdView;
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

///////////////MDVIEW
template <size_t N, size_t M, typename T>
bool testmdview_fixed(const std::vector<T> &arr, mdView<T, N, M> view) {
  std::cout << "testmdview_fixed<" << N << ", " << M << ">\n";
  bool success = true;

  for (size_t i = 0; i < N; i++) {
    for (size_t j = 0; j < M; j++) {
      auto idx = i * M + j;
      if (view[i][j] != arr[idx]) {
        std::cout << idx << " (" << i << ", " << j << ") " << view[i][j] << " "
                  << arr[idx] << "\n";

        success = false;
      }
    }
  }
  return success;
}

template <typename T>
bool testmdview_subarray(const std::vector<T> &arr, size_t sub,
                         mdView<T> view) {
  const auto N = view.size();
  const auto M = view[0].size();
  std::cout << "testmdview_nonfixed (+" << sub << ", [" << N << ", " << M
            << "])\n";
  //   assert(view.size() == 10 - sub);
  bool success = true;

  for (size_t i = 0; i < N; i++) {
    for (size_t j = 0; j < M; j++) {
      auto idx = sub + i * M + j;
      if (view[i][j] != arr[idx]) {
        std::cout << idx << " (" << i << ", " << j << ") " << view[i][j] << " "
                  << arr[idx] << "\n";

        success = false;
      }
    }
  }
  return success;
}

template <size_t N, size_t M, typename T>
void print_mdView(mdView<T, N, M> view) {
  std::cout << "printmdView<" << N << ", " << M << ">\n";
  for (size_t i = 0; i < N; i++) {
    for (size_t j = 0; j < M; j++) {

      std::cout << view[i][j] << " ";
    }

    std::cout << "\n";
  }
}

int main() {
  std::cout << "#View\n";

  {
    std::cout << "## with std::array<int,N> \n";
    std::array<int, 10> arr = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    assert(testview_fixed(arr, {arr.data()}));
    assert(testview_subarray(arr, 4, {arr.data() + 4, 6}));
    assert(testview_subarray(arr, 5, {arr.data() + 5, 3}));
  }
  ////
  {
    std::cout << "## with std::vector<int> \n";
    std::vector<int> arr = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    assert(testview_fixed<3>(arr, {arr.data()}));
  }

  {
    std::cout << "## with std::vector<AcomplexType> \n";
    std::vector<i3> arr = {{1, 2, 3},    {4, 5, 6},    {7, 8, 9},
                           {10, 11, 12}, {13, 14, 15}, {16, 17, 18},
                           {19, 20, 21}};

    assert(testview_fixed<3>(arr, {arr.data()}));
    // twist: I also specify the size
    assert(testview_fixed<3>(arr, {arr.data(), 3}));
    assert(testview_subarray(arr, 1, {arr.data() + 1, 2}));
    // Is upt to the user to give a valid size
    assert(testview_subarray(arr, 2, {arr.data() + 2, 4}));
  }

  std::cout << "#mdView\n";
  {
    std::cout << "## with std::vector<int> \n";
    std::vector<int> arr = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    // print_mdView<3, 4, int>({arr.data()});
    // print_mdView<4, 3, int>({arr.data()});
    // print_mdView<6, 2, int>({arr.data()});
    // print_mdView<2, 6, int>({arr.data()});
    auto res = testmdview_fixed<3, 4>(arr, {arr.data()});
    assert(res);
    res = testmdview_fixed<4, 3>(arr, {arr.data()});
    assert(res);
    // twist: I also specify the size
    res = testmdview_fixed<2, 6>(arr, {arr.data(), 2, 6});
    assert(res);
  }
  {
    std::cout << "## with std::vector<AcomplexType> \n";
    std::vector<i3> arr = {{1, 2, 3},    {4, 5, 6},    {7, 8, 9},
                           {10, 11, 12}, {13, 14, 15}, {16, 17, 18},
                           {19, 20, 21}};

    auto res = testmdview_fixed<2, 3>(arr, {arr.data()});
    assert(res);
    res = testmdview_fixed<3, 2>(arr, {arr.data(), 3, 2});
    assert(res);

    res = testmdview_subarray(arr, 1, {arr.data() + 1, 3, 2});
    assert(res);
    res = testmdview_subarray(arr, 1, {arr.data() + 1, 2, 3});
    assert(res);
    res = testmdview_subarray(arr, 2, {arr.data() + 2, 2, 2});
    assert(res);
  }
  return 0;
}
