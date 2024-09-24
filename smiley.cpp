#include "smiley.h"
#include "qevent.h"
#include "qpainterpath.h"
#include <QPainter>

Smiley::Smiley(QWidget *parent)
    : QWidget(parent)
{
}

QSize Smiley::sizeHint() const {
    return QSize(200,200);
}

void Smiley::setMood(Mood newMood) {
    currentMood = newMood;
    update();
}

void Smiley::paintEvent(QPaintEvent *pe) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    QRect boundingBox = rect().adjusted(10, 0, -10, 0);

    QPoint center = boundingBox.center();
    int size = qMin(boundingBox.width(), boundingBox.height());

    // draw round face with cen in 'tercenter' and diameter of 'size'
    QPen pen;
    pen.setWidth(2);
    pen.setColor(Qt::black);
    painter.setPen(pen);
    switch (currentMood) {
    case Blij:
        painter.setBrush(Qt::green);  // Groen voor blij
        break;
    case Neutraal:
        painter.setBrush(QColorConstants::Svg::orange);  // Oranje voor neutraal
        break;
    case Sip:
        painter.setBrush(Qt::red);  // Rood voor sip
        break;
    default:
        painter.setBrush(Qt::yellow);  // Standaard geel
        break;
    }

    // painter.setBrush(Qt::yellow);
    painter.drawEllipse(center, size/2, size/2);

    // draw eyes
    int eyeHeight = center.y() - size/4;
    QPoint leftEye(center.x()-size/8, eyeHeight);
    QPoint rightEye(center.x()+size/8, eyeHeight);

    QPoint eyeFocus;  // Focuspunt voor de pupillen
    switch (currentMood) {
    case Blij:
        // Ogen recht vooruit
        paintEye(&painter, leftEye, size/8, leftEye);
        paintEye(&painter, rightEye, size/8, rightEye);
        break;
    case Neutraal:
        // Ogen recht vooruit
        paintEye(&painter, leftEye, size/8, leftEye);
        paintEye(&painter, rightEye, size/8, rightEye);
        break;
    case Sip:
        // Ogen naar beneden
        eyeFocus = QPoint(leftEye.x(), leftEye.y() + size/6);
        paintEye(&painter, leftEye, size/8, eyeFocus);
        eyeFocus.setX(rightEye.x());
        paintEye(&painter, rightEye, size/8, eyeFocus);
        break;
    }

    // draw smile
    int smileHeight = center.y()-size/8;
    paintSmile(&painter, QRect(center.x()-size/3, smileHeight, 2*size/3, size/2));

}

QPoint computePupil (const QPoint &center, const QPoint &focus, int eyeWidth, int eyeHeight)
{
    QPointF dPoint = focus-center;
    if (dPoint.x() == 0 && dPoint.y() == 0) {
        return center;
    } else {
        double angle = atan2 (dPoint.y(), dPoint.x());
        double cosa = cos (angle);
        double sina = sin (angle);
        double h = hypot (eyeHeight * cosa, eyeWidth * sina);
        double x = (eyeWidth * eyeHeight) * cosa / h;
        double y = (eyeWidth * eyeHeight) * sina / h;
        double dist = hypot (x*0.7, y*0.7);
        if (dist > hypot (dPoint.x(), dPoint.y())) {
            return dPoint.toPoint()+center;
        } else {
            return QPoint(dist*cosa+center.x(), dist*sina+center.y());
        }
    }
}

void Smiley::paintEye(QPainter *painter, const QPoint &pt, int size, const QPoint &focus) {
    // Oog
    painter->save();
    QPen pen(Qt::black);
    pen.setWidth(2);
    painter->setPen(pen);
    painter->setBrush(Qt::white);
    painter->drawEllipse(pt, size / 2, size);

    // Pupil
    pen.setWidth(0);
    painter->setPen(pen);
    painter->setBrush(Qt::black);
    QPoint pupilCenter = computePupil(pt, focus, size / 2, size);
    painter->drawEllipse(pupilCenter, size / 8, size / 8);

    painter->restore();
}


void Smiley::paintSmile(QPainter *painter, const QRect &r) {
    // draw an arc inside the area of r

    QPen pen;
    pen.setWidth(2);
    pen.setColor(Qt::black);
    painter->setPen(pen);

    int startAngle;
    int spanAngle;
    int smileOffset;
    QPoint startPoint, endPoint;
    QRect adjustedRect;

    switch (currentMood) {
    case Blij:
        startAngle = 0;
        spanAngle = -180 * 16;
        smileOffset = -5;

        adjustedRect = r.adjusted(0, smileOffset, 0, smileOffset);
        painter->drawArc(adjustedRect, startAngle, spanAngle);
        // painter->restore();
        break;
    case Neutraal:
        smileOffset = 0;

        startPoint = QPoint(r.left(), r.center().y() + smileOffset);
        endPoint = QPoint(r.right(), r.center().y() + smileOffset);
        painter->drawLine(startPoint, endPoint);
        // painter->restore();
        break;
    case Sip:
        startAngle = 0;
        spanAngle = 180 * 16;
        smileOffset = 20;

        adjustedRect = r.adjusted(0, smileOffset, 0, smileOffset);
        painter->drawArc(adjustedRect, startAngle, spanAngle);
        // painter->restore();
        break;
    }
}
