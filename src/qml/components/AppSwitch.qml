// Copyright 2020 Bartosz Bilas <bartosz.bilas@hotmail.com>
import QtQuick
import QtQuick.Controls.Basic

Switch {
    id: root

    hoverEnabled: true
    padding: 0
    implicitWidth: implicitIndicatorWidth + leftPadding + rightPadding

    indicator: Rectangle {
        implicitWidth: 44
        implicitHeight: 26
        x: root.leftPadding
        y: (root.height - height) / 2
        radius: height / 2
        color: root.checked ? Theme.accent : Theme.borderStrong
        Behavior on color { ColorAnimation { duration: Theme.animationFast } }

        Rectangle {
            width: 20
            height: 20
            radius: 10
            y: 3
            x: root.checked ? parent.width - width - 3 : 3
            color: "#ffffff"
            Behavior on x { NumberAnimation { duration: Theme.animation; easing.type: Easing.OutCubic } }
        }
    }

    contentItem: Item {}
}
