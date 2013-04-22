cmake_minimum_required(VERSION 2.6)

include(ReMake)

remake_project(
  curb-detection
  VERSION 1.0
  RELEASE beta
  SUMMARY "A C++ based library for curb detection"
  AUTHOR "Jerome Maye"
  CONTACT "jerome.maye@mavt.ethz.ch"
  HOME "https://github.com/jmaye/curb-detection"
  LICENSE "GNU Lesser General Public License (LGPL)"
  INSTALL /usr
  EXTRA_CXX_FLAGS -std=c++0x
)

remake_pack_deb(libdai libftgl2 libfreetype6 libqt4-opengl libqt4-gui)

remake_pack_deb(
  COMPONENT dev
  DESCRIPTION "Development headers"
  curb-detection
  libdai-dev
)

remake_doc(
  html
  latex
)

remake_pack_deb(
  COMPONENT doc
  DESCRIPTION "Documentation"
  curb-detection
)
