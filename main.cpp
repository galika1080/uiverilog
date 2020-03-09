#include "workspace.h"
#include "compiler.h"
#include "module.h"

#include <QApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Workspace w;
    w.show();

    Compiler c{};

    std::vector<std::pair<int, int>> positions;
    Module* m1 = new Module("and", "a1", 3, positions);
    Module* m2 = new Module("or", "o1", 3, positions);

    c.addMod(m1);
    c.addMod(m2);

    c.connect(0, 0, 1, 0, "wire_out");
    c.connect(m1, 2, m2, 2, "wire_in");
    
    c.addOutput("wire_out");
    c.addInput("wire_in");

    c.sever("wire_one");
    c.sever("this_wire_doesn't_exist");

    c.compile("\\Users\\epics\\Documents\\GitHub\\uiverilog\\output.v");

    return a.exec();
}
