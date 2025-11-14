# FluentUI
add_subdirectory(thirdparty/FluentUI)
set(FLUENTUI_BUILD_EXAMPLES OFF)
set(FLUENTUI_BUILD_STATIC_LIB OFF)

# qt
find_package(Qt6 REQUIRED COMPONENTS Core)
qt_standard_project_setup()
file(GLOB SRC_FILES "src/*.cpp" "src/**/*.cpp")
file(GLOB HEADER_FILES "include/*.h" "include/**/*.h")
qt_add_executable(BiliQt ${SRC_FILES} ${HEADER_FILES})
target_link_libraries(BiliQt PRIVATE Qt6::Core)
target_include_directories(BiliQt PRIVATE "include")
