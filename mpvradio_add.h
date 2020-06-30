#ifndef MPVRADIO_ADD_H
#define MPVRADIO_ADD_H

#include <QDialog>
#include "channel_list_manager.h"

namespace Ui {
class mpvradio_add;
}

class mpvradio_add : public QDialog
{
    Q_OBJECT

public:
    explicit mpvradio_add(QWidget *parent = nullptr);
    ~mpvradio_add();

    list_item result;

private slots:
    void on_buttonBox_accepted();

private:
    Ui::mpvradio_add *ui;
};

#endif // MPVRADIO_ADD_H
