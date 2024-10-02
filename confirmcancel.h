#ifndef CONFIRMCANCEL_H
#define CONFIRMCANCEL_H

#include <QDialog>

namespace Ui {
class confirmCancel;
}

class confirmCancel : public QDialog
{
    Q_OBJECT

public:
    explicit confirmCancel(QWidget *parent = nullptr);
    ~confirmCancel();

private:
    Ui::confirmCancel *ui;
};

#endif // CONFIRMCANCEL_H
