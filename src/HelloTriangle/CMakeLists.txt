
#learn opengl

find_package(Qt5 COMPONENTS Core Gui Widgets OpenGL)

set(SRCS
    main.cpp
    MainWindow.cpp
    MainWindow.h
    View3dGL.cpp
    View3dGL.h
)

set(LIBS
    Qt5::Core
    Qt5::Gui
    Qt5::Widgets
    Qt5::OpenGL
    GLEW::glew_s
)

add_executable(HelloTriangle ${SRCS})
target_link_libraries(HelloTriangle ${LIBS})

set_target_properties(HelloTriangle PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/$<CONFIG>)

set(QT_DLLS Qt5Core Qt5Gui Qt5Widgets Qt5OpenGL)

foreach (_dll ${QT_DLLS})
    add_custom_command(TARGET HelloTriangle POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different
    ${QT5_BIN_DIR}/${_dll}$<$<CONFIG:Debug>:d>.dll ${CMAKE_BINARY_DIR}/bin/$<CONFIG>)
endforeach ()

