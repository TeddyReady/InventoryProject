#ifndef DATABASEVIEW_H
#define DATABASEVIEW_H

#include <QSqlTableModel>
#include <QVariantList>
#include <QTableView>
#include <QWidget>

#include "database.h"

namespace Ui {
class DataBaseView;
}
//Класс для вывода информаций с БД
class DataBaseView : public QWidget {
    Q_OBJECT
private:
    //Установка БД в виджет
    void setupModel(const QString &tableName, const QStringList &headers);

    //Создание UI составляющей
    void createUI();
public:
    explicit DataBaseView(QString tableName = "Item", QWidget *parent = nullptr);
    ~DataBaseView();
private:
    QSqlTableModel *model;
    QString tableName;
    Ui::DataBaseView *ui;
};

#endif // DATABASEVIEW_H
