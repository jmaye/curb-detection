remake_qt4_include()
remake_find_library(qwt-qt4 qwt-qt4/qwt.h PACKAGE libqwt5-qt4-dev)
remake_find_file(eigen2/Eigen/Core PACKAGE libeigen2-dev)
remake_find_library(dai dai/alldai.h PACKAGE libdai-dev)
remake_find_library(gsl gsl/gsl_math.h PACKAGE libgsl0-dev)
remake_find_library(gslcblas gsl/gsl_blas.h PACKAGE libgsl0-dev)

remake_project_header(config.h.remake)

remake_include(${LIBEIGEN2_DEV_FILE}/eigen2 ${QWT_QT4_HEADERS} ${DAI_HEADERS}
  ${GSL_HEADERS} ${GSLCBLAS_HEADERS})

remake_add_directories(lib bin)
