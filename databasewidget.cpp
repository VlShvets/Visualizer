#include "databasewidget.h"

DataBaseWidget::DataBaseWidget()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("E:\\PTPV_DB.db");
    db.open();
    if (!db.open()){
        qDebug()<<"Cannot open Db: "<<db.lastError();
    }else{
        qDebug()<<"BdConnect";
    }
    setWindowTitle("База данных");

    model = new QSqlQueryModel;

    model->setQuery("SELECT * FROM Tracks");

    this->setModel(model);

}

DataBaseWidget::~DataBaseWidget()
{
    delete model;
}


void DataBaseWidget::updateDb()
{
    model->setQuery("SELECT * FROM Tracks");
}
