#include "tertiaryprocessingofdata.h"

namespace Visualizer
{

/// Статические переменные
air::TMsgFormSet    TertiaryProcessingOfData::tMsgFormSetAir;       /// Признаки формирования сообщений потребителям по воздушным объектам
sea::TMsgFormSet    TertiaryProcessingOfData::tMsgFormSetSurface;   /// Признаки формирования сообщений потребителям по поверхностным объектам
PTPV_TGenTrcMsg     TertiaryProcessingOfData::tGenTrcMsg[2];        /// Сообщение с результатом третичной обработки данных
TUTrcMsg            TertiaryProcessingOfData::tOrderSP[2];          /// Распоряжения третичной обработки данных (не используются)

/// Статический указатель
TertiaryProcessingOfData *TertiaryProcessingOfData::tempObject = nullptr;

/// Класс внутренней третичной обработки данных
TertiaryProcessingOfData::TertiaryProcessingOfData()
{
    tAir        = new TAir;
    tSurface    = new TSea;

    periodicLastTime = 0.0;

    /// Установка статического указателя для работы с нестатическими объектами класса
    tempObject = this;
}

TertiaryProcessingOfData::~TertiaryProcessingOfData()
{
    surfaceTracks.clear();
    airTracks.clear();

    /// Очищение указателей на объекты классов
    delete tSurface;
    tSurface    = nullptr;
    delete tAir;
    tAir        = nullptr;

    /// Очищение указателей на статические массивы
    tUTrcMsg    = nullptr;
}

/// Установка указателя на статический массив сообщений об эталонах
void TertiaryProcessingOfData::setTUTrcMsg(TUTrcMsg *_tUTrcMsg)
{
    if(_tUTrcMsg == nullptr)
        return;

    tUTrcMsg = _tUTrcMsg;
}

/// Вычислительный процесс
void TertiaryProcessingOfData::run(const int _count, const float _currentTime)
{
    if(tUTrcMsg == nullptr)
        return;

    for(int i = 1; i < _count + 1; ++i)
    {
        switch(tUTrcMsg[i].objClass)
        {
        /// Воздушные трассы
        case UOC_AIR:
        {
            tAir->GetMsg(tUTrcMsg[i], _currentTime, &tMsgFormSetAir, tGenTrcMsg, tOrderSP);

            for(int j = 0; j < 2; ++j)
            {
                if(tMsgFormSetAir.genTrcMsg[j])
                    tGenTrcAir[tGenTrcMsg[j].genTrcNum] = tGenTrcMsg[j].trc;
            }

        }
            break;
            /// Поверхностные трассы
        case UOC_SEA:
        case UOC_GROUND:
        case UOC_SURFACE:
        {
            tSurface->GetMsg(tUTrcMsg[i], _currentTime, &tMsgFormSetSurface, tGenTrcMsg);

            for(int j = 0; j < 2; ++j)
            {
                if(tMsgFormSetSurface.genTrcMsg[j])
                    tGenTrcSurface[tGenTrcMsg[j].genTrcNum] = tGenTrcMsg[j].trc;
            }

        }
            break;
        default:
            break;
        }
    }

    /// Периодическая проверка состояний объектов
    if(abs(_currentTime - periodicLastTime) > 10)
    {
        /// Периодическая проверка воздушных трасс
        tAir->TrcStateCheck(_currentTime, &tMsgFormSetAir, tGenTrcMsg, tOrderSP, fpResultAir);
        /// Периодическая проверка поверхностных трасс
        tSurface->TrcStateCheck(_currentTime, fpResultSurface);

        /// Обновление времени последнего вызова периодической проверки
        periodicLastTime = _currentTime;
    }

    updateAirTracks();
    updateSurfaceTracks();
}

/// Обновление словаря воздушных трасс
void TertiaryProcessingOfData::updateAirTracks()
{
    for(int i = 1; i < UGEN_TRC_MAX + 1; ++i)
    {
        if(tGenTrcAir[i].tXYUpdate != 0)
        {
            if(!airTracks.contains(i))
                airTracks[i].setTGenTrc(&tGenTrcAir[i]);

            airTracks[i].saveTrack();
        }
    }
}

/// Обновление словаря поверхностных трасс
void TertiaryProcessingOfData::updateSurfaceTracks()
{
    for(int i = 1; i < UGEN_SURFACE_TRC_MAX + 1; ++i)
    {
        if(tGenTrcSurface[i].tXYUpdate != 0.0)
        {
            if(!surfaceTracks.contains(i))
                surfaceTracks[i].setTGenTrc(&tGenTrcSurface[i]);

            surfaceTracks[i].saveTrack();
        }
    }
}

/// Приём результатов "периодики" по каждой воздушной трассе
void TertiaryProcessingOfData::fpResultAir()
{
    if(tMsgFormSetAir.genTrcMsg[0])
    {
        /// Сброс трассы
        if(tGenTrcMsg[0].trcState == EU_TS_END)
        {
            tempObject->tGenTrcAir[tGenTrcMsg[0].genTrcNum].tXYUpdate = 0.0;
            tempObject->airTracks.remove(tGenTrcMsg[0].genTrcNum);
        }
        /// Обновление сопровождаемых трасс
        else if(tGenTrcMsg[0].sensDelete == EU_YES)
            tempObject->tGenTrcAir[tGenTrcMsg[0].genTrcNum] = tGenTrcMsg[0].trc;
    }
}

/// Приём результатов "периодики" по каждой поверхностной трассе
void TertiaryProcessingOfData::fpResultSurface(PTPV_TGenTrcMsg *_pGenTrcMsg, void *_pobject)
{
    /// Сброс трассы
    if(_pGenTrcMsg[0].trcState == EU_TS_END)
    {
        tempObject->tGenTrcSurface[_pGenTrcMsg[0].genTrcNum].tXYUpdate = 0.0;
        tempObject->surfaceTracks.remove(_pGenTrcMsg[0].genTrcNum);
    }
    /// Обновление сопровождаемых трасс
    else if(_pGenTrcMsg[0].sensDelete == EU_YES)
        tempObject->tGenTrcSurface[_pGenTrcMsg[0].genTrcNum] = _pGenTrcMsg[0].trc;
}

}
