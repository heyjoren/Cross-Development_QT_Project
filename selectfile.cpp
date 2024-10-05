#include "selectfile.h"
#include "ui_selectfile.h"

#include <QtWidgets>

Selectfile::Selectfile(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Selectfile)
{
    ui->setupUi(this);

    connect(ui->pbChoose, &QPushButton::clicked, this, &Selectfile::chooseFile);
}

Selectfile::~Selectfile()
{
    delete ui;
}

QFileInfo Selectfile::getFileInfo()
{
    QFileInfo file (ui->lEFile->text());

    return file;
}

void Selectfile::on_pbCancel_clicked()
{
    auto cancel = new popup(this);
    cancel->setTitle("Confirm");
    cancel->setTypeMessage("Confirm:");
    cancel->setMessage("Are you sure you want to cancel?");
    if (cancel->exec() == QDialog::Accepted)
    {
        cancel->close();
        ui->lEFile->clear();
        this->close();
    }
    else
    {
        cancel->close();
    }
}


void Selectfile::on_pbSave_clicked()
{
    if(ui->lEFile->text().isEmpty())
    {
        auto error = new popup(this);
        error->setTitle("Error");
        error->setTypeMessage("Error:");
        error->setMessage("Please select a file. To save to.");
        error->setButtons(QDialogButtonBox::Ok);

        error->exec();

    }
    else
    {
        QString path = ui->lEFile->text();
        QFileInfo fileInfo (path);

        if(!fileInfo.isFile())
        {
            if (fileInfo.suffix().isEmpty())
            {
                path +=".txt";
                fileInfo = QFileInfo(path);
            }

            QFile file(path);
            if (file.open(QIODevice::WriteOnly)) {
                file.close(); // Sluit het bestand onmiddellijk nadat het is aangemaakt
            } else {
                QMessageBox::critical(this, "Error", "Could not create file: " + file.errorString());
            }
        }
        this->accept();
    }
}

void Selectfile::chooseFile()
{
    QString path = QFileDialog::getSaveFileName(
        this,
        "Save File",
        "",
        "Text Files (*.txt);;All Files (*)"
        );

    ui->lEFile->setText(path);
}

