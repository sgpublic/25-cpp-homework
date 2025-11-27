# qt
find_package(Qt6 CONFIG COMPONENTS Core Gui Widgets Quick REQUIRED)

qt_standard_project_setup()


# BiliQt
file(GLOB SRC_FILES "src/*.cpp" "src/**/*.cpp")
file(GLOB HEADER_FILES "include/*.h" "include/**/*.h")

qt_add_executable(BiliQt ${SRC_FILES} ${HEADER_FILES})
target_link_libraries(BiliQt PRIVATE Qt6::Core Qt6::Gui Qt6::Widgets Qt6::Quick)
target_include_directories(BiliQt PRIVATE include)


# FluentUI
set(FLUENTUI_BUILD_EXAMPLES OFF)
set(FLUENTUI_BUILD_STATIC_LIB OFF)
add_subdirectory(thirdparty/FluentUI)
