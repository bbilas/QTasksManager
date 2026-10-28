// Copyright 2020 Bartosz Bilas <bartosz.bilas@hotmail.com>
import QtQuick
import QtQuick.Layouts
import TasksManager

Rectangle {
    id: root

    readonly property real goal: Math.max(1, AppSettings.dailyWorkingSeconds)
    readonly property real progress: TaskModel.totalSeconds / goal
    readonly property bool overtime: TaskModel.totalSeconds > AppSettings.dailyWorkingSeconds

    implicitHeight: content.implicitHeight + 44
    radius: Theme.radiusLarge
    color: Theme.surface
    border.width: 1
    border.color: Theme.border

    ColumnLayout {
        id: content
        anchors.fill: parent
        anchors.margins: 22
        spacing: 16

        RowLayout {
            Layout.fillWidth: true
            spacing: 16

            ColumnLayout {
                spacing: 4

                Text {
                    text: qsTr("TOTAL TRACKED")
                    color: Theme.textMuted
                    font.pixelSize: 11
                    font.weight: Font.DemiBold
                    font.letterSpacing: 1.2
                }
                Text {
                    text: TaskModel.formatDuration(TaskModel.totalSeconds)
                    color: Theme.text
                    font.features: Theme.tabularFigures
                    font.pixelSize: 40
                    font.weight: Font.DemiBold
                    font.letterSpacing: -1
                }
            }

            Item { Layout.fillWidth: true }

            ColumnLayout {
                spacing: 8
                Layout.alignment: Qt.AlignTop | Qt.AlignRight

                Chip {
                    Layout.alignment: Qt.AlignRight
                    visible: TaskModel.runningCount > 0
                    pulsing: true
                    tint: Theme.success
                    tintSoft: Theme.successSoft
                    text: TaskModel.runningCount === 1 ? qsTr("1 running") : qsTr("%1 running").arg(TaskModel.runningCount)
                }
                Chip {
                    Layout.alignment: Qt.AlignRight
                    visible: TaskModel.runningCount === 0
                    tint: Theme.textMuted
                    tintSoft: Theme.field
                    text: qsTr("Idle")
                }
                Chip {
                    Layout.alignment: Qt.AlignRight
                    visible: root.overtime
                    tint: Theme.warning
                    tintSoft: Theme.warningSoft
                    text: qsTr("Overtime +%1").arg(TaskModel.formatDuration(TaskModel.totalSeconds - AppSettings.dailyWorkingSeconds))
                }
            }
        }

        ColumnLayout {
            Layout.fillWidth: true
            spacing: 8

            Rectangle {
                Layout.fillWidth: true
                implicitHeight: 8
                radius: 4
                color: Theme.field

                Rectangle {
                    height: parent.height
                    radius: parent.radius
                    width: parent.width * Math.min(1, root.progress)
                    Behavior on width { NumberAnimation { duration: 400; easing.type: Easing.OutCubic } }
                    gradient: Gradient {
                        orientation: Gradient.Horizontal
                        GradientStop { position: 0; color: root.overtime ? Theme.warning : Theme.accent }
                        GradientStop { position: 1; color: root.overtime ? Theme.danger : Theme.accentEnd }
                    }
                }
            }

            RowLayout {
                Layout.fillWidth: true
                Text {
                    text: qsTr("Daily goal %1").arg(AppSettings.dailyWorkingTime)
                    color: Theme.textMuted
                    font.pixelSize: 12
                }
                Item { Layout.fillWidth: true }
                Text {
                    text: qsTr("%1%").arg(Math.round(root.progress * 100))
                    color: root.overtime ? Theme.warning : Theme.textMuted
                    font.pixelSize: 12
                    font.weight: Font.DemiBold
                    font.features: Theme.tabularFigures
                }
            }
        }
    }

    component Chip: Rectangle {
        id: chip
        property string text
        property color tint
        property color tintSoft
        property bool pulsing: false

        implicitWidth: chipRow.implicitWidth + 20
        implicitHeight: 26
        radius: height / 2
        color: tintSoft

        Row {
            id: chipRow
            anchors.centerIn: parent
            spacing: 7

            Rectangle {
                anchors.verticalCenter: parent.verticalCenter
                width: 7
                height: 7
                radius: 3.5
                color: chip.tint

                SequentialAnimation on opacity {
                    running: chip.pulsing && chip.visible
                    loops: Animation.Infinite
                    NumberAnimation { to: 0.3; duration: 700; easing.type: Easing.InOutSine }
                    NumberAnimation { to: 1; duration: 700; easing.type: Easing.InOutSine }
                }
            }
            Text {
                text: chip.text
                color: chip.tint
                font.pixelSize: 12
                font.weight: Font.DemiBold
            }
        }
    }
}
