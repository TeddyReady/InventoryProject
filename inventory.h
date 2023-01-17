#ifndef INVENTORY_H
#define INVENTORY_H

#include <QTableWidgetItem>
#include <QDragEnterEvent>
#include <QApplication>
#include <QTableWidget>
#include <QMouseEvent>
#include <QHeaderView>
#include <QScrollBar>
#include <QDropEvent>
#include <QMimeData>
#include <QPixmap>
#include <QLabel>
#include <QDrag>

class Inventory: public QTableWidget {
    Q_OBJECT
public:
    explicit Inventory(QWidget *parent = nullptr);
protected:
    void dragEnterEvent(QDragEnterEvent *);
    void dropEvent(QDropEvent *);
    void dragMoveEvent(QDragMoveEvent *);
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
private:
    QPoint dragStartPosition;
};

#endif // INVENTORY_H
