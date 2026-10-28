// Copyright 2020 Bartosz Bilas <bartosz.bilas@hotmail.com>
import QtQuick
import QtQuick.Controls.Basic

// The visual state is driven only by `checkState`/`checked` bindings; clicks
// are reported through clicked() so the bindings are never broken.
CheckBox {
    id: root

    checkable: false
    tristate: true
    hoverEnabled: true
    focusPolicy: Qt.NoFocus
    padding: 4
    spacing: 10

    readonly property bool marked: checkState !== Qt.Unchecked

    indicator: Rectangle {
        x: root.leftPadding
        y: (root.height - height) / 2
        implicitWidth: 20
        implicitHeight: 20
        radius: 6
        color: root.marked ? Theme.accent : "transparent"
        border.width: root.marked ? 0 : 1.5
        border.color: root.hovered ? Theme.accent : Theme.borderStrong

        Behavior on color { ColorAnimation { duration: Theme.animationFast } }

        Icon {
            anchors.centerIn: parent
            size: 14
            strokeWidth: 3
            color: Theme.accentForeground
            path: root.checkState === Qt.PartiallyChecked ? Icons.minus : Icons.check
            opacity: root.marked ? 1 : 0
            scale: root.marked ? 1 : 0.6
            Behavior on opacity { NumberAnimation { duration: Theme.animationFast } }
            Behavior on scale { NumberAnimation { duration: Theme.animationFast; easing.type: Easing.OutBack } }
        }
    }

    contentItem: Text {
        leftPadding: root.text.length > 0 ? root.indicator.width + root.spacing : root.indicator.width
        text: root.text
        font: root.font
        color: Theme.textMuted
        verticalAlignment: Text.AlignVCenter
    }
}
