#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->smiley->setMood(Smiley::Neutraal);

    this->setWindowTitle("To do list");

    ui->stackedWidget->setCurrentWidget(ui->pageHome);

    //TEST
    //verwijder test en test in header en op regel 43
    test = 0;
    // TEST tot hier

    connect(ui->pbAddTask, &QPushButton::clicked,  this, &MainWindow::updateSmileyStatus);

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
    ui->tEditToDo->setText("");
    ui->lETitle->setText("");

    ui->stackedWidget->setCurrentWidget(ui->pageFillIn);
}

void MainWindow::onTaskDeleted(task* taak)
{
    m_listTask.removeOne(taak);

    ui->scrollAreaWidgetContents->layout()->removeWidget(taak);

    taak->deleteLater();
}

void MainWindow::updateSmileyStatus()
{
    int totaal = m_listTask.count();
    int aangevinkt = 0;

    for (const auto& taak : m_listTask) {
        if (taak->getKlaarCheckbox()->isChecked()) {
            aangevinkt++;
        }
    }

    if (totaal == 0) {
        ui->smiley->setMood(Smiley::Neutraal);
        return;
    }

    double percentage = static_cast<double>(aangevinkt) / totaal * 100;

    if (percentage < 40) {
        ui->smiley->setMood(Smiley::Sip);

    } else if (percentage >= 40 && percentage <= 60) {
        ui->smiley->setMood(Smiley::Neutraal);

    } else if (percentage > 60) {
        ui->smiley->setMood(Smiley::Blij);
    }

}


void MainWindow::on_pbBack_clicked()
{

    ui->stackedWidget->setCurrentWidget(ui->pageHome);
}


void MainWindow::on_pbAdd_clicked()
{
    auto taak = new task();
    m_listTask.append(taak);

    taak->SetTitle(ui->lETitle->text());

    ui->tasksLayout->insertWidget(ui->tasksLayout->count() -1, taak);

    connect(taak->getDeleteButton(), &QPushButton::clicked, this, [=]() {
        onTaskDeleted(taak);
        emit taak->statusChanged();
    });

    connect(taak->getKlaarCheckbox(), &QCheckBox::stateChanged, this, [=]() {
        emit taak->statusChanged();
    });

    taak->SetTodo(ui->tEditToDo->toPlainText());

    connect(taak, &task::statusChanged, this, &MainWindow::updateSmileyStatus);

    ui->stackedWidget->setCurrentWidget(ui->pageHome);
}

