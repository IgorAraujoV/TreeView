#include "treeapp.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TreeApp w;
    w.show();

    return a.exec();
}
