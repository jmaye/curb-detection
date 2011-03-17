remake_find_library(ann ANN/ANN.h PACKAGE libann0)
remake_add_library(data-structures LINK ${ANN_LIBRARY} statistics)
remake_add_headers()
