#ifndef TERTIARYPROCESSINGOFDATA_H
#define TERTIARYPROCESSINGOFDATA_H

#include "target.h"

#include <QMap>

#include "TAir.h"
#include "TSea.h"

using namespace BIUS_A100::PTPV::air;
using namespace BIUS_A100::PTPV::sea;

namespace Visualizer
{

/// Класс внутренней третичной обработки информации
class TertiaryProcessingOfData
{
public:
    explicit    TertiaryProcessingOfData();
    ~TertiaryProcessingOfData();

    /// Установление эталонов
    inline void                 setEtalons(const QMap <int, Etalon> &_etalons);

    /// Возврат указателя на словарь воздушных трасс
    inline QMap <int, Track>    *getAirTracks();

    /// Возврат указателя на словарь поверхностных трасс
    inline QMap <int, Track>    *getSurfaceTracks();

    /// Вычислительный процесс
    void                        run();

private:
    /// Приём результатов "периодики" Air по каждой трассе
    static void fpResultAir();

    /// Приём результатов "периодики" Surface по каждой трассе
    static void fpResultSurface(PTPV_TGenTrcMsg* pGenTrcMsg, void *pobject);

    /// --------------------------------------------------
    /// Указатели на объекты классов
    /// --------------------------------------------------
    TAir        *tAir;      /// Указатель на объект класса третичной обработки данных по воздушным объектам
    TSea        *tSurface;  /// Указатель на объект класса третичной обработки данных по поверхностным объектам

    /// --------------------------------------------------
    /// Переменные
    /// --------------------------------------------------

    /// Словари параметров стационарных объектов и эталонов
    const QMap <int, Etalon>        *etalons;       /// Словарь эталонов                <номер, структура параметров>

    /// Словарь параметров трасс
    QMap <int, Track>               airTracks;      /// Словарь воздушных трасс         <номер, структура параметров>
    QMap <int, Track>               surfaceTrack;   /// Словарь поверхностных трасс     <номер, структура параметров>

    static air::TMsgFormSet msgFormSet;     /// Признаки формирования сообщений потребителям по рез-там обработки на "периодике"
    static PTPV_TGenTrcMsg genTrcMsg;       /// Сообщение с результатом ТОИ на "периодике"
    static TUTrcMsg orderSP;                /// Распоряжения ТОИ на ВОИ на "периодике" (не используется)
};

/// Установление эталонов
void TertiaryProcessingOfData::setEtalons(const QMap<int, Etalon> &_etalons)
{
    etalons = &_etalons;
}

/// Возврат указателя на словарь воздушных трасс
QMap<int, Track> *TertiaryProcessingOfData::getAirTracks()
{
    return &airTracks;
}

/// Возврат указателя на словарь поверхностных трасс
QMap<int, Track> *TertiaryProcessingOfData::getSurfaceTracks()
{
    return &surfaceTrack;
}

}

#endif // TERTIARYPROCESSINGOFDATA_H
