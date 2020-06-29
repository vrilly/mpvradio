#include "mpvradio.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    mpvradio w;
    w.show();
    return a.exec();
}
