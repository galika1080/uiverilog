#include "workspace.h"
#include "compiler.h"
#include "module.h"
#include "FileUtils.hpp"

#include <QApplication>
#include <QDebug>
#include <QScrollArea>
#include <QHBoxLayout>
#include <QPushButton>
#include <QIcon>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    Workspace w;
    w.show();

    Compiler c{};

    qDebug() << w.children();

    QScrollArea* module_selector = w.findChild<QScrollArea*>();
    QHBoxLayout* module_selector_layout = w.findChild<QHBoxLayout*>();

    QIcon icon(":/resources/icon_and.png");
    QPushButton* to_add = new QPushButton(icon, "");
    to_add->setIconSize(QSize(100, 100));
    to_add->setFixedSize(QSize(100, 100));
    to_add->show();

    QIcon icon2(":/resources/icon_or.png");
    QPushButton* to_add2 = new QPushButton(icon2, "");
    to_add2->setIconSize(QSize(100, 100));
    to_add2->setFixedSize(QSize(100, 100));
    to_add2->show();

    module_selector_layout->addWidget(to_add);
    module_selector_layout->addWidget(to_add2);

    std::vector<std::pair<int,int>> positions;

    positions.push_back(std::pair<int,int>(100, 25));
    positions.push_back(std::pair<int,int>(100, 75));
    positions.push_back(std::pair<int,int>(100, 75));
    Module m1("and", "screw your stupid IDE", 3, positions);
    m1.symbol = ":resources/icon_and.png";

    //FileUtils::ModuleToFile(m1, "C:\\Users\\epics\\Documents\\GitHub\\uiverilog\\moduleoutput.uiv");

    std::vector<Module*> heck_yeah = FileUtils::ModulesFromFile("C:\\Users\\epics\\Documents\\GitHub\\uiverilog\\moduleoutput.uiv");

    int i = 0;
    i = 2 * 4;
    return a.exec();
}

void exampleStuff(Compiler & c) {
    std::vector<std::pair<int, int>> positions;
    Module* m1 = new Module("and", "a1", 3, positions);
    Module* m2 = new Module("or", "o1", 3, positions);

    c.addMod(m1);
    c.addMod(m2);

    c.connect(m1, 0, m2, 0, "wire_out");
    c.connect(m1, 1, m2, 1, "wire_in");

    c.addOutput("wire_out");
    c.addInput("wire_in");

    c.sever("wire_in");
    c.removeInput("wire_in");

    c.compile("\\Users\\epics\\Documents\\GitHub\\uiverilog\\output.v");
}
