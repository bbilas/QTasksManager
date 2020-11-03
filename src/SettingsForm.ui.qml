// Copyright 2020 Bartosz Bilas <bartosz.bilas@hotmail.com>
import QtQuick 2.4
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.11

Page {
    width: 640
    height: 480

    RowLayout {
        id: settingsItemRow
        width: parent.width
        height: 50
        Layout.alignment: Qt.AlignTop | Qt.AlignLeft | Qt.AlignRight

        Label {
            Layout.alignment: Qt.AlignLeft
            Layout.leftMargin: 5
            text: qsTr("Restore the task switch state at startup")
            font.pointSize: 15
        }

        Switch {
            Component.onCompleted: checked = userSettings.taskSwitchStateAtStartUp
            onCheckedChanged: userSettings.taskSwitchStateAtStartUp = checked
        }
    }

    Rectangle {
        width: settingsItemRow.width
        anchors.top: settingsItemRow.bottom
        height: 2
        color: "black"
    }
}
