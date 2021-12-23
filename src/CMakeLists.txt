set(ycolorpicker_SRCS
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
