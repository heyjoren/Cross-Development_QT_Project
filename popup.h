#ifndef POPUP_H
#define POPUP_H

#include <QDialog>
#include <QtWidgets>

namespace Ui {
class popup;
}

class popup : public QDialog
{
    Q_OBJECT

public:
    explicit popup(QWidget *parent = nullptr);
    ~popup();

    void setTitle(QString);

    void setTypeMessage(QString);

    void setMessage(QString);

    void setButtons(QDialogButtonBox::StandardButtons);


private:
    Ui::popup *ui;
};

#endif // POPUP_H
