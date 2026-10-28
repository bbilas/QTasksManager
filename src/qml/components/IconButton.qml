// Copyright 2020 Bartosz Bilas <bartosz.bilas@hotmail.com>
import QtQuick
import QtQuick.Controls.Basic

AbstractButton {
    id: root

    property string iconPath
    property real iconSize: 18
    property color iconColor: Theme.textMuted
    property color hoverIconColor: Theme.text
    property color hoverBackground: Theme.hover
    property string toolTip

    implicitWidth: 36
    implicitHeight: 36
    hoverEnabled: true
    focusPolicy: Qt.NoFocus

    background: Rectangle {
        radius: Theme.radiusSmall + 2
        color: root.pressed ? Theme.pressed : root.hovered ? root.hoverBackground : "transparent"
        Behavior on color { ColorAnimation { duration: Theme.animationFast } }
    }

    contentItem: Item {
        Icon {
            anchors.centerIn: parent
            path: root.iconPath
            size: root.iconSize
            color: root.hovered ? root.hoverIconColor : root.iconColor
        }
    }

    ToolTip.visible: hovered && toolTip.length > 0
    ToolTip.text: toolTip
    ToolTip.delay: 600
}
