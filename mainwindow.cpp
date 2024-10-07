#include "mainwindow.h"
#include "ui_mainwindow.h"

/*
 * Tool typs zijn voor knoppen niet menu acties.
 *
*/

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->smiley->setMood(Smiley::Neutraal);

    this->setWindowTitle("To do list");

    setHomeScreen();

    connect(ui->pbAddTask, &QPushButton::clicked, this, &MainWindow::setTaskScreen);
    connect(ui->pbBack, &QPushButton::clicked, this, &MainWindow::setHomeScreen);
    connect(ui->aHomePage, &QAction::triggered, this, &MainWindow::setHomeScreen);
    connect(ui->aAddTask, &QAction::triggered, this, &MainWindow::setTaskScreen);

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

    _percentage = static_cast<double>(aangevinkt) / totaal * 100;

    if (_percentage < 40) {
        ui->smiley->setMood(Smiley::Sip);

    } else if (_percentage >= 40 && _percentage <= 60) {
        ui->smiley->setMood(Smiley::Neutraal);

    } else if (_percentage > 60) {
        ui->smiley->setMood(Smiley::Blij);
    }

}

void MainWindow::on_pbAdd_clicked()
{
    if(ui->lETitle->text().isEmpty())
    {
        QMessageBox::critical(this, "Error", "Het titelveld mag niet leeg zijn. Vul een titel in voordat je een taak toevoegt.");
    }
    else {
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

        updateSmileyStatus();

        ui->stackedWidget->setCurrentWidget(ui->pageHome);
    }
}

void MainWindow::setHomeScreen()
{
    ui->stackedWidget->setCurrentWidget(ui->pageHome);
}

void MainWindow::setTaskScreen()
{
    ui->tEditToDo->setText("");
    ui->lETitle->setText("");

    ui->stackedWidget->setCurrentWidget(ui->pageFillIn);
}


void MainWindow::on_actionsave_triggered()
{


    if(_fileInfo.filePath().isEmpty())
    {
        auto selectFile = new Selectfile;

        selectFile->setWindowTitle("Choose a file to save");

        int result = selectFile->exec();


        if (result == QDialog::Accepted)
        {
            _fileInfo =  selectFile->getFileInfo();
            selectFile->deleteLater();
            saveToFile();
        }
    }

}


void MainWindow::on_actionopen_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(
        this,
        "Open File",
        "",
        "Text Files (*.txt);;All Files (*)"
        );

    if (fileName.isEmpty()) {
        QMessageBox::critical(this, "Error", "No file selected ");
    }
    else
    {
        QFileInfo fileInfo (fileName);

        _fileInfo = fileInfo;

        QFile file(_fileInfo.filePath());

        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QMessageBox::critical(this, "Error", "Could not open file: " + file.errorString());
        }
        else
        {
            QTextStream in(&file);

            QString title;
            QString todo;
            bool completed, add = false;


            while (!in.atEnd()) {
                QString line = in.readLine();
                if (line.startsWith("Title: ")) {
                    title = line.mid(7);
                } else if (line.startsWith("Todo: ")) {
                    todo = line.mid(6);
                } else if (line.startsWith("Completed: ")) {
                    QString status = line.mid(11);
                    completed = (status == "Yes");
                    add = true;
                }
                if (add){
                        addTaskFromFile(title, todo, completed);
                        title.clear();
                        todo.clear();
                        completed = false;
                        add = false;
                }
            }
            file.close();

            updateSmileyStatus();
        }
    }
}

void MainWindow::addTaskFromFile(const QString title, const QString todo, bool completed)
{

    auto taak = new task();
    taak->SetTitle(title);
    taak->SetTodo(todo);
    taak->getKlaarCheckbox()->setChecked(completed);

    m_listTask.append(taak);
    ui->tasksLayout->insertWidget(ui->tasksLayout->count() - 1, taak);

    connect(taak->getDeleteButton(), &QPushButton::clicked, this, [=]() {
        onTaskDeleted(taak);
        emit taak->statusChanged();
    });

    connect(taak->getKlaarCheckbox(), &QCheckBox::stateChanged, this, [=]() {
        emit taak->statusChanged();
    });

    connect(taak, &task::statusChanged, this, &MainWindow::updateSmileyStatus);
}


void MainWindow::on_asave_as_triggered()
{
    // verplicht een file te kiezen.

    auto selectFile = new Selectfile;

    selectFile->setWindowTitle("Choose a file to save");

    int result = selectFile->exec();

    if (result == QDialog::Accepted)
    {
        _fileInfo =  selectFile->getFileInfo();
        saveToFile();
    }

}

void MainWindow::saveToFile()
{
    QFile file(_fileInfo.filePath());

    // Probeer het bestand te openen voor schrijven
    if (file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream out(&file);

        for (const auto& taak : m_listTask) {
            out << "Title: " << taak->getTitle() << "\n";
            out << "Todo: " << taak->getTodo() << "\n";
            out << "Completed: " << (taak->getKlaarCheckbox()->isChecked() ? "Yes" : "No") << "\n";
            out << "--------------------------\n";
        }

        out << "Totaal percentage gedaan: " << _percentage << "%\n";
    }
    else
    {
        qDebug() << "het probleem is hier";
        QMessageBox::critical(this, "Error", "Could not open file: " + file.errorString());
    }
}

