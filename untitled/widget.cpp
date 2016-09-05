#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    UGlobalHotkeys *hotkeyManager = new UGlobalHotkeys();
    hotkeyManager->registerHotkey("Ctrl+Shift+F12");
    connect(hotkeyManager, &UGlobalHotkeys::activated, [=](size_t id)
    {
        qDebug() << "Activated: " << QString::number(id);
        hotKeyPressed = true;
        timer->stop();
    });

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(MyTimerSlot()));

    showFullScreen();
    setWindowOpacity(windowOpacity);

    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::paintEvent(QPaintEvent *e)
{
    qDebug() << "paintEvent";

    if(modified) {
        QPainter painter(this);
        QPen pen(Qt::red, 3, Qt::DashDotLine, Qt::RoundCap, Qt::RoundJoin);
        painter.setPen(pen);

        painter.drawRect(rectangleAreaStartPoint.x(),
                         rectangleAreaStartPoint.y(),
                         rectangleAreaMoveNormPoint.x(),
                         rectangleAreaMoveNormPoint.y());

        modified = false;
    }
}

void Widget::mousePressEvent(QMouseEvent *event)
{
    qDebug() << "mousePressEvent";
    qDebug() << event->pos();

    if (event->button() == Qt::LeftButton) {
        rectangleAreaStartPoint = event->pos();
    }

    if (event->button() == Qt::RightButton) {
        this->showMinimized();
        timer->start(timerInterval);
    }
}

void Widget::MyTimerSlot()
{
    qDebug() << "Timer...";

    QScreen *screen = QGuiApplication::primaryScreen();
    if (const QWindow *window = windowHandle())
        screen = window->screen();
    if (!screen)
        return;

//    Magick::readImages(&images, "x:root");
//    qDebug() << images.size() * sizeof(Magick::Image);
//    Magick::writeImages(images.begin(), images.end(), "animation.gif", true);


    QImage originalPixmap = screen->grabWindow(0).copy(rectangleAreaStartPoint.x(),
                                                       rectangleAreaStartPoint.y(),
                                                       rectangleAreaMoveNormPoint.x(),
                                                       rectangleAreaMoveNormPoint.y()).toImage();

    Qimages.push_back(originalPixmap);
    toImage(&originalPixmap);
//    images.push_back(toImage(originalPixmap));
//    Magick::writeImages(images.begin(), images.end(), "animation.gif", true);



    // still slow
//    shotsCount++;
//    QString path = QDir::currentPath() + QDir::separator() + QString::number(shotsCount) + ".jpeg";
//    QString path = QDir::currentPath() + QDir::separator() + "temp.jpeg";

//    if (!originalPixmap.save(path, Q_NULLPTR, 50)) {
//        QMessageBox::warning(this, tr("Save Error"),
//                             tr("The image could not be saved to \"%1\"."));
//    }

//    Magick::readImages(&images, path.toStdString());
//    Magick::writeImages(images.begin(), images.end(), "animation.gif", true);
//    for (Magick::Image image : images) {
//        image.animationDelay(200);
//    }

//    qDebug() << path;
//    qDebug() << images.size();
//    qDebug() << "";




    // super slow
//    QProcess _FFMPEG;
//    QString _process = "ffmpeg";
//    QStringList _paramList;
//    _paramList << "-framerate"
//               << "5"

//               << "-y" // Overwrite output files without asking.

//               << "-i"
//               << "%00d.jpeg"

//               << "output.gif";

//    _FFMPEG.start(_process, _paramList);

//    if ( !(_FFMPEG.waitForFinished()) )
//        qDebug() << "Conversion failed:" << _FFMPEG.errorString();
//    else
//        qDebug() << "Conversion output:" << _FFMPEG.readAll();
}

void Widget::mouseMoveEvent(QMouseEvent *event)
{
    qDebug() << "mouseMoveEvent";
    qDebug() << event->pos();

    if (event->buttons() & Qt::LeftButton) {
        rectangleAreaMoveNormPoint = event->pos() - rectangleAreaStartPoint;
        modified = true;
        this->update();
    }
}

void Widget::mouseReleaseEvent(QMouseEvent *event)
{
    qDebug() << "mouseReleaseEvent";
    qDebug() << event->pos();

    //    if (event->button() == Qt::LeftButton && scribbling) {
    //        drawLineTo(event->pos());
    //        scribbling = false;
    //    }
}

Magick::Image* Widget::toImage(QImage* qimage)
{
    qDebug() << "toImage:" << qimage->width() << qimage->height();

    Magick::Image *newImage = new Magick::Image(Magick::Geometry(qimage->width(), qimage->height()), Magick::ColorRGB(0.5, 0.2, 0.3));

    double scale = 1 / 256.0;
    newImage->modifyImage();
    Magick::Quantum *pixels;
    Magick::ColorRGB mgc;
    for (int y = 0; y < qimage->height(); y++) {
        pixels = newImage->setPixels(0, y, newImage->columns(), 1);
        for (int x = 0; x < qimage->width(); x++) {
            QColor pix = qimage->pixel(x, y);
            qDebug() << "pix: " << pix;
//                  *pixels++ = Magick::ColorRGB(256 * pix.red(), 256 * pix.green(), 256 * pix.blue());
//            mgc.red(scale *pix.red());
//            mgc.green(scale *pix.green());
//            mgc.blue(scale *pix.blue());
//                  *pixels++ = static_cast<Magick::Quantum>(Magick::ColorRGB(scale *pix.red(), scale * pix.green(), scale * pix.blue()));
//            *pixels++ = mgc;
        }
        newImage->syncPixels();
    }

    return newImage;
}

Magick::Image* Widget::toImage2(QImage& qimage)
{
    qDebug() << "toImage:" << qimage.width() << qimage.height();

    Magick::Image *newImage = new Magick::Image(Magick::Geometry(qimage.width(), qimage.height()), Magick::ColorRGB(0.5, 0.2, 0.3));

    double scale = 1 / 256.0;
    newImage->modifyImage();
    Magick::Quantum *pixels;
    Magick::ColorRGB mgc;
    for (int y = 0; y < qimage.height(); y++) {
        pixels = newImage->setPixels(0, y, newImage->columns(), 1);
        for (int x = 0; x < qimage.width(); x++) {
//            QColor pix = qimage.pixel(x, y);
//            //      *pixels++ = Magick::ColorRGB(256 * pix.red(), 256 * pix.green(), 256 * pix.blue());
//            mgc.red(scale *pix.red());
//            mgc.green(scale *pix.green());
//            mgc.blue(scale *pix.blue());
//            //      *pixels++ = Magick::ColorRGB(scale *pix.red(), scale * pix.green(), scale * pix.blue());
//            *pixels++ = mgc;
        }
        newImage->syncPixels();
    }

    return newImage;
}
