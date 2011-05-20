remake_find_file(eigen2/Eigen/Core PACKAGE libeigen2-dev)
remake_include(${LIBEIGEN2_DEV_FILE}/eigen2)
remake_add_library(statistics LINK ${DAI_LIBRARY} exceptions)
