// Copyright 2020 Bartosz Bilas <bartosz.bilas@hotmail.com>
import QtQuick
import QtQuick.Controls.Basic
import QtQuick.Layouts
import TasksManager

Page {
    id: page

    signal backRequested()

    background: Rectangle { color: Theme.background }

    Shortcut { sequences: [StandardKey.Back, "Escape"]; onActivated: page.backRequested() }

    Flickable {
        anchors.fill: parent
        contentHeight: column.implicitHeight + Theme.pagePadding * 2
        boundsBehavior: Flickable.StopAtBounds
        ScrollBar.vertical: ScrollBar {}

        ColumnLayout {
            id: column
            width: Math.min(680, page.width - Theme.pagePadding * 2)
            x: (page.width - width) / 2
            y: Theme.pagePadding - 4
            spacing: 10

            RowLayout {
                Layout.fillWidth: true
                Layout.bottomMargin: 12
                spacing: 8

                IconButton {
                    Layout.leftMargin: -8
                    iconPath: Icons.back
                    iconSize: 22
                    toolTip: qsTr("Back")
                    onClicked: page.backRequested()
                }
                Text {
                    text: qsTr("Settings")
                    color: Theme.text
                    font.pixelSize: 28
                    font.weight: Font.Bold
                    font.letterSpacing: -0.5
                }
            }

            SectionLabel { text: qsTr("Tracking") }

            Card {
                Layout.fillWidth: true

                SettingRow {
                    title: qsTr("Daily working time")
                    description: qsTr("You get a notification once the total tracked time goes past it.")

                    TextField {
                        id: dailyTime
                        implicitWidth: 112
                        implicitHeight: 36
                        horizontalAlignment: Text.AlignHCenter
                        inputMask: "99:99:99"
                        text: AppSettings.dailyWorkingTime
                        color: acceptableInput ? Theme.text : Theme.danger
                        font.features: Theme.tabularFigures
                        font.pixelSize: 15
                        selectByMouse: true
                        selectionColor: Theme.accent
                        selectedTextColor: Theme.accentForeground
                        validator: RegularExpressionValidator { regularExpression: /([01]\d|2[0-3]):[0-5]\d:[0-5]\d/ }
                        background: Rectangle {
                            radius: Theme.radiusSmall
                            color: Theme.field
                            border.width: dailyTime.activeFocus ? 1 : 0
                            border.color: Theme.accent
                        }
                        onEditingFinished: {
                            AppSettings.dailyWorkingTime = text
                            text = Qt.binding(() => AppSettings.dailyWorkingTime)
                        }
                    }
                }

                SettingRow {
                    title: qsTr("Pause timers when the screen locks")
                    description: qsTr("Running tasks are paused while the screensaver or lock screen is active and resume after unlocking.")

                    AppSwitch {
                        checked: AppSettings.pauseOnScreenLock
                        onToggled: AppSettings.pauseOnScreenLock = checked
                    }
                }

                SettingRow {
                    title: qsTr("Resume running tasks at startup")
                    description: qsTr("Tasks that were running when the app was closed keep running after it starts again.")
                    showDivider: false

                    AppSwitch {
                        checked: AppSettings.restoreRunningOnStartup
                        onToggled: AppSettings.restoreRunningOnStartup = checked
                    }
                }
            }

            SectionLabel {
                Layout.topMargin: 14
                text: qsTr("Appearance")
            }

            Card {
                Layout.fillWidth: true

                SettingRow {
                    title: qsTr("Theme")
                    description: qsTr("Follow the system color scheme or pick one.")
                    showDivider: false

                    SegmentedControl {
                        model: [qsTr("System"), qsTr("Light"), qsTr("Dark")]
                        currentIndex: AppSettings.theme
                        onActivated: index => AppSettings.theme = index
                    }
                }
            }

            Text {
                Layout.alignment: Qt.AlignHCenter
                Layout.topMargin: 20
                text: qsTr("QTasksManager %1").arg(AppSettings.version)
                color: Theme.textFaint
                font.pixelSize: 12
            }
        }
    }

    component SectionLabel: Text {
        Layout.leftMargin: 4
        color: Theme.textMuted
        font.pixelSize: 12
        font.weight: Font.DemiBold
        font.letterSpacing: 1.1
        font.capitalization: Font.AllUppercase
    }
}
