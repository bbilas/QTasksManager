// Copyright 2020 Bartosz Bilas <bartosz.bilas@hotmail.com>
import QtQuick
import QtQuick.Layouts

// Floating contextual action bar shown while tasks are selected.
Rectangle {
    id: root

    property int selectedCount: 0
    readonly property bool shown: selectedCount > 0

    signal clearRequested()
    signal deleteRequested()

    width: layout.implicitWidth + 16
    height: 56
    radius: 16
    color: Theme.inverseSurface
    y: parent.height - (shown ? height + 24 : -12)
    opacity: shown ? 1 : 0
    visible: opacity > 0

    Behavior on y { NumberAnimation { duration: Theme.animation + 60; easing.type: Easing.OutCubic } }
    Behavior on opacity { NumberAnimation { duration: Theme.animation } }

    // Keep the last count visible while sliding out.
    property int shownCount: 1
    onSelectedCountChanged: if (selectedCount > 0) shownCount = selectedCount

    RowLayout {
        id: layout
        anchors.verticalCenter: parent.verticalCenter
        x: 8
        spacing: 6

        Rectangle {
            Layout.leftMargin: 8
            implicitWidth: Math.max(26, countText.implicitWidth + 12)
            implicitHeight: 26
            radius: 13
            color: Theme.accent

            Text {
                id: countText
                anchors.centerIn: parent
                text: root.shownCount
                color: Theme.accentForeground
                font.pixelSize: 13
                font.weight: Font.Bold
            }
        }

        Text {
            Layout.rightMargin: 12
            text: root.shownCount === 1 ? qsTr("task selected") : qsTr("tasks selected")
            color: Theme.inverseText
            font.pixelSize: 14
            font.weight: Font.Medium
        }

        BarButton {
            text: qsTr("Clear")
            onClicked: root.clearRequested()
        }

        AppButton {
            kind: AppButton.Danger
            text: qsTr("Delete")
            iconPath: Icons.trash
            onClicked: root.deleteRequested()
        }
    }

    component BarButton: AppButton {
        id: barButton
        kind: AppButton.Ghost
        contentItem: Text {
            text: barButton.text
            font: barButton.font
            color: Theme.inverseText
            verticalAlignment: Text.AlignVCenter
        }
        background: Rectangle {
            radius: Theme.radius - 2
            color: barButton.hovered ? Qt.alpha(Theme.inverseText, 0.12) : "transparent"
        }
    }
}
