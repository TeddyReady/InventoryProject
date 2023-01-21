#ifndef DATABASE_H
#define DATABASE_H

#include <QSqlRecord>
#include <QSqlQuery>
#include <QDebug>
#include <QtSql>

enum class TableType: quint8 {
    Inventory, Item
};

/* Класс Базы Данных сделанный
 * паттерном Одиночка         */
class DataBase: public QObject {
    Q_OBJECT
public:
    ~DataBase();
    DataBase(const DataBase& oterDB) = delete ;
    void operator=(const DataBase& oterDB) = delete ;

    //Основная функция, создающая экземпляр
    static DataBase* createConnection();

    //Создание таблиц
    void createTable(TableType type) const ;

    //Вывод всех созданных таблиц в qDebug для отладки
    void printTables() const;

    //Добавление данных в БД
    void addData(QString tableName, const QVariantList &data);

    //Чтение данных из БД
    QString getData(QString tableName, QString selected, QString option, int value);
signals:
    //Обновление сопряженного с классом виджета
    void updateDBView();
protected:
    static DataBase* isConnected;
    explicit DataBase(QObject *parent = nullptr);
};

#endif // DATABASE_H
