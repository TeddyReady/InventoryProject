#ifndef DATABASE_H
#define DATABASE_H

#include <QSqlRecord>
#include <QSqlQuery>
#include <QDebug>
#include <QtSql>

enum class TableType: quint8 {
    Inventory, Item
};

class DataBase {
public:
    ~DataBase();
    DataBase(const DataBase& oterDB) = delete ;
    void operator=(const DataBase& oterDB) = delete ;

    static DataBase* createConnection();
    void createTable(TableType type) const ;
    void printTables() const;
    void addData(QString tableName, const QVariantList &data);
    QString getData(QString tableName, QString selected, QString option, int value);
protected:
    static DataBase* isConnected;
    explicit DataBase();
};

#endif // DATABASE_H
