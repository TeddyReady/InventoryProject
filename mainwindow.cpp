#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    uploadUI();
}

MainWindow::~MainWindow()
{
    DataBase::createConnection()->~DataBase();
    delete ui;
}

void MainWindow::uploadUI()
{
    //Настройки главного окна
    ui->setupUi(this);
    setMaximumSize(850, 900);

    //Настройки тулбара
    ui->toolBar->addAction(new QAction("Новая Игра", ui->toolBar));
    ui->toolBar->addSeparator();
    ui->toolBar->addAction(new QAction("Открыть базу данных инвентаря", ui->toolBar));
    ui->toolBar->addAction(new QAction("Открыть базу данных предмета", ui->toolBar));
    ui->toolBar->addSeparator();
    ui->toolBar->addAction(new QAction("Выход", ui->toolBar));

    //Настройки виджетов MainWindow
    ui->gameZone->setTitle("Инвентарь");
    item = new Item(this, ItemType::Food, ":/new/prefix1/img/apple.png");
    inventory = new Inventory(this);
    item->setDisabled(true);
    inventory->setDisabled(true);
    ui->nameStorage->setDisabled(true);
    ui->gridForItem->addWidget(item);
    ui->gridForInventory->addWidget(inventory);

    //Связываем сигналы со слотами
    connect(ui->toolBar->actions().at(0), &QAction::triggered, [&](){
        if (ui->toolBar->actions().at(0)->text() == "Новая Игра") {
            item->setEnabled(true);
            inventory->setEnabled(true);
            ui->nameStorage->setEnabled(true);
            ui->toolBar->actions().at(0)->setText("Завершить игру");
            ui->toolBar->actions().at(5)->setDisabled(true); //Quit Act
        } else {
            delete ui->gridForInventory->takeAt(0);
            inventory = new Inventory(this);
            ui->gridForInventory->addWidget(inventory);

            item->setDisabled(true);
            inventory->setDisabled(true);
            ui->nameStorage->setDisabled(true);

            ui->toolBar->actions().at(0)->setText("Новая Игра");
            ui->toolBar->actions().at(5)->setEnabled(true);
        }
    });
    connect(ui->toolBar->actions().at(2), &QAction::triggered, [&](){
        DataBaseView *widget = new DataBaseView("Inventory");
        widget->setWindowTitle("База Данных Инвентаря");
        widget->resize(800, 600);
        widget->show();
    });
    connect(ui->toolBar->actions().at(3), &QAction::triggered, [&](){
        DataBaseView *widget = new DataBaseView("Item");
        widget->setWindowTitle("База Данных Предмета");
        widget->resize(800, 600);
        widget->show();
    });
    connect(ui->toolBar->actions().at(5), &QAction::triggered, [&](){ qApp->exit(); });
    connect(this, SIGNAL(reloadImage(QString)), item, SLOT(changeImage(QString)));
}

void MainWindow::on_nameStorage_currentTextChanged(const QString &imageName)
{
    if (imageName == "Food") {
        emit reloadImage(":/new/prefix1/img/apple.png");
    } else if (imageName == "Armor") {
        emit reloadImage(":/new/prefix1/img/armor.png");
    } else {
        emit reloadImage(":/new/prefix1/img/weapon.png");
    }
}
