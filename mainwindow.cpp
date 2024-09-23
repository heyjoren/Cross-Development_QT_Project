#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "smiley.h"
#include "task.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->smiley->setMood(Smiley::Blij);

    // TEST functie's task
    auto taak = new task();

    taak->SetTitle("test");


    qDebug() << taak->getTitle();

    taak->SetTodo("werkt het?");

    qDebug() << taak->getTodo();

    qDebug() << taak->getKlaarStatus();

    // TEST tot hier

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionexit_triggered()
{
    QApplication::quit();
}

