set(ycolorpicker_SRCS
    color.cpp
    hueslider.cpp
    main.cpp
    mainwindow.cpp
    rgbsliders.cpp
    rgbspinners.cpp
    satval.cpp
)

add_executable(ycolorpicker ${ycolorpicker_SRCS})

target_link_libraries(ycolorpicker PRIVATE Qt5::Widgets)
