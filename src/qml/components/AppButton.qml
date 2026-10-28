// Copyright 2020 Bartosz Bilas <bartosz.bilas@hotmail.com>
import QtQuick
import QtQuick.Controls.Basic
import QtQuick.Layouts

AbstractButton {
    id: root

    enum Kind { Primary, Secondary, Danger, Ghost }

    property int kind: AppButton.Primary
    property string iconPath

    readonly property color foreground: {
        switch (kind) {
        case AppButton.Primary:
        case AppButton.Danger:
            return Theme.accentForeground
        default:
            return Theme.text
        }
    }
    readonly property color baseColor: {
        switch (kind) {
        case AppButton.Primary: return Theme.accent
        case AppButton.Danger: return Theme.danger
        case AppButton.Secondary: return Theme.field
        default: return "transparent"
        }
    }

    implicitWidth: Math.max(implicitBackgroundWidth, implicitContentWidth + leftPadding + rightPadding)
    implicitHeight: 38
    leftPadding: iconPath.length > 0 ? 12 : 16
    rightPadding: 16
    hoverEnabled: true
    font.weight: Font.DemiBold

    background: Rectangle {
        radius: Theme.radius - 2
        color: root.baseColor
        opacity: root.enabled ? 1 : 0.5

        Rectangle {
            anchors.fill: parent
            radius: parent.radius
            color: root.pressed ? Qt.rgba(0, 0, 0, 0.12) : root.hovered ? Qt.rgba(1, 1, 1, 0.10) : "transparent"
            visible: root.kind === AppButton.Primary || root.kind === AppButton.Danger
        }
        Rectangle {
            anchors.fill: parent
            radius: parent.radius
            color: root.pressed ? Theme.pressed : root.hovered ? Theme.hover : "transparent"
            visible: !(root.kind === AppButton.Primary || root.kind === AppButton.Danger)
        }

        scale: root.pressed ? 0.98 : 1
        Behavior on scale { NumberAnimation { duration: Theme.animationFast } }
    }

    contentItem: RowLayout {
        spacing: 8

        Icon {
            visible: root.iconPath.length > 0
            path: root.iconPath
            size: 18
            strokeWidth: 2.2
            color: root.foreground
        }

        Text {
            text: root.text
            font: root.font
            color: root.foreground
            Layout.alignment: Qt.AlignVCenter
        }
    }
}
