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

remake_pack_deb(libann0 libeigen2-dev libglut3-dev)
