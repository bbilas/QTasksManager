// Copyright 2020 Bartosz Bilas <bartosz.bilas@hotmail.com>
import QtQuick
import QtQuick.Controls.Basic

// Looks like plain text until hovered or focused.
TextField {
    id: root

    leftPadding: 6
    rightPadding: 6
    topPadding: 3
    bottomPadding: 3
    hoverEnabled: true
    color: Theme.text
    placeholderTextColor: Theme.textFaint
    selectionColor: Theme.accent
    selectedTextColor: Theme.accentForeground
    selectByMouse: true

    background: Rectangle {
        radius: Theme.radiusSmall - 2
        color: root.activeFocus ? Theme.field : root.hovered ? Theme.hover : "transparent"
        border.width: root.activeFocus ? 1 : 0
        border.color: Theme.accent
    }

    onAccepted: focus = false
    Keys.onEscapePressed: focus = false
}
