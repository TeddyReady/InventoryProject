#include "databaseview.h"
#include "ui_databaseview.h"

DataBaseView::DataBaseView(QString tableName, QWidget *parent) :
    QWidget(parent), tableName(tableName),
    ui(new Ui::DataBaseView)
{
    ui->setupUi(this);

    if (tableName == "Inventory") {
        setupModel(tableName,
                   QStringList() << "Ячейка"
                   << "Название"
                   << "Путь"
                   << "Количество в ячейке" );
    } else {
        setupModel(tableName,
                   QStringList() << "Тип предмета"
                   << "Название предмета"
                   << "Путь" );
    }
    this->createUI();
}

DataBaseView::~DataBaseView()
{
    delete ui;
}

void DataBaseView::setupModel(const QString &tableName, const QStringList &headers)
{
    model = new QSqlTableModel(this);
    model->setTable(tableName);

    for(int i = 0, j = 0; i < model->columnCount(); i++, j++){
        model->setHeaderData(i, Qt::Horizontal, headers[j]);
    }
}

void DataBaseView::createUI()
{
    ui->table->setModel(model);
    ui->table->setSelectionMode(QAbstractItemView::NoSelection);
    ui->table->resizeColumnsToContents();
    ui->table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->table->horizontalHeader()->setStretchLastSection(true);

    model->select();
}
