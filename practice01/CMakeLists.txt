cmake_minimum_required(VERSION 3.22)
project(BiliQt LANGUAGES CXX)

# ================================
# Qt
# ================================
find_package(Qt6 CONFIG REQUIRED Core Gui Widgets Quick LinguistTools)
qt_standard_project_setup(
        I18N_TRANSLATED_LANGUAGES zh_CN en
)

# ================================
# 源码 / 资源目录
# ================================
set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(INC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include")
set(RES_DIR "${CMAKE_CURRENT_SOURCE_DIR}/res")
set(QML_DIR "${RES_DIR}/qml")
set(DRAWABLE_DIR "${RES_DIR}/drawable")
set(TRANS_DIR "${RES_DIR}/translations")

file(GLOB_RECURSE SRC_FILES "${SRC_DIR}/*")
file(GLOB_RECURSE HEADER_FILES "${INC_DIR}/*")
file(GLOB_RECURSE QML_FILES "${QML_DIR}/*")

# ================================
# 可执行文件
# ================================
qt_add_executable(${PROJECT_NAME}
        ${SRC_FILES}
        ${HEADER_FILES}
)

target_link_libraries(${PROJECT_NAME}
        PRIVATE
        Qt6::Core
        Qt6::Gui
        Qt6::Widgets
        Qt6::Quick
        fluentuiplugin
)

target_include_directories(${PROJECT_NAME}
        PRIVATE ${INC_DIR}
)


# ================================
# 自动添加资源文件到 qrc
# ================================
file(GLOB_RECURSE RESOURCE_FILES
        "${QML_DIR}/*"
        "${DRAWABLE_DIR}/*"
)

qt_add_resources(${PROJECT_NAME} ${PROJECT_NAME}
        PREFIX "/biliqt"
        BASE ${RES_DIR}
        FILES ${RESOURCE_FILES}
)


# ================================
# 自动生成翻译文件并加入资源
# ================================
# qt6_add_translation 会自动：
# - 创建 ts 文件（不存在时）
# - 执行 lupdate 更新 ts
# - 执行 lrelease 生成 qm
qt_add_translations(${PROJECT_NAME}
        SOURCE_TARGETS ${PROJECT_NAME}
        TS_OUTPUT_DIRECTORY ${TRANS_DIR}
        INCLUDE_DIRECTORIES ${SRC_DIR} ${INC_DIR} ${QML_DIR}
        RESOURCE_PREFIX "/biliqt/i18n"
)
add_dependencies(${PROJECT_NAME} ${PROJECT_NAME}_lupdate)
add_dependencies(${PROJECT_NAME} update_translations)
add_dependencies(${PROJECT_NAME} ${PROJECT_NAME}_lrelease)


# ================================
# Fluent UI
# ================================
set(FLUENTUI_BUILD_EXAMPLES OFF)
set(FLUENTUI_BUILD_STATIC_LIB OFF)
add_subdirectory(thirdparty/FluentUI)
