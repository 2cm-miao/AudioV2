#include "playerInterface.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
     
    AudioV2 w;
    w.show();
    return a.exec();
}