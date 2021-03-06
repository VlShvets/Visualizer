#include "mainthread.h"

namespace Visualizer
{

/// Класс главного потока вычислений
MainThread::MainThread(Painter *_painter, Status *_status, const QString _deltaTime)
    : painter(_painter), status(_status), sleepTime(_deltaTime.toInt()),
      isCompleted(false), isPause(false)
{
    imitation                   = new Imitation;
    preliminaryProcessingOfData = new PreliminaryProcessingOfData;
    tertiaryProcessingOfData    = new TertiaryProcessingOfData;

    /// --------------------------------------------------
    /// Имитация
    /// --------------------------------------------------

    /// Получение поверхностных стацционарных объектов
//    stationary = imitation->getStationary();

    /// Получение эталонов
    etalons = imitation->getEtalons();

    /// --------------------------------------------------
    /// Предварительная обработка данных
    /// --------------------------------------------------

    /// Установка указателя на статический массив эталонов
    preliminaryProcessingOfData->setTPubEtalon(imitation->getTPubEtalon());

    /// Установка указателя на статический массив сообщений об эталонах
    preliminaryProcessingOfData->setTMsgTrc(imitation->getTMsgTrc());

    /// --------------------------------------------------
    /// Третичная обработка данных
    /// --------------------------------------------------

    /// Установка указателя на статический массив сообщений об эталонах
    tertiaryProcessingOfData->setTUTrcMsg(preliminaryProcessingOfData->getTUTrcMsg());

    /// Получение воздушных трасс
    airTracks = tertiaryProcessingOfData->getAirTracks();

    /// Получение поверхностных трасс
    surfaceTracks = tertiaryProcessingOfData->getSurfaceTracks();

    /// --------------------------------------------------
    /// Отрисовка
    /// --------------------------------------------------

    /// Отправление ЗКВ на виджет отрисовки
//    painter->setStationary(*stationary);

    /// Отправление эталонов на виджет отрисокви
    painter->setEtalons(*etalons);

    /// Отправление воздушных трасс на виджет отрисовки
    painter->setAirTracks(*airTracks);

    /// Отправление поверхностных трасс на виджет отрисовки
    painter->setSurfaceTracks(*surfaceTracks);
}

MainThread::~MainThread()
{
    /// Удаление объекта класса внутренней третичной обработки данных
    delete tertiaryProcessingOfData;
    tertiaryProcessingOfData        = nullptr;

    /// Удаление объекта класса внутренней предварительной обработки данных
    delete preliminaryProcessingOfData;
    preliminaryProcessingOfData     = nullptr;

    /// Удаление объекта класса внутренней имитации
    delete imitation;
    imitation                       = nullptr;

    /// Очищение виджета отрисовки
    painter->clearing();
    painter     = nullptr;

    /// Очищение виджета отображения текущего состояния потока вычислений
    status->clearing();
    status      = nullptr;

    /// Очищение указателей на словари параметров ЗКВ, эталонов и трасс
//    stationary      = nullptr;
    etalons         = nullptr;
    airTracks       = nullptr;
    surfaceTracks   = nullptr;
}

/// Поток вычислений
void MainThread::run()
{
    float   time    = 0.0;  /// Время
    int     count   = 0;    /// Количество сообщений для третичной обработки данных

    /// Флаг завершения потока вычислений
    while(!isCompleted)
    {
         /// Флаг приостановки потока вычислений
        if(isPause)
        {
            msleep(PAUSE_T);
            continue;
        }

        msleep(sleepTime);

        time += DELTA_T;
        status->showInfo(Time, time);

        /// Имитация
        count = imitation->run(time);

        /// Предварительная обработка данных
        preliminaryProcessingOfData->run(count, time);

        /// Третичная обработка данных
        tertiaryProcessingOfData->run(count, time);

        /// Определение количества воздушных объектов
        status->showInfo(AirTrack, airTracks->count());

        /// Определение количества поверхностных объектов
        status->showInfo(SurfaceTrack, surfaceTracks->count());

        /// Обнуление количества сообщений для третичной обработки данных
        count = 0;
    }
}

}
