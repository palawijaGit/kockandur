#include <QtGui/QApplication>
#include "aranyositator.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    aranyositator w;
    w.show();
    return a.exec();
}
