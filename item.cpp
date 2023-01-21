#include "item.h"

Item::Item(QWidget *parent, ItemType type, QString path)
    : QWidget(parent), type(type), path(path)
{
    img = new QLabel(this);
    type == ItemType::Food;
    img->setPixmap(QPixmap(path).scaled(150, 180));

    setLayout(new QGridLayout(this));
    layout()->addWidget(img);

    //Заполняем БД
    for (int i = 0; i < 3; ++i) {
        QVariantList data;
        switch (i) {
        case 0:
            data.append(QString::number(static_cast<int>(ItemType::Food)));
            data.append("Apple");
            data.append(":/new/prefix1/img/apple.png");
            break;
        case 1:
            data.append(QString::number(static_cast<int>(ItemType::Weapon)));
            data.append("Swords");
            data.append(":/new/prefix1/img/weapon.png");
            break;
        case 2:
            data.append(QString::number(static_cast<int>(ItemType::Armor)));
            data.append("ChestPlate");
            data.append(":/new/prefix1/img/armor.png");
            break;
        } DataBase::createConnection()->addData("Item", data);
    }
}

void Item::changeImage(QString path)
{
    //Меняем путь и имя
    this->path = path;
    img->setPixmap(QPixmap(path).scaled(150, 180));
    if (path == ":/new/prefix1/img/apple.png")
        type = ItemType::Food;
    else if (path == ":/new/prefix1/img/armor.png")
        type = ItemType::Armor;
    else type = ItemType::Weapon;
}

void Item::mouseMoveEvent(QMouseEvent *event)
{
    if (!(event->buttons() & Qt::LeftButton)) return;
    if ((event->pos() - dragStartPosition).manhattanLength() < QApplication::startDragDistance())
        return;

    //Настройки Drag
    QDrag *drag = new QDrag(this);
    QMimeData *mmd = new QMimeData;
    mmd->setImageData(QPixmap(path).scaled(150, 180));
    mmd->setText("1," + QString::number(static_cast<int>(type)));
    drag->setMimeData(mmd);
    drag->setPixmap(QPixmap(path).scaled(150, 180));
    drag->exec(Qt::MoveAction);
}

void Item::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
        dragStartPosition = event->pos();
}
