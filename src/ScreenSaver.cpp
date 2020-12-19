#include "ScreenSaver.h"
#include <QDebug>

ScreenSaver::ScreenSaver(QObject *parent) : QObject(parent) {
    mOrgCinnamonScreenSaverInterface.reset(new OrgCinnamonScreenSaverInterface(QStringLiteral("org.cinnamon.ScreenSaver"),
                                                                               QStringLiteral("/org/cinnamon/ScreenSaver"),
                                                                               QDBusConnection::sessionBus()));
    connect(mOrgCinnamonScreenSaverInterface.data(), &OrgCinnamonScreenSaverInterface::ActiveChanged, this, &ScreenSaver::activeChanged);
}
