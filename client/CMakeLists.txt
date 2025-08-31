cmake_minimum_required(VERSION 3.16)

project(chatProject VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)        # ✅ 启用自动处理 .ui 文件
set(CMAKE_AUTOMOC ON)        # ✅ 启用自动处理 moc
set(CMAKE_AUTORCC ON)        # ✅ 启用自动处理 .qrc

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Network)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Network)

# 统一管理所有源文件
set(PROJECT_SOURCES
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    logindialog.h
    logindialog.cpp
    logindialog.ui
    res.qrc
    registerdialog.h
    registerdialog.cpp
    registerdialog.ui
    global.h
    global.cpp
    singleton.h
    httpmgr.h
    httpmgr.cpp
    timerbtn.h
    timerbtn.cpp
    clickedlabel.h
    clickedlabel.cpp
    resetdialog.h
    resetdialog.cpp
    resetdialog.ui
    config.ini
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(chatProject
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        tcpmgr.h tcpmgr.cpp
        usermgr.h usermgr.cpp
        chatdialog.h chatdialog.cpp chatdialog.ui
        clickedbtn.h clickedbtn.cpp
        customizeedit.h customizeedit.cpp
        chatuserlist.h chatuserlist.cpp
        chatuserwid.h chatuserwid.cpp chatuserwid.ui
        listitembase.h listitembase.cpp
        loadingdlg.h loadingdlg.cpp loadingdlg.ui
        chatpage.h chatpage.cpp chatpage.ui

    )
else()
    if(ANDROID)
        add_library(chatProject SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(chatProject
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(chatProject PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Network)

# 添加头文件搜索路径
target_include_directories(chatProject PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

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

if(WIN32)
    set(SOURCE_FILE "${CMAKE_CURRENT_SOURCE_DIR}/config.ini")
    set(DESTINATION_DIR "$<TARGET_FILE_DIR:chatProject>")
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
install(FILES "config.ini" DESTINATION ${CMAKE_INSTALL_BINDIR})

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(chatProject)
endif()
