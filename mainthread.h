#ifndef MAINTHREAD_H
#define MAINTHREAD_H

#include <QThread>
#include <QApplication>

#include <iostream>         /// Для std::cout
#include <ctime>            /// Для CLOCKS_PER_SEC

#include "MainWindow.h"

#include "TImit.h"
#include "Poi.h"
#include "TAir.h"
#include "TSea.h"

using namespace BIUS_A100::PTPV::air;
using namespace BIUS_A100::PTPV::sea;

//#include "test.h"

class MainThread : public QThread
{
public:
    MainThread(MainWindow *_mainWindow);

    void run();

private:
    static void fpResultAir();                                                  /// Приём результатов "периодики" Air по каждой трассе
    static void fpResultSurface(PTPV_TGenTrcMsg* pGenTrcMsg, void *pobject);    /// Приём результатов "периодики" Surface по каждой трассе

    /// Выводы на печать в консоль различной информации
    void testPubEtalon(const TPubEtalon *_tPubEtalon, int _count) const;  /// Вывод на печать значений основных характеристик первых эталонов
    void testTrcMsg(const TUTrcMsg &_tTrcMsg) const;                      /// Вывод на печать результата Предварительной Обработки Информации
    void testGenTrcMsg(const PTPV_TGenTrcMsg *_tGenTrcMsg) const;         /// Вывод на печать результата Третичной Обработки Информации
    void testGenTrc(const PTPV_TGenTrc *_tGenTrc, int _count) const;      /// Вывод на печать значений основных характеристик первых целей

    static air::TMsgFormSet msgFormSet;     /// Признаки формирования сообщений потребителям по рез-там обработки на "периодике"
    static PTPV_TGenTrcMsg genTrcMsg;       /// Сообщение с результатом ТОИ на "периодике"
    static TUTrcMsg orderSP;                /// Распоряжения ТОИ на ВОИ на "периодике" (не используется)

    MainWindow *mainWindow;     /// Главное окно
};



#endif // MAINTHREAD_H
