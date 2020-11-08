cmake_minimum_required(VERSION 3.13)

project(QTasksManager LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Core Quick Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Quick Widgets REQUIRED)

set(QT5_MINIMUM_VERSION_MAJOR 5)
set(QT5_MINIMUM_VERSION_MINOR 14)

if (${QT_VERSION_MAJOR} LESS ${QT5_MINIMUM_VERSION_MAJOR} OR ${QT_VERSION_MINOR} LESS ${QT5_MINIMUM_VERSION_MINOR})
    MESSAGE(FATAL_ERROR "Installed Qt5 version is too old. Minimum required is ${QT5_MINIMUM_VERSION_MAJOR}.${QT5_MINIMUM_VERSION_MINOR}")
endif()

add_executable(QTasksManager
    src/main.cpp
    src/qml.qrc
    src/icons.qrc
    src/WorkPackage.cpp
    src/WorkPackagesModel.cpp
    src/UserSettings.cpp
    src/WorkPackagesManager.cpp
    src/TrayIcon.cpp
    )

target_compile_definitions(QTasksManager
  PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(QTasksManager
  PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Quick Qt${QT_VERSION_MAJOR}::Widgets)

