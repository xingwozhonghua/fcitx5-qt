/*
 * SPDX-FileCopyrightText: 2012~2017 CSSlayer <wengxt@gmail.com>
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef _DBUSADDONS_FCITXQTINPUTCONTEXTPROXY_H_
#define _DBUSADDONS_FCITXQTINPUTCONTEXTPROXY_H_

#include "fcitx5qt4dbusaddons_export.h"

#include "fcitxqtdbustypes.h"
#include <QDBusConnection>
#include <QDBusPendingReply>
#include <QDBusServiceWatcher>
#include <QObject>

class QDBusPendingCallWatcher;

namespace fcitx {

class FcitxQtWatcher;
class FcitxQtInputContextProxyPrivate;

class FCITX5QT4DBUSADDONS_EXPORT FcitxQtInputContextProxy : public QObject {
    Q_OBJECT
public:
    FcitxQtInputContextProxy(FcitxQtWatcher *watcher, QObject *parent);
    ~FcitxQtInputContextProxy();

    bool isValid() const;
    void setDisplay(const QString &display);
    const QString &display() const;

public slots:
    QDBusPendingReply<> focusIn();
    QDBusPendingReply<> focusOut();
    QDBusPendingReply<bool> processKeyEvent(uint keyval, uint keycode,
                                            uint state, bool type, uint time);
    QDBusPendingReply<> reset();
    QDBusPendingReply<> setCapability(qulonglong caps);
    QDBusPendingReply<> setCursorRect(int x, int y, int w, int h);
    QDBusPendingReply<> setSurroundingText(const QString &text, uint cursor,
                                           uint anchor);
    QDBusPendingReply<> setSurroundingTextPosition(uint cursor, uint anchor);

signals:
    void commitString(const QString &str);
    void currentIM(const QString &name, const QString &uniqueName,
                   const QString &langCode);
    void deleteSurroundingText(int offset, uint nchar);
    void forwardKey(uint keyval, uint state, bool isRelease);
    void updateFormattedPreedit(const FcitxQtFormattedPreeditList &str,
                                int cursorpos);
    void inputContextCreated(const QByteArray &uuid);

private:
    Q_PRIVATE_SLOT(d_func(), void availabilityChanged());
    Q_PRIVATE_SLOT(d_func(), void recheck());
    Q_PRIVATE_SLOT(d_func(), void cleanUp());
    Q_PRIVATE_SLOT(d_func(), void serviceUnregistered());
    Q_PRIVATE_SLOT(d_func(), void createInputContextFinished());

    FcitxQtInputContextProxyPrivate *const d_ptr;
    Q_DECLARE_PRIVATE(FcitxQtInputContextProxy);
};

} // namespace fcitx

#endif // _DBUSADDONS_FCITXQTINPUTCONTEXTPROXY_H_
