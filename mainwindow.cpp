#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->smiley->setMood(Smiley::Blij);

    //verwijder test en test in header
    test = 0;

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionexit_triggered()
{
    QApplication::quit();
}


void MainWindow::on_pbAddTask_clicked()
{
    auto taak = new task();
    m_listTask.append(taak);

    taak->SetTitle(QString::number(test));

    ui->tasksLayout->insertWidget(ui->tasksLayout->count() -1, taak);

    connect(taak->getDeleteButton(), &QPushButton::clicked, this, [=]() {
        onTaskDeleted(taak);
    });

    test ++;

}

void MainWindow::onTaskDeleted(task* taak)
{
    m_listTask.removeOne(taak);

    ui->scrollAreaWidgetContents->layout()->removeWidget(taak);

    taak->deleteLater();
}

