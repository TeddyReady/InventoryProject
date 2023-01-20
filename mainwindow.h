#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QPropertyAnimation>
#include <QMainWindow>
#include <QToolBar>
#include <QFile>

#include "inventory.h"
#include "item.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT
private:
    //Загрузка UI
    void uploadUI();
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
signals:
    //Обновление предмета (сигнал)
    void reloadImage(QString);
private slots:
    //Обновление предмета (слот)
    void on_nameStorage_currentTextChanged(const QString &arg1);
private:
    Item *item;
    Inventory *inventory;
    DataBaseView *tableInventory, *tableItem;
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
