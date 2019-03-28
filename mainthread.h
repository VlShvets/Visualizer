#ifndef MAINTHREAD_H
#define MAINTHREAD_H

#include "painter.h"
#include "status.h"

#include "dbthread.h"
#include "imitation.h"
#include "preliminaryprocessingofdata.h"
#include "tertiaryprocessingofdata.h"

#include <QThread>
#include <databasewidget.h>

namespace Visualizer
{

/// Класс главного потока вычислений
class MainThread : public QThread
{
    Q_OBJECT

public:
    explicit    MainThread(Painter *_painter, Status *_status,DataBaseWidget *_dataBaseWidget, const QString _deltaTime); //
    ~MainThread();

    /// Поток вычислений
    void run();

    /// Установление флага приостановления потока вычислений
    inline void     setPause(const bool _pause);

    /// Возвращение флага приостановления потока вычислений
    inline bool     isPaused();

    /// Передача информации в строку состояния
    inline void     sendToStatus(TypeOfInfo _typeOfInfo, double _info);

    void            completeOfThreadDb();
signals:
    void signalInDb(int, int, int, int);
public slots:
    /// Завершение потока вычислений
    inline void     complete();

    /// Установление времени между итерациями потока вычислений
    inline void     setSleepTime(const QString _sleepTime);

private:
    /// --------------------------------------------------
    /// Указатели на объекты классов
    /// --------------------------------------------------

    Painter                     *painter;                       /// Указатель на объект класса отрисовки эталонов и трасс
    Status                      *status;                        /// Указатель на объект класса отображения текущего состояния потока вычислений

    Imitation                   *imitation;                     /// Указатель на объект класса внутренней имитации
    PreliminaryProcessingOfData *preliminaryProcessingOfData;   /// Указатель на объект класса внутренней предварительной обработки информации
    TertiaryProcessingOfData    *tertiaryProcessingOfData;      /// Указатель на объект класса внутренней третичной обработки информации
    DbThread                    *dbThread;
    DataBaseWidget              *dataBaseWidget;

    /// --------------------------------------------------
    /// Переменные
    /// --------------------------------------------------

    /// Параметры процесса потока
    int                 sleepTime;      /// Время между итерациями потока вычислений (в мс)
    bool                isCompleted;    /// Флаг завершения потока вычислений
    bool                isPause;        /// Флаг приостановления потока вычислений

    /// Указатели на словари параметров ЗКВ, эталонов и трасс
//    QMap <int, Stationary>  *stationary;    /// Словарь стационарных объектов               <номер, структура параметров>
    QMap <int, Etalon>      *etalons;       /// Указатель на словарь эталонов               <номер, структура параметров>
    QMap <int, Track>       *airTracks;     /// Указатель на словарь воздушных трасс        <номер, структура параметров>
    QMap <int, Track>       *surfaceTracks; /// Указатель на словарь поверхностных трасс    <номер, структура параметров>

    /// --------------------------------------------------
    /// Константы
    /// --------------------------------------------------

    static constexpr float  PAUSE_T = 1000.0;   /// Интервал проверки флага приостановления потока вычислений       (в мс)
    static constexpr float  DELTA_T = 1.0;      /// Интервал времени ожидания между итерациями потока вычислний     (в мс)
};

/// Установка флага приостановления потока вычислений
void MainThread::setPause(const bool _pause)
{
    isPause = _pause;

    //Time redaction
    dbThread->setPause(_pause);
}

/// Возвращение флага приостановления потока вычислений
bool MainThread::isPaused()
{
    return isPause;
}

/// Передача информации в строку состояния
void MainThread::sendToStatus(TypeOfInfo _typeOfInfo, double _info)
{
    status->showInfo(_typeOfInfo, _info);
}

/// Завершение потока вычислений
void MainThread::complete()
{
    isCompleted = true;

    //Time redaction
    dbThread->setComplited(true);
}

/// Установление времени между итерациями потока вычислений
void MainThread::setSleepTime(const QString _sleepTime)
{
    sleepTime = _sleepTime.toInt();
}

}

#endif // MAINTHREAD_H
