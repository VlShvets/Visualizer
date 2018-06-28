#include "MainThread.h"

MainThread::MainThread(MainWindow *_mainWindow) :
    mainWindow(_mainWindow)
{
}

air::TMsgFormSet MainThread::msgFormSet;     /// Признаки формирования сообщений потребителям по рез-там обработки на "периодике"
PTPV_TGenTrcMsg MainThread::genTrcMsg;       /// Сообщение с результатом ТОИ на "периодике"
TUTrcMsg MainThread::orderSP;                /// Распоряжения ТОИ на ВОИ на "периодике" (не используется)

void MainThread::run()
{
    double T = 0.0;                         /// Общее время
    T = (double) clock() / CLOCKS_PER_SEC;  /// Начало цикла по времени

    static TImit Imit;  /// Объект класса Имитации
    int count = 0;      /// Колличество формуляров для Третичной Обработки Информации

    TUTrcMsg Msg;   /// Результат Предварительной Обработки Информации

    BIUS_A100::TWP aWP;                                                 /// Объект класса условной точки, относительно котороый вычисляются координаты
    static TAir Air(aWP);                                               /// Объект класса Третичной Обработки Информации по воздушным объектам
    static TSea Surface;                                                /// Объект класса Третичной Обработки Информации по поверхностным объектам
    PTPV_TGenTrcMsg pGenTrcMsg[2];                                      /// Результат Третичной Обработки Информации
    TUTrcMsg pOrderSP[2];                                               /// Распоряжения Третичной Обработки Информации
    PTPV_TGenTrc pGenTrcAir[BIUS_A100::UGEN_TRC_MAX + 1];               /// Массив воздушных объектов для отображения
    memset(pGenTrcAir, 0, sizeof(pGenTrcAir));                          /// Обнуление массива воздушных объектов
    PTPV_TGenTrc pGenTrcSurface[BIUS_A100::UGEN_SURFACE_TRC_MAX + 501];   /// Массив поверхностных объектов для отображения
    memset(pGenTrcSurface, 0, sizeof(pGenTrcSurface));                  /// Обнуление массива поверхностных объектов

    Imit.ObjectStart(T); /// Заполнение исходных даннных Имитации

    while(T < 10000.0)
    {
        msleep(50.0);  /// 0.0500 c
//        msleep(500.0);  /// 0.5000 c
 T = (double) clock() / CLOCKS_PER_SEC*10;
//        T = (double) clock() / CLOCKS_PER_SEC;
        std::cout << "T = " << T << std::endl;

        mainWindow->sendToTool(Time, T);

//        QApplication::postEvent(mainWindow, new TPubEtalonEvent(Test::generateEtalons(5, currentT)));
//        QApplication::postEvent(mainWindow, new TGenTrcEvent(Test::generateTracks(5, currentT)));

        /// Имитация эталонов

        count = Imit.ImitAir(T);
//        testPubEtalon(Imit.PubEtalon, 5);

        QApplication::postEvent(mainWindow, new TPubEtalonEvent(Imit.PubEtalon, T));

        /// Предварительная и третичная обработка информации

        if(count > 0)
        {
            for(int i = 1; i < count + 1; ++i)
            {

                /// Предварительная обработка информации

                BIUS_A100::Poi::PackMsg(Imit.PubEtalon[Imit.MsgTrc[i].numEt], Imit.MsgTrc[i], &Msg, T);
//                testTrcMsg(Msg);

                /// Третичная Обработка Информации

                switch (Msg.objClass)
                {

                /// Воздушные цели

                case BIUS_A100::EUObjClass::UOC_AIR:
                {
                    air::TMsgFormSet msgFormSet;
                    Air.GetMsg(Msg, T, &msgFormSet, pGenTrcMsg, pOrderSP);
//                  testGenTrcMsg(pGenTrcMsg);

                    /// Заполнение массива воздушных целей для отображения
                    for(int j = 0; j < 2; ++j)
                    {
                        if(msgFormSet.genTrcMsg[j])
                            pGenTrcAir[pGenTrcMsg[j].genTrcNum] = pGenTrcMsg[j].trc;
                    }
//                    testGenTrc(pGenTrcAir, 5);
                }
                break;

                /// Поверхностные цели

                case BIUS_A100::EUObjClass::UOC_SEA:
                case BIUS_A100::EUObjClass::UOC_GROUND:
                case BIUS_A100::EUObjClass::UOC_SURFACE:
                {
                    sea::TMsgFormSet msgFormSet;
                    Surface.GetMsg(Msg, T, &msgFormSet, pGenTrcMsg);

                    /// Заполнение массива поверхностных целей для отображения
                    for(int j = 0; j < 2; ++j)
                    {
                        if(msgFormSet.genTrcMsg[j])
                            pGenTrcSurface[pGenTrcMsg[j].genTrcNum + 500] = pGenTrcMsg[j].trc;
                    }
//                    testGenTrc(pGenTrcSurface, 5);
                }
                break;

                default:
                break;
                }
            }
        }

        /// Определение количества воздушных объектов
        count = 0;
        for(int i = 1; i < BIUS_A100::UGEN_TRC_MAX + 1; ++i)
        {
            if(pGenTrcAir[i].tXYUpdate != 0)
                ++count;
        }
        mainWindow->sendToTool(TrackAir, count);

        /// Определение количества поверхностных объектов
        count = 0;
        for(int i = 1; i < BIUS_A100::UGEN_SURFACE_TRC_MAX + 1; ++i)
        {
            if(pGenTrcSurface[i].tXYUpdate != 0)
                ++count;
        }
        mainWindow->sendToTool(TrackSurface, count);

        QApplication::postEvent(mainWindow, new TGenTrcEvent(pGenTrcAir));
        QApplication::postEvent(mainWindow, new TGenTrcEvent(pGenTrcSurface));

        msleep(50.0);  /// 0.0500 c
//        msleep(500.0);  /// 0.5000 c

        /// Периодическая проверка состояний объектов
        if((int) T % 10 == 0)
        {
            Air.TrcStateCheck(T, &msgFormSet, &genTrcMsg, &orderSP, fpResultAir);
            Surface.TrcStateCheck(T, fpResultSurface);

            /// Определение количества воздушных объектов
            count = 0;
            for(int i = 1; i < BIUS_A100::UGEN_TRC_MAX + 1; ++i)
            {
                if(pGenTrcAir[i].tXYUpdate != 0)
                    ++count;
            }
            mainWindow->sendToTool(TrackAir, count);

            /// Определение количества поверхностных объектов
            count = 0;
            for(int i = 1; i < BIUS_A100::UGEN_SURFACE_TRC_MAX + 1; ++i)
            {
                if(pGenTrcSurface[i].tXYUpdate != 0)
                    ++count;
            }
            mainWindow->sendToTool(TrackSurface, count);

            QApplication::postEvent(mainWindow, new TGenTrcEvent(pGenTrcAir));
            QApplication::postEvent(mainWindow, new TGenTrcEvent(pGenTrcSurface));
        }

        /// Обнуление количества сообщений
        count = 0;

        /// Завершение работы
        if(!mainWindow->isVisible())
            quit();
    }

    exec();
}

void MainThread::testPubEtalon(const TPubEtalon *_tPubEtalon, int _count) const
{
    std::cout << "x\ty\th\tvx\tvy\tvh\t---===PubEtalon===---" << std::endl;
    for(int i = 0; i < _count; ++i)
    {
        std::cout << _tPubEtalon[i].x << "\t" << _tPubEtalon[i].y << "\t" << _tPubEtalon[i].h << "\t"
                  << _tPubEtalon[i].vx << "\t" << _tPubEtalon[i].vy << "\t" << _tPubEtalon[i].vh << std::endl;
    }
    std::cout << std::endl;
}

void MainThread::testTrcMsg(const TUTrcMsg &_tTrcMsg) const
{
    std::cout << "x\ty\th\tv\t---===TrcMsg===---" << std::endl;
    std::cout << _tTrcMsg.x << "\t" << _tTrcMsg.y << "\t" << _tTrcMsg.h << "\t" << _tTrcMsg.v << std::endl;
    std::cout << std::endl;
}

void MainThread::testGenTrcMsg(const PTPV_TGenTrcMsg *_tGenTrcMsg) const
{
    std::cout << "x\ty\th\tvX\tvY\tv\t---===GenTrcMsg===---" << std::endl;
    for(int i = 0; i < 2; ++i)
    {
        std::cout << _tGenTrcMsg[i].trc.x << "\t" << _tGenTrcMsg[i].trc.y << "\t" << _tGenTrcMsg[i].trc.h << "\t"
                  << _tGenTrcMsg[i].trc.vX << "\t" << _tGenTrcMsg[i].trc.vY << "\t" << _tGenTrcMsg[i].trc.v << std::endl;
    }
    std::cout << std::endl;
}

void MainThread::testGenTrc(const PTPV_TGenTrc *_tGenTrc, int _count) const
{
    std::cout << "x\ty\th\tvx\tvy\tv\t---===GenTrc===---" << std::endl;
    for(int i = 0; i < _count; ++i)
    {
        std::cout << _tGenTrc[i].x << "\t" << _tGenTrc[i].y << "\t" << _tGenTrc[i].h << "\t"
                  << _tGenTrc[i].vX << "\t" << _tGenTrc[i].vY << "\t" << _tGenTrc[i].v << std::endl;
    }
    std::cout << std::endl;
}

void MainThread::fpResultAir()
{

}

void MainThread::fpResultSurface(PTPV_TGenTrcMsg *pGenTrcMsg, void *pobject)
{

}

