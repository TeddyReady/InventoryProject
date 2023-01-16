#include "item.h"

Item::Item(QWidget *parent) : QWidget(parent)
{
    img = new QLabel(this);
    img->setPixmap(QPixmap(":/new/prefix1/img/apple.png").scaled(150, 180));

    setLayout(new QGridLayout(this));
    layout()->addWidget(img);
}
void Item::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton &&
            QApplication::startDragDistance() <= (event->pos() - startPosition).manhattanLength()) {
        QDrag *drag = new QDrag(this);
        QMimeData *mmd = new QMimeData;
        mmd->setImageData( img->pixmap()->toImage());
        drag->setMimeData(mmd);
        drag->setPixmap(*img->pixmap());
        drag->exec(Qt::MoveAction);
    }
}

void Item::mousePressEvent(QMouseEvent *event)
{
    startPosition = event->pos();
}
