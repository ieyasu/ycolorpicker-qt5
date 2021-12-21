set(ycolorpicker_SRCS
    color.cpp
    color_formats.cpp
    component_spinners.cpp
    currcolordisplay.cpp
    hueslider.cpp
    main.cpp
    mainwindow.cpp
    palette.cpp
    rgbsliders.cpp
    satval.cpp
)

add_executable(ycolorpicker ${ycolorpicker_SRCS})

target_link_libraries(ycolorpicker PRIVATE Qt5::Widgets)
