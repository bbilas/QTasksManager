// Copyright 2020 Bartosz Bilas <bartosz.bilas@hotmail.com>

#ifndef TASK_H
#define TASK_H

#include <QString>
#include <QUuid>

struct Task {
    QUuid id = QUuid::createUuid();
    QString project;
    QString name;
    qint64 seconds = 0;
    bool running = false;
    bool selected = false;  // UI state only, never persisted
};

#endif  // TASK_H
