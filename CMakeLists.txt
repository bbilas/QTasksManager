cmake_minimum_required(VERSION 3.13)

project(QTasksManager LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_CPPLINT "cpplint;--root=src")

find_package(QT NAMES Qt6 Qt5 COMPONENTS Core Quick Widgets Qml DBus REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Quick Widgets Qml DBus REQUIRED)

set(QT5_MINIMUM_VERSION_MAJOR 5)
set(QT5_MINIMUM_VERSION_MINOR 14)

if (${QT_VERSION_MAJOR} LESS ${QT5_MINIMUM_VERSION_MAJOR} OR ${QT_VERSION_MINOR} LESS ${QT5_MINIMUM_VERSION_MINOR})
    MESSAGE(FATAL_ERROR "Installed Qt5 version is too old. Minimum required is ${QT5_MINIMUM_VERSION_MAJOR}.${QT5_MINIMUM_VERSION_MINOR}")
endif()

add_executable(QTasksManager
    src/main.cpp
    src/qml.qrc
    src/icons.qrc
    src/components.qrc
    src/WorkPackage.cpp
    src/WorkPackagesModel.cpp
    src/UserSettings.cpp
    src/WorkPackagesManager.cpp
    src/TrayIcon.cpp
    src/DateTimeValidator.cpp
    src/dbus/OrgCinnamonScreenSaver.cpp
    src/ScreenSaver.cpp
    )

target_compile_definitions(QTasksManager
  PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(QTasksManager
  PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Quick Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Qml Qt${QT_VERSION_MAJOR}::DBus)

set(EXTRA_DIR "${CMAKE_CURRENT_SOURCE_DIR}/extra")

install(FILES ${EXTRA_DIR}/desktop/qtasksmanager.desktop
        DESTINATION /usr/share/applications)
install(FILES ${EXTRA_DIR}/desktop/qtasksmanager.svg
        DESTINATION /usr/share/icons/hicolor/scalable/apps)
install(TARGETS ${PROJECT_NAME}
        RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}")
