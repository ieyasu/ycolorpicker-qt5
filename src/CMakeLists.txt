set(ycolorpicker_SRCS
    color.cpp
    main.cpp
    mainwindow.cpp
    satval.cpp
)

add_executable(ycolorpicker ${ycolorpicker_SRCS})

target_link_libraries(ycolorpicker PRIVATE Qt5::Widgets)
