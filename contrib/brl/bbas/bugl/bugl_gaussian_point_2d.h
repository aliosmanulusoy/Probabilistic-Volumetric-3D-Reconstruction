#ifndef gaussian_point_2d_h_
#define gaussian_point_2d_h_
//:
// \file
// \author Kongbin Kang
// A class for 2d point with Gaussian distribution

#include "bugl_uncertainty_point_2d.h"
#include <vnl/vnl_matrix_fixed.h>
template<class T>
class bugl_gaussian_point_2d:public bugl_uncertainty_point_2d<T>
{
 private:
  vnl_matrix_fixed<T, 2, 2> sigma_;
  vnl_matrix_fixed<T, 2, 2> sigma_inv_;
 public:
  bugl_gaussian_point_2d(T x, T y, vnl_matrix_fixed<T, 2, 2> & s);
  ~bugl_gaussian_point_2d() {}
};

#define BUGL_GAUSSIAN_POINT_2D_INSTANTIATE(T) extern "please include bugl/gaussian_point_2d.txx first"
#endif
