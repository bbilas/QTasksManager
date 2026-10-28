// Copyright 2020 Bartosz Bilas <bartosz.bilas@hotmail.com>
import QtQuick
import QtQuick.Layouts

Rectangle {
    default property alias content: column.data

    implicitHeight: column.implicitHeight
    radius: Theme.radiusLarge
    color: Theme.surface
    border.width: 1
    border.color: Theme.border
    clip: true

    ColumnLayout {
        id: column
        anchors.left: parent.left
        anchors.right: parent.right
        spacing: 0
    }
}
