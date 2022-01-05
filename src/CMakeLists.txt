# CMakeLists.txt for YColorPicker
set(ycolorpicker_SRCS
    aboutdialog.cpp
    color.cpp
    color_formats.cpp
    component_spinners.cpp
    currcolordisplay.cpp
    hueslider.cpp
    main.cpp
    mainwindow.cpp
    palette.cpp
    push_button.cpp
    rgbsliders.cpp
    sample_button.cpp
    satval.cpp
    resources.qrc
)

add_executable(ycolorpicker ${ycolorpicker_SRCS})

target_link_libraries(ycolorpicker PRIVATE Qt5::Widgets)

install(TARGETS ycolorpicker RUNTIME)
install(FILES images/app-128.png RENAME ycolorpicker.png DESTINATION share/icons/hicolor/128x128/apps)
install(FILES images/app-48.png RENAME ycolorpicker.png DESTINATION share/icons/hicolor/48x48/apps)
install(FILES images/app-32.png RENAME ycolorpicker.png DESTINATION share/icons/hicolor/32x32/apps)
install(FILES images/app-16.png RENAME ycolorpicker.png DESTINATION share/icons/hicolor/16x16/apps)
install(FILES ycolorpicker.desktop DESTINATION share/applications)
