#ifndef ITEM_H
#define ITEM_H

#include <QApplication>
#include <QGridLayout>
#include <QMouseEvent>
#include <QMimeData>
#include <QComboBox>
#include <QPixmap>
#include <QAction>
#include <QPoint>
#include <QLabel>
#include <QDrag>

#include "databaseview.h"

enum class ItemType : quint8 {
    Food, Armor, Weapon
};

class Item : public QWidget {
    Q_OBJECT
public:
    explicit Item(QWidget *parent = nullptr, ItemType type = ItemType::Food,
                  QString = ":/new/prefix1/img/white.jpg");
public slots:
    //Слот для изменения изоображения
    void changeImage(QString);
protected:
    //События для Drag
    void mouseMoveEvent(QMouseEvent *);
    void mousePressEvent(QMouseEvent *);
private:
    ItemType type;
    QString path;
    QLabel *img;
    QPoint dragStartPosition;
};

#endif // ITEM_H
