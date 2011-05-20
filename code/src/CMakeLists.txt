remake_find_library(dai dai/alldai.h PACKAGE libdai-dev)
remake_include(${DAI_HEADERS})
remake_project_header(config.h.remake)
remake_add_directories(lib bin)
