// Copyright 2020 Bartosz Bilas <bartosz.bilas@hotmail.com>
pragma Singleton
import QtQuick
import TasksManager

QtObject {
    readonly property bool dark: AppSettings.theme === AppSettings.Dark
                                 || (AppSettings.theme === AppSettings.System
                                     && Qt.styleHints.colorScheme === Qt.ColorScheme.Dark)

    // Surfaces
    readonly property color background: dark ? "#0e1014" : "#f4f5f8"
    readonly property color surface: dark ? "#171a20" : "#ffffff"
    readonly property color surfaceHover: dark ? "#1d2129" : "#fafbfc"
    readonly property color field: dark ? "#1f232b" : "#f0f2f5"
    readonly property color hover: dark ? Qt.rgba(1, 1, 1, 0.06) : Qt.rgba(0, 0, 0, 0.05)
    readonly property color pressed: dark ? Qt.rgba(1, 1, 1, 0.10) : Qt.rgba(0, 0, 0, 0.09)
    readonly property color border: dark ? "#262a33" : "#e6e8ee"
    readonly property color borderStrong: dark ? "#3a404b" : "#c9ced8"
    readonly property color inverseSurface: dark ? "#e9ebf0" : "#191c22"
    readonly property color inverseText: dark ? "#14171c" : "#f3f4f7"

    // Text
    readonly property color text: dark ? "#eceef2" : "#15181d"
    readonly property color textMuted: dark ? "#8a919e" : "#6a7180"
    readonly property color textFaint: dark ? "#5b616c" : "#a0a6b1"

    // Accents
    readonly property color accent: dark ? "#8b8ff8" : "#5b5ff0"
    readonly property color accentStrong: dark ? "#a5a8fb" : "#4a4ed8"
    readonly property color accentEnd: dark ? "#c084fc" : "#a855f7"
    readonly property color accentSoft: dark ? Qt.rgba(0.545, 0.561, 0.973, 0.14) : "#eeefff"
    readonly property color accentForeground: "#ffffff"
    readonly property color success: dark ? "#34d399" : "#0ea371"
    readonly property color successSoft: dark ? Qt.rgba(0.204, 0.827, 0.6, 0.13) : "#e5f7f0"
    readonly property color warning: dark ? "#fbbf24" : "#d97706"
    readonly property color warningSoft: dark ? Qt.rgba(0.984, 0.749, 0.141, 0.13) : "#fdf3e1"
    readonly property color danger: dark ? "#f87171" : "#e5484d"
    readonly property color dangerSoft: dark ? Qt.rgba(0.973, 0.443, 0.443, 0.13) : "#fdeceb"

    // Metrics
    readonly property int radiusSmall: 8
    readonly property int radius: 12
    readonly property int radiusLarge: 18
    readonly property int spacing: 12
    readonly property int pagePadding: 28
    readonly property int animationFast: 120
    readonly property int animation: 220

    // Tabular figures keep running timers from jittering.
    readonly property var tabularFigures: ({ "tnum": 1 })
}
