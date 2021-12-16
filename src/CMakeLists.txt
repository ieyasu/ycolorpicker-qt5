set(ycolorpicker_SRCS
    main.cpp
)

add_executable(ycolorpicker ${ycolorpicker_SRCS})

target_link_libraries(ycolorpicker PRIVATE Qt5::Widgets)
