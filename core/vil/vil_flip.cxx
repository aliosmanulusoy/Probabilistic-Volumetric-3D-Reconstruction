// This is mul/vil2/vil2_flip.cxx
#ifdef VCL_NEEDS_PRAGMA_INTERFACE
#pragma implementation
#endif
//:
// \file
// \author Ian Scott.
//
//-----------------------------------------------------------------------------

#include "vil2_flip.h"
#include <vil2/vil2_property.h>

vil2_image_resource_sptr vil2_flip_lr(const vil2_image_resource_sptr &src)
{
  return new vil2_flip_lr_image_resource(src);
}

vil2_flip_lr_image_resource::vil2_flip_lr_image_resource(vil2_image_resource_sptr const& src):
  src_(src)
{
}

vil2_image_view_base_sptr vil2_flip_lr_image_resource::get_copy_view(unsigned i0, unsigned ni, 
                                                                     unsigned j0, unsigned nj) const
{
  if (i0 + ni > src_->ni()) return 0;
  vil2_image_view_base_sptr vs = src_->get_copy_view(src_->ni()- i0-ni, ni, j0, nj);
  if (!vs) return 0;

  switch (vs->pixel_format())
  {
#define macro( F, T ) \
  case F : \
    return new vil2_image_view<T > (vil2_flip_lr(static_cast<const vil2_image_view<T >&>(*vs)));

  macro(VIL2_PIXEL_FORMAT_BYTE, vxl_byte)
  macro(VIL2_PIXEL_FORMAT_SBYTE, vxl_sbyte)
  macro(VIL2_PIXEL_FORMAT_UINT_32, vxl_uint_32)
  macro(VIL2_PIXEL_FORMAT_UINT_16, vxl_uint_16)
  macro(VIL2_PIXEL_FORMAT_INT_32, vxl_int_32)
  macro(VIL2_PIXEL_FORMAT_INT_16, vxl_int_16)
  macro(VIL2_PIXEL_FORMAT_FLOAT, float)
  macro(VIL2_PIXEL_FORMAT_DOUBLE, double)
#undef macro
  default:
    return 0;
  }
}

vil2_image_view_base_sptr vil2_flip_lr_image_resource::get_view(unsigned i0, unsigned ni,
                                                                unsigned j0, unsigned nj) const
{
  if (i0 + ni > src_->ni()) return 0;
  vil2_image_view_base_sptr vs = src_->get_view(src_->ni()- i0-ni, ni, j0, nj);
  if (!vs) return 0;

  switch (vs->pixel_format())
  {
#define macro( F, T ) \
  case F : \
    return new vil2_image_view<T > (vil2_flip_lr(static_cast<const vil2_image_view<T >&>(*vs)));

  macro(VIL2_PIXEL_FORMAT_BYTE, vxl_byte)
  macro(VIL2_PIXEL_FORMAT_SBYTE, vxl_sbyte)
  macro(VIL2_PIXEL_FORMAT_UINT_32, vxl_uint_32)
  macro(VIL2_PIXEL_FORMAT_UINT_16, vxl_uint_16)
  macro(VIL2_PIXEL_FORMAT_INT_32, vxl_int_32)
  macro(VIL2_PIXEL_FORMAT_INT_16, vxl_int_16)
  macro(VIL2_PIXEL_FORMAT_FLOAT, float)
  macro(VIL2_PIXEL_FORMAT_DOUBLE, double)
#undef macro
  default:
    return 0;
  }
}

//: Put the data in this view back into the image source.
bool vil2_flip_lr_image_resource::put_view(const vil2_image_view_base& im, unsigned i0,
                                           unsigned j0)
{
  if (i0 + im.ni() > src_->ni()) return false;
  switch (im.pixel_format())
  {
#define macro( F, T ) \
  case F : \
    return src_->put_view(vil2_flip_lr(static_cast<const vil2_image_view<T >&>(im)), src_->ni()-i0-im.ni(), j0); 

  macro(VIL2_PIXEL_FORMAT_BYTE, vxl_byte)
  macro(VIL2_PIXEL_FORMAT_SBYTE, vxl_sbyte)
  macro(VIL2_PIXEL_FORMAT_UINT_32, vxl_uint_32)
  macro(VIL2_PIXEL_FORMAT_UINT_16, vxl_uint_16)
  macro(VIL2_PIXEL_FORMAT_INT_32, vxl_int_32)
  macro(VIL2_PIXEL_FORMAT_INT_16, vxl_int_16)
  macro(VIL2_PIXEL_FORMAT_FLOAT, float)
  macro(VIL2_PIXEL_FORMAT_DOUBLE, double)
#undef macro
  default:
    return false;
  }
}

vil2_image_resource_sptr vil2_flip_ud(const vil2_image_resource_sptr &src)
{
  return new vil2_flip_ud_image_resource(src);
}

vil2_flip_ud_image_resource::vil2_flip_ud_image_resource(vil2_image_resource_sptr const& src):
  src_(src)
{
}


vil2_image_view_base_sptr vil2_flip_ud_image_resource::get_copy_view(unsigned i0, unsigned ni, 
                                                                     unsigned j0, unsigned nj) const
{
  if (j0 + nj > src_->nj()) return 0;
  vil2_image_view_base_sptr vs = src_->get_copy_view(i0, ni, src_->nj()- j0-nj, nj);
  if (!vs) return 0;

  switch (vs->pixel_format())
  {
#define macro( F, T ) \
  case F : \
    return new vil2_image_view<T > (vil2_flip_ud(static_cast<const vil2_image_view<T >&>(*vs)));

  macro(VIL2_PIXEL_FORMAT_BYTE, vxl_byte)
  macro(VIL2_PIXEL_FORMAT_SBYTE, vxl_sbyte)
  macro(VIL2_PIXEL_FORMAT_UINT_32, vxl_uint_32)
  macro(VIL2_PIXEL_FORMAT_UINT_16, vxl_uint_16)
  macro(VIL2_PIXEL_FORMAT_INT_32, vxl_int_32)
  macro(VIL2_PIXEL_FORMAT_INT_16, vxl_int_16)
  macro(VIL2_PIXEL_FORMAT_FLOAT, float)
  macro(VIL2_PIXEL_FORMAT_DOUBLE, double)
#undef macro
  default:
    return 0;
  }
}

vil2_image_view_base_sptr vil2_flip_ud_image_resource::get_view(unsigned i0, unsigned ni,
                                                                unsigned j0, unsigned nj) const
{
  if (i0 + ni > src_->ni()) return 0;
  vil2_image_view_base_sptr vs = src_->get_view(i0, ni, src_->nj()-j0-nj, nj);
  if (!vs) return 0;

  switch (vs->pixel_format())
  {
#define macro( F, T ) \
  case F : \
    return new vil2_image_view<T > (vil2_flip_ud(static_cast<const vil2_image_view<T >&>(*vs)));

      macro(VIL2_PIXEL_FORMAT_BYTE, vxl_byte)
      macro(VIL2_PIXEL_FORMAT_SBYTE, vxl_sbyte)
      macro(VIL2_PIXEL_FORMAT_UINT_32, vxl_uint_32)
      macro(VIL2_PIXEL_FORMAT_UINT_16, vxl_uint_16)
      macro(VIL2_PIXEL_FORMAT_INT_32, vxl_int_32)
      macro(VIL2_PIXEL_FORMAT_INT_16, vxl_int_16)
      macro(VIL2_PIXEL_FORMAT_FLOAT, float)
      macro(VIL2_PIXEL_FORMAT_DOUBLE, double)
#undef macro
  default:
    return 0;
  }
}

//: Put the data in this view back into the image source.
bool vil2_flip_ud_image_resource::put_view(const vil2_image_view_base& im, unsigned i0,
                                           unsigned j0)
{
  if (i0 + im.ni() > src_->ni()) return false;
  switch (im.pixel_format())
  {
#define macro( F, T ) \
  case F : \
    return src_->put_view(vil2_flip_ud(static_cast<const vil2_image_view<T >&>(im)), i0, src_->nj()-j0-im.nj()); \

      macro(VIL2_PIXEL_FORMAT_BYTE, vxl_byte)
      macro(VIL2_PIXEL_FORMAT_SBYTE, vxl_sbyte)
      macro(VIL2_PIXEL_FORMAT_UINT_32, vxl_uint_32)
      macro(VIL2_PIXEL_FORMAT_UINT_16, vxl_uint_16)
      macro(VIL2_PIXEL_FORMAT_INT_32, vxl_int_32)
      macro(VIL2_PIXEL_FORMAT_INT_16, vxl_int_16)
      macro(VIL2_PIXEL_FORMAT_FLOAT, float)
      macro(VIL2_PIXEL_FORMAT_DOUBLE, double)
#undef macro
  default:
    return false;
  }
}
