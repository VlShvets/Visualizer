#ifndef TERTIARYPROCESSINGOFDATA_H
#define TERTIARYPROCESSINGOFDATA_H

#include "target.h"

#include <QMap>

#include "TAir.h"
#include "TSea.h"

namespace Visualizer
{

using namespace BIUS_A100;
using namespace PTPV::air;
using namespace PTPV::sea;

/// Класс внутренней третичной обработки данных
class TertiaryProcessingOfData
{
public:
    explicit    TertiaryProcessingOfData();
    ~TertiaryProcessingOfData();

    /// Установка указателя на статический массив сообщений об эталонах
    void                        setTUTrcMsg(TUTrcMsg *_tUTrcMsg);

    /// Возврат указателя на словарь воздушных трасс
    inline QMap <int, Track>    *getAirTracks();

    /// Возврат указателя на словарь поверхностных трасс
    inline QMap <int, Track>    *getSurfaceTracks();

    /// Вычислительный процесс
    void                        run(const int _count, const float _currentTime);

private:
    /// Обновление словаря воздушных трасс
    void                            updateAirTracks();

    /// Обновление словаря поверхностных трасс
    void                            updateSurfaceTracks();

    /// Приём результатов периодической проверки по каждой воздушной трассе
    static void                     fpResultAir();

    /// Приём результатов периодической проверки по каждой поверхностной трассе
    static void                     fpResultSurface(PTPV_TGenTrcMsg *_pGenTrcMsg, void *_pobject);

    /// --------------------------------------------------
    /// Указатели
    /// --------------------------------------------------

    /// Указатели на объекты классов
    TAir        *tAir;      /// Указатель на объект класса третичной обработки данных по воздушным объектам
    TSea        *tSurface;  /// Указатель на объект класса третичной обработки данных по поверхностным объектам

    /// Указатели на статические массивы
    TUTrcMsg    *tUTrcMsg;  /// Указатель на статический массив сообщений об эталонах

    /// --------------------------------------------------
    /// Переменные
    /// --------------------------------------------------

    /// Время последнего вызова периодической проверки
    float   periodicLastTime;   /// Время последнего вызова периодической проверки

    /// Статические массивы структур трасс
    PTPV_TGenTrc    tGenTrcAir[UGEN_TRC_MAX + 1];               /// Статический массив структур воздушных трасс
    PTPV_TGenTrc    tGenTrcSurface[UGEN_SURFACE_TRC_MAX + 1];   /// Статический массив структур поверхностных трасс

    /// Словарь параметров трасс
    QMap <int, Track>   airTracks;      /// Словарь воздушных трасс         <номер, структура параметров>
    QMap <int, Track>   surfaceTracks;  /// Словарь поверхностных трасс     <номер, структура параметров>

    /// Статические переменные
    static air::TMsgFormSet     tMsgFormSetAir;         /// Признаки формирования сообщений потребителям по воздушным объектам
    static sea::TMsgFormSet     tMsgFormSetSurface;     /// Признаки формирования сообщений потребителям по поверхностным объектам
    static PTPV_TGenTrcMsg      tGenTrcMsg[2];          /// Сообщение с результатом третичной обработки данных
    static TUTrcMsg             tOrderSP[2];            /// Распоряжения третичной обработки данных (не используются)

    /// Статический указатель
    static TertiaryProcessingOfData     *tempObject;    /// Статический указатель для работы с не статическими объектами класса
};

/// Возврат указателя на словарь воздушных трасс
QMap <int, Track> *TertiaryProcessingOfData::getAirTracks()
{
    return &airTracks;
}

/// Возврат указателя на словарь поверхностных трасс
QMap <int, Track> *TertiaryProcessingOfData::getSurfaceTracks()
{
    return &surfaceTracks;
}

}

#endif // TERTIARYPROCESSINGOFDATA_H
