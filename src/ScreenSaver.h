#ifndef SCREENSAVER_H
#define SCREENSAVER_H

#include <QObject>
#include "dbus/OrgCinnamonScreenSaver.h"

class ScreenSaver : public QObject
{
    Q_OBJECT
public:
    explicit ScreenSaver(QObject *parent = nullptr);

private:
    QScopedPointer<OrgCinnamonScreenSaverInterface> mOrgCinnamonScreenSaverInterface;

signals:
    void activeChanged(bool active);
};

#endif // SCREENSAVER_H
