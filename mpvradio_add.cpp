#include "mpvradio_add.h"
#include "ui_mpvradio_add.h"

mpvradio_add::mpvradio_add(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::mpvradio_add)
{
    ui->setupUi(this);
}

mpvradio_add::~mpvradio_add()
{
    delete ui;
}

void mpvradio_add::on_buttonBox_accepted()
{
    this->result.channel_name =
            this->ui->name_input->text();
    this->result.channel_url =
            this->ui->url_input->text();
}
