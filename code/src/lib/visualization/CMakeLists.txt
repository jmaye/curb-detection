remake_find_package(OpenGL)
remake_add_library(visualization LINK data-structures ${OPENGL_LIBRARIES})
