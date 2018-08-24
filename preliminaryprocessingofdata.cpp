#include "preliminaryprocessingofdata.h"

namespace Visualizer
{

/// Класс внутренней предварительной обработки данных
PreliminaryProcessingOfData::PreliminaryProcessingOfData()
{    
}

PreliminaryProcessingOfData::~PreliminaryProcessingOfData()
{
    /// Очищение указателей на статические массивы
    tPubEtalon  = nullptr;
    tMsgTrc     = nullptr;
}

/// Установление указателя на статический массив эталонов
void PreliminaryProcessingOfData::setTPubEtalon(TPubEtalon *_tPubEtalon)
{
    if(_tPubEtalon == nullptr)
        return;

    tPubEtalon = _tPubEtalon;
}

/// Установка указателя на статический массив сообщений об эталонах
void PreliminaryProcessingOfData::setTMsgTrc(TMsgTrc *_tMsgTrc)
{
    if(_tMsgTrc == nullptr)
        return;

    tMsgTrc = _tMsgTrc;
}

/// Вычислительный процесс
void PreliminaryProcessingOfData::run(const int _count, const float _currentTime)
{
    if(tPubEtalon == nullptr || tMsgTrc == nullptr)
        return;

    for(int i = 1; i < _count + 1; ++i)
        Poi::PackMsg(tPubEtalon[tMsgTrc[i].numEt], tMsgTrc[i], &tUTrcMsg[i], _currentTime);
}

}
