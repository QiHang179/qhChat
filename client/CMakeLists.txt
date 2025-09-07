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
        chatitembase.h chatitembase.cpp
        bubbleframe.h bubbleframe.cpp
        textbubble.h textbubble.cpp
        picturebubble.h picturebubble.cpp
        messagetextedit.h messagetextedit.cpp
        chatview.h chatview.cpp
        statewidget.h statewidget.cpp
        searchlist.h searchlist.cpp
        userdata.h userdata.cpp
        adduseritem.h adduseritem.cpp adduseritem.ui
        findsuccessdlg.h findsuccessdlg.cpp findsuccessdlg.ui
        applyfriend.h applyfriend.cpp applyfriend.ui
        clickedoncelabel.h clickedoncelabel.cpp
        friendlabel.h friendlabel.cpp friendlabel.ui
        contactuserlist.h contactuserlist.cpp
        conuseritem.h conuseritem.cpp conuseritem.ui
        grouptipitem.h grouptipitem.cpp grouptipitem.ui


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

# 针对MSVC编译器添加特定编译选项（对应qmake的win32-msvc*:QMAKE_CXXFLAGS += /wd"4819" /utf-8）
if(MSVC)
    # 禁用警告4819（文件包含不能在当前代码页中表示的字符）
    # 设置源文件编码为UTF-8
    target_compile_options(chatProject PRIVATE /wd4819 /utf-8)
endif()

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

# 根据构建类型输出信息（类似qmake的message）
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    message(STATUS "debug mode")
else()
    message(STATUS "release mode")
endif()

# 拷贝config.ini文件到输出目录
set(SOURCE_CONFIG "${CMAKE_CURRENT_SOURCE_DIR}/config.ini")
set(DESTINATION_DIR "$<TARGET_FILE_DIR:chatProject>")
add_custom_command(TARGET chatProject POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "${SOURCE_CONFIG}"
    "${DESTINATION_DIR}"
    COMMENT "Copying config.ini to build directory"
)

# 拷贝image文件夹到输出目录（类似qmake的static文件夹拷贝）
set(SOURCE_IMAGE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/image")
set(DEST_IMAGE_DIR "$<TARGET_FILE_DIR:chatProject>/image")
add_custom_command(TARGET chatProject POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${SOURCE_IMAGE_DIR}"
    "${DEST_IMAGE_DIR}"
    COMMENT "Copying image directory to build directory"
)

# 拷贝style文件夹到输出目录
set(SOURCE_STYLE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/style")
set(DEST_STYLE_DIR "$<TARGET_FILE_DIR:chatProject>/style")
add_custom_command(TARGET chatProject POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${SOURCE_STYLE_DIR}"
    "${DEST_STYLE_DIR}"
    COMMENT "Copying style directory to build directory"
)

# 如果存在static文件夹，也进行拷贝（为了兼容原qmake项目）
if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/static")
    set(SOURCE_STATIC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/static")
    set(DEST_STATIC_DIR "$<TARGET_FILE_DIR:chatProject>/static")
    add_custom_command(TARGET chatProject POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${SOURCE_STATIC_DIR}"
        "${DEST_STATIC_DIR}"
        COMMENT "Copying static directory to build directory"
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
