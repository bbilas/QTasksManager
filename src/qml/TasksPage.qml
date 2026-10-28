// Copyright 2020 Bartosz Bilas <bartosz.bilas@hotmail.com>
import QtQuick
import QtQuick.Controls.Basic
import QtQuick.Layouts
import TasksManager

Page {
    id: page

    signal settingsRequested()

    background: Rectangle { color: Theme.background }

    function addTask() {
        searchField.clear()
        TaskModel.addTask()
        taskList.positionViewAtBeginning()
        Qt.callLater(() => {
            const card = taskList.itemAtIndex(0)
            if (card)
                card.editName()
        })
    }

    function requestDeleteSelected() {
        const count = TaskModel.selectedCount
        if (count === 0)
            return
        confirmDialog.ask(count === 1 ? qsTr("Delete 1 task?") : qsTr("Delete %1 tasks?").arg(count),
                          qsTr("The selected tasks and their tracked time will be removed permanently."),
                          qsTr("Delete"),
                          () => TaskModel.removeSelected())
    }

    function requestDelete(taskId, taskName) {
        confirmDialog.ask(qsTr("Delete task?"),
                          taskName.length > 0
                              ? qsTr("“%1” and its tracked time will be removed permanently.").arg(taskName)
                              : qsTr("This task and its tracked time will be removed permanently."),
                          qsTr("Delete"),
                          () => TaskModel.removeTask(taskId))
    }

    TaskFilterModel {
        id: filteredTasks
        sourceModel: TaskModel
        filterText: searchField.text
    }

    Shortcut { sequences: [StandardKey.New]; onActivated: page.addTask() }
    Shortcut { sequences: [StandardKey.Find]; onActivated: searchField.forceActiveFocus() }
    Shortcut { sequence: "Delete"; enabled: TaskModel.selectedCount > 0; onActivated: page.requestDeleteSelected() }
    Shortcut { sequence: "Escape"; enabled: TaskModel.selectedCount > 0; onActivated: TaskModel.clearSelection() }

    ColumnLayout {
        anchors.fill: parent
        anchors.leftMargin: Theme.pagePadding
        anchors.rightMargin: Theme.pagePadding
        anchors.topMargin: Theme.pagePadding - 4
        spacing: 18

        // Title bar
        RowLayout {
            Layout.fillWidth: true
            spacing: 8

            ColumnLayout {
                spacing: 2
                Text {
                    text: qsTr("Tasks")
                    color: Theme.text
                    font.pixelSize: 28
                    font.weight: Font.Bold
                    font.letterSpacing: -0.5
                }
                Text {
                    text: TaskModel.count === 1 ? qsTr("1 task") : qsTr("%1 tasks").arg(TaskModel.count)
                    color: Theme.textMuted
                    font.pixelSize: 13
                }
            }

            Item { Layout.fillWidth: true }

            IconButton {
                iconPath: Icons.settings
                iconSize: 20
                toolTip: qsTr("Settings")
                onClicked: page.settingsRequested()
            }

            AppButton {
                text: qsTr("New task")
                iconPath: Icons.plus
                onClicked: page.addTask()
            }
        }

        SummaryCard {
            Layout.fillWidth: true
        }

        // List toolbar
        RowLayout {
            Layout.fillWidth: true
            spacing: 12

            AppCheckBox {
                enabled: filteredTasks.count > 0
                text: filteredTasks.selectedCount > 0
                      ? qsTr("%1 of %2 selected").arg(filteredTasks.selectedCount).arg(filteredTasks.count)
                      : qsTr("Select all")
                checkState: filteredTasks.selectedCount === 0 ? Qt.Unchecked
                          : filteredTasks.selectedCount === filteredTasks.count ? Qt.Checked
                          : Qt.PartiallyChecked
                onClicked: filteredTasks.selectAll(filteredTasks.selectedCount !== filteredTasks.count)
            }

            Item { Layout.fillWidth: true }

            SearchField {
                id: searchField
                Layout.preferredWidth: 300
                Layout.maximumWidth: page.width * 0.45
            }
        }

        ListView {
            id: taskList

            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.leftMargin: -6
            Layout.rightMargin: -6
            leftMargin: 6
            rightMargin: 6
            clip: true
            spacing: 8
            model: filteredTasks
            boundsBehavior: Flickable.StopAtBounds
            reuseItems: true

            ScrollBar.vertical: ScrollBar {
                policy: ScrollBar.AsNeeded
                contentItem: Rectangle {
                    implicitWidth: 6
                    radius: 3
                    color: Theme.borderStrong
                    opacity: parent.active ? 1 : 0.5
                }
            }

            delegate: TaskCard {
                width: ListView.view.width - ListView.view.leftMargin - ListView.view.rightMargin
                onDeleteRequested: (taskId, taskName) => page.requestDelete(taskId, taskName)
            }

            footer: Item {
                width: 1
                height: selectionBar.shown ? selectionBar.height + 40 : Theme.pagePadding
            }

            add: Transition {
                ParallelAnimation {
                    NumberAnimation { property: "opacity"; from: 0; to: 1; duration: Theme.animation }
                    NumberAnimation { property: "scale"; from: 0.97; to: 1; duration: Theme.animation; easing.type: Easing.OutCubic }
                }
            }
            displaced: Transition {
                NumberAnimation { properties: "y"; duration: Theme.animation; easing.type: Easing.OutCubic }
                NumberAnimation { properties: "opacity,scale"; to: 1; duration: Theme.animation }
            }
        }
    }

    EmptyState {
        anchors.centerIn: parent
        anchors.verticalCenterOffset: 110
        visible: filteredTasks.count === 0
        filtered: searchField.text.length > 0
        query: searchField.text
        onCreateRequested: page.addTask()
    }

    SelectionBar {
        id: selectionBar
        anchors.horizontalCenter: parent.horizontalCenter
        selectedCount: TaskModel.selectedCount
        onClearRequested: TaskModel.clearSelection()
        onDeleteRequested: page.requestDeleteSelected()
    }

    ConfirmDialog {
        id: confirmDialog
    }
}
