# qt
find_package(Qt6 CONFIG COMPONENTS Core Gui Widgets Quick REQUIRED)

qt_standard_project_setup()

set(CURRENT_PROJECT_NAME BiliQt)


# BiliQt
file(GLOB SRC_FILES "src/**/*.cpp")
file(GLOB HEADER_FILES "include/*.h" "include/**/*.h")

list(APPEND SRC_FILES src/qml.qrc)
file(GLOB QML_FILES "src/**/*.qml")
qt_add_resources(QML_RES src/qml.qrc)
qt_add_executable(${CURRENT_PROJECT_NAME} ${QML_RES} ${SRC_FILES} ${HEADER_FILES})

target_link_libraries(${CURRENT_PROJECT_NAME} PRIVATE Qt6::Core Qt6::Gui Qt6::Widgets Qt6::Quick fluentuiplugin)
target_include_directories(${CURRENT_PROJECT_NAME} PRIVATE include)


# 自动把 QML 写入 qml.qrc
set(QML_QRC_PATH src/qml.qrc)
file(WRITE ${QML_QRC_PATH} "<RCC>\n  <qresource prefix=\"/\">\n")
foreach(qml ${QML_FILES})
    file(RELATIVE_PATH REL ${CMAKE_CURRENT_SOURCE_DIR}/src/ ${qml})
    file(APPEND ${QML_QRC_PATH} "    <file>${REL}</file>\n")
endforeach()
file(APPEND ${QML_QRC_PATH} "  </qresource>\n</RCC>\n")


# FluentUI
set(FLUENTUI_BUILD_EXAMPLES OFF)
set(FLUENTUI_BUILD_STATIC_LIB OFF)
add_subdirectory(thirdparty/FluentUI)
