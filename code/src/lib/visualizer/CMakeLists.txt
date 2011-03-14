remake_find_package(opencv CONFIG)
remake_include(${OPENCV_INCLUDE_DIRS})
remake_add_library(visualizer
  LINK ${MOOS_LIBRARIES} messages ${OPENCV_LIBRARIES})
remake_add_headers()
