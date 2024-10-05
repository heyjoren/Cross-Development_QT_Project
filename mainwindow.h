#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "smiley.h"
#include "task.h"
#include "selectfile.h"
#include <QtWidgets>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionexit_triggered();

    void onTaskDeleted(task* taak);

    void updateSmileyStatus();

    // void on_pbBack_clicked();

    void on_pbAdd_clicked();

    void addToChangeToTaskScreen();

    void setHomeScreen();

    void setTaskScreen();

    void on_actionsave_triggered();

    void on_actionopen_triggered();

    void addTaskFromFile(const QString title, const QString todo, bool);

    void on_asave_as_triggered();

    void saveToFile();

private:
    Ui::MainWindow *ui;
    QList<task*> m_listTask;


    //TEST
    int test;
    //TEST tot hier

    QFileInfo _fileInfo;

    double _percentage;
};
#endif // MAINWINDOW_H
