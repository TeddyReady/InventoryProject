#include "item.h"

Item::Item(QWidget *parent, ItemType type, QString path)
    : QWidget(parent), type(type), path(path)
{
    img = new QLabel(this);
    img->setPixmap(QPixmap(path).scaled(150, 180));

    setLayout(new QGridLayout(this));
    layout()->addWidget(img);
}

void Item::mouseMoveEvent(QMouseEvent *event)
{
    if (!(event->buttons() & Qt::LeftButton)) return;
    if ((event->pos() - dragStartPosition).manhattanLength() < QApplication::startDragDistance())
        return;

    QDrag *drag = new QDrag(this);
    QMimeData *mmd = new QMimeData;
    mmd->setImageData( img->pixmap()->toImage());
    mmd->setText("1");
    drag->setMimeData(mmd);
    drag->setPixmap(*img->pixmap());
    drag->exec(Qt::CopyAction | Qt::MoveAction);

}

void Item::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
        dragStartPosition = event->pos();
}
