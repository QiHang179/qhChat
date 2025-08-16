cmake_minimum_required(VERSION 3.16)

project(chatProject VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Network)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Network)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(chatProject
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        logindialog.h logindialog.cpp logindialog.ui
        res.qrc
        registerdialog.h registerdialog.cpp registerdialog.ui
        global.h
        global.cpp
        singleton.h
        httpmgr.h httpmgr.cpp
        config.ini
    )
else()
    if(ANDROID)
        add_library(chatProject SHARED
            ${PROJECT_SOURCES}
            logindialog.h logindialog.cpp logindialog.ui
            res.qrc
            registerdialog.h registerdialog.cpp registerdialog.ui
            global.h
            global.cpp
            singleton.h
            httpmgr.h httpmgr.cpp
        )
    else()
        add_executable(chatProject
            ${PROJECT_SOURCES}
            logindialog.h logindialog.cpp logindialog.ui
            res.qrc
            registerdialog.h registerdialog.cpp registerdialog.ui
            global.h
            global.cpp
            singleton.h
            httpmgr.h httpmgr.cpp
        )
    endif()
endif()

target_link_libraries(chatProject PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Network)

if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.chatProject)
endif()
set_target_properties(chatProject PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

# 拷贝配置文件的操作
if(WIN32)
    # 仅在Release配置下执行拷贝
    set(SOURCE_FILE "${CMAKE_CURRENT_SOURCE_DIR}/config.ini")
    set(DESTINATION_DIR "$<TARGET_FILE_DIR:chatProject>")

    # 添加自定义命令，在目标构建后执行拷贝
    add_custom_command(TARGET chatProject POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${SOURCE_FILE}"
        "${DESTINATION_DIR}"
        COMMENT "Copying config.ini to build directory"
    )
endif()

include(GNUInstallDirs)
install(TARGETS chatProject
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# 安装时也拷贝配置文件
install(FILES "config.ini" DESTINATION ${CMAKE_INSTALL_BINDIR})

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(chatProject)
endif()
