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
    delete ui;
}

void MainWindow::uploadUI()
{
    ui->setupUi(this);
    setMaximumSize(850, 900);
    connect(ui->btnExit, &QPushButton::clicked, [&](){ qApp->exit(); });
    ui->gameZone->setTitle("Инвентарь");
    item = new Item(this, ItemType::Food, ":/new/prefix1/img/apple.png");
    inventory = new Inventory(this);
    ui->gridForItem->addWidget(item);
    ui->gridForInventory->addWidget(inventory);
}
