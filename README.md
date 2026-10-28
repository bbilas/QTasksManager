# QTasksManager [![Build Status](https://travis-ci.com/bbilas/QTasksManager.svg?branch=master)](https://travis-ci.com/bbilas/QTasksManager) [![AUR package](https://repology.org/badge/version-for-repo/aur/qtasksmanager.svg)](https://repology.org/project/qtasksmanager/versions)
QTasksManager is a graphical application, written in Qt 6 / QML that can help you organize all your tasks and count how much time you've spent on them.

# Features

  - Modern Qt Quick UI with light/dark theme (follows the system color scheme)
  - Multi-select with checkboxes and bulk delete, search across tasks
  - Pauses running timers while the screen is locked and resumes them afterwards
    (Cinnamon, GNOME, freedesktop screensavers and systemd-logind)
  - Notification about starting overhours (defined in settings)
  - Keyboard shortcuts: Ctrl+N new task, Ctrl+F search, Delete removes selected, Esc clears selection

TODO:
  - Add missing unit tests...
  - Synchronization with OpenProject
  - Exporting data to CSV sheet
  - Windows support
  - suggest what you need  ;)

### Installation (Arch Linux)

QTasksManager is available on the AUR repository so you can easily install the application using e.g yay

```sh
$ yay -S qtasksmanager
```

### Development

Feel free to send PRs with the new functionality that you want to have :)

### Building from sources
Requirements: CMake >= 3.21, a C++17 compiler and Qt >= 6.6 (Core, DBus, Gui, Qml, Quick, QuickControls2, Widgets).

Tasks saved by QTasksManager 1.x are migrated automatically on first start.

For release type:
```sh
$ git clone https://github.com/bbilas/QTasksManager
$ cd QTasksManager
$ mkdir build && cd build
$ cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=/usr -Wno-dev ..
$ make install
```

For debug type:
```sh
$ git clone https://github.com/bbilas/QTasksManager
$ cd QTasksManager
$ mkdir build && cd build
$ cmake -DCMAKE_BUILD_TYPE=Debug -DCMAKE_INSTALL_PREFIX=/usr ..
$ make install
```

License
----

 GPL-3.0


**Free Software, Hell Yeah!**

