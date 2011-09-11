remake_qt4_ui(seg-visual)
remake_qt4_moc(seg-visual)

remake_add_library(seg-visual LINK ${QT_QTGUI_LIBRARY}
  ${QT_QTOPENGL_LIBRARY})
remake_add_headers(INSTALL seg-visual)
