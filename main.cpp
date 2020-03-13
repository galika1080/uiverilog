#include "workspace.h"
#include "compiler.h"
#include "module.h"
#include "FileUtils.hpp"
#include "msbutton.h"

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

    QHBoxLayout* module_selector_layout = w.findChild<QHBoxLayout*>();
    std::vector<Module*> defined_modules = FileUtils::ModulesFromFile("C:\\Users\\epics\\Documents\\GitHub\\uiverilog\\moduleoutput.uiv");

    for (auto & m : defined_modules) {
        QIcon icon(QString::fromStdString(m->symbol));
        MSButton* to_add = new MSButton(icon, "", m);
        to_add->setIconSize(QSize(100, 100));
        to_add->setFixedSize(QSize(100, 100));
        to_add->show();
        module_selector_layout->addWidget(to_add);

		QObject::connect(to_add, SIGNAL (clicked_mod(Module*)), &w, SLOT (makeModule(Module*)));
    }

    Compiler c{};

    return a.exec();
}

void makeModule(Module* m) {

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
