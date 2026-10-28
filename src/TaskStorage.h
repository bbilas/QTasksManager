// Copyright 2020 Bartosz Bilas <bartosz.bilas@hotmail.com>

#ifndef TASKSTORAGE_H
#define TASKSTORAGE_H

#include <QList>
#include "Task.h"

class QSettings;

namespace TaskStorage {

// Loads tasks from the settings file. Data written by QTasksManager 1.x (a
// binary "workPackages" blob) is migrated transparently on first load.
QList<Task> load(QSettings &settings);
void save(QSettings &settings, const QList<Task> &tasks);

}  // namespace TaskStorage

#endif  // TASKSTORAGE_H
