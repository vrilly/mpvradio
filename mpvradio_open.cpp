#include "mpvradio_open.h"
#include "ui_mpvradio_open.h"

mpvradio_open::mpvradio_open(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::mpvradio_open)
{
    ui->setupUi(this);
}

mpvradio_open::~mpvradio_open()
{
    delete ui;
}

void mpvradio_open::on_buttonBox_accepted()
{
    this->url = ui->stream_url_input->text().toStdString();
}
