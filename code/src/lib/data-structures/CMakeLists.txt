remake_find_library(ann ANN/ANN.h PACKAGE libann0)
remake_add_library(data-structures LINK ${ANN_LIBRARY}
  ${GRAPHTOOL_GRAPHMOD_LIBRARY} statistics sensor exceptions)
remake_add_headers()
