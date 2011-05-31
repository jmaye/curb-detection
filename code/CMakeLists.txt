cmake_minimum_required(VERSION 2.6)

include(ReMake)

remake_project(
  curb-detection
  VERSION 0.1
  RELEASE alpha
  SUMMARY "Curb detection module"
  AUTHOR "Jerome Maye"
  CONTACT "jerome.maye@mavt.ethz.ch"
  HOME "http://aslforge.ethz.ch/projects/curb-detection"
  LICENSE "GNU Lesser General Public License (LGPL)"
  INSTALL /usr
)

remake_pack_deb(libdai libftgl2 libfreetype6 libqt4-opengl libqt4-gui)

remake_pack_deb(
  COMPONENT dev
  DESCRIPTION "Development headers"
  curb-detection
  libdai-dev
)

remake_pack_deb(
  COMPONENT test
  DESCRIPTION "Test programs"
  curb-detection
)
