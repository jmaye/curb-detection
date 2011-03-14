remake_europa_find_moos()
remake_find_library(europa_alu_moosMessages moosMessages/genericMessage.h
  PACKAGE moosMessages)
remake_find_library(firecam libfirecam/firecam.h PACKAGE libfirecam)
remake_include(${EUROPA_ALU_MOOSMESSAGES_HEADERS} ${FIRECAM_HEADERS})
remake_add_directories(lib bin)
