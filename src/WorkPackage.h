// Copyright 2020 Bartosz Bilas <bartosz.bilas@hotmail.com>

#ifndef WORKPACKAGE_H_
#define WORKPACKAGE_H_

#include <QObject>
#include <QDataStream>

typedef struct {
    QString projectName = QStringLiteral("Project Name");
    QString taskName = QStringLiteral("Task Name");
    int activityTime = 0;
    bool active = false;
} WorkPackageDescription;

Q_DECLARE_METATYPE(WorkPackageDescription)

class WorkPackage : public QObject {
    Q_OBJECT

    Q_PROPERTY(QString projectName READ projectName WRITE setProjectName NOTIFY projectNameChanged)
    Q_PROPERTY(QString taskName READ taskName WRITE setTaskName NOTIFY taskNameChanged)
    Q_PROPERTY(int expiredTime READ activityTime WRITE setActivityTime NOTIFY activityTimeChanged)
    Q_PROPERTY(bool active READ active WRITE setActive NOTIFY activeChanged)

 public:
    explicit WorkPackage(QObject *parent = nullptr);
    explicit WorkPackage(const WorkPackage &other);
    explicit WorkPackage(const WorkPackageDescription &config, QObject *parent = nullptr);

    ~WorkPackage();

    QString projectName() const;
    void setProjectName(const QString &projectName);

    QString taskName() const;
    void setTaskName(const QString &taskName);

    int activityTime() const;
    void setActivityTime(const int activityTime);

    bool active() const;
    void setActive(const bool active);

    const WorkPackageDescription* config();

 private:
    WorkPackageDescription mConfig;

 signals:
    void projectNameChanged();
    void taskNameChanged();
    void activityTimeChanged();
    void activeChanged();
};

Q_DECLARE_METATYPE(WorkPackage)

QDataStream& operator<<(QDataStream& out, const WorkPackageDescription& v);
QDataStream& operator>>(QDataStream& in, WorkPackageDescription& v);

#endif  // WORKPACKAGE_H_
