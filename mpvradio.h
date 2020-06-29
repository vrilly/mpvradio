#ifndef MPVRADIO_H
#define MPVRADIO_H

#include <QMainWindow>
#include <QTimer>
#include <mpv/client.h>

QT_BEGIN_NAMESPACE
namespace Ui { class mpvradio; }
QT_END_NAMESPACE

class mpv_control
{
public:
    mpv_control();
    void play_url(const char *url);
    void update_track();
    void end();
    mpv_handle *handle;
    mpv_handle *client_handle;
    char *current_track;
};

class mpvradio : public QMainWindow
{
    Q_OBJECT

public:
    mpvradio(QWidget *parent = nullptr);
    ~mpvradio();
    char stream_url[256];

private slots:
    void on_actionExit_triggered();

    void on_actionOpen_URL_triggered();

    void update_label();

    void on_pause_btn_clicked();

private:
    Ui::mpvradio *ui;
    mpv_control mpv;
    QTimer *timer;
};

#endif // MPVRADIO_H
