remake_find_package(OpenGL CONFIG gl)
remake_find_package(GLU CONFIG glu)
remake_find_package(GLUT)
remake_add_library(visualization LINK data-structures ${OPENGL_LIBRARIES}
  ${GLU_LIBRARIES} ${GLUT_LIBRARIES})
remake_add_headers()
