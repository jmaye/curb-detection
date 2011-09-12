remake_find_library(ann ANN/ANN.h PACKAGE ANN)

remake_include(${ANN_HEADERS})

remake_add_library(statistics LINK base ${ANN_LIBRARY} ${GSL_LIBRARY}
  ${GSLCBLAS_LIBRARY})
remake_add_headers(INSTALL statistics)
