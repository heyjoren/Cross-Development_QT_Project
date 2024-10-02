#include "confirmcancel.h"
#include "ui_confirmcancel.h"

confirmCancel::confirmCancel(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::confirmCancel)
{
    ui->setupUi(this);
}

confirmCancel::~confirmCancel()
{
    delete ui;
}
