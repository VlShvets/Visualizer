#include "abouttrack.h"

namespace Visualizer
{

/// Класс виджета отображения параметров трасс
AboutTrack::AboutTrack(QWidget *_parent)
    : QScrollArea(_parent)
{
    labelNumber     = new QLabel(this);
    labelAT         = new LabelAT;

    QWidget *pWidget = new QWidget(this);

    QFormLayout *formLayout = new QFormLayout(this);
    formLayout->addRow(tr("Номер цели:"), labelNumber);
    formLayout->addRow(tr("Время образования обобщенной трассы:"), &labelAT->lTStart);
    formLayout->addRow(tr("Время реального обновления координат X и Y:"), &labelAT->lTXYUpdate);
    formLayout->addRow(tr("Время реального обновления высоты:"), &labelAT->lTHUpdate);

//    formLayout->addRow(tr("Время реального обновления\n"
//                                   "барометрической высоты:"), &labelAT->lTHBarUpdate);
//    formLayout->addRow(tr("Время обновления ОГП:"), &labelAT->lTOGPUpdate);
//    formLayout->addRow(tr("Время обновления индивидуального номера:"), &labelAT->lTIndNumUpdate);
//    formLayout->addRow(tr("Время обновления полетной информации:"), &labelAT->lTFlyInfUpdate);

    formLayout->addRow(tr("Координата X:"), &labelAT->lX);
    formLayout->addRow(tr("Координата Y:"), &labelAT->lY);
    formLayout->addRow(tr("Радиолокационная высота:"), &labelAT->lH);

//    formLayout->addRow(tr("Барометрическая высота:"), &labelAT->lHBar);

    formLayout->addRow(tr("1/2 доверительного интервала\n"
                                   "по координатам X, Y:"), &labelAT->lTrustXY);
    formLayout->addRow(tr("1/2 доверительного интервала\n"
                                   "по высоте:"), &labelAT->lTrustH);
    formLayout->addRow(tr("Составляющая скорости по X:"), &labelAT->lVX);
    formLayout->addRow(tr("Составляющая скорости по Y:"), &labelAT->lVY);
    formLayout->addRow(tr("Модуль скорости\n"
                                   "(по плоскостным координатам X, Y):"), &labelAT->lV);
    formLayout->addRow(tr("Курс движения"), &labelAT->lPsi);

//    formLayout->addRow(tr("Индивидуальный номер ВО по системам\n"
//                                   "УВД, \"Пароль\", \"Пароль-Радуга\":"), &labelAT->lIndNum);
//    formLayout->addRow(tr("Индивидуальный номер ВО по RBS:"), &labelAT->lIndNumRBS);
//    formLayout->addRow(tr("Индивидуальный номер ВО по Mk-XA/Mk-XII:"), &labelAT->lIndNumMK);

    formLayout->addRow(tr("Единый номер объекта:"), &labelAT->lUniNum);

//    formLayout->addRow(tr("Номер трассы в системе оповещения:"), &labelAT->lRSTrcNum);

    formLayout->addRow(tr("Номера трасс от источников,\n"
                                   "сопровождающих данную обобщенную трассу:"), &labelAT->lSeneTrcNum);
    formLayout->addRow(tr("Количество источников сопровождения:"), &labelAT->lSensCount);

//    formLayout->addRow(tr("Признак получения ЦУ по ВО:"), &labelAT->lTargCP);

    formLayout->addRow(tr("Информация о группе объекта:"), &labelAT->lGrpInfo);

//    formLayout->addRow(tr("Модель в рамках типа класса:"), &labelAT->lObjTypeModel);
//    formLayout->addRow(tr("Тип объекта внутри класса:"), &labelAT->lObjType);
//    formLayout->addRow(tr("Класс объекта:"), &labelAT->lObjClass);
//    formLayout->addRow(tr("Тип объекта в текстовом виде:"), &labelAT->lObjTypeTxt);
//    formLayout->addRow(tr("Признак вида воздушного объекта:"), &labelAT->lAirObjType);
//    formLayout->addRow(tr("Признак имитационного объекта:"), &labelAT->lImitObj);

    formLayout->addRow(tr("Признак наличия маневра:"), &labelAT->lManevr);

    formLayout->addRow(tr("ОГП:"), &labelAT->lOGP);

    formLayout->addRow(tr("Индекс объекта:"), &labelAT->lIVO);
    formLayout->addRow(tr("Тип объекта:"), &labelAT->lTVO);
    formLayout->addRow(tr("Количественный состав:"), &labelAT->lQuant);

//    formLayout->addRow(tr("Признак воздействия ИА:"), &labelAT->lAttackStateFA);
//    formLayout->addRow(tr("Признак воздействия ЗУР:"), &labelAT->lAttackStateSAM);
//    formLayout->addRow(tr("Резерв:"), &labelAT->lAttackStateReserve);
//    formLayout->addRow(tr("Признак вида бедствия:"), &labelAT->lSOS);
//    formLayout->addRow(tr("Признак канальной цели либо объекта:"), &labelAT->lChanTarg);
//    formLayout->addRow(tr("Линия запроса:"), &labelAT->lReqLine);
//    formLayout->addRow(tr("Блокировка отождествления по координатам:"), &labelAT->lIdentBlock);

//    formLayout->addRow(tr("Признак размера ЭПР объекта\n"
//                                   "в P-диапазоне:"), &labelAT->lObjSizeP);
//    formLayout->addRow(tr("Признак размера ЭПР объекта\n"
//                                   "в S-диапазоне:"), &labelAT->lObjSizeS);
//    formLayout->addRow(tr("Полетная информация:"), &labelAT->lFlyInf);

    pWidget->setLayout(formLayout);

    setWidget(pWidget);

    resetInfoAboutTrack();
}

AboutTrack::~AboutTrack()
{
    delete labelAT;
    delete labelNumber;
}

/// Установка информации о трассе
void AboutTrack::setInfoAboutTrack(Track *_track, int _number)
{
    if(_track->getTGenTrc() == NULL)
    {
        resetInfoAboutTrack();
        return;
    }

    labelNumber->setText(QString::number(_number));
    tGenTrc = _track->getTGenTrc();

    updateInfoAboutTrack();
}

/// Очистка всех полей информации о трассе
void AboutTrack::resetInfoAboutTrack()
{
    labelNumber->setText(QString::number(0.0));

    labelAT->lTStart.setText(QString::number(0.0));
    labelAT->lTXYUpdate.setText(QString::number(0.0));
    labelAT->lTHUpdate.setText(QString::number(0.0));

//    labelAT->lTHBarUpdate.setText(QString::number(0.0));
//    labelAT->lTOGPUpdate.setText(QString::number(0.0));
//    labelAT->lTIndNumUpdate.setText(QString::number(0.0));
//    labelAT->lTFlyInfUpdate.setText(QString::number(0.0));

    labelAT->lX.setText(QString::number(0.0));
    labelAT->lY.setText(QString::number(0.0));
    labelAT->lH.setText(QString::number(0.0));

//    labelAT->lHBar.setText(QString::number(0.0));

    labelAT->lTrustXY.setText(QString::number(0.0));
    labelAT->lTrustH.setText(QString::number(0.0));
    labelAT->lVX.setText(QString::number(0.0));
    labelAT->lVY.setText(QString::number(0.0));
    labelAT->lV.setText(QString::number(0.0));
    labelAT->lPsi.setText(QString::number(0.0));

//    labelAT->lIndNum.setText(QString::number(0.0));
//    labelAT->lIndNumRBS.setText(QString::number(0.0));
//    labelAT->lIndNumMK.setText(QString::number(0.0));

    labelAT->lUniNum.setText(QString::number(0.0));

//    labelAT->lRSTrcNum.setText(QString::number(0.0));

    labelAT->lSeneTrcNum.setText(QString::number(0.0));
    labelAT->lSensCount.setText(QString::number(0.0));

//    labelAT->lTargCP.setText(QString::number(0.0));

    labelAT->lGrpInfo.setText(QString::number(0.0));

//    labelAT->lObjTypeModel.setText(QString::number(0.0));
//    labelAT->lObjType.setText(QString::number(0.0));
//    labelAT->lObjClass.setText(QString::number(0.0));
//    labelAT->lObjTypeTxt.setText(QString::number(0.0));
//    labelAT->lAirObjType.setText(QString::number(0.0));
//    labelAT->lImitObj.setText(tr("Нет"));

    labelAT->lManevr.setText(tr("Нет"));

    labelAT->lOGP.setText(QString::number(0.0));

    labelAT->lIVO.setText(QString::number(0.0));
    labelAT->lTVO.setText(QString::number(0.0));
    labelAT->lQuant.setText(QString::number(0.0));

//    labelAT->lAttackStateFA.setText(QString::number(0.0));
//    labelAT->lAttackStateSAM.setText(QString::number(0.0));
//    labelAT->lAttackStateReserve.setText(QString::number(0.0));
//    labelAT->lSOS.setText(QString::number(0.0));
//    labelAT->lChanTarg.setText(tr("Нет"));
//    labelAT->lReqLine.setText(QString::number(0.0));
//    labelAT->lIdentBlock.setText(tr("Нет"));
//    labelAT->lObjSizeP.setText(QString::number(0.0));
//    labelAT->lObjSizeS.setText(QString::number(0.0));
//    labelAT->lFlyInf.setText(QString::number(0.0));
}

/// Обновление информации о трассе
void AboutTrack::updateInfoAboutTrack()
{
    labelAT->lTStart.setText(QString::number(tGenTrc->tStart));
    labelAT->lTXYUpdate.setText(QString::number(tGenTrc->tXYUpdate));
    labelAT->lTHUpdate.setText(QString::number(tGenTrc->tHUpdate));

//    labelAT->lTHBarUpdate.setText(QString::number(tGenTrc->tHBarUpdate));
//    labelAT->lTOGPUpdate.setText(QString::number(tGenTrc->tOGPUpdate));
//    labelAT->lTIndNumUpdate.setText(QString::number(tGenTrc->tIndNumUpdate));
//    labelAT->lTFlyInfUpdate.setText(QString::number(tGenTrc->tFlyInfUpdate));

    labelAT->lX.setText(QString::number(tGenTrc->x));
    labelAT->lY.setText(QString::number(tGenTrc->y));
    labelAT->lH.setText(QString::number(tGenTrc->h));

//    labelAT->lHBar.setText(QString::number(tGenTrc->hBar));

    labelAT->lTrustXY.setText(QString::number(tGenTrc->trustXY));
    labelAT->lTrustH.setText(QString::number(tGenTrc->trustH));
    labelAT->lVX.setText(QString::number(tGenTrc->vX));
    labelAT->lVY.setText(QString::number(tGenTrc->vY));
    labelAT->lV.setText(QString::number(tGenTrc->v));
    labelAT->lPsi.setText(QString::number(tGenTrc->psi));

//    labelAT->lIndNum.setText(QString::number(tGenTrc->indNum));
//    labelAT->lIndNumRBS.setText(QString::number(tGenTrc->indNumRBS));
//    labelAT->lIndNumMK.setText(QString::number(tGenTrc->indNumMK));

    labelAT->lUniNum.setText(QString::number(tGenTrc->uniNum));

//    labelAT->lRSTrcNum.setText(QString::number(tGenTrc->RSTrcNum));

    QString temp(QString::number(tGenTrc->sensTrcNum[1]));
    for(int i = 2; tGenTrc->sensTrcNum[i] != -1.0 && i < GEN_SUM_VISUAL_VALUES; ++i)
        temp += QString(",") + ((i % 10 == 0) ? (QString("\n")) : (QString(" "))) + QString::number(tGenTrc->sensTrcNum[i]);
    labelAT->lSeneTrcNum.setText(temp);
    temp.clear();
    labelAT->lSensCount.setText(QString::number(tGenTrc->sensCount));

//    labelAT->lTargCP.setText(QString::number(tGenTrc->targCP));

    temp = QString::number(tGenTrc->grpInfo.num) +
            QString(", ") + QString::number(tGenTrc->grpInfo.leadTrcNum) +
            QString(", ") + QString::number(tGenTrc->grpInfo.trcCount);
    labelAT->lGrpInfo.setText(temp);
    temp.clear();

//    labelAT->lObjTypeModel.setText(QString::number(tGenTrc->objTypeModel));
//    labelAT->lObjType.setText(QString::number(tGenTrc->objType));
//    labelAT->lObjClass.setText(QString::number(tGenTrc->objClass));
//    labelAT->lObjTypeTxt.setText(QString((const char*) tGenTrc->objTypeTxt));
//    labelAT->lAirObjType.setText(QString::number(tGenTrc->airObjType));
//    labelAT->lImitObj.setText(tGenTrc->imitObj ? QObject::tr("Да") : QObject::tr("Нет"));

    labelAT->lManevr.setText(tGenTrc->manevr?QObject::tr("Да"):QObject::tr("Нет"));

    labelAT->lOGP.setText(QString::number(tGenTrc->OGP));

    labelAT->lIVO.setText(QString::number(tGenTrc->IVO));
    labelAT->lTVO.setText(QString::number(tGenTrc->TVO));
    labelAT->lQuant.setText(QString::number(tGenTrc->quant));

//    labelAT->lAttackStateFA.setText(QString::number(tGenTrc->attackStateFA));
//    labelAT->lAttackStateSAM.setText(QString::number(tGenTrc->attackStateSAM));
//    labelAT->lAttackStateReserve.setText(QString::number(tGenTrc->attackStateReserve));
//    labelAT->lSOS.setText(QString::number(tGenTrc->SOS));
//    labelAT->lChanTarg.setText(tGenTrc->chanTarg ? QObject::tr("Да") : QObject::tr("Нет"));
//    labelAT->lReqLine.setText(QString::number(tGenTrc->reqLine));
//    labelAT->lIdentBlock.setText(tGenTrc->identBlock ? QObject::tr("Да") : QObject::tr("Нет"));
//    labelAT->lObjSizeP.setText(QString::number(tGenTrc->objSizeP));
//    labelAT->lObjSizeS.setText(QString::number(tGenTrc->objSizeS));
//    temp = QString::number(tGenTrc->flyInf.fuelLevel) +
//            QString(", ") + QString::number(tGenTrc->flyInf.levelHBar) +
//            QString(", ") + QString::number(tGenTrc->flyInf.msg1) +
//            QString(", ") + QString::number(tGenTrc->flyInf.msg2) +
//            QString(", ") + QString::number(tGenTrc->flyInf.msg3) +
//            QString(", ") + QString::number(tGenTrc->flyInf.msg4) +
//            QString(", ") + QString::number(tGenTrc->flyInf.msg5) +
//            QString(", ") + QString::number(tGenTrc->flyInf.weapLoad);
//    labelAT->lFlyInf.setText(temp);
    temp.clear();
}

}
