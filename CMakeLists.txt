cmake_minimum_required(VERSION 3.21)

project(QTasksManager VERSION 2.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(GNUInstallDirs)

find_package(Qt6 6.6 REQUIRED COMPONENTS Core DBus Gui Qml Quick QuickControls2 Widgets)

qt_standard_project_setup(REQUIRES 6.6)

qt_add_executable(QTasksManager
    src/main.cpp
    src/AppSettings.cpp
    src/AppSettings.h
    src/ScreenLockMonitor.cpp
    src/ScreenLockMonitor.h
    src/Task.h
    src/TaskFilterModel.cpp
    src/TaskFilterModel.h
    src/TaskModel.cpp
    src/TaskModel.h
    src/TaskStorage.cpp
    src/TaskStorage.h
    src/TimeTracker.cpp
    src/TimeTracker.h
    src/TrayIcon.cpp
    src/TrayIcon.h
)

set(QML_FILES
    src/qml/Main.qml
    src/qml/Theme.qml
    src/qml/Icons.qml
    src/qml/TasksPage.qml
    src/qml/SettingsPage.qml
    src/qml/TaskCard.qml
    src/qml/SummaryCard.qml
    src/qml/SelectionBar.qml
    src/qml/EmptyState.qml
    src/qml/ConfirmDialog.qml
    src/qml/components/Icon.qml
    src/qml/components/IconButton.qml
    src/qml/components/AppButton.qml
    src/qml/components/AppCheckBox.qml
    src/qml/components/AppSwitch.qml
    src/qml/components/PlayButton.qml
    src/qml/components/InlineTextField.qml
    src/qml/components/SearchField.qml
    src/qml/components/SegmentedControl.qml
    src/qml/components/SettingRow.qml
    src/qml/components/Card.qml
)

# Flatten the resource layout so every QML file lives in the module root and
# sees the module's singletons (Theme, Icons) without explicit imports.
foreach(qml_file IN LISTS QML_FILES)
    get_filename_component(qml_name ${qml_file} NAME)
    set_source_files_properties(${qml_file} PROPERTIES QT_RESOURCE_ALIAS ${qml_name})
endforeach()
set_source_files_properties(src/qml/Theme.qml src/qml/Icons.qml
    PROPERTIES QT_QML_SINGLETON_TYPE TRUE)

qt_add_qml_module(QTasksManager
    URI TasksManager
    VERSION 1.0
    QML_FILES ${QML_FILES}
)

qt_add_resources(QTasksManager "icons"
    PREFIX "/"
    BASE src
    FILES src/media/icons/tray_icon.png
)

# qmltyperegistrar includes the QML_ELEMENT headers by their bare names.
target_include_directories(QTasksManager PRIVATE src)

target_compile_definitions(QTasksManager PRIVATE
    QTASKSMANAGER_VERSION="${PROJECT_VERSION}"
    $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>
)

target_link_libraries(QTasksManager PRIVATE
    Qt6::Core
    Qt6::DBus
    Qt6::Gui
    Qt6::Qml
    Qt6::Quick
    Qt6::QuickControls2
    Qt6::Widgets
)

set(EXTRA_DIR "${CMAKE_CURRENT_SOURCE_DIR}/extra")

install(TARGETS QTasksManager
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
install(FILES ${EXTRA_DIR}/desktop/qtasksmanager.desktop
        DESTINATION ${CMAKE_INSTALL_DATADIR}/applications)
install(FILES ${EXTRA_DIR}/desktop/qtasksmanager.svg
        DESTINATION ${CMAKE_INSTALL_DATADIR}/icons/hicolor/scalable/apps)
