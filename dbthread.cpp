#include "dbthread.h"

namespace Visualizer {

DbThread::DbThread(DataBaseWidget *_dataBaseWidget) : dataBaseWidget(_dataBaseWidget)
{
    startTimer(10000);
}

void DbThread::operationWithDb(int y, int x, int s, int n)
{

      queDbObjects.enqueue(DbObject(y,x,s,n));

}

Visualizer::DbThread::~DbThread()
{
    surfaceTrack = nullptr;
    dataBaseWidget = nullptr;

}

void DbThread::run()
{

    while(!is_complitely){
        if(is_pause){
            msleep(1000);
            continue;
        }

        QSqlQuery query;
        DbObject dbobject;

        if(!queDbObjects.empty()){

            query.exec("SELECT id, numTrack, type, class, time FROM Tracks");

            dbobject = queDbObjects.dequeue();

            while(query.next() && dbobject.numTrack != query.value(1).toInt()){
                int numTrack   = query.value(1).toInt();
                QString _type  = query.value(2).toString();
                QString _class = query.value(3).toString();
                QString _time  = query.value(4).toString();
            }
            if(dbobject.numTrack == query.value(1).toInt()){
                //обновление обьекта в бд
                query.exec("UPDATE Tracks SET time = "+ QString::number(dbobject.time) +", x = " + QString::number(dbobject.x) +
                           ", y = " + QString::number(dbobject.y) + " WHERE numTrack = " + QString::number(dbobject.numTrack));

            }else{
                //выполняем вставку объекта в таблицу БД

                query.exec("INSERT INTO Tracks (numTrack, type, class, time, x, y) VALUES(" + QString::number(dbobject.numTrack) +
                           ", 'sea', 'board', 100, " + QString::number(dbobject.x )+ ", " + QString::number(dbobject.y) + ")");

            }
            dataBaseWidget->updateDb();

        }

        msleep(1000);
    }
}

void DbThread::timerEvent(QTimerEvent *)
{
    if(queDbObjects.size() > 30){
        queDbObjects.clear();
    }
}
}
