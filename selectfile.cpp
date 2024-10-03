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
        qDebug()<< "if (accepted)";
        cancel->close();
        ui->lEFile->clear();
        this->close();
    }
    else
    {
        qDebug()<< "else (rejected)";
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
        QFileInfo fileInfo (ui->lEFile->text());

        if(fileInfo.isFile() && fileInfo.exists())
        {
            // EERST ZIEN OF HET EEN FILE IS.
            // DAN ZIEN OF HIJ BESTAAT OF NIET

            qDebug() << "gelukt";
        }
        else if(fileInfo.isDir())
        {
            //vraag naam van de file
            bool ok;
            QString fileNaam;
            do {
                fileNaam = QInputDialog::getText(this, "Enter File Name", "Please enter a file name:", QLineEdit::Normal, "", &ok);

                if (!ok) {
                    QMessageBox::warning(this, "Input Required", "You must enter a valid file name.");
                }
            } while (!ok || fileNaam.isEmpty());

            //Windows file toevoegen aan pad
            QString completeFilePath = fileInfo.absoluteFilePath() + "/" + fileNaam;

            fileInfo = QFileInfo(completeFilePath);

            qDebug() << "Nieuw volledig pad met bestandsnaam: " << fileInfo.absoluteFilePath();
        }
        else
        {
            auto error = new popup(this);
            error->setTitle("Error");
            error->setTypeMessage("Error:");
            error->setMessage("Invalid file path. Please enter a valid file or directory.");
            error->setButtons(QDialogButtonBox::Ok);

            error->exec();
        }


        this->close();
    }
}

void Selectfile::chooseFile()
{
    QString path = QFileDialog::getOpenFileName(this);

    ui->lEFile->setText(path);
}

