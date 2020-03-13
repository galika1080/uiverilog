#pragma once

#include <QMainWindow>
#include <QDebug>

#include "module.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Workspace; }
QT_END_NAMESPACE

class Workspace : public QMainWindow
{
    Q_OBJECT

public:
    Workspace(QWidget *parent = nullptr);
    ~Workspace();

private:
    Ui::Workspace *ui;

public slots:
	void makeModule(Module* m);
};
