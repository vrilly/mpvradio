#include "mpvradio.h"
#include "ui_mpvradio.h"
#include "mpvradio_open.h"
#include "mpvradio_add.h"

mpvradio::mpvradio(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::mpvradio)
{
    this->channellist = new channel_list_manager();
    this->dbus = new dbus_connector(&this->mpv);
    ui->setupUi(this);
    ui->channelView->setModel(this->channellist);
    this->timer = new QTimer(this);
    connect(this->timer, &QTimer::timeout, this, &mpvradio::update_label);
    this->timer->start(1000);
}

mpvradio::~mpvradio()
{
    this->mpv.end();
    delete this->channellist;
    delete this->dbus;
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
    this->dbus->update();
}

void mpvradio::update_label()
{
    this->mpv.update_track();
    ui->txt_title->setText(this->mpv.current_track);
    setWindowTitle(this->mpv.current_track);
}

void mpvradio::on_actionAdd_triggered()
{
    mpvradio_add add_dialog;

    if (add_dialog.exec())
    {
        this->channellist->channels.append(add_dialog.result);
        this->channellist->write_config();
    }
}

void mpvradio::on_channelView_doubleClicked(const QModelIndex &index)
{
    list_item item = this->channellist->channels.at(index.row());
    this->mpv.play_url(item.channel_url.toStdString().c_str());
    this->dbus->update();
}

void mpvradio::on_actionDelete_triggered()
{
    int row = ui->channelView->selectionModel()->currentIndex().row();
    this->channellist->channels.removeAt(row);
    this->channellist->write_config();
    ui->actionDelete->setEnabled(false);
}

void mpvradio::on_channelView_clicked(const QModelIndex &index)
{
    (void)index;
    ui->actionDelete->setEnabled(true);
}

void mpvradio::on_pause_btn_clicked()
{
    this->mpv.toggle_pause();
    this->dbus->update();
}
