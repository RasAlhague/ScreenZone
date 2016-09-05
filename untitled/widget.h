#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTimer>
#include <QImage>
#include <QThread>
#include <QDialog>
#include <QPainter>
#include <QPolygon>
#include <QPainterPath>
#include "QDebug"
#include "QPalette"
#include "QPainter"
#include "QPen"
#include "QScreen"
#include "QPixmap"
#include "QWindow"
#include "QMessageBox"
#include "QDir"
#include "QProcess"
#include "QStringList"

#include <list>
#include "Magick++.h"

#include "uglobalhotkeys.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

public slots:
    void MyTimerSlot();

protected:
    void paintEvent(QPaintEvent *e);
    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;

private:
    Magick::Image* toImage(QImage *qimage);
    Magick::Image* toImage2(QImage &qimage);

    Ui::Widget *ui;

    QPoint rectangleAreaStartPoint;
    QPoint rectangleAreaMoveNormPoint;

    std::list<Magick::Image> images;
    std::list<QImage> Qimages;

    QTimer *timer;

    int shotsCount = 0;
    const int timerInterval = 200;
    const qreal windowOpacity = 0.5;

    bool modified;
    bool hotKeyPressed;
};

#endif // WIDGET_H
