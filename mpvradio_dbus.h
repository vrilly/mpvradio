#ifndef MPVRADIO_DBUS_H
#define MPVRADIO_DBUS_H

#include <QDBusAbstractAdaptor>
#include <QDBusConnection>
#include <QDBusContext>
#include <QDBusObjectPath>
#include <QTimer>
#include <QMap>
#include "mpv_control.h"

typedef QMap<QString, QDBusVariant> StringMap;
Q_DECLARE_METATYPE(StringMap);

class mpvradio_dbus : public QDBusAbstractAdaptor
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "org.mpris.MediaPlayer2")
    Q_PROPERTY(bool CanQuit READ get_false)
    Q_PROPERTY(bool CanRaise READ get_false)
    Q_PROPERTY(bool HasTrackList READ get_false)
    Q_PROPERTY(QString Identity READ get_name)
    Q_PROPERTY(QStringList SupportedUriSchemes READ get_uri)
    Q_PROPERTY(QStringList SupportedMimeTypes READ get_mime)
public:
    mpvradio_dbus(QObject *obj);
    bool get_true();
    bool get_false();
    QString get_name();
    QStringList get_uri();
    QStringList get_mime();
};

class mpvradio_dbus_player : public QDBusAbstractAdaptor
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "org.mpris.MediaPlayer2.Player")
    Q_PROPERTY(bool CanGoNext READ get_false)
    Q_PROPERTY(bool CanGoPrevious READ get_false)
    Q_PROPERTY(bool CanSeek READ get_false)
    Q_PROPERTY(bool CanControl READ get_true)
    Q_PROPERTY(bool CanPlay READ get_true)
    Q_PROPERTY(bool CanPause READ get_true)
    Q_PROPERTY(double MinimumRate READ get_true)
    Q_PROPERTY(double MaximumRate READ get_true)
    Q_PROPERTY(qlonglong Position READ get_false)
    Q_PROPERTY(double Volume READ get_rate)
    Q_PROPERTY(double Rate READ get_rate)
    Q_PROPERTY(QString PlaybackStatus READ get_playbackstatus WRITE set_playbackstatus)
    Q_PROPERTY(StringMap MetaData READ get_metadata)
private:
    mpv_control *mpv;
public slots:
    void Pause();
    void PlayPause();
    void Play();
    void Stop();
public:
    bool get_true();
    bool get_false();
    double get_rate();
    QString get_playbackstatus();
    void set_playbackstatus(QString newstr);
    QMap<QString, QDBusVariant> get_metadata();
    mpvradio_dbus_player(QObject *obj, mpv_control *mpv);
};

class dbus_connector : public QObject, public QDBusContext
{
    Q_OBJECT
private:
    mpvradio_dbus *mpris_mediaplayer;
    mpvradio_dbus_player *mpris_player;
    QDBusConnection *dbus;
public:
    dbus_connector(mpv_control *mpv);
    void update();
};

#endif // MPVRADIO_DBUS_H
