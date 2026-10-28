// Copyright 2020 Bartosz Bilas <bartosz.bilas@hotmail.com>
import QtQuick
import QtQuick.Controls.Basic
import QtQuick.Layouts
import TasksManager

Rectangle {
    id: card

    required property var model
    required property string taskId
    required property string project
    required property string name
    required property string elapsed
    required property bool running
    required property bool selected

    signal deleteRequested(string taskId, string taskName)

    function editName() {
        nameField.forceActiveFocus()
    }

    implicitHeight: 72
    radius: Theme.radius + 2
    color: selected ? Theme.accentSoft : hover.hovered ? Theme.surfaceHover : Theme.surface
    border.width: 1
    border.color: selected ? Qt.alpha(Theme.accent, 0.55)
                : running ? Qt.alpha(Theme.success, 0.45)
                : Theme.border

    Behavior on color { ColorAnimation { duration: Theme.animationFast } }
    Behavior on border.color { ColorAnimation { duration: Theme.animationFast } }

    HoverHandler { id: hover }

    // Clicking the card background toggles the selection.
    TapHandler {
        onTapped: card.model.selected = !card.selected
    }

    RowLayout {
        anchors.fill: parent
        anchors.leftMargin: 12
        anchors.rightMargin: 12
        spacing: 12

        AppCheckBox {
            checked: card.selected
            onClicked: card.model.selected = !card.selected
        }

        PlayButton {
            running: card.running
            idleColor: card.selected ? Theme.surface : Theme.accentSoft
            onClicked: TaskModel.toggleRunning(card.taskId)
        }

        ColumnLayout {
            Layout.fillWidth: true
            Layout.leftMargin: 2
            spacing: 0

            InlineTextField {
                id: nameField
                Layout.fillWidth: true
                text: card.name
                placeholderText: qsTr("Untitled task")
                font.pixelSize: 15
                font.weight: Font.DemiBold
                onTextEdited: card.model.name = text
            }

            RowLayout {
                spacing: 0
                Layout.fillWidth: true

                Icon {
                    Layout.leftMargin: 6
                    size: 13
                    strokeWidth: 2
                    path: Icons.folder
                    color: Theme.textFaint
                }

                InlineTextField {
                    Layout.fillWidth: true
                    text: card.project
                    placeholderText: qsTr("Add project")
                    font.pixelSize: 13
                    color: Theme.textMuted
                    onTextEdited: card.model.project = text
                }
            }
        }

        Text {
            text: card.elapsed
            font.features: Theme.tabularFigures
            font.pixelSize: 19
            font.weight: Font.Medium
            color: card.running ? Theme.success : card.elapsed === "00:00:00" ? Theme.textFaint : Theme.text
            Layout.rightMargin: 6
            Behavior on color { ColorAnimation { duration: Theme.animationFast } }
        }

        Row {
            spacing: 2
            opacity: hover.hovered || card.selected ? 1 : 0.55
            Behavior on opacity { NumberAnimation { duration: Theme.animationFast } }

            IconButton {
                iconPath: Icons.reset
                toolTip: qsTr("Reset time")
                enabled: card.elapsed !== "00:00:00"
                opacity: enabled ? 1 : 0.4
                onClicked: TaskModel.resetTime(card.taskId)
            }

            IconButton {
                iconPath: Icons.trash
                toolTip: qsTr("Delete")
                hoverIconColor: Theme.danger
                hoverBackground: Theme.dangerSoft
                onClicked: card.deleteRequested(card.taskId, card.name)
            }
        }
    }
}
