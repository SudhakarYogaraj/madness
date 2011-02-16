/*
  This file is part of MADNESS.
  
  Copyright (C) 2007,2010 Oak Ridge National Laboratory
  
  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.
  
  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
  GNU General Public License for more details.
  
  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
  
  For more information please contact:

  Robert J. Harrison
  Oak Ridge National Laboratory
  One Bethel Valley Road
  P.O. Box 2008, MS-6367

  email: harrisonrj@ornl.gov 
  tel:   865-241-3937
  fax:   865-572-0680

  
  $Id$
*/

  
#ifndef MADNESS_LINALG_CBLAS_H__INCLUDED
#define MADNESS_LINALG_CBLAS_H__INCLUDED

#include <fortran_ctypes.h>

#ifdef FORTRAN_LINKAGE_LC
#  define sgemm_ sgemm
#  define dgemm_ dgemm
#  define cgemm_ cgemm
#  define zgemm_ zgemm
#else
  // only lowercase with zero and one underscores are handled -- if detected another convention complain loudly
#  ifndef FORTRAN_LINKAGE_LCU
#    error "cblas.h does not support the current Fortran symbol convention -- please, edit and check in the changes."
#  endif
#endif


namespace madness {

    /// BLAS gemm exists only for float, double, float_complex, double_complex.

    template <typename T> void gemm(bool transa, bool transb,
                                    integer m, integer n, integer k,
                                    T alpha, const T* a, integer lda, const T*b, integer ldb,
                                    T beta, T* c, integer ldc);
}

#endif // MADNESS_LINALG_CBLAS_H__INCLUDED

