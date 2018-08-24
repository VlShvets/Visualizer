#ifndef PRELIMINARYPROCESSINGOFDATA_H
#define PRELIMINARYPROCESSINGOFDATA_H

#include "TImit.h"
#include "Poi.h"

namespace Visualizer
{

using namespace BIUS_A100;

/// Класс внутренней предварительной обработки данных
class PreliminaryProcessingOfData
{
public:
    explicit            PreliminaryProcessingOfData();
    ~PreliminaryProcessingOfData();

    /// Установка указателя на статический массив эталонов
    void                setTPubEtalon(TPubEtalon *_tPubEtalon);

    /// Установка указателя на статический массив сообщений об эталонах
    void                setTMsgTrc(TMsgTrc *_tMsgTrc);

    /// Возвращение указателя на статический массив сообщений об эталонах
    inline TUTrcMsg     *getTUTrcMsg();


    /// Вычислительный процесс
    void                run(const int _count, const float _currentTime);

private:
    /// --------------------------------------------------
    /// Указатели на объекты классов
    /// --------------------------------------------------

    /// Указатели на статические массивы
    TPubEtalon  *tPubEtalon;    /// Указатель на статический массив эталонов
    TMsgTrc     *tMsgTrc;       /// Указатель на статический массив сообщений об эталонах

    /// --------------------------------------------------
    /// Переменные
    /// --------------------------------------------------

    /// Статические массивы
    TUTrcMsg    tUTrcMsg[UGEN_TRC_MAX + 1];     /// Статический массив сообщений об эталонах
};

/// Возвращение указателя на статический массив сообщений об эталонах
TUTrcMsg *PreliminaryProcessingOfData::getTUTrcMsg()
{
    return tUTrcMsg;
}

}

#endif // PRELIMINARYPROCESSINGOFDATA_H
