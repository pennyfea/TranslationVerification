#include "widgetwindow.h"
#include "qonlinetranslator.h"
#include "addlanguagedialog.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    widgetwindow w;
    w.show();
    return a.exec();
}
