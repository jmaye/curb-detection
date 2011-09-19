remake_find_library(gsl gsl/gsl_math.h PACKAGE libgsl0-dev)
remake_find_library(gslcblas gsl/gsl_blas.h PACKAGE libgsl0-dev)

remake_include(${GSL_HEADERS} ${GSLCBLAS_HEADERS})

remake_add_library(tpl-impl LINK ${GSL_LIBRARY} ${GSLCBLAS_LIBRARY})
