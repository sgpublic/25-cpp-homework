# qt
find_package(Qt6 CONFIG COMPONENTS Core Gui Widgets Quick REQUIRED)

qt_standard_project_setup()

set(CURRENT_PROJECT_NAME BiliQt)


# BiliQt
file(GLOB_RECURSE SRC_FILES "src/*")
file(GLOB_RECURSE HEADER_FILES "include/*")
file(GLOB_RECURSE QML_FILES "res/qml/*")
list(APPEND SRC_FILES ${QRC_PATH})
qt_add_resources(QML_RES ${QRC_PATH})
qt_add_executable(${CURRENT_PROJECT_NAME} ${QML_RES} res/biliqt.qrc ${SRC_FILES} ${HEADER_FILES})
target_link_libraries(${CURRENT_PROJECT_NAME} PRIVATE Qt6::Core Qt6::Gui Qt6::Widgets Qt6::Quick fluentuiplugin)
target_include_directories(${CURRENT_PROJECT_NAME} PRIVATE include)


# 添加国际化脚本
find_program(QT_LUPDATE NAMES lupdate lupdate-qt6 REQUIRED)
find_program(QT_LRELEASE NAMES lrelease lrelease-qt6 REQUIRED)
set(LANGUAGES en_US zh_CN)
file(GLOB_RECURSE LUPDATE_SOURCES
        "${CMAKE_CURRENT_LIST_DIR}/res/*.qml"
)
set(GENERATED_QM_FILES "")
set(TRANSLATION_FILE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/res/translations")
foreach(LANG ${LANGUAGES})
    set(TS_FILE "${TRANSLATION_FILE_DIR}/${CURRENT_PROJECT_NAME}_${LANG}.ts")
    set(QM_FILE "${TRANSLATION_FILE_DIR}/${CURRENT_PROJECT_NAME}_${LANG}.qm")
    add_custom_command(
            OUTPUT ${QM_FILE}
            COMMAND ${QT_LUPDATE} ${CMAKE_CURRENT_LIST_DIR} -ts ${TS_FILE}
            COMMAND ${QT_LRELEASE} ${TS_FILE}
            COMMAND ${CMAKE_COMMAND} -E copy_if_different ${QM_FILE} ${APPLICATION_DIR_PATH}/i18n/${QM_FILE}
            DEPENDS ${LUPDATE_SOURCES}
            WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
            COMMENT "Updating translations for ${LANG}"
    )
    list(APPEND GENERATED_QM_FILES ${QM_FILE})
endforeach()
add_custom_target(${CURRENT_PROJECT_NAME}_Translations ALL
        DEPENDS ${GENERATED_QM_FILES}
)
add_dependencies(${CURRENT_PROJECT_NAME} ${CURRENT_PROJECT_NAME}_Translations)


# 自动把 QML 写入 biliqt.qrc
file(WRITE ${QRC_PATH} "<RCC>\n  <qresource prefix=\"/biliqt\">\n")
file(GLOB_RECURSE RESOURCE_FILE "res/qml/*" "res/drawble/*" "res/translations/*.qm")
list(APPEND RESOURCE_FILE ${QML_FILES})
foreach(res ${RESOURCE_FILE})
    if (IS_DIRECTORY ${res})
        continue()
    endif()
    file(RELATIVE_PATH REL ${CMAKE_CURRENT_SOURCE_DIR}/res/ ${res})
    file(APPEND ${QRC_PATH} "    <file>${REL}</file>\n")
endforeach()
file(APPEND ${QRC_PATH} "  </qresource>\n</RCC>\n")


# FluentUI
set(FLUENTUI_BUILD_EXAMPLES OFF)
set(FLUENTUI_BUILD_STATIC_LIB OFF)
add_subdirectory(thirdparty/FluentUI)
