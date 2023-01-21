#include "database.h"

DataBase* DataBase::isConnected = nullptr;

DataBase::DataBase(QObject *parent) : QObject(parent)
{
    //Создание БД и настройка
    QSqlDatabase dataBase = QSqlDatabase::addDatabase("QSQLITE");
    dataBase.setDatabaseName("GameInventory");
    dataBase.setUserName("Terry");
    dataBase.setHostName("TeddyOn");
    dataBase.setPassword("HelloSQL");
    if (!dataBase.open()) {
        qDebug() << "Cannot open DataBase: " << dataBase.lastError();
    }
    //Создаем таблицы
    createTable(TableType::Inventory);
    createTable(TableType::Item);
}

DataBase::~DataBase()
{
    //Удаляем таблицы при завершении работы приложения
    QSqlQuery query;
    if (!query.exec("DROP TABLE Item"))
        qDebug() << "CANNOT DELETE ITEM TABLE: " << query.lastError().text();
    if (!query.exec("DROP TABLE Inventory"))
        qDebug() << "CANNOT DELETE INVENTORY TABLE: " << query.lastError().text();

    //Закрываем соединение с БД
    QSqlDatabase::database().close();
}

DataBase* DataBase::createConnection()
{
    if (isConnected == nullptr)
        isConnected = new DataBase();
    return isConnected;
}

void DataBase::createTable(TableType type) const
{
    //Посредством запросов создаем нужные таблицы
    QSqlQuery query;
    QString table;
    switch (type) {
    case TableType::Inventory :
        table = "CREATE TABLE Inventory ("
                "cell INTEGER PRIMARY KEY NOT NULL, "
                "name VARCHAR(15) NOT NULL, "
                "path VARCHAR(50) NOT NULL, "
                "count INTEGER "
                ");";
        if (!query.exec(table))
            qDebug() << "CANNOT CREATE TABLE INVENTORY: " << query.lastError().text();
        break;

    case TableType::Item :
        table = "CREATE TABLE Item ("
                "type INTEGER, "
                "name VARCHAR(15) PRIMARY KEY NOT NULL, "
                "path VARCHAR(50) NOT NULL "
                ");";
        if (!query.exec(table))
            qDebug() << "CANNOT CREATE TABLE ITEM: " << query.lastError().text();
        break;
    }
}

void DataBase::printTables() const
{
    foreach (QString tableName, QSqlDatabase::database().tables()) {
        qDebug() << tableName << " ";
    }
}

void DataBase::addData(QString tableName, const QVariantList &data)
{
    QSqlQuery query;
    if (tableName == "Inventory") {
        query.prepare("INSERT INTO Inventory (cell, name, path, count) "
                      "VALUES (:cell, :name, :path, :count )");

        query.bindValue(":cell",  data[0].toInt());
        query.bindValue(":name",  data[1].toString());
        query.bindValue(":path",  data[2].toString());
        query.bindValue(":count", data[3].toInt());

        if (!query.exec()) {
            if (query.lastError().text() == "UNIQUE constraint failed: Inventory.cell Unable to fetch row") {
                query.prepare("UPDATE Inventory SET name =:name, path =:path, count =:count"
                              " WHERE cell =:cell");

                query.bindValue(":cell",  data[0].toInt());
                query.bindValue(":name",  data[1].toString());
                query.bindValue(":path",  data[2].toString());
                query.bindValue(":count", data[3].toInt());

                if (!query.exec()) {
                    qDebug() << "Error with UPDATING Inventory: " << query.lastError().text();
                }

            } else qDebug() << "Error insert into Inventory: " << query.lastError().text();

        }
    } else {
        query.prepare("INSERT INTO Item (type, name, path) "
                      "VALUES (:type, :name, :path )");

        query.bindValue(":type",  data[0].toInt());
        query.bindValue(":name",  data[1].toString());
        query.bindValue(":path",  data[2].toString());

        if (!query.exec())
            qDebug() << "error insert into Item: " << query.lastError().text();
    } emit updateDBView();
}

QString DataBase::getData(QString tableName, QString selected, QString option, int value)
{
    QSqlQuery query;
    query.prepare("SELECT " + selected + " FROM " + tableName + " WHERE " + option + " =:type");
    query.bindValue(":type", value);
    if (!query.exec()) {
        qDebug() << "error select from " + tableName + ": " << query.lastError().text();
        return "ERROR";
    } query.next();
    return query.value(0).toString();

}
