#ifndef ITEM_H
#define ITEM_H

#include <QApplication>
#include <QGridLayout>
#include <QMouseEvent>
#include <QMimeData>
#include <QComboBox>
#include <QPixmap>
#include <QPoint>
#include <QLabel>
#include <QDrag>

enum class ItemType : quint8 {
    Food, Armor, Weapon
};

class Item : public QWidget {
    Q_OBJECT
public:
    explicit Item(QWidget *parent = nullptr, ItemType type = ItemType::Food, QString = ":/new/prefix1/img/white.jpg");
protected:
    void mouseMoveEvent(QMouseEvent *);
    void mousePressEvent(QMouseEvent *);
private:
    ItemType type;
    QString path;
    QPoint dragStartPosition;
};

#endif // ITEM_H
