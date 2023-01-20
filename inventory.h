#ifndef INVENTORY_H
#define INVENTORY_H

#include <QTableWidgetItem>
#include <QDragEnterEvent>
#include <QMediaPlaylist>
#include <QApplication>
#include <QTableWidget>
#include <QMediaPlayer>
#include <QMouseEvent>
#include <QHeaderView>
#include <QScrollBar>
#include <QDropEvent>
#include <QMimeData>
#include <QPixmap>
#include <QSound>
#include <QLabel>
#include <QDrag>
#include <QUrl>

#include "databaseview.h"

class Inventory: public QTableWidget {
    Q_OBJECT
public:
    explicit Inventory(QWidget *parent = nullptr);
protected:
    void dragEnterEvent(QDragEnterEvent *event);
    void dropEvent(QDropEvent *event);
    void dragMoveEvent(QDragMoveEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
private:
    QPoint dragStartPosition;
    QMediaPlayer *m_player;
    QMediaPlaylist *m_playlist;

    int getCellNumber(QPoint point);
    void saveToDB(int cell, QString name, QString path, int count);
};

#endif // INVENTORY_H
