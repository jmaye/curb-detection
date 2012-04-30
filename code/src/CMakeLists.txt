remake_qt4_include()
remake_find_library(qwt-qt4 qwt-qt4/qwt.h PACKAGE libqwt5-qt4-dev)
remake_find_library(qwtplot3d-qt4 qwtplot3d-qt4/qwt3d_plot.h PACKAGE
  libqwtplot3d-qt4-dev)
remake_find_file(eigen2/Eigen/Core PACKAGE libeigen2-dev)
remake_find_library(gsl gsl/gsl_math.h PACKAGE libgsl0-dev)
remake_find_library(gslcblas gsl/gsl_blas.h PACKAGE libgsl0-dev)
remake_find_library(dai dai/alldai.h PACKAGE libdai-dev)
remake_find_library(ann ANN/ANN.h PACKAGE ANN)
remake_find_package(freetype2 CONFIG)
remake_find_package(ftgl CONFIG)

remake_project_header(config.h.remake)

remake_include(${LIBEIGEN2_DEV_FILE}/eigen2 ${QWT_QT4_HEADERS}
  ${QWTPLOT3D_QT4_HEADERS} ${GSL_HEADERS} ${GSLCBLAS_HEADERS} ${DAI_HEADERS}
  ${ANN_HEADERS} ${FREETYPE2_INCLUDE_DIRS})

remake_add_directories(lib bin)
