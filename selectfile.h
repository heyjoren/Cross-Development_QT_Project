#ifndef SELECTFILE_H
#define SELECTFILE_H

#include <QDialog>
#include "confirmcancel.h"

namespace Ui {
class Selectfile;
}

class Selectfile : public QDialog
{
    Q_OBJECT

public:
    explicit Selectfile(QWidget *parent = nullptr);
    ~Selectfile();

private slots:
    void on_pbCancel_clicked();

    void on_pbSave_clicked();

private:
    Ui::Selectfile *ui;
};

#endif // SELECTFILE_H
