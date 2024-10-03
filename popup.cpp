#include "popup.h"
#include "ui_popup.h"

popup::popup(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::popup)
{
    ui->setupUi(this);
}

popup::~popup()
{
    delete ui;
}

void popup::setTitle(QString title)
{
    this->setWindowTitle(title);
}

void popup::setTypeMessage(QString typeMssg)
{
    ui->lTypeMssg->setText(typeMssg);
}

void popup::setMessage(QString mssg)
{
    ui->lMssg->setText(mssg);
}

void popup::setButtons(QDialogButtonBox::StandardButtons buttons)
{
    ui->buttonBox->setStandardButtons(buttons);
}

