// Copyright 2020 Bartosz Bilas <bartosz.bilas@hotmail.com>
import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.12

ApplicationWindow {
    id: window
    width: 640
    height: 480
    visible: true
    title: qsTr("QTasksManager")

    header: ToolBar {
        contentHeight: toolButton.implicitHeight

        RowLayout {
            anchors.fill: parent

            ToolButton {
                id: toolButton
                text: stackView.depth > 1 ? "\u25C0" : "\u2630"
                font.pixelSize: Qt.application.font.pixelSize * 1.6
                onClicked: {
                    if (stackView.depth > 1) {
                        stackView.pop()
                    } else {
                        drawer.open()
                    }
                }
            }

            Label {
                Layout.alignment: Qt.AlignRight
                Layout.rightMargin: 5
                font.pointSize: 11
                text: qsTr(
                          "Total activity time: " + taskModel.totalActivityTime)
            }
        }
    }

    Drawer {
        id: drawer
        width: 200
        height: window.height

        Column {
            anchors.fill: parent

            ItemDelegate {
                id: taskMenuButton
                text: qsTr("Add Task")
                width: parent.width
                onClicked: {
                    taskModel.addNewEmptyTask()
                    drawer.close()
                }
            }

            ItemDelegate {
                text: qsTr("Settings")
                width: parent.width
                onClicked: {
                    stackView.push("qrc:/Settings.qml")
                    drawer.close()
                }
            }
        }
    }

    StackView {
        id: stackView
        initialItem: WorkPackages {}
        anchors.fill: parent
    }
}
