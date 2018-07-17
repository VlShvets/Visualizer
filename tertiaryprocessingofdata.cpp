#include "tertiaryprocessingofdata.h"

namespace Visualizer
{

//air::TMsgFormSet MainThread::msgFormSet;     /// Признаки формирования сообщений потребителям по рез-там обработки на "периодике"
//PTPV_TGenTrcMsg MainThread::genTrcMsg;       /// Сообщение с результатом ТОИ на "периодике"
//TUTrcMsg MainThread::orderSP;                /// Распоряжения ТОИ на ВОИ на "периодике" (не используется)

/// Класс внутренней третичной обработки информации
TertiaryProcessingOfData::TertiaryProcessingOfData()
{
    tAir = new TAir;
    tSurface = new TSea;
}

TertiaryProcessingOfData::~TertiaryProcessingOfData()
{
}

/// Вычислительный процесс
void TertiaryProcessingOfData::run()
{
//    double T = 0.0;                         /// Общее время
//    T = (double) clock() / CLOCKS_PER_SEC;  /// Начало цикла по времени

//    static TImit Imit;  /// Объект класса Имитации
//    int count = 0;      /// Колличество формуляров для Третичной Обработки Информации

//    TUTrcMsg Msg;   /// Результат Предварительной Обработки Информации

//    static TAir Air;                                                    /// Объект класса Третичной Обработки Информации по воздушным объектам
//    static TSea Surface;                                                /// Объект класса Третичной Обработки Информации по поверхностным объектам
//    PTPV_TGenTrcMsg pGenTrcMsg[2];                                      /// Результат Третичной Обработки Информации
//    TUTrcMsg pOrderSP[2];                                               /// Распоряжения Третичной Обработки Информации
//    PTPV_TGenTrc pGenTrcAir[BIUS_A100::UGEN_TRC_MAX + 1];               /// Массив воздушных объектов для отображения
//    memset(pGenTrcAir, 0, sizeof(pGenTrcAir));                          /// Обнуление массива воздушных объектов
//    PTPV_TGenTrc pGenTrcSurface[BIUS_A100::UGEN_SURFACE_TRC_MAX + 501];   /// Массив поверхностных объектов для отображения
//    memset(pGenTrcSurface, 0, sizeof(pGenTrcSurface));                  /// Обнуление массива поверхностных объектов

//    Imit.ObjectStart(T); /// Заполнение исходных даннных Имитации

//    while(T < 10000.0)
//    {
//        msleep(500.0);  /// 0.5000 c
//        T = (double) clock() / CLOCKS_PER_SEC;
//        std::cout << "T = " << T << std::endl;

//        mainWindow->sendToTool(Time, T);

//        /// Имитация эталонов

//        count = Imit.ImitAir(T);

//        /// Предварительная и третичная обработка информации

//        if(count > 0)
//        {
//            for(int i = 1; i < count + 1; ++i)
//            {

//                /// Предварительная обработка информации


//                /// Третичная Обработка Информации

//                switch (Msg.objClass)
//                {

//                /// Воздушные цели

//                case BIUS_A100::EUObjClass::UOC_AIR:
//                {
//                    air::TMsgFormSet msgFormSet;
//                    Air.GetMsg(Msg, T, &msgFormSet, pGenTrcMsg, pOrderSP);

//                    /// Заполнение массива воздушных целей для отображения
//                    for(int j = 0; j < 2; ++j)
//                    {
//                        if(msgFormSet.genTrcMsg[j])
//                            pGenTrcAir[pGenTrcMsg[j].genTrcNum] = pGenTrcMsg[j].trc;
//                    }
//                }
//                break;

//                /// Поверхностные цели

//                case BIUS_A100::EUObjClass::UOC_SEA:
//                case BIUS_A100::EUObjClass::UOC_GROUND:
//                case BIUS_A100::EUObjClass::UOC_SURFACE:
//                {
//                    sea::TMsgFormSet msgFormSet;
//                    Surface.GetMsg(Msg, T, &msgFormSet, pGenTrcMsg);

//                    /// Заполнение массива поверхностных целей для отображения
//                    for(int j = 0; j < 2; ++j)
//                    {
//                        if(msgFormSet.genTrcMsg[j])
//                            pGenTrcSurface[pGenTrcMsg[j].genTrcNum + 500] = pGenTrcMsg[j].trc;
//                    }
//                }
//                break;

//                default:
//                break;
//                }
//            }
//        }

//        /// Определение количества воздушных объектов
//        count = 0;
//        for(int i = 1; i < BIUS_A100::UGEN_TRC_MAX + 1; ++i)
//        {
//            if(pGenTrcAir[i].tXYUpdate != 0)
//                ++count;
//        }
//        mainWindow->sendToTool(TrackAir, count);

//        /// Определение количества поверхностных объектов
//        count = 0;
//        for(int i = 1; i < BIUS_A100::UGEN_SURFACE_TRC_MAX + 1; ++i)
//        {
//            if(pGenTrcSurface[i].tXYUpdate != 0)
//                ++count;
//        }
//        mainWindow->sendToTool(TrackSurface, count);

//        msleep(500.0);  /// 0.5000 c

//        /// Периодическая проверка состояний объектов
//        if((int) T % 10 == 0)
//        {
//            Air.TrcStateCheck(T, &msgFormSet, &genTrcMsg, &orderSP, fpResultAir);
//            Surface.TrcStateCheck(T, fpResultSurface);

//            /// Определение количества воздушных объектов
//            count = 0;
//            for(int i = 1; i < BIUS_A100::UGEN_TRC_MAX + 1; ++i)
//            {
//                if(pGenTrcAir[i].tXYUpdate != 0)
//                    ++count;
//            }
//            mainWindow->sendToTool(TrackAir, count);

//            /// Определение количества поверхностных объектов
//            count = 0;
//            for(int i = 1; i < BIUS_A100::UGEN_SURFACE_TRC_MAX + 1; ++i)
//            {
//                if(pGenTrcSurface[i].tXYUpdate != 0)
//                    ++count;
//            }
//            mainWindow->sendToTool(TrackSurface, count);
//        }

//        /// Обнуление количества сообщений
//        count = 0;

//        /// Завершение работы
//        if(!mainWindow->isVisible())
//            quit();
//    }

//    exec();
}

void TertiaryProcessingOfData::fpResultAir()
{

}

void TertiaryProcessingOfData::fpResultSurface(PTPV_TGenTrcMsg *pGenTrcMsg, void *pobject)
{

}

}
