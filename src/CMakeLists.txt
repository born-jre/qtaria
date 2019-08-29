cmake_minimum_required(VERSION 3.8)
project(qtaria)

find_package(Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt5Core REQUIRED)
find_package(Qt5Gui REQUIRED)
find_package(Qt5Network REQUIRED)
#find_library(ARIA aria2)

SET(CMAKE_AUTOUIC ON)
SET(CMAKE_AUTOMOC ON)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        core/handlers/qtweb/downloadjob.h
        core/handlers/downloaderinterface.h
        addnewdialog.cpp
        addnewdialog.h
        main.cpp
        mainwindow.cpp
        mainwindow.h
        core/managers/uimanager/uielementgroup.cpp
        core/managers/uimanager/uielementgroup.h
        core/handlers/qtweb/qtwebhandler.cpp
        core/handlers/qtweb/qtwebhandler.h
        core/handlers/qtweb/downloadjob.cpp core/managers/sessionmanager/sessionmanager.cpp core/managers/sessionmanager/sessionmanager.h core/managers/uimanager/listwidget.cpp core/managers/uimanager/listwidget.h)

add_executable(qtaria ${SOURCE_FILES} )
#MESSAGE(STATUS "${ARIA}" )
#target_link_libraries(qtaria "${ARIA}")


#find_library(LOCAL_ARIA "${CMAKE_SOURCE_DIR}/lib/libaria2.so")
#find_file(LOCAL_ARIA "$../../lib/libaria2.so")
#MESSAGE(STATUS "${LOCAL_ARIA}" )
#TARGET_LINK_LIBRARIES(qtaria "${LOCAL_ARIA}" )

qt5_use_modules(qtaria Core Gui Widgets Network)