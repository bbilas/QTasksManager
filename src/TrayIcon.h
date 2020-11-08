// Copyright 2020 Bartosz Bilas <bartosz.bilas@hotmail.com>

#ifndef TRAYICON_H
#define TRAYICON_H

#include <QAction>
#include <QObject>
#include <QMenu>
#include <QQuickView>
#include <QSystemTrayIcon>

class TrayIcon : public QSystemTrayIcon {
    Q_OBJECT

 public:
    TrayIcon(QQuickWindow *window);

 private:
   QSharedPointer<QAction> mMinimizeWindowAction;
   QSharedPointer<QAction> mRestoreWindowAction;
   QSharedPointer<QAction> mQuitWindowAction;
   QSharedPointer<QMenu> mTrayIconMenu;

};

#endif // TRAYICON_H