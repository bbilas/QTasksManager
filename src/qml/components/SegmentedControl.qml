// Copyright 2020 Bartosz Bilas <bartosz.bilas@hotmail.com>
import QtQuick
import QtQuick.Controls.Basic

Rectangle {
    id: root

    property var model: []
    property int currentIndex: 0
    signal activated(int index)

    readonly property Item currentItem: repeater.count > currentIndex ? repeater.itemAt(currentIndex) : null

    implicitWidth: row.implicitWidth + 8
    implicitHeight: 36
    radius: Theme.radius - 2
    color: Theme.field

    Rectangle {
        id: highlight
        y: 4
        height: parent.height - 8
        radius: Theme.radiusSmall
        color: Theme.surface
        border.width: Theme.dark ? 0 : 1
        border.color: Theme.border
        x: root.currentItem ? root.currentItem.x + 4 : 4
        width: root.currentItem ? root.currentItem.width : 0
        Behavior on x { NumberAnimation { duration: Theme.animation; easing.type: Easing.OutCubic } }
        Behavior on width { NumberAnimation { duration: Theme.animation; easing.type: Easing.OutCubic } }
    }

    Row {
        id: row
        x: 4
        anchors.verticalCenter: parent.verticalCenter

        Repeater {
            id: repeater
            model: root.model

            AbstractButton {
                required property int index
                required property string modelData

                implicitWidth: label.implicitWidth + 28
                implicitHeight: root.height - 8
                hoverEnabled: true
                focusPolicy: Qt.NoFocus
                onClicked: root.activated(index)

                contentItem: Text {
                    id: label
                    text: parent.modelData
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    font.weight: Font.Medium
                    color: parent.index === root.currentIndex || parent.hovered ? Theme.text : Theme.textMuted
                }
                background: Item {}
            }
        }
    }
}
