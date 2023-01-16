#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QPropertyAnimation>
#include <QMainWindow>

#include "inventory.h"
#include "database.h"
#include "item.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT
private:
    void uploadUI();
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Item *item;
    Inventory *inventory;
    DataBase *db;
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
