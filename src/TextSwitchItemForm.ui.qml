import QtQuick 2.4
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.11

Item {
    property alias itemLabel: itemLabel
    property alias itemSwitch: itemSwitch

    RowLayout {
        id: itemRowLayout
        width: parent.width
        height: 50
        Layout.alignment: Qt.AlignTop | Qt.AlignLeft | Qt.AlignRight

        Label {
            id: itemLabel
            Layout.alignment: Qt.AlignLeft
            Layout.leftMargin: 5
            text: qsTr("dummy text")
            font.pointSize: 15
        }

        Switch {
            id: itemSwitch
            Layout.alignment: Qt.AlignRight
        }
    }

    Rectangle {
        width: parent.width
        height: 2
        color: "black"
        anchors.bottom: itemRowLayout.bottom
    }
}
