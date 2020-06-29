#ifndef MPVRADIO_OPEN_H
#define MPVRADIO_OPEN_H

#include <QDialog>

namespace Ui {
class mpvradio_open;
}

class mpvradio_open : public QDialog
{
    Q_OBJECT

public:
    explicit mpvradio_open(QWidget *parent = nullptr);
    ~mpvradio_open();
    std::string url;

private slots:
    void on_buttonBox_accepted();

private:
    Ui::mpvradio_open *ui;
};

#endif // MPVRADIO_OPEN_H
