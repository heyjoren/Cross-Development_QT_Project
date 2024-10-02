#include "selectfile.h"
#include "ui_selectfile.h"

Selectfile::Selectfile(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Selectfile)
{
    ui->setupUi(this);
}

Selectfile::~Selectfile()
{
    delete ui;
}

void Selectfile::on_pbCancel_clicked()
{
    auto cancel = new confirmCancel(this);
    // ConfirmCancel cancelDialog(this);
    if (cancel->exec() == QDialog::Accepted)
    {
        cancel->close();
    }
    else
    {
        cancel->close();
        ui->lAFile->clear();
        this->close();
    }
}


void Selectfile::on_pbSave_clicked()
{

}

