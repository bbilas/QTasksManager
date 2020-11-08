import QtQuick 2.4
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.11

Item {
    property alias itemLabel: itemLabel
    property alias itemTextField: itemTextField

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

        TextField {
            id: itemTextField
            width: 50
            height: 50
            text: "00:00:00"
            horizontalAlignment: Text.AlignHCenter
            Layout.rightMargin: 5
            font.pointSize: 13
            Layout.maximumWidth: 100
            Layout.fillHeight: false
            Layout.fillWidth: false
            Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
        }
    }

    Rectangle {
        width: parent.width
        height: 2
        color: "black"
        anchors.bottom: itemRowLayout.bottom
    }
}
