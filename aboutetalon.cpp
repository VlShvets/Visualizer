#include "AboutEtalon.h"

AboutEtalon::AboutEtalon(QWidget *_parent) : QScrollArea(_parent)
{
    labelNumber.setText(QObject::tr("\t\t\t"));

    QWidget *pWidget = new QWidget(this);

    QFormLayout *formLayout = new QFormLayout;
    formLayout->addRow(QObject::tr("Номер эталона:"), &labelNumber);
    formLayout->addRow(QObject::tr("Скорость объекта:"), &labelAE.lV);
    formLayout->addRow(QObject::tr("Составляющая скорости по X:"), &labelAE.lVx);
    formLayout->addRow(QObject::tr("Составляющая скорости по Y:"), &labelAE.lVy);
    formLayout->addRow(QObject::tr("Скорость изменения высоты:"), &labelAE.lVh);
    formLayout->addRow(QObject::tr("Составляющая ускорения по X:"), &labelAE.lAx);
    formLayout->addRow(QObject::tr("Составляющая ускорения по Y:"), &labelAE.lAy);
    formLayout->addRow(QObject::tr("Ускорение изменения высоты:"), &labelAE.lAh);
    formLayout->addRow(QObject::tr("Курс объекта:"), &labelAE.lPsi);
    formLayout->addRow(QObject::tr("Координата объекта по X:"), &labelAE.lX);
    formLayout->addRow(QObject::tr("Координата объекта по Y:"), &labelAE.lY);
    formLayout->addRow(QObject::tr("Высота объекта:"), &labelAE.lH);
    formLayout->addRow(QObject::tr("Номера трасс источников,\n"
                                   "сопровождающих данный эталон:"), &labelAE.lTrcNumSens);
    formLayout->addRow(QObject::tr("Источники,\n"
                                   "назначенные на имитацию даннного эталона:"), &labelAE.lSensImit);

//    formLayout->addRow(QObject::tr("Запрет оповещения даннного эталона:"), &labelAE.lNoInform);

    formLayout->addRow(QObject::tr("Доверительный интервал:"), &labelAE.lTrustXY);
    formLayout->addRow(QObject::tr("Индекс объекта"), &labelAE.lIVO);
    formLayout->addRow(QObject::tr("Тип объекта"), &labelAE.lTVO);
    formLayout->addRow(QObject::tr("Госпринадлежность объекта:"), &labelAE.lOGP);
    formLayout->addRow(QObject::tr("Наличие маневра:\n"
                                   "(Да - есть маневр)"), &labelAE.lManevr);

//    formLayout->addRow(QObject::tr("Необходимость отображать информацию:\n"
//                                   "(Да - отображать)"), &labelAE.lVisual);
//    formLayout->addRow(QObject::tr("Имитационный объект:\n"
//                                   "0 - трасса реальная\n"
//                                   "1 - трасса тренажная\n"
//                                   "2 - трасса эталонная"), &labelAE.lImitObj);
//    formLayout->addRow(QObject::tr("Тип трассы:\n"
//                                   "0 - обычная\n"
//                                   "1 - ГЗЛА\n"
//                                   "2 - БЦ\n"
//                                   "3 - БТ (баллистическая траектория)"), &labelAE.lTrsChar);
    pWidget->setLayout(formLayout);

    this->setWidget(pWidget);

    resetInfoAboutEtalon();
}

AboutEtalon::~AboutEtalon()
{
}

void AboutEtalon::setInfoAboutEtalon(Etalon *_etalon, int _number)
{
    if(_etalon->getTPubEtalon() == NULL)
    {
        resetInfoAboutEtalon();
        return;
    }

    tPubEtalon = _etalon->getTPubEtalon();

    labelNumber.setText(QString::number(_number));
    updateInfoAboutEtalon();
}

void AboutEtalon::resetInfoAboutEtalon()
{
    labelNumber.setText(QString::number(0.0));

    labelAE.lV.setText(QString::number(0.0));
    labelAE.lVx.setText(QString::number(0.0));
    labelAE.lVy.setText(QString::number(0.0));
    labelAE.lVh.setText(QString::number(0.0));
    labelAE.lAx.setText(QString::number(0.0));
    labelAE.lAy.setText(QString::number(0.0));
    labelAE.lAh.setText(QString::number(0.0));
    labelAE.lPsi.setText(QString::number(0.0));
    labelAE.lX.setText(QString::number(0.0));
    labelAE.lY.setText(QString::number(0.0));
    labelAE.lH.setText(QString::number(0.0));
    labelAE.lTrcNumSens.setText(QString::number(0.0));
    labelAE.lSensImit.setText(QString::number(0.0));

//    labelAE.lNoInform.setText(QString::number(0.0));

    labelAE.lTrustXY.setText(QString::number(0.0));
    labelAE.lIVO.setText(QString::number(0.0));
    labelAE.lTVO.setText(QString::number(0.0));
    labelAE.lOGP.setText(QString::number(0.0));
    labelAE.lManevr.setText(QObject::tr("Нет"));

//    labelAE.lVisual.setText(QObject::tr("Нет"));
//    labelAE.lImitObj.setText(QString::number(0.0));
//    labelAE.lTrsChar.setText(QString::number(0.0));
}

void AboutEtalon::updateInfoAboutEtalon()
{
    labelAE.lV.setText(QString::number(tPubEtalon->v));
    labelAE.lVx.setText(QString::number(tPubEtalon->vx));
    labelAE.lVy.setText(QString::number(tPubEtalon->vy));
    labelAE.lVh.setText(QString::number(tPubEtalon->vh));
    labelAE.lAx.setText(QString::number(tPubEtalon->ax));
    labelAE.lAy.setText(QString::number(tPubEtalon->ay));
    labelAE.lAh.setText(QString::number(tPubEtalon->ah));
    labelAE.lPsi.setText(QString::number(tPubEtalon->psi));
    labelAE.lX.setText(QString::number(tPubEtalon->x));
    labelAE.lY.setText(QString::number(tPubEtalon->y));
    labelAE.lH.setText(QString::number(tPubEtalon->h));
    QString temp = QString::number(tPubEtalon->trcNumSens[1]);
    for(int i = 2; tPubEtalon->trcNumSens[i] != -1.0 && i < GEN_SUM_VISUAL_VALUES; ++i)
        temp += QString(",") + ((i % 10 == 0)?(QString("\n")):(QString(" "))) + QString::number(tPubEtalon->trcNumSens[i]);
    labelAE.lTrcNumSens.setText(temp);
    temp.clear();
    temp = QString::number(tPubEtalon->sensImit[1]);
    for(int i = 2; tPubEtalon->sensImit[i] != -1.0 && i < GEN_SUM_VISUAL_VALUES; ++i)
        temp += QString(",") + ((i % 10 == 0)?(QString("\n")):(QString(" "))) + QString::number(tPubEtalon->sensImit[i]);
    labelAE.lSensImit.setText(temp);
    temp.clear();

//    temp = QString::number(tPubEtalon->noInform[0]);
//    for(int i = 1; tPubEtalon->noInform[i] != -1.0 && i < COUNTVISUALVALUES; ++i)
//        temp += QString(",") + ((i % 10 == 0)?(QString("\n")):(QString(" "))) + QString::number(tPubEtalon->noInform[i]);
//    labelAE.lNoInform.setText(temp);
//    temp.clear();

    labelAE.lTrustXY.setText(QString::number(tPubEtalon->trustXY));
    labelAE.lIVO.setText(QString::number(tPubEtalon->IVO));
    labelAE.lTVO.setText(QString::number(tPubEtalon->TVO));
    labelAE.lOGP.setText(QString::number(tPubEtalon->OGP));
    labelAE.lManevr.setText(tPubEtalon->manevr?QObject::tr("Да"):QObject::tr("Нет"));

//    labelAE.lVisual.setText(tPubEtalon->visual?QObject::tr("Да"):QObject::tr("Нет"));
//    labelAE.lImitObj.setText(QString::number(tPubEtalon->imitObj));
//    labelAE.lTrsChar.setText(QString::number(tPubEtalon->trsChar));
}
