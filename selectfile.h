#ifndef SELECTFILE_H
#define SELECTFILE_H

#include <QDialog>
#include "popup.h"

namespace Ui {
class Selectfile;
}

class Selectfile : public QDialog
{
    Q_OBJECT

public:
    explicit Selectfile(QWidget *parent = nullptr);
    ~Selectfile();

    QFileInfo getFileInfo();

private slots:
    void on_pbCancel_clicked();

    void on_pbSave_clicked();

    void chooseFile();

private:
    Ui::Selectfile *ui;
};

#endif // SELECTFILE_H
