remake_find_package(OpenGL)
remake_find_package(GLU)
remake_find_package(GLUT)
remake_add_library(visualization LINK data-structures ${OPENGL_LIBRARIES}
  ${GLU_LIBRARIES} ${GLUT_LIBRARIES})
