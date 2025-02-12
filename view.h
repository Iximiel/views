#ifndef VIEW_H
#define VIEW_H
#include <cstddef>
#include <limits>
#include <stdexcept>
#include <type_traits>

namespace view {
constexpr auto dynamic_extent = std::numeric_limits<std::size_t>::max();
template <typename T, std::size_t N = dynamic_extent>
class View { // this is duplicated in PBC.h, this need to be uniformed!!!
  T *ptr_;
  const std::size_t size_;

public:
  template <size_t NN = N, typename = std::enable_if_t<NN != dynamic_extent>>
  View(T *p) : ptr_(p), size_(N) {}
  template <size_t NN = N, typename = std::enable_if_t<NN == dynamic_extent>>
  View(T *p, size_t size) : ptr_(p), size_(size) {}
  constexpr size_t size() const { return size_; }
  T &operator[](size_t i) { return ptr_[i]; }
  const T &operator[](size_t i) const { return ptr_[i]; }
  T &at(size_t i) {
    if (i >= size_) {
      throw std::out_of_range("out of range");
    }
    return ptr_[i];
  }
  const T &at(size_t i) const {
    if (i >= size_) {
      throw std::out_of_range("out of range");
    }
    return ptr_[i];
  }
};
} // namespace view

#endif // VIEW_H