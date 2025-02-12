#include "view.h"
#include <array>
#include <cassert>
#include <iostream>
#include <vector>

using view::View;

bool testview_fixed(const std::array<int, 10> &arr, View<int, 10> view) {
  std::cout << "testview_fixed\n";
  assert(view.size() == 10);
  bool success = true;
  for (size_t i = 0; i < arr.size(); i++) {
    if (view[i] != arr[i]) {
      std::cout << i << " " << view[i] << " " << arr[i] << "\n";
      success = false;
    }
  }
  return success;
}

bool testview_subarray(const std::array<int, 10> &arr, size_t sub,
                       View<int> view) {
  std::cout << "testview_nonfixed (+" << sub << ", " << view.size() << ")\n";
  //   assert(view.size() == 10 - sub);
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
  std::array<int, 10> arr = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  assert(testview_fixed(arr, {arr.data()}));
  assert(testview_subarray(arr, 4, {arr.data() + 4, 6}));
  assert(testview_subarray(arr, 5, {arr.data() + 5, 3}));

  return 0;
}