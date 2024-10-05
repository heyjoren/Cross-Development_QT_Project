#ifndef SMILEY_H
#define SMILEY_H

#include <QWidget>

class Smiley : public QWidget
{
    Q_OBJECT

public:
    Smiley(QWidget *parent = 0);
    QSize sizeHint() const;
    enum Mood { Blij, Neutraal, Sip };

    void setMood(Mood newMood);

protected:
    void paintEvent(QPaintEvent *);
    void paintEye(QPainter *painter, const QPoint &pt, int size, const QPoint &focus = QPoint());
    void paintSmile(QPainter *painter, const QRect &r);

private:
    Mood currentMood = Neutraal;
};

#endif // SMILEY_H
