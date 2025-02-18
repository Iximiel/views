#ifndef MDVIEW_H
#define MDVIEW_H
#include "view.h"
namespace view {
template <typename T, std::size_t N = dynamic_extent,
          std::size_t M = dynamic_extent>
class mdView {
  T *ptr_;
  const std::size_t sizeN_;
  const std::size_t sizeM_;

public:
  // Specialized ctor for when only the dimensions are known at compile time
  template <
      size_t NN = N, size_t MM = M,
      typename = std::enable_if_t<NN != dynamic_extent && MM != dynamic_extent>>
  mdView(T *p) : ptr_(p), sizeN_(N), sizeM_(M) {}
  // Specialized ctor for when only the second dimension is known at compile
  // time declared as mdView<T, dynamic_extent, M>
  template <size_t MM = M, typename = std::enable_if_t<MM != dynamic_extent>>
  mdView(T *p, size_t NN) : ptr_(p), sizeN_(NN), sizeM_(M) {}
  mdView(T *p, size_t NN, size_t MM) : ptr_(p), sizeN_(NN), sizeM_(MM) {}

  //   constexpr size_t size() const { return size_; }
  View<T, M> operator[](size_t i) {
    return View<T, M>(ptr_ + i * sizeM_, sizeM_);
  }
  View<T, M> operator[](size_t i) const {
    return View<T, M>(ptr_ + i * sizeM_, sizeM_);
  }
  constexpr size_t size() const { return sizeN_; }
  //   T &at(size_t i) {
  //     if (i >= size_) {
  //       throw std::out_of_range("out of range");
  //     }
  //     return ptr_[i];
  //   }
  //   const T &at(size_t i) const {
  //     if (i >= size_) {
  //       throw std::out_of_range("out of range");
  //     }
  //     return ptr_[i];
  //   }
};
} // namespace view
#endif // MDVIEW_H