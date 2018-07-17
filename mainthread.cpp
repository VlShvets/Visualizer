#include "mainthread.h"

namespace Visualizer
{

/// Класс главного потока вычислений
MainThread::MainThread(Painter *_painter, Status *_status, const QString _deltaTime)
    : painter(_painter), status(_status), deltaTime(_deltaTime.toInt()),
      isCompleted(false), isPause(false)
{
    imitation = new Imitation;
    tertiaryProcessingOfData = new TertiaryProcessingOfData;

    /// --------------------------------------------------
    /// Имитация
    /// --------------------------------------------------

    /// Получение поверхностных стацционарных объектов
//    stationary = imitation->getStationary();

    /// Получение эталонов
    etalons = imitation->getEtalons();

    /// --------------------------------------------------
    /// Третичная обработка данных
    /// --------------------------------------------------

    /// Отправление эталонов в класс третичной обработки данных
    tertiaryProcessingOfData->setEtalons(*etalons);

    /// Получение воздушных трасс
    airTracks = tertiaryProcessingOfData->getAirTracks();

    /// Получение поверхностных трасс
    surfaceTrack = tertiaryProcessingOfData->getSurfaceTracks();

    /// --------------------------------------------------
    /// Отрисовка
    /// --------------------------------------------------

    /// Отправление ЗКВ на виджет отрисовки
//    painter->setStationary(*stationary);

    /// Отправление эталонов на виджет отрисокви
//    painter->setEtalons(*etalons);

    /// Отправление трасс на виджет отрисовки
//    painter->setTracks(*tracks);
}

MainThread::~MainThread()
{
    delete tertiaryProcessingOfData;
    delete imitation;

    /// Очищение виджета отрисовки
    painter->clearing();

    /// Очищение виджета отображения текущего состояния потока вычислений
//    status->clearing();
}

/// Поток вычислений
void MainThread::run()
{
    float time = 0.0;   /// Время

    /// Флаг завершения потока вычислений
    while(!isCompleted)
    {
         /// Флаг приостановки потока вычислений
        if(isPause)
        {
            msleep(PAUSE_T);
            continue;
        }

        msleep(WAITING_T);
        time += deltaTime;

        /// Имитация
        imitation->run(time);

        /// Третичная обработка данных
        tertiaryProcessingOfData->run();

        /// Определение уровня угроз
//        definitionOfThreatLevel->run();

        /// График количественного состава налета
//        graphOfTracksCount->loadTracksCount();
    }
}

}
