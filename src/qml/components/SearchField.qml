// Copyright 2020 Bartosz Bilas <bartosz.bilas@hotmail.com>
import QtQuick
import QtQuick.Controls.Basic

TextField {
    id: root

    implicitHeight: 38
    leftPadding: 38
    rightPadding: text.length > 0 ? 36 : 12
    hoverEnabled: true
    placeholderText: qsTr("Search tasks")
    color: Theme.text
    placeholderTextColor: Theme.textMuted
    selectionColor: Theme.accent
    selectedTextColor: Theme.accentForeground
    selectByMouse: true

    background: Rectangle {
        radius: Theme.radius - 2
        color: Theme.surface
        border.width: 1
        border.color: root.activeFocus ? Theme.accent : root.hovered ? Theme.borderStrong : Theme.border
        Behavior on border.color { ColorAnimation { duration: Theme.animationFast } }

        Icon {
            anchors.left: parent.left
            anchors.leftMargin: 12
            anchors.verticalCenter: parent.verticalCenter
            size: 17
            path: Icons.search
            color: Theme.textMuted
        }
    }

    IconButton {
        anchors.right: parent.right
        anchors.rightMargin: 4
        anchors.verticalCenter: parent.verticalCenter
        implicitWidth: 28
        implicitHeight: 28
        iconSize: 14
        iconPath: Icons.close
        visible: root.text.length > 0
        onClicked: root.clear()
    }

    Keys.onEscapePressed: {
        if (text.length > 0)
            clear()
        else
            focus = false
    }
}
