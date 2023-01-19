#include "inventory.h"

Inventory::Inventory(QWidget *parent) : QTableWidget(parent)
{
    //Отключаем подсветку выбранных ячеек
    setSelectionMode(QAbstractItemView::NoSelection);
    setEditTriggers(QAbstractItemView::NoEditTriggers);
    setFocusPolicy(Qt::NoFocus);
    //Устанавливаем необходимые размеры
    setRowCount(3);
    setColumnCount(3);
    setMinimumSize(600, 600);
    setMaximumSize(600, 600);
    setColumnWidth(0, 200);
    setColumnWidth(1, 199);
    setColumnWidth(2, 199);
    setRowHeight(0, 200);
    setRowHeight(1, 199);
    setRowHeight(2, 199);
    //Отключаем заголовки
    horizontalHeader()->setVisible(false);
    verticalHeader()->setVisible(false);
    //Отключаем ползунки прокрутки
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    //Настройки Drag & Drop
    setDragDropOverwriteMode(true);
    setAcceptDrops(true);
    setDragEnabled(true);
    setDropIndicatorShown(true);

    //Создаем items в таблицу
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            QTableWidgetItem *item = new QTableWidgetItem("");
            item->setTextAlignment(Qt::AlignBottom | Qt::AlignRight);
            item->setFlags(item->flags() ^ (Qt::ItemIsDropEnabled));
            setItem(i, j, item);
        }
    }
}

void Inventory::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->source() != this)
        setDragDropMode(InternalMove);
    QStringList formats = event->mimeData()->formats();
    if (formats.contains("application/x-qt-image") && formats.contains("text/plain")){
        event->acceptProposedAction();
    }
}

void Inventory::dropEvent(QDropEvent *event)
{
    QTableWidgetItem *item = itemAt(event->pos());
    if (dragDropMode() == InternalMove) {
        if (item != nullptr) {
            item->setData(Qt::DecorationRole, QPixmap::fromImage(event->mimeData()->imageData().value<QImage>()));
            if (item->text() == "")
                item->setText(QString::number(1));
            else item->setText(QString::number(QString(item->text()).toInt() + 1));
        }
    } else {
        if (item != nullptr) {
            item->setData(Qt::DecorationRole, QPixmap::fromImage(event->mimeData()->imageData().value<QImage>()));
            if (item->text() == "")
                item->setText(QString::number(event->mimeData()->text().toInt()));
            else item->setText(QString::number(QString(item->text()).toInt() +
                                               event->mimeData()->text().split(',').first().toInt()));
        }
    }

    saveToDB(getCellNumber(QPoint(item->row(), item->column())),
             DataBase::createConnection()->getData("Item", "name", "type", event->mimeData()->text().split(',').last().toInt()),
             DataBase::createConnection()->getData("Item", "path", "type", event->mimeData()->text().split(',').last().toInt()),
             item->text().toInt());

    event->acceptProposedAction();
}

void Inventory::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::RightButton) {
        QTableWidgetItem *item = itemAt(event->pos());
        if (item != nullptr) {
            if (item->text().toInt() > 1) {
                item->setText(QString::number(QString(item->text()).toInt() - 1));

                saveToDB(getCellNumber(QPoint(item->row(), item->column())),
                         DataBase::createConnection()->getData("Inventory", "name", "cell", getCellNumber(QPoint(item->row(), item->column()))),
                         DataBase::createConnection()->getData("Inventory", "path", "cell", getCellNumber(QPoint(item->row(), item->column()))),
                         item->text().toInt());


            } else if (item->text().toInt() == 1) {
                item->setText("");
                item->setData(Qt::DecorationRole, QPixmap(":/new/prefix1/img/white.jpg"));
                saveToDB(getCellNumber(QPoint(item->row(), item->column())),
                        "None", ":/new/prefix1/img/white.jpg", 0);
            }
        }
    } else if (event->buttons() & Qt::LeftButton) {
        QTableWidgetItem *item = itemAt(event->pos());
        if (item != nullptr && item->text() != "") {
            setDragDropMode(DragDrop);
            QDrag *drag = new QDrag(this);
            QMimeData *mmd = new QMimeData;
            mmd->setImageData(QPixmap(DataBase::createConnection()->getData("Inventory", "path", "cell",
                                                                            getCellNumber(QPoint(item->row(), item->column())))).scaled(150, 180));
            mmd->setText(item->text());
            drag->setMimeData(mmd);
            drag->setPixmap(QPixmap(DataBase::createConnection()->getData("Inventory", "path", "cell",
                                                                          getCellNumber(QPoint(item->row(), item->column())))).scaled(150, 180));
            drag->exec(Qt::MoveAction);
            item->setText("");
            item->setData(Qt::DecorationRole, QPixmap(":/new/prefix1/img/white.jpg"));

            saveToDB(getCellNumber(QPoint(item->row(), item->column())),
                    "None", ":/new/prefix1/img/white.jpg", 0);
        }
    }
}

void Inventory::mouseMoveEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
        dragStartPosition = event->pos();
}

void Inventory::dragMoveEvent(QDragMoveEvent *event)
{
    Q_UNUSED(event);
}

int Inventory::getCellNumber(QPoint point)
{
    return (point.x() * 3 + (point.y() + 1));
}

void Inventory::saveToDB(int cell, QString name, QString path, int count){
    QVariantList data;
    data.append(cell);
    data.append(name);
    data.append(path);
    data.append(count);
    DataBase::createConnection()->addData("Inventory", data);
}
