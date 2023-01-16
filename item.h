#ifndef ITEM_H
#define ITEM_H

#include <QApplication>
#include <QGridLayout>
#include <QMouseEvent>
#include <QMimeData>
#include <QPixmap>
#include <QPoint>
#include <QLabel>
#include <QDrag>

class Item : public QWidget {
    Q_OBJECT
public:
    explicit Item(QWidget *parent = nullptr);
protected:
    void mouseMoveEvent(QMouseEvent *);
    void mousePressEvent(QMouseEvent *);
private:
    QLabel *img;
    QPoint startPosition;
};

#endif // ITEM_H
