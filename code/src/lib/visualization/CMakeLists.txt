remake_find_package(gl CONFIG)
remake_find_package(glu CONFIG)
remake_find_package(GLUT)
remake_add_library(visualization LINK data-structures ${OPENGL_LIBRARIES}
  ${GLU_LIBRARIES} ${GLUT_LIBRARIES})
