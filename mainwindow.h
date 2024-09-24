#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "smiley.h"
#include "task.h"

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

    void on_pbAddTask_clicked();

    void onTaskDeleted(task* taak);

    void updateSmileyStatus();

    void on_pbBack_clicked();

    void on_pbAdd_clicked();

private:
    Ui::MainWindow *ui;
    QList<task*> m_listTask;

    int test;
};
#endif // MAINWINDOW_H
