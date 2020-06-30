#include "mpvradio_dbus.h"
#include <QDBusError>
#include <QDBusMessage>
#include <QTimer>
#include <iostream>
#include <QDBusMetaType>

bool mpvradio_dbus::get_true()
{
    return (1);
}

bool mpvradio_dbus::get_false()
{
    return (0);
}

bool mpvradio_dbus_player::get_true()
{
    return (1);
}

bool mpvradio_dbus_player::get_false()
{
    return (0);
}

double mpvradio_dbus_player::get_rate()
{
    return (1.0);
}

QString mpvradio_dbus::get_name()
{
    return ("MPV Radio");
}

QStringList mpvradio_dbus::get_uri()
{
   QStringList list;

    list.append("http");
    list.append("https");

    return (list);
}

QStringList mpvradio_dbus::get_mime()
{
    QStringList list;

    list.append("audio/vorbis");
    list.append("audio/flac");
    list.append("audio/aac");
    list.append("audio/mpeg");

    return (list);
}

QString mpvradio_dbus_player::get_playbackstatus()
{
    return (mpv->paused) ? "Paused" : "Playing";
}

void mpvradio_dbus_player::set_playbackstatus(QString newstr)
{
    (void)newstr;
    QString currstat = (mpv->paused) ? "Paused" : "Playing";
    QDBusMessage msg = QDBusMessage::createSignal(
                "/org/mpris/MediaPlayer2",
                "org.freedesktop.DBus.Properties",
                "PropertiesChanged");
    msg << "org.mpris.MediaPlayer2.Player";
    QVariantMap changedProps;
    changedProps.insert("PlaybackStatus", currstat);
    msg << changedProps;
    changedProps.clear();
    msg << changedProps;
    QDBusConnection::sessionBus().send(msg);
}

void mpvradio_dbus_player::Pause()
{
    this->mpv->toggle_pause();
}

void mpvradio_dbus_player::PlayPause()
{
    this->mpv->toggle_pause();
}

void mpvradio_dbus_player::Play()
{
    this->mpv->toggle_pause();
}

void mpvradio_dbus_player::Stop()
{
    this->mpv->toggle_pause();
}

mpvradio_dbus::mpvradio_dbus(QObject *obj) : QDBusAbstractAdaptor(obj)
{
}

mpvradio_dbus_player::mpvradio_dbus_player(QObject *obj, mpv_control *mpv) : QDBusAbstractAdaptor(obj)
{
    this->mpv = mpv;
}

QMap<QString, QDBusVariant> mpvradio_dbus_player::get_metadata()
{
    QMap<QString, QDBusVariant> map;

    map.insert("mpris:trackid", QDBusVariant(QVariant(QDBusObjectPath("/music/internetradio"))));
    map.insert("xesam:artist", QDBusVariant(QVariant("mpvradio")));
    map.insert("xesam:title", QDBusVariant(QVariant("Internet Radio")));

    return (map);
}

dbus_connector::dbus_connector(mpv_control *mpv)
{
    qDBusRegisterMetaType<StringMap>();
    this->mpris_mediaplayer = new mpvradio_dbus(this);
    this->mpris_player = new mpvradio_dbus_player(this, mpv);
    QDBusConnection::sessionBus().registerObject("/org/mpris/MediaPlayer2", this);
    QDBusConnection::sessionBus().registerService("org.mpris.MediaPlayer2.mpvradio");

}

void dbus_connector::update()
{
    mpris_player->set_playbackstatus("brr");
}
