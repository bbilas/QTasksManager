// Copyright 2020 Bartosz Bilas <bartosz.bilas@hotmail.com>

#ifndef TRAYICON_H
#define TRAYICON_H

#include <QMenu>
#include <QPointer>
#include <QSystemTrayIcon>

class QAction;
class QWindow;
class TaskModel;

class TrayIcon : public QSystemTrayIcon {
    Q_OBJECT

 public:
    TrayIcon(QWindow *window, TaskModel *model, QObject *parent = nullptr);

 public slots:
    void showOvertimeMessage(const QString &totalTime);

 private:
    void onActivated(QSystemTrayIcon::ActivationReason reason);
    void toggleWindow();
    void updateToolTip();

    QPointer<QWindow> mWindow;
    TaskModel *mModel;
    QMenu mMenu;
    QAction *mToggleAction;
};

#endif  // TRAYICON_H
