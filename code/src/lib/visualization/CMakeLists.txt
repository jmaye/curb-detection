remake_find_package(gl CONFIG)
remake_find_package(glu CONFIG)
remake_find_package(GLUT)
remake_add_library(visualization LINK ${OPENGL_LIBRARIES} ${GLU_LIBRARIES}
  ${GLUT_LIBRARIES})
remake_add_headers()
