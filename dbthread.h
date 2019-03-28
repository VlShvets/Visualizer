#ifndef DBTHREAD_H
#define DBTHREAD_H

#include <QDebug>
#include "target.h"
#include <QThread>
#include <QString>
#include <databasewidget.h>
#include <QSqlQuery>
#include <QErrorMessage>
#include <QVector>
#include <QTimerEvent>

namespace Visualizer{

//поток работы с базой данных
//поток осуществляет работу с бд посредством сигнала из главного потока Mainthread

class DbThread : public QThread
{
    Q_OBJECT
public:
    explicit DbThread(DataBaseWidget *_dataBaseWidget);
    ~DbThread();

    inline      void requestInDb(int x, int y) {qDebug()<<"x: "<<x<<", y: "<<y<<" ."<<"Request In DataBases";}
    inline      void writeInDb(int s) {qDebug() <<"s: "<<s<<"Write in DataBases or No";}

    inline      bool getComplited() {return is_pause;}
    inline      void setComplited(bool _compl) {is_complitely = _compl;}
    inline      void setPause(bool _pause) {is_pause = _pause;}

    void        run();
    void        timerEvent(QTimerEvent *);
    void        complete();
signals:
    void get_ptr_for_DbaseWidget();

public slots:
    void operationWithDb(int x, int y, int s, int n);

private:
    //структура обьектов в бд
    struct DbObject{
        DbObject(){}
        DbObject(int _x, int _y, int _time, int _numTrack) : x{_x}, y{_y}, numTrack{_numTrack}, time{_time} {}
        int x;
        int y;
        int numTrack;
        int time;
    };

    bool is_complitely      = false;
    bool is_pause           = false;
    QMap<int, Track>        *surfaceTrack;
    QQueue<DbObject>        queDbObjects;       // Очередь обьектов для записи в бд
    DataBaseWidget          *dataBaseWidget;

};
}

#endif // DBTHREAD_H
