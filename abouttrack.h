#ifndef ABOUTTRACK_H
#define ABOUTTRACK_H

#include "target.h"

#include <QScrollArea>
#include <QFormLayout>
#include <QLabel>

namespace Visualizer
{

/// Класс виджета отображения параметров трасс
class AboutTrack : public QScrollArea
{
public:
    explicit    AboutTrack(QWidget *_parent = nullptr);
    ~AboutTrack();

    /// Установка информации о трассе
    void        setInfoAboutTrack(PTPV_TGenTrc *_tGenTrc, int _number);

    /// Очистка всех полей информации о трассе
    void        resetInfoAboutTrack();

protected:
    /// Обновление виджета отображения параметров трасс
    void        timerEvent(QTimerEvent *);

private:
    /// Обновление информации о трассе
    void        updateInfoAboutTrack();

    /// --------------------------------------------------
    /// Переменные
    /// --------------------------------------------------

    PTPV_TGenTrc    *tGenTrc;  /// Структура данных трассы

    /// Указатели на виджеты

    QLabel          *labelNumber;     /// Номер трассы

    struct LabelAT
    {
        QLabel      lTStart;
        QLabel      lTXYUpdate;
        QLabel      lTHUpdate;

//        QLabel      lTHBarUpdate;
//        QLabel      lTOGPUpdate;
//        QLabel      lTIndNumUpdate;
//        QLabel      lTFlyInfUpdate;

        QLabel      lX;
        QLabel      lY;
        QLabel      lH;

//        QLabel      lHBar;

        QLabel      lTrustXY;
        QLabel      lTrustH;
        QLabel      lVX;
        QLabel      lVY;
        QLabel      lV;
        QLabel      lPsi;

//        QLabel      lIndNum;
//        QLabel      lIndNumRBS;
//        QLabel      lIndNumMK;

        QLabel      lUniNum;

//        QLabel      lRSTrcNum;

        QLabel      lSeneTrcNum;
        QLabel      lSensCount;

//        QLabel      lTargCP;

        QLabel      lGrpInfo;

//        QLabel      lObjTypeModel;
//        QLabel      lObjType;
//        QLabel      lObjClass;
//        QLabel      lObjTypeTxt;
//        QLabel      lAirObjType;
//        QLabel      lImitObj;

        QLabel      lManevr;

        QLabel      lOGP;

        QLabel      lIVO;
        QLabel      lTVO;
        QLabel      lQuant;

//        QLabel      lAttackStateFA;
//        QLabel      lAttackStateSAM;
//        QLabel      lAttackStateReserve;
//        QLabel      lSOS;
//        QLabel      lChanTarg;
//        QLabel      lReqLine;
//        QLabel      lIdentBlock;

//        QLabel      lObjSizeP;
//        QLabel      lObjSizeS;
//        QLabel      lFlyInf;
    }               *labelAT;
};

}

#endif // ABOUTTRACK_H
