#ifndef DATABASEWIDGET_H
#define DATABASEWIDGET_H

#include <QObject>
#include <QtSql>
#include <QTableView>
#include <QTableWidget>
#include <QMessageBox>
#include <QString>
#include <QDebug>
#include <QLabel>

class DataBaseWidget : public QTableView
{
    Q_OBJECT
public:
    DataBaseWidget();
    ~DataBaseWidget();

    void        updateDb();
    void        write_Db();

public slots:

    // (показать / скрыть) виджет бд
    inline void        show_hide(bool _b){ if(_b){ this->show(); }else{ this->hide(); }}

private:

    QSqlQuery query;
    QSqlQueryModel *model;
};

#endif // DATABASEWIDGET_H
