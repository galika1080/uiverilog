#ifndef WORKSPACE_H
#define WORKSPACE_H

#include <QMainWindow>

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
};
#endif // WORKSPACE_H
