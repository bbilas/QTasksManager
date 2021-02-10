// Copyright 2021 Bartosz Bilas <bartosz.bilas@hotmail.com>
import QtQuick 2.4
import QtQuick.Layouts 1.11
import QtQuick.Controls 2.15

Popup {
    focus: true
    modal: true
    dim: true
    property alias buttonYes: buttonYes
    property alias buttonNo: buttonNo

    ColumnLayout {
        anchors.fill: parent

        Label {
            id: label
            text: qsTr("Are you sure?")
            font.pointSize: 20
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
        }

        RowLayout {
            width: parent.width
            height: 100
            spacing: 10
            Layout.fillHeight: false
            Layout.fillWidth: true

            Button {
                id: buttonYes
                text: qsTr("Yes")
                Layout.fillWidth: true
            }

            Button {
                id: buttonNo
                text: qsTr("No")
                Layout.fillWidth: true
            }
        }
    }
}
