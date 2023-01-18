#include "item.h"

Item::Item(QWidget *parent, ItemType type, QString path)
    : QWidget(parent), type(type), path(path)
{
    QLabel *img = new QLabel(this);
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
    mmd->setImageData(QPixmap(path).scaled(150, 180));
    mmd->setText("1");
    drag->setMimeData(mmd);
    drag->setPixmap(QPixmap(path).scaled(150, 180));
    drag->exec(Qt::MoveAction);

}

void Item::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
        dragStartPosition = event->pos();
}
