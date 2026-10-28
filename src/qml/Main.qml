// Copyright 2020 Bartosz Bilas <bartosz.bilas@hotmail.com>
import QtQuick
import QtQuick.Controls.Basic

ApplicationWindow {
    id: window

    width: 980
    height: 720
    minimumWidth: 600
    minimumHeight: 460
    visible: true
    title: "QTasksManager"
    color: Theme.background
    font.pixelSize: 14

    palette {
        window: Theme.background
        windowText: Theme.text
        base: Theme.surface
        text: Theme.text
        button: Theme.surface
        buttonText: Theme.text
        highlight: Theme.accent
        highlightedText: Theme.accentForeground
        placeholderText: Theme.textMuted
        toolTipBase: Theme.inverseSurface
        toolTipText: Theme.inverseText
        mid: Theme.border
        dark: Theme.borderStrong
    }

    StackView {
        id: stack
        anchors.fill: parent

        initialItem: TasksPage {
            onSettingsRequested: stack.push(settingsPage)
        }

        pushEnter: Transition {
            ParallelAnimation {
                NumberAnimation { property: "opacity"; from: 0; to: 1; duration: Theme.animation; easing.type: Easing.OutCubic }
                NumberAnimation { property: "x"; from: 40; to: 0; duration: Theme.animation; easing.type: Easing.OutCubic }
            }
        }
        pushExit: Transition {
            NumberAnimation { property: "opacity"; from: 1; to: 0; duration: Theme.animation }
        }
        popEnter: Transition {
            NumberAnimation { property: "opacity"; from: 0; to: 1; duration: Theme.animation }
        }
        popExit: Transition {
            ParallelAnimation {
                NumberAnimation { property: "opacity"; from: 1; to: 0; duration: Theme.animation; easing.type: Easing.OutCubic }
                NumberAnimation { property: "x"; from: 0; to: 40; duration: Theme.animation; easing.type: Easing.OutCubic }
            }
        }
    }

    Component {
        id: settingsPage
        SettingsPage {
            onBackRequested: stack.pop()
        }
    }
}
