// Copyright 2020 Bartosz Bilas <bartosz.bilas@hotmail.com>
import QtQuick
import QtQuick.Controls.Basic

AbstractButton {
    id: root

    property bool running: false
    property color idleColor: Theme.accentSoft

    implicitWidth: 40
    implicitHeight: 40
    hoverEnabled: true
    focusPolicy: Qt.NoFocus

    ToolTip.visible: hovered
    ToolTip.text: running ? qsTr("Pause") : qsTr("Start")
    ToolTip.delay: 600

    // Soft pulse around a running timer.
    Rectangle {
        id: pulse
        anchors.centerIn: parent
        width: parent.width
        height: parent.height
        radius: width / 2
        color: "transparent"
        border.color: Theme.success
        border.width: 2
        opacity: 0
        visible: root.running

        SequentialAnimation {
            running: root.running && root.visible
            loops: Animation.Infinite
            ParallelAnimation {
                NumberAnimation { target: pulse; property: "scale"; from: 1; to: 1.45; duration: 1400; easing.type: Easing.OutCubic }
                NumberAnimation { target: pulse; property: "opacity"; from: 0.55; to: 0; duration: 1400; easing.type: Easing.OutCubic }
            }
        }
    }

    background: Rectangle {
        radius: width / 2
        color: root.running ? Theme.success : root.hovered ? Theme.accent : root.idleColor
        scale: root.pressed ? 0.9 : 1
        Behavior on color { ColorAnimation { duration: Theme.animationFast } }
        Behavior on scale { NumberAnimation { duration: Theme.animationFast } }
    }

    contentItem: Item {
        Icon {
            anchors.centerIn: parent
            anchors.horizontalCenterOffset: root.running ? 0 : 1
            size: 18
            filled: true
            path: root.running ? Icons.pause : Icons.play
            color: root.running || root.hovered ? Theme.accentForeground : Theme.accent
        }
    }
}
