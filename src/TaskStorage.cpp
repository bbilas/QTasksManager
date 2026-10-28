// Copyright 2020 Bartosz Bilas <bartosz.bilas@hotmail.com>

#include "TaskStorage.h"

#include <QDataStream>
#include <QMetaType>
#include <QSettings>

namespace {

constexpr auto kTasksKey = "tasks";
constexpr auto kLegacyKey = "workPackages";

// Mirrors the 1.x on-disk format: qint32 count followed by
// (QString project, QString task, qint32 seconds, bool active) records.
struct LegacyTaskList {
    QList<Task> tasks;
};

QDataStream &operator<<(QDataStream &out, const LegacyTaskList &list) {
    out << qint32(list.tasks.size());
    for (const Task &task : list.tasks)
        out << task.project << task.name << qint32(task.seconds) << task.running;
    return out;
}

QDataStream &operator>>(QDataStream &in, LegacyTaskList &list) {
    qint32 count = 0;
    in >> count;
    for (qint32 i = 0; i < count && in.status() == QDataStream::Ok; ++i) {
        Task task;
        qint32 seconds = 0;
        in >> task.project >> task.name >> seconds >> task.running;
        task.seconds = seconds;
        list.tasks.append(task);
    }
    return in;
}

}  // namespace

Q_DECLARE_METATYPE(LegacyTaskList)

namespace {

// The blob is tagged with its 1.x type name. QSettings decodes every value as
// soon as the file is first read, so the alias must exist before any QSettings
// is used anywhere in the process.
void registerLegacyType() {
    qRegisterMetaType<LegacyTaskList>("WorkPackagesDescription");
}
Q_CONSTRUCTOR_FUNCTION(registerLegacyType)

QList<Task> loadLegacy(QSettings &settings) {
    return settings.value(kLegacyKey).value<LegacyTaskList>().tasks;
}

}  // namespace

namespace TaskStorage {

QList<Task> load(QSettings &settings) {
    QList<Task> tasks;

    if (!settings.childGroups().contains(kTasksKey)) {
        if (!settings.contains(kLegacyKey))
            return tasks;

        tasks = loadLegacy(settings);
        // Keep the legacy blob untouched so a downgrade does not lose data.
        save(settings, tasks);
        settings.sync();
        return tasks;
    }

    const int size = settings.beginReadArray(kTasksKey);
    tasks.reserve(size);
    for (int i = 0; i < size; ++i) {
        settings.setArrayIndex(i);
        Task task;
        const QUuid id = QUuid::fromString(settings.value("id").toString());
        if (!id.isNull())
            task.id = id;
        task.project = settings.value("project").toString();
        task.name = settings.value("name").toString();
        task.seconds = settings.value("seconds").toLongLong();
        task.running = settings.value("running").toBool();
        tasks.append(task);
    }
    settings.endArray();

    return tasks;
}

void save(QSettings &settings, const QList<Task> &tasks) {
    settings.remove(kTasksKey);
    settings.beginWriteArray(kTasksKey, int(tasks.size()));
    for (int i = 0; i < tasks.size(); ++i) {
        const Task &task = tasks.at(i);
        settings.setArrayIndex(i);
        settings.setValue("id", task.id.toString(QUuid::WithoutBraces));
        settings.setValue("project", task.project);
        settings.setValue("name", task.name);
        settings.setValue("seconds", task.seconds);
        settings.setValue("running", task.running);
    }
    settings.endArray();
}

}  // namespace TaskStorage
