#ifndef DATABASE_H
#define DATABASE_H

#include <QSqlQuery>
#include <QtSql>
#include <QDebug>

class DataBase {
public:
    ~DataBase();
    DataBase(const DataBase&) = delete;
    void operator=(const DataBase&) = delete;

    static DataBase* createConnection();
    void createTable() const;
    void printTables() const;
protected:
    static DataBase* isConnected;
    explicit DataBase();
};

#endif // DATABASE_H
