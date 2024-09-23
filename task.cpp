#include "task.h"
#include "ui_task.h"

task::task(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::task)
{
    ui->setupUi(this);
}

task::~task()
{
    delete ui;
}

QString task::getTitle()
{
    QString title;
    title = ui->grBoxTitle->title();

    title = title.remove(0,7);
    return title;
}

void task::SetTitle(QString title)
{
    QString fullTitle = "Title: " + title;
    ui->grBoxTitle->setTitle(fullTitle);
}

QString task::getTodo()
{
    QString todo;
    todo = ui->lbTodo->text();
    return todo;
}

void task::SetTodo(QString todo)
{
    ui->lbTodo->setText(todo);
}

bool task::getKlaarStatus()
{
    bool status;
    status = ui->chBoxKlaar->checkState();
    return status;
}

QPushButton* task::getDeleteButton()
{
    return ui->pbDelete;
}
