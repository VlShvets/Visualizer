#include "imitation.h"

namespace Visualizer
{

/// Класс внутренней имитации
Imitation::Imitation()
{
    tImit = new TImit;

    tPubEtalon = tImit->PubEtalon;
    tMsgTrc = tImit->MsgTrc;

    tImit->ObjectStart(0.1);
}

Imitation::~Imitation()
{
//    stationary.clear();
    etalons.clear();

    tPubEtalon  = nullptr;
    tMsgTrc     = nullptr;

    delete tImit;
    tImit = nullptr;
}

/// Возвращение указателя на статический массив эталонов
TPubEtalon *Imitation::getTPubEtalon()
{
    if(tPubEtalon == nullptr)
        return nullptr;

    return tPubEtalon;
}

/// Возвращение указателя на статический массив сообщений об эталонах
TMsgTrc *Imitation::getTMsgTrc()
{
    if(tMsgTrc == nullptr)
        return nullptr;

    return tMsgTrc;
}

/// Вычислительный процесс
int Imitation::run(const float _currentTime)
{
    int count = tImit->ImitAir(_currentTime);

    updateEtalons(_currentTime);

    return count;
}

/// Обновление словаря эталонов
void Imitation::updateEtalons(const float _currentTime)
{
    if(tPubEtalon == nullptr)
        return;

    for(int i = 1; i < UGEN_TRC_MAX + 1; ++i)
    {
        if(tPubEtalon[i].visual == EU_YES)
        {
            if(!etalons.contains(i))
                etalons[i].setTPubEtalon(&tPubEtalon[i]);

            etalons[i].saveEtalon(_currentTime);
        }
        else
        {
            if(etalons.contains(i))
                etalons.remove(i);
        }
    }
}

}
