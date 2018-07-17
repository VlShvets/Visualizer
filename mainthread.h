#ifndef MAINTHREAD_H
#define MAINTHREAD_H

#include "painter.h"
#include "imitation.h"
#include "tertiaryprocessingofdata.h"
#include "status.h"

#include <QThread>

namespace Visualizer
{

/// Класс главного потока вычислений
class MainThread : public QThread
{
    Q_OBJECT

public:
    explicit    MainThread(Painter *_painter, Status *_status, const QString _deltaTime);
    ~MainThread();

    /// Поток вычислений
    void run();

    /// Установление флага приостановления потока вычислений
    inline void     setPause(const bool _pause);

    /// Возвращение флага приостановления потока вычислений
    inline bool     isPaused();

    /// Передача информации в строку состояния
    inline void     sendToStatus(TypeOfInfo _typeOfInfo, double _info);

public slots:
    /// Завершение потока вычислений
    inline void     complete();

    /// Установление времени между итерациями потока вычислений
    inline void     setDeltaTime(const QString _deltaTime);

private:
    /// --------------------------------------------------
    /// Указатели на объекты классов
    /// --------------------------------------------------

    Imitation                   *imitation;                 /// Указатель на объект класса внутренней имитации
    TertiaryProcessingOfData    *tertiaryProcessingOfData;  /// Указатель на объект класса внутренней третичной обработки информации
    Painter                     *painter;                   /// Указатель на объект класса отрисовки эталонов и трасс
    Status                      *status;                    /// Указатель на объект класса отображения текущего состояния потока вычислений

    /// --------------------------------------------------
    /// Переменные
    /// --------------------------------------------------

    /// Параметры процесса потока
    int                 deltaTime;      /// Время между итерациями потока вычислений (в мс)
    bool                isCompleted;    /// Флаг завершения потока вычислений
    bool                isPause;        /// Флаг приостановления потока вычислений

    /// Словари параметров ЗКВ, эталонов и трасс
//    QMap <int, Stationary>      *stationary;    /// Словарь стационарных объектов   <номер, структура параметров>
    const QMap <int, Etalon>    *etalons;       /// Словарь эталонов                <номер, структура параметров>
    QMap <int, Track>           *airTracks;     /// Словарь воздушных трасс         <номер, структура параметров>
    QMap <int, Track>           *surfaceTrack;  /// Словарь поверхностных трасс     <номер, структура параметров>

    /// --------------------------------------------------
    /// Константы
    /// --------------------------------------------------

    static constexpr float  PAUSE_T     = 1000.0;   /// Интервал проверки флага приостановления потока вычислений       (в мс)
    static constexpr float  WAITING_T   = 1000.0;   /// Интервал времени ожидания между итерациями потока вычислний     (в мс)
};

/// Установление флага приостановления потока вычислений
void MainThread::setPause(const bool _pause)
{
    isPause = _pause;
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
}

/// Установление времени между итерациями потока вычислений
void MainThread::setDeltaTime(const QString _deltaTime)
{
    deltaTime = _deltaTime.toInt();
}

}

#endif // MAINTHREAD_H
