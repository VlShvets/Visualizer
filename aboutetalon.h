#ifndef ABOUTETALON_H
#define ABOUTETALON_H

#include "target.h"

#include <QScrollArea>
#include <QFormLayout>
#include <QLabel>

namespace Visualizer
{

/// Класс виджета отображения параметров эталонов
class AboutEtalon : public QScrollArea
{
public:
    explicit    AboutEtalon(QWidget *_parent = nullptr);
    ~AboutEtalon();

    /// Установка информации об эталоне
    void        setInfoAboutEtalon(TPubEtalon *_tPubEtalon, int _number);

    /// Очистка всех полей информации об эталоне
    void        resetInfoAboutEtalon();

protected:
    /// Обновление виджета отображения параметров эталона
    void        timerEvent(QTimerEvent *);

private:
    /// Обновление информации об эталоне
    void        updateInfoAboutEtalon();

    /// --------------------------------------------------
    /// Переменные
    /// --------------------------------------------------

    TPubEtalon  *tPubEtalon;    /// Структура данных эталона

    /// Указатели на виджеты

    QLabel      *labelNumber;   /// Номер эталона

    struct LabelAE
    {
        QLabel  lV;
        QLabel  lVx;
        QLabel  lVy;
        QLabel  lVh;
        QLabel  lAx;
        QLabel  lAy;
        QLabel  lAh;
        QLabel  lPsi;
        QLabel  lX;
        QLabel  lY;
        QLabel  lH;
        QLabel  lTrcNumSens;
        QLabel  lSensImit;

//        QLabel  lNoInform;

        QLabel  lTrustXY;
        QLabel  lIVO;
        QLabel  lTVO;
        QLabel  lOGP;
        QLabel  lManevr;

//        QLabel  lVisual;
//        QLabel  lImitObj;
//        QLabel  lTrsChar;
    }           *labelAE;
};

}

#endif // ABOUTETALON_H
