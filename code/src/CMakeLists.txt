remake_qt4_include()

remake_project_header(config.h.remake)

remake_add_directories(lib)
remake_add_directories(bin COMPONENT test)
