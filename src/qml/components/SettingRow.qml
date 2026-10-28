// Copyright 2020 Bartosz Bilas <bartosz.bilas@hotmail.com>
import QtQuick
import QtQuick.Layouts

Item {
    id: root

    property string title
    property string description
    property bool showDivider: true
    default property alias trailing: trailingContainer.data

    implicitHeight: Math.max(64, layout.implicitHeight + 28)
    Layout.fillWidth: true

    RowLayout {
        id: layout
        anchors.fill: parent
        anchors.leftMargin: 20
        anchors.rightMargin: 20
        spacing: 24

        ColumnLayout {
            Layout.fillWidth: true
            spacing: 3

            Text {
                Layout.fillWidth: true
                text: root.title
                color: Theme.text
                font.pixelSize: 15
                font.weight: Font.Medium
                wrapMode: Text.WordWrap
            }
            Text {
                Layout.fillWidth: true
                visible: text.length > 0
                text: root.description
                color: Theme.textMuted
                font.pixelSize: 13
                wrapMode: Text.WordWrap
            }
        }

        RowLayout {
            id: trailingContainer
            Layout.alignment: Qt.AlignVCenter | Qt.AlignRight
        }
    }

    Rectangle {
        visible: root.showDivider
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.leftMargin: 20
        height: 1
        color: Theme.border
    }
}
