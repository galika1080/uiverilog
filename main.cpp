#include "workspace.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Workspace w;
    w.show();
    return a.exec();
}
