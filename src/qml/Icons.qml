// Copyright 2020 Bartosz Bilas <bartosz.bilas@hotmail.com>
pragma Singleton
import QtQuick

// 24x24 stroke icon paths, rendered by Icon.qml.
QtObject {
    readonly property string play: "M8 5.5v13a1 1 0 0 0 1.5 .86l10.5-6.5a1 1 0 0 0 0-1.72L9.5 4.64A1 1 0 0 0 8 5.5z"
    readonly property string pause: "M7 5h3.2v14H7z M13.8 5H17v14h-3.2z"
    readonly property string plus: "M12 5v14 M5 12h14"
    readonly property string trash: "M4 7h16 M10 11v6 M14 11v6 M6 7l1 12a2 2 0 0 0 2 2h6a2 2 0 0 0 2-2l1-12 M9 7V4h6v3"
    readonly property string reset: "M3 12a9 9 0 1 0 2.64-6.36L3 8.27 M3 3v5.27h5.27"
    readonly property string search: "M4 11a7 7 0 1 0 14 0a7 7 0 1 0 -14 0 M20 20l-3.5-3.5"
    readonly property string settings: "M4 7h9 M17 7h3 M15 5v4 M4 17h3 M11 17h9 M9 15v4"
    readonly property string back: "M15 18l-6-6 6-6"
    readonly property string check: "M5 12.5l4.5 4.5L19 7.5"
    readonly property string minus: "M6 12h12"
    readonly property string close: "M6 6l12 12 M18 6L6 18"
    readonly property string clock: "M3 12a9 9 0 1 0 18 0a9 9 0 1 0 -18 0 M12 7v5l3.5 2"
    readonly property string folder: "M3 7a2 2 0 0 1 2-2h4l2 2h8a2 2 0 0 1 2 2v8a2 2 0 0 1-2 2H5a2 2 0 0 1-2-2z"
}
