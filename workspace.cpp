#include "workspace.h"
#include "ui_workspace.h"

Workspace::Workspace(QWidget *parent) : QMainWindow(parent) , ui(new Ui::Workspace) {
    ui->setupUi(this);
}

Workspace::~Workspace() {
    delete ui;
}

void Workspace::makeModule(Module* m) {
    qDebug() << QString::fromStdString(m->id);
}
