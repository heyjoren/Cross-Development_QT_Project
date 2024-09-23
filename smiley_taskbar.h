#ifndef SMILEY_TASKBAR_H
#define SMILEY_TASKBAR_H

#include <QObject>
#include <QWidget>

class Smiley_taskBar
{
public:
    Smiley_taskBar(QWidget *parent = 0);

    QSize sizeHint() const;
    int smileSize() const;
public slots:
    void setSmileSize(int);

protected:
    void paintEvent(QPaintEvent *);
    void paintEye(QPainter *painter, const QPoint &pt, int size);
    // void paintEye(QPainter *painter, const QPoint &pt, int size, const QPoint &focus = QPoint());
    void paintSmile(QPainter *painter, const QRect &r, int angle);

private:
    QPoint focusPoint;
    int m_smileSize;
};

#endif // SMILEY_TASKBAR_H
