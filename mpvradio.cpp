#include "mpvradio.h"
#include "ui_mpvradio.h"
#include "mpvradio_open.h"

mpvradio::mpvradio(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::mpvradio)
{
    ui->setupUi(this);
    this->timer = new QTimer(this);
    connect(this->timer, &QTimer::timeout, this, &mpvradio::update_label);
    this->timer->start(1000);
}

mpvradio::~mpvradio()
{
    delete ui;
}


void mpvradio::on_actionExit_triggered()
{
    exit(EXIT_SUCCESS);
}

void mpvradio::on_actionOpen_URL_triggered()
{
    mpvradio_open stream_dialog;

    if (stream_dialog.exec())
        this->mpv.play_url(stream_dialog.url.c_str());
}

void mpvradio::update_label()
{
    this->mpv.update_track();
    ui->txt_title->setText(this->mpv.current_track);
    setWindowTitle(this->mpv.current_track);
}

void mpvradio::on_pause_btn_clicked()
{
    static int paused = 0;

    if (paused)
    {
        paused = 0;
        mpv_set_property_string(this->mpv.handle, "pause", "no");
    }
    else
    {
        paused = 1;
        mpv_set_property_string(this->mpv.handle, "pause", "yes");
    }
}
