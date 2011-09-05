remake_qt4_include()
remake_find_library(qwt-qt4 qwt-qt4/qwt.h PACKAGE libqwt5-qt4-dev)
remake_find_file(eigen2/Eigen/Core PACKAGE libeigen2-dev)

remake_project_header(config.h.remake)

remake_include(${LIBEIGEN2_DEV_FILE}/eigen2 ${QWT_QT4_HEADERS})

remake_add_directories(lib bin)
