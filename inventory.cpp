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
    setDragDropMode(QAbstractItemView::InternalMove);
    setAcceptDrops(true);
    setDropIndicatorShown(true);

    //Счетчики предметов
    cnt1 = 0;
    cnt2 = 0;
    cnt3 = 0;
    cnt4 = 0;
    cnt5 = 0;
    cnt6 = 0;
    cnt7 = 0;
    cnt8 = 0;
    cnt9 = 0;
}

void Inventory::dragEnterEvent(QDragEnterEvent *event)
{
    QStringList formats = event->mimeData()->formats();
    if (formats.contains("application/x-qt-image"))
        event->acceptProposedAction();
}

void Inventory::dropEvent(QDropEvent *event)
{
    QTableWidgetItem *item = new QTableWidgetItem();
    item->setData(Qt::DecorationRole, QPixmap::fromImage(event->mimeData()->imageData().value<QImage>()));
    //В зависимости от координат добавляем предмет
    //Первая ячейка
    if ( (event->pos().x() <= geometry().topLeft().x() + 200)
      && (event->pos().y() <= geometry().topLeft().y() + 200)){
        cnt1++;
        item->setText(QString::number(cnt1));
        setItem(0, 0, item);
    }
    //Вторая ячейка
    else if ( ((event->pos().x() <= geometry().topLeft().x() + 399) && (event->pos().x() > geometry().topLeft().x() + 200))
           && (event->pos().y() <= geometry().topLeft().y() + 200)) {
        cnt2++;
        item->setText(QString::number(cnt2));
        setItem(0, 1, item);
    }
    //Третья ячейка
    else if ( ((event->pos().x() <= geometry().topLeft().x() + 598) && (event->pos().x() > geometry().topLeft().x() + 399))
           && (event->pos().y() <= geometry().topLeft().y() + 200)) {
        cnt3++;
        item->setText(QString::number(cnt3));
        setItem(0, 2, item);
    }
    //Четвертая ячейка
    else if ( (event->pos().x() <= geometry().topLeft().x() + 200)
           && ((event->pos().y() <= geometry().topLeft().y() + 399) && (event->pos().y() > geometry().topLeft().y() + 200))) {
        cnt4++;
        item->setText(QString::number(cnt4));
        setItem(1, 0, item);
    }
    //Пятая ячейка
    else if ( ((event->pos().x() <= geometry().topLeft().x() + 399) && (event->pos().x() > geometry().topLeft().x() + 200))
           && ((event->pos().y() <= geometry().topLeft().y() + 399) && (event->pos().y() > geometry().topLeft().y() + 200))) {
        cnt5++;
        item->setText(QString::number(cnt5));
        setItem(1, 1, item);
    }
    //Шестая ячейка
    else if ( ((event->pos().x() <= geometry().topLeft().x() + 598) && (event->pos().x() > geometry().topLeft().x() + 399))
           && ((event->pos().y() <= geometry().topLeft().y() + 399) && (event->pos().y() > geometry().topLeft().y() + 200))) {
        cnt6++;
        item->setText(QString::number(cnt6));
        setItem(1, 2, item);
    }
    //Седьмая ячейка
    else if ( (event->pos().x() <= geometry().topLeft().x() + 200)
           && ((event->pos().y() <= geometry().topLeft().y() + 598) && (event->pos().y() > geometry().topLeft().y() + 399))) {
        cnt7++;
        item->setText(QString::number(cnt7));
        setItem(2, 0, item);
    }
    //Восьмая ячейка
    else if ( ((event->pos().x() <= geometry().topLeft().x() + 399) && (event->pos().x() > geometry().topLeft().x() + 200))
           && ((event->pos().y() <= geometry().topLeft().y() + 598) && (event->pos().y() > geometry().topLeft().y() + 399))) {
        cnt8++;
        item->setText(QString::number(cnt8));
        setItem(2, 1, item);
    }
    //Девятая ячейка
    else if ( ((event->pos().x() <= geometry().topLeft().x() + 598) && (event->pos().x() > geometry().topLeft().x() + 399))
           && ((event->pos().y() <= geometry().topLeft().y() + 598) && (event->pos().y() > geometry().topLeft().y() + 399))) {
        cnt9++;
        item->setText(QString::number(cnt9));
        setItem(2, 2, item);
    }

    event->acceptProposedAction();
}

void Inventory::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::RightButton) {
        //Первая ячейка
        if ( (event->pos().x() <= geometry().topLeft().x() + 200)
          && (event->pos().y() <= geometry().topLeft().y() + 200)){
            if (cnt1 > 1) {
                cnt1--;
                itemAt(0, 0)->setText(QString::number(cnt1));
            } else if (cnt1 == 1) {
                cnt1--;
                delete itemAt(0, 0);
            }
        }
        //Вторая ячейка
        else if ( ((event->pos().x() <= geometry().topLeft().x() + 399) && (event->pos().x() > geometry().topLeft().x() + 200))
               && (event->pos().y() <= geometry().topLeft().y() + 200)) {
            if (cnt2 > 1) {
                cnt2--;
                itemAt(0, 1)->setText(QString::number(cnt2));
            } else if (cnt2 == 1) {
                cnt2--;
                delete itemAt(0, 1);
            }
        }
        //Третья ячейка
        else if ( ((event->pos().x() <= geometry().topLeft().x() + 598) && (event->pos().x() > geometry().topLeft().x() + 399))
               && (event->pos().y() <= geometry().topLeft().y() + 200)) {
            if (cnt3 > 1) {
                cnt3--;
                itemAt(0, 2)->setText(QString::number(cnt3));
            } else if (cnt3 == 1) {
                cnt3--;
                delete itemAt(0, 2);
            }
        }
        //Четвертая ячейка
        else if ( (event->pos().x() <= geometry().topLeft().x() + 200)
               && ((event->pos().y() <= geometry().topLeft().y() + 399) && (event->pos().y() > geometry().topLeft().y() + 200))) {
            if (cnt4 > 1) {
                cnt4--;
                itemAt(1, 0)->setText(QString::number(cnt4));
            } else if (cnt4 == 1) {
                cnt4--;
                delete itemAt(1, 0);
            }
        }
        //Пятая ячейка
        else if ( ((event->pos().x() <= geometry().topLeft().x() + 399) && (event->pos().x() > geometry().topLeft().x() + 200))
               && ((event->pos().y() <= geometry().topLeft().y() + 399) && (event->pos().y() > geometry().topLeft().y() + 200))) {
            if (cnt5 > 1) {
                cnt5--;
                itemAt(1, 1)->setText(QString::number(cnt5));
            } else if (cnt5 == 1) {
                cnt5--;
                delete itemAt(1, 1);
            }
        }
        //Шестая ячейка
        else if ( ((event->pos().x() <= geometry().topLeft().x() + 598) && (event->pos().x() > geometry().topLeft().x() + 399))
               && ((event->pos().y() <= geometry().topLeft().y() + 399) && (event->pos().y() > geometry().topLeft().y() + 200))) {
            if (cnt6 > 1) {
                cnt6--;
                itemAt(1, 2)->setText(QString::number(cnt6));
            } else if (cnt6 == 1) {
                cnt6--;
                delete itemAt(1, 2);
            }
        }
        //Седьмая ячейка
        else if ( (event->pos().x() <= geometry().topLeft().x() + 200)
               && ((event->pos().y() <= geometry().topLeft().y() + 598) && (event->pos().y() > geometry().topLeft().y() + 399))) {
            if (cnt7 > 1) {
                cnt7--;
                itemAt(2, 0)->setText(QString::number(cnt7));
            } else if (cnt7 == 1) {
                cnt7--;
                delete itemAt(2, 0);
            }
        }
        //Восьмая ячейка
        else if ( ((event->pos().x() <= geometry().topLeft().x() + 399) && (event->pos().x() > geometry().topLeft().x() + 200))
               && ((event->pos().y() <= geometry().topLeft().y() + 598) && (event->pos().y() > geometry().topLeft().y() + 399))) {
            if (cnt8 > 1) {
                cnt8--;
                itemAt(2, 1)->setText(QString::number(cnt8));
            } else if (cnt8 == 1) {
                cnt8--;
                delete itemAt(2, 1);
            }
        }
        //Девятая ячейка
        else if ( ((event->pos().x() <= geometry().topLeft().x() + 598) && (event->pos().x() > geometry().topLeft().x() + 399))
               && ((event->pos().y() <= geometry().topLeft().y() + 598) && (event->pos().y() > geometry().topLeft().y() + 399))) {
            if (cnt9 > 1) {
                cnt9--;
                itemAt(2, 2)->setText(QString::number(cnt9));
            } else if (cnt9 == 1) {
                cnt9--;
                delete itemAt(2, 2);
            }
        }
    }
}
