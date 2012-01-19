remake_find_package(freetype2 CONFIG)
remake_find_package(ftgl CONFIG)

remake_include(${FREETYPE2_INCLUDE_DIRS})

remake_qt4_ui(visualization)
remake_qt4_moc(visualization)

remake_add_library(visualization LINK ${QT_QTGUI_LIBRARY} ${QT_QTOPENGL_LIBRARY}
  ${QWT_QT4_LIBRARY} ${FTGL_LIBRARIES} ${DAI_LIBRARY} base evaluation)
remake_add_headers(INSTALL visualization)
