// Copyright 2021 Bartosz Bilas <bartosz.bilas@hotmail.com>
import QtQuick
import QtQuick.Controls.Basic
import QtQuick.Layouts

Dialog {
    id: root

    property string heading
    property string message
    property string confirmText: qsTr("Confirm")
    property var pendingAction: null

    function ask(heading, message, confirmText, action) {
        root.heading = heading
        root.message = message
        root.confirmText = confirmText
        root.pendingAction = action
        open()
    }

    parent: Overlay.overlay
    anchors.centerIn: parent
    width: Math.min(420, parent.width - 48)
    modal: true
    focus: true
    padding: 24
    header: null
    footer: null

    onAccepted: {
        if (pendingAction)
            pendingAction()
        pendingAction = null
    }
    onRejected: pendingAction = null

    Overlay.modal: Rectangle {
        color: Qt.rgba(0.03, 0.04, 0.06, Theme.dark ? 0.6 : 0.35)
    }

    background: Rectangle {
        radius: Theme.radiusLarge + 2
        color: Theme.surface
        border.width: 1
        border.color: Theme.border
    }

    enter: Transition {
        ParallelAnimation {
            NumberAnimation { property: "opacity"; from: 0; to: 1; duration: Theme.animation; easing.type: Easing.OutCubic }
            NumberAnimation { property: "scale"; from: 0.94; to: 1; duration: Theme.animation; easing.type: Easing.OutCubic }
        }
    }
    exit: Transition {
        ParallelAnimation {
            NumberAnimation { property: "opacity"; to: 0; duration: Theme.animationFast }
            NumberAnimation { property: "scale"; to: 0.97; duration: Theme.animationFast }
        }
    }

    contentItem: ColumnLayout {
        spacing: 0
        focus: true
        Keys.onReturnPressed: root.accept()
        Keys.onEnterPressed: root.accept()

        Rectangle {
            implicitWidth: 44
            implicitHeight: 44
            radius: 22
            color: Theme.dangerSoft

            Icon {
                anchors.centerIn: parent
                size: 22
                path: Icons.trash
                color: Theme.danger
            }
        }

        Text {
            Layout.fillWidth: true
            Layout.topMargin: 16
            text: root.heading
            color: Theme.text
            font.pixelSize: 18
            font.weight: Font.DemiBold
            wrapMode: Text.WordWrap
        }

        Text {
            Layout.fillWidth: true
            Layout.topMargin: 6
            text: root.message
            color: Theme.textMuted
            wrapMode: Text.WordWrap
            lineHeight: 1.15
        }

        RowLayout {
            Layout.fillWidth: true
            Layout.topMargin: 24
            spacing: 10

            Item { Layout.fillWidth: true }

            AppButton {
                kind: AppButton.Secondary
                text: qsTr("Cancel")
                onClicked: root.reject()
            }

            AppButton {
                id: confirmButton
                kind: AppButton.Danger
                text: root.confirmText
                onClicked: root.accept()
            }
        }
    }
}
