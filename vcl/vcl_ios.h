#ifndef vcl_ios_h_
#define vcl_ios_h_
#ifdef __GNUC__
#pragma interface
#endif
/*
  fsm@robots.ox.ac.uk
*/

#include "vcl_compiler.h"

// FIXME
#include "vcl_iostream.h"

#if defined(VCL_SGI_CC_720)
# include "sgi/vcl_ios.h"

#else // -------------------- ISO
# include "iso/vcl_ios.h"
#endif



#endif // vcl_ios_h_
