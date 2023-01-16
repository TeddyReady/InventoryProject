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
    ui->gameZone->setTitle("Раунд 1");
    item = new Item(this);
    inventory = new Inventory(this);
    ui->gridForItem->addWidget(item);
    ui->gridForInventory->addWidget(inventory);
}
