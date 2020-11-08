// Copyright 2020 Bartosz Bilas <bartosz.bilas@hotmail.com>
import QtQuick 2.4
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.11
import DateTimeValidator 1.0

Page {
    property alias dailyWorkingTime: dailyWorkingTime
    width: 640
    height: 480

    Column {
        anchors.fill: parent
        spacing: 0

        TextSwitchItem {
            width: parent.width
            height: 50
            itemLabel.text: qsTr("Restore the task switch state at startup")
            itemSwitch.checked: itemSwitch.checked = userSettings.taskSwitchStateAtStartUp
            itemSwitch.onCheckedChanged: userSettings.taskSwitchStateAtStartUp = itemSwitch.checked
        }

        TextTextEditItem {
            id: dailyWorkingTime
            width: parent.width
            height: 50
            itemLabel.text: qsTr("Daily working time")
            itemTextField.inputMask: "00:00:00"
            itemTextField.placeholderText: qsTr("08:00:00")
            itemTextField.validator: DateTimeValidator {}
            itemTextField.text: userSettings.dailyWorkingTime
            itemTextField.onTextEdited: userSettings.dailyWorkingTime
                                        = dailyWorkingTime.itemTextField.text
        }
    }
}
