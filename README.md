# QTasksManager [![Build Status](https://travis-ci.com/bbilas/QTasksManager.svg?branch=master)](https://travis-ci.com/bbilas/QTasksManager) [![AUR package](https://repology.org/badge/version-for-repo/aur/qtasksmanager.svg)](https://repology.org/project/qtasksmanager/versions)
QTasksManager is a graphical application, written in Qt5 that can help you organize all your tasks and count how much time you've spent on them.

# Features

  - Support of Cinnamon screensaver for pausing/restoring task counting automatically
  - Notification about starting overhours (defined in settings)

TODO:
  - Add missing unit tests...
  - Synchronization with OpenProject
  - Exporting data to CSV sheet
  - Windows support
  - Dark mode
  - suggest what you need  ;)

### Installation (Arch Linux)

QTasksManager is available on the AUR repository so you can easily install the application using e.g yay

```sh
$ yay -S qtasksmanager
```

### Development

Feel free to send PRs with the new functionality that you want to have :)

### Building from sources
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

