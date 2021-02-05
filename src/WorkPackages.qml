// Copyright 2020 Bartosz Bilas <bartosz.bilas@hotmail.com>
import QtQuick 2.4
import QtQuick.Layouts 1.11
import QtQuick.Controls 2.4

WorkPackagesForm {
    readonly property int minColumWidth: 160
    readonly property int extraColumnMargin: 10

    function updateCurrentRow(idx) {
        tasksTable.selection.clear()
        tasksTable.selection.select(idx)
        tasksTable.currentRow = idx
    }

    projectNameColumn.delegate: RowLayout {
        anchors.fill: parent

        TextInput {
            id: input
            text: model.projectName
            onFocusChanged: updateCurrentRow(styleData.row)
            onDisplayTextChanged: {
                model.projectName = text
                if (contentWidth.toFixed() > projectNameColumn.width)
                    projectNameColumn.width = parseInt(
                                contentWidth.toFixed()) + extraColumnMargin
            }
            Keys.onReleased: {
                if (event.key === Qt.Key_Backspace) {
                    projectNameColumn.resizeToContents()
                    if (projectNameColumn.width < minColumWidth)
                        projectNameColumn.width = minColumWidth
                }
            }
        }
    }

    taskNameColumn.delegate: RowLayout {
        anchors.fill: parent

        TextInput {
            text: model.taskName
            onFocusChanged: updateCurrentRow(styleData.row)
            onDisplayTextChanged: {
                model.taskName = text
                if (contentWidth.toFixed() > taskNameColumn.width)
                    taskNameColumn.width = parseInt(contentWidth.toFixed(
                                                        )) + extraColumnMargin
            }
            Keys.onReleased: {
                if (event.key === Qt.Key_Backspace) {
                    taskNameColumn.resizeToContents()
                    if (taskNameColumn.width < minColumWidth)
                        taskNameColumn.width = minColumWidth
                }
            }
        }
    }

    actionsColumn.delegate: RowLayout {
        anchors.fill: parent

        Switch {
            checked: model.active
            onCheckedChanged: model.active = checked
        }

        Image {
            id: deleteIcon
            sourceSize.width: 25
            sourceSize.height: 25
            fillMode: Image.PreserveAspectFit
            clip: true
            source: "qrc:/media/icons/garbage.png"

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    taskModel.removeWorkPackage(styleData.row)
                }
            }
        }

        Image {
            sourceSize.width: 25
            sourceSize.height: 25
            fillMode: Image.PreserveAspectFit
            clip: true
            source: "qrc:/media/icons/reload.png"

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    taskModel.reloadActivityTime(styleData.row)
                }
            }
        }

        Label {
            text: model.activityTime
            onTextChanged: model.activityTimeHumanString = text
        }
    }

    tasksTable.rowDelegate: Rectangle {
        height: 50

        SystemPalette {
            id: myPalette
            colorGroup: SystemPalette.Active
        }
        color: {
            var baseColor = styleData.alternate ? myPalette.alternateBase : myPalette.base
            return styleData.selected ? myPalette.highlight : baseColor
        }
    }
}
