#include "database.h"

DataBase* DataBase::isConnected = nullptr;

DataBase::DataBase()
{
    QSqlDatabase dataBase = QSqlDatabase::addDatabase("QSQLITE");
    dataBase.setDatabaseName("GameInventory");
    dataBase.setUserName("Terry");
    dataBase.setHostName("TeddyOn");
    dataBase.setPassword("HelloSQL");
    if (!dataBase.open()) {
        qDebug() << "Cannot open DataBase: " << dataBase.lastError();
    }
}

DataBase::~DataBase()
{
   QSqlDatabase::database().close();
}

DataBase* DataBase::createConnection()
{
    if (isConnected == nullptr)
        isConnected = new DataBase();
    return isConnected;
}

void DataBase::createTable() const
{
    QSqlQuery *query = new QSqlQuery(QSqlDatabase::database());
    QString table = "CREATE TABLE Inventory ("
                        "number INTEGER PRIMARY KEY NOT NULL, "
                        "type VARCHAR(15), "
                        "name VARCHAR(15), "
                        "count INTEGER "
                    ");";
    if (!query->exec(table))
        qDebug() << "Cannot create a table Inventory";
    delete query;
}

void DataBase::printTables() const
{
    foreach (QString tableName, QSqlDatabase::database().tables()) {
        qDebug() << tableName << " ";
    }
}
