#include "Tomato.h"

#include <QApplication>

#pragma comment(lib, "user32.lib")

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Tomato w;
    w.show();
    return QApplication::exec();
}
