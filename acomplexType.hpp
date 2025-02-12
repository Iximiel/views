#ifndef ACOMPLEXTYPE_HPP
#define ACOMPLEXTYPE_HPP
#include <array>
#include <cstddef>
#include <ostream>
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
#endif // ACOMPLEXTYPE_HPP
