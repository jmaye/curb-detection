cmake_minimum_required(VERSION 2.6)

include(ReMake)

remake_project(
  moos-stingray
  VERSION 0.1
  RELEASE alpha
  SUMMARY "MOOS Wrapper for Stingray camera"
  AUTHOR "Jerome Maye"
  CONTACT "jerome.maye@mavt.ethz.ch"
  HOME "http://aslforge.ethz.ch/projects/europa"
  LICENSE "GNU Lesser General Public License (LGPL)"
  INSTALL /usr
  MODULES ../modules
)

remake_pack_deb()
