#include "view.h"
#include <array>
#include <cassert>
#include <iostream>
#include <vector>

using view::View;

template <typename T, size_t N> class AcomplexType {
  std::array<T, N> vals;

public:
  AcomplexType() : vals() {}
  template <typename... Args>
  AcomplexType(Args &&...args) : vals{{std::forward<Args>(args)...}} {}
  AcomplexType(const AcomplexType &other) : vals(other.vals) {}
  AcomplexType(AcomplexType &&other) : vals(std::move(other.vals)) {}
  AcomplexType &operator=(const AcomplexType &other) {
    vals = other.vals;
    return *this;
  }
  AcomplexType &operator=(AcomplexType &&other) {
    vals = std::move(other.vals);
    return *this;
  }
  T &operator[](size_t i) { return vals[i]; }
  const T &operator[](size_t i) const { return vals[i]; }
  constexpr T *data() { return vals.vals(); }
  bool operator==(const AcomplexType &other) {
    for (size_t i = 0; i < N; i++) {
      if (vals[i] != other.vals[i]) {
        return false;
      }
    }
    return true;
  }
  bool operator!=(const AcomplexType &other) { return !(*this == other); }
};
template <typename T, size_t N>
std::ostream &operator<<(std::ostream &os, const AcomplexType<T, N> &arr) {
  os << arr[0];
  for (size_t i = 1; i < N; i++) {
    os << " " << arr[i];
  }
  return os;
}

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
    std::vector<i3> arr = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};

    assert(testview_fixed<3>(arr, {arr.data()}));
  }

  return 0;
}
