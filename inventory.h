#ifndef INVENTORY_H
#define INVENTORY_H

#include <QTableWidgetItem>
#include <QDragEnterEvent>
#include <QTableWidget>
#include <QMouseEvent>
#include <QHeaderView>
#include <QScrollBar>
#include <QDropEvent>
#include <QMimeData>
#include <QPixmap>
#include <QLabel>

#include <QDebug>

class Inventory: public QTableWidget {
    Q_OBJECT
public:
    explicit Inventory(QWidget *parent = nullptr);
protected:
    void dragEnterEvent(QDragEnterEvent *);
    void dropEvent(QDropEvent *);
    void mousePressEvent(QMouseEvent *event);
private:
    int cnt1, cnt2, cnt3, cnt4, cnt5, cnt6, cnt7, cnt8, cnt9;
};

#endif // INVENTORY_H
