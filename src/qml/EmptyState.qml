// Copyright 2020 Bartosz Bilas <bartosz.bilas@hotmail.com>
import QtQuick
import QtQuick.Layouts

ColumnLayout {
    id: root

    property bool filtered: false
    property string query
    signal createRequested()

    spacing: 10

    Rectangle {
        Layout.alignment: Qt.AlignHCenter
        Layout.bottomMargin: 6
        implicitWidth: 64
        implicitHeight: 64
        radius: 32
        color: Theme.accentSoft

        Icon {
            anchors.centerIn: parent
            size: 30
            path: root.filtered ? Icons.search : Icons.clock
            color: Theme.accent
        }
    }

    Text {
        Layout.alignment: Qt.AlignHCenter
        text: root.filtered ? qsTr("No matching tasks") : qsTr("No tasks yet")
        color: Theme.text
        font.pixelSize: 18
        font.weight: Font.DemiBold
    }

    Text {
        Layout.alignment: Qt.AlignHCenter
        text: root.filtered ? qsTr("Nothing matches “%1”.").arg(root.query)
                            : qsTr("Create a task and hit play to start tracking time.")
        color: Theme.textMuted
    }

    AppButton {
        Layout.alignment: Qt.AlignHCenter
        Layout.topMargin: 8
        visible: !root.filtered
        text: qsTr("New task")
        iconPath: Icons.plus
        onClicked: root.createRequested()
    }
}
