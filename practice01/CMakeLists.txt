cmake_minimum_required(VERSION 3.22)
project(BiliQt LANGUAGES CXX)

# ================================
# Qt
# ================================
find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets Quick Concurrent LinguistTools)
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

target_link_libraries(${PROJECT_NAME} PRIVATE
        Qt6::Core
        Qt6::Gui
        Qt6::Widgets
        Qt6::Quick
        Qt6::Concurrent
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
add_dependencies(${PROJECT_NAME} ${PROJECT_NAME}_lrelease)

include(FetchContent)

# ================================
# Third Party
# ================================
# FluentUI
set(FLUENTUI_BUILD_EXAMPLES OFF)
set(FLUENTUI_BUILD_STATIC_LIB OFF)
FetchContent_Declare(
        FluentUI
        GIT_REPOSITORY https://github.com/zhuzichu520/FluentUI.git
        GIT_TAG        0cd0b83a10ae67aab9fbe06dcd205c08e7be4383
)
FetchContent_MakeAvailable(FluentUI)
target_link_libraries(${PROJECT_NAME} PRIVATE
        fluentuiplugin
)


# ================================
# 其他依赖
# ================================
find_package(oatpp CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE
        oatpp::oatpp
)

find_package(OpenSSL CONFIG REQUIRED)
find_package(oatpp-openssl CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE
        OpenSSL::SSL
        oatpp::oatpp-openssl
)

find_package(Boost REQUIRED COMPONENTS url)
target_link_libraries(${PROJECT_NAME} PRIVATE Boost::url)

find_package(nlohmann_json CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE nlohmann_json::nlohmann_json)

find_package(CURL CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE CURL::libcurl)
