#include "Target.h"

float Target::scale = (float) GEN_ZOOM / XY_MEASURE;
bool Target::bTrace = false;

Target::Target() : QPolygon(6)
{
}

Target::Target(float _x, float _y, float _alpha) : QPolygon(6)
{
    setCM(_x, _y, _alpha);
}

Target::~Target()
{
}

const QPointF Target::getMemoryCoord(int _index) const
{
    if(_index > memoryPoints.count())
        exit(1);

    return memoryPoints[_index].coord;
}

float Target::getMemoryHeight(int _index) const
{
    if(_index > memoryPoints.count())
        exit(1);

    return memoryPoints[_index].h;
}

double Target::getMemoryTime(int _index) const
{
    if(_index > memoryPoints.count())
        exit(1);

    return memoryPoints[_index].time;
}

unsigned char Target::getMemorySensCount(int _index) const
{
    if(_index > memoryPoints.count())
        exit(1);

    return memoryPoints[_index].sensCount;
}

int Target::getCountPoints()
{
    if(bTrace)
        return memoryPoints.count();

    return 0;
}

void Target::setHA(float _x, float _y, float _alpha)
{
    setPoint(0, _x * scale, -_y * scale);
    setPoint(1, _x * scale + XY_HA_LENGTH * qCos(_alpha), -(_y * scale + XY_HA_LENGTH * qSin(_alpha)));
    setPoint(2, _x * scale - (0.5 * XY_HA_LENGTH) * qCos(_alpha - XY_HA_ANGLE),
             -(_y * scale - (0.5 * XY_HA_LENGTH) * qSin(_alpha - XY_HA_ANGLE)));
    setPoint(3, _x * scale + XY_HA_LENGTH * qCos(_alpha), -(_y * scale + XY_HA_LENGTH * qSin(_alpha)));
    setPoint(4, _x * scale - (0.5 * XY_HA_LENGTH) * qCos(_alpha + XY_HA_ANGLE),
             -(_y * scale - (0.5 * XY_HA_LENGTH) * qSin(_alpha + XY_HA_ANGLE)));
    setPoint(5, _x * scale + XY_HA_LENGTH * qCos(_alpha), -(_y * scale + XY_HA_LENGTH * qSin(_alpha)));
}

void Target::setBG(float _x, float _y, float _alpha)
{
    setPoint(0, _x * scale, -_y * scale);
    setPoint(1, _x * scale + XY_BG_LENGTH * qCos(_alpha), -(_y * scale + XY_BG_LENGTH * qSin(_alpha)));
    setPoint(2, _x * scale - (0.5 * XY_BG_LENGTH) * qCos(_alpha - XY_BG_ANGLE / 2.0),
             -(_y * scale - (0.5 * XY_BG_LENGTH) * qSin(_alpha - XY_BG_ANGLE / 2.0)));
    setPoint(3, _x * scale + XY_BG_LENGTH * qCos(_alpha), -(_y * scale + XY_BG_LENGTH * qSin(_alpha)));
    setPoint(4, _x * scale - (0.5 * XY_BG_LENGTH) * qCos(_alpha + XY_BG_ANGLE / 2.0),
             -(_y * scale - (0.5 * XY_BG_LENGTH) * qSin(_alpha + XY_BG_ANGLE / 2.0)));
    setPoint(5, _x * scale + XY_BG_LENGTH * qCos(_alpha), -(_y * scale + XY_BG_LENGTH * qSin(_alpha)));
}

void Target::setCM(float _x, float _y, float _alpha)
{
    setPoint(0, _x * scale, -_y * scale);
    setPoint(1, _x * scale + XY_CM_LENGTH * qCos(_alpha), -(_y * scale + XY_CM_LENGTH * qSin(_alpha)));
    setPoint(2, _x * scale + (0.5 * XY_CM_LENGTH) * qCos(_alpha - XY_CM_ANGLE / 2.0),
             -(_y * scale + (0.5 * XY_CM_LENGTH) * qSin(_alpha - XY_CM_ANGLE / 2.0)));
    setPoint(3, _x * scale + XY_CM_LENGTH * qCos(_alpha), -(_y * scale + XY_CM_LENGTH * qSin(_alpha)));
    setPoint(4, _x * scale + (0.5 * XY_CM_LENGTH) * qCos(_alpha + XY_CM_ANGLE / 2.0),
             -(_y * scale + (0.5 * XY_CM_LENGTH) * qSin(_alpha + XY_CM_ANGLE / 2.0)));
    setPoint(5, _x * scale + XY_CM_LENGTH * qCos(_alpha), -(_y * scale + XY_CM_LENGTH * qSin(_alpha)));
}

void Target::setSA(float _x, float _y, float _alpha)
{
    setPoint(0, _x * scale, -_y * scale);
    setPoint(1, _x * scale + XY_SA_LENGTH * qCos(_alpha), -(_y * scale + XY_SA_LENGTH * qSin(_alpha)));
    setPoint(2, _x * scale + XY_SA_LENGTH * qCos(_alpha) - (0.5 * XY_SA_LENGTH) * qCos(_alpha - XY_SA_ANGLE / 2.0),
             -(_y * scale + XY_SA_LENGTH * qSin(_alpha) - (0.5 * XY_SA_LENGTH) * qSin(_alpha - XY_SA_ANGLE / 2.0)));
    setPoint(3, _x * scale + XY_SA_LENGTH * qCos(_alpha), -(_y * scale + XY_SA_LENGTH * qSin(_alpha)));
    setPoint(4, _x * scale + XY_SA_LENGTH * qCos(_alpha) - (0.5 * XY_SA_LENGTH) * qCos(_alpha + XY_SA_ANGLE / 2.0),
             -(_y * scale + XY_SA_LENGTH * qSin(_alpha) - (0.5 * XY_SA_LENGTH) * qSin(_alpha + XY_SA_ANGLE / 2.0)));
    setPoint(5, _x * scale + XY_SA_LENGTH * qCos(_alpha), -(_y * scale + XY_SA_LENGTH * qSin(_alpha)));
}

void Target::setSEA(float _x, float _y, float _alpha)
{
    setPoint(0, _x * scale - XY_SEA_LENGTH * qCos(_alpha) / 2.0, -(_y * scale - XY_SEA_LENGTH * qSin(_alpha) / 2.0));
    setPoint(1, _x * scale - (0.5 * XY_SEA_LENGTH) * qCos(_alpha - XY_SEA_ANGLE / 4.0),
             -(_y * scale - (0.5 * XY_SEA_LENGTH) * qSin(_alpha - XY_SEA_ANGLE / 4.0)));
    setPoint(2, _x * scale + XY_SEA_LENGTH * qCos(_alpha) - (0.5 * XY_SEA_LENGTH) * qCos(_alpha - XY_SEA_ANGLE / 2.0),
             -(_y * scale + XY_SEA_LENGTH * qSin(_alpha) - (0.5 * XY_SEA_LENGTH) * qSin(_alpha - XY_SEA_ANGLE / 2.0)));
    setPoint(3, _x * scale + XY_SEA_LENGTH * qCos(_alpha), -(_y * scale + XY_SEA_LENGTH * qSin(_alpha)));
    setPoint(4, _x * scale + XY_SEA_LENGTH * qCos(_alpha) - (0.5 * XY_SEA_LENGTH) * qCos(_alpha + XY_SEA_ANGLE / 2.0),
             -(_y * scale + XY_SEA_LENGTH * qSin(_alpha) - (0.5 * XY_SEA_LENGTH) * qSin(_alpha + XY_SEA_ANGLE / 2.0)));
    setPoint(5, _x * scale - (0.5 * XY_SEA_LENGTH) * qCos(_alpha + XY_SEA_ANGLE / 4.0),
             -(_y * scale - (0.5 * XY_SEA_LENGTH) * qSin(_alpha + XY_SEA_ANGLE / 4.0)));
}

void Target::setGROUND(float _x, float _y, float _alpha)
{
    setPoint(0, _x * scale, -_y * scale);
    setPoint(1, _x * scale + XY_GROUND_LENGTH * qCos(_alpha) / 2.0, -(_y * scale + XY_GROUND_LENGTH * qSin(_alpha) / 2.0));
    setPoint(2, _x * scale, -_y * scale);
    setPoint(3, _x * scale - (0.5 * XY_GROUND_LENGTH) * qCos(_alpha - XY_GROUND_ANGLE / 2.0),
             -(_y * scale - (0.5 * XY_GROUND_LENGTH) * qSin(_alpha - XY_GROUND_ANGLE / 2.0)));
    setPoint(4, _x * scale, -_y * scale);
    setPoint(5, _x * scale - (0.5 * XY_GROUND_LENGTH) * qCos(_alpha + XY_GROUND_ANGLE / 2.0),
             -(_y * scale - (0.5 * XY_GROUND_LENGTH) * qSin(_alpha + XY_GROUND_ANGLE / 2.0)));
}

/// Класс эталонов

bool Etalon::bEtalon = true;

Etalon::Etalon() : Target()
{
}

Etalon::Etalon(TPubEtalon *_tPubEtalon, double _time) : Target()
{
    setTPubEtalon(_tPubEtalon, _time);
    Etalon::setSymbol();
}

Etalon::~Etalon()
{
}

void Etalon::setTPubEtalon(TPubEtalon *_tPubEtalon, double _time)
{
    if(!bEtalon || !_tPubEtalon ||
            _tPubEtalon->visual == BIUS_A100::_PTPV_::EU_NO)
    {
        tPubEtalon = NULL;
        return;
    }

    /// Обновление данных эталона
    tPubEtalon = _tPubEtalon;

    saveEtalon(tPubEtalon->x, tPubEtalon->y, tPubEtalon->h, _time);
}

void Etalon::setSymbol()
{
    if(tPubEtalon == NULL)
        return;

    if(tPubEtalon->ObjClass == BIUS_A100::EUObjClass::UOC_AIR)
    {
        if(tPubEtalon->TVO == BIUS_A100::EUTVO::EU_TVO_HS_AIRCRAFT)
            setHA(tPubEtalon->y, tPubEtalon->x, qAtan2(tPubEtalon->vx, tPubEtalon->vy));
        else if(tPubEtalon->TVO == BIUS_A100::EUTVO::EU_TVO_ROCKET_BALL)
            setBG(tPubEtalon->y, tPubEtalon->x, qAtan2(tPubEtalon->vx, tPubEtalon->vy));
        else if (tPubEtalon->TVO == BIUS_A100::EUTVO::EU_TVO_ROCKET_CR)
            setCM(tPubEtalon->y, tPubEtalon->x, qAtan2(tPubEtalon->vx, tPubEtalon->vy));
        else
            setSA(tPubEtalon->y, tPubEtalon->x, qAtan2(tPubEtalon->vx, tPubEtalon->vy));
    }
    else if(tPubEtalon->ObjClass == BIUS_A100::EUObjClass::UOC_SEA)
    {
        setSEA(tPubEtalon->y, tPubEtalon->x, qAtan2(tPubEtalon->vx, tPubEtalon->vy));
    }
    else if(tPubEtalon->ObjClass == BIUS_A100::EUObjClass::UOC_GROUND)
    {
        setGROUND(tPubEtalon->y, tPubEtalon->x, qAtan2(tPubEtalon->vx, tPubEtalon->vy));
    }
}

bool Etalon::containsPoint(const QPoint &_pt, Qt::FillRule _fillRule) const
{
    QPolygon temp(*(dynamic_cast <const QPolygon *> (this)));

    if(tPubEtalon && tPubEtalon->ObjClass == BIUS_A100::EUObjClass::UOC_AIR)
    {
        temp.remove(1);
        temp.remove(4);
    }
    else if(tPubEtalon && tPubEtalon->ObjClass == BIUS_A100::EUObjClass::UOC_GROUND)
    {
        temp.remove(0);
        temp.remove(1);
        temp.remove(2);
    }

    return temp.containsPoint(_pt, _fillRule);
}

void Etalon::saveEtalon(float _x, float _y, float _h, double _time)
{
    /// Сохранине текущей цели в миссив памяти
    MemoryPoint temp;
    temp.coord = QPointF(_y, _x);
    temp.h = _h;
    temp.time = _time;
    memoryPoints.push_front(temp);

    /// Проверка предельного количества точек в памяти
    if(memoryPoints.count() > GEN_LIMIT_POINTS)
        memoryPoints.removeLast();
}

/// Класс трасс

bool Track::bTrack = true;
bool Track::bGroup = false;

Track::Track() : Target()
{
}

Track::Track(PTPV_TGenTrc *_tGenTrc) : Target()
{
    setTGenTrc(_tGenTrc);
    Track::setSymbol();
}

Track::~Track()
{
}

void Track::setTGenTrc(PTPV_TGenTrc *_tGenTrc)
{
    if(!bTrack || (bGroup && _tGenTrc->grpInfo.trcCount == 0) ||
            !_tGenTrc || _tGenTrc->tXYUpdate == 0)
    {
        tGenTrc = NULL;
        return;
    }

    /// Обновление данных трассы
    tGenTrc = _tGenTrc;

    saveTrack(tGenTrc->x, tGenTrc->y, tGenTrc->h, tGenTrc->sensCount);
}

void Track::setSymbol()
{
    if(tGenTrc == NULL)
        return;

    if(tGenTrc->objClass == BIUS_A100::EUObjClass::UOC_AIR)
    {
        if(tGenTrc->TVO == BIUS_A100::EUTVO::EU_TVO_HS_AIRCRAFT)
            setHA(tGenTrc->y, tGenTrc->x, qAtan2(tGenTrc->vX, tGenTrc->vY));
        else if(tGenTrc->TVO == BIUS_A100::EUTVO::EU_TVO_ROCKET_BALL)
            setBG(tGenTrc->y, tGenTrc->x, qAtan2(tGenTrc->vX, tGenTrc->vY));
        else if (tGenTrc->TVO == BIUS_A100::EUTVO::EU_TVO_ROCKET_CR)
            setCM(tGenTrc->y, tGenTrc->x, qAtan2(tGenTrc->vX, tGenTrc->vY));
        else
            setSA(tGenTrc->y, tGenTrc->x, qAtan2(tGenTrc->vX, tGenTrc->vY));
    }
    else if(tGenTrc->objClass == BIUS_A100::EUObjClass::UOC_SEA)
        setSEA(tGenTrc->y, tGenTrc->x, qAtan2(tGenTrc->vX, tGenTrc->vY));
    else if(tGenTrc->objClass == BIUS_A100::EUObjClass::UOC_GROUND)
        setGROUND(tGenTrc->y, tGenTrc->x, qAtan2(tGenTrc->vX, tGenTrc->vY));
    else
        setSURFACE(tGenTrc->y, tGenTrc->x, qAtan2(tGenTrc->vX, tGenTrc->vY));
}

bool Track::containsPoint(const QPoint &_pt, Qt::FillRule _fillRule) const
{
    QPolygon temp(*(dynamic_cast <const QPolygon *> (this)));

    if(tGenTrc && tGenTrc->objClass == BIUS_A100::EUObjClass::UOC_AIR)
    {
        temp.remove(1);
        temp.remove(4);
    }
    else if(tGenTrc && tGenTrc->objClass == BIUS_A100::EUObjClass::UOC_GROUND)
    {
        temp.remove(0);
        temp.remove(1);
        temp.remove(2);
    }
    else if(tGenTrc && tGenTrc->objClass == BIUS_A100::EUObjClass::UOC_SURFACE)
    {
        temp.remove(0);
        temp.remove(3);
        temp.remove(3);
        temp.remove(4);
        temp.remove(4);
        temp.remove(5);
    }

    return temp.containsPoint(_pt, _fillRule);
}

void Track::setSURFACE(float _x, float _y, float _alpha)
{
    this->resize(11);
    setPoint(0, _x * scale, -_y * scale);
    setPoint(1, _x * scale + XY_GROUND_LENGTH * qCos(_alpha) / 2.0, -(_y * scale + XY_GROUND_LENGTH * qSin(_alpha) / 2.0));
    setPoint(2, _x * scale + XY_SEA_LENGTH * qCos(_alpha) - (0.5 * XY_SEA_LENGTH) * qCos(_alpha - XY_SEA_ANGLE / 2.0),
             -(_y * scale + XY_SEA_LENGTH * qSin(_alpha) - (0.5 * XY_SEA_LENGTH) * qSin(_alpha - XY_SEA_ANGLE / 2.0)));
    setPoint(3, _x * scale - (0.5 * XY_SEA_LENGTH) * qCos(_alpha - XY_SEA_ANGLE / 4.0),
             -(_y * scale - (0.5 * XY_SEA_LENGTH) * qSin(_alpha - XY_SEA_ANGLE / 4.0)));
    setPoint(4, _x * scale, -_y * scale);
    setPoint(5, _x * scale - (0.5 * XY_SEA_LENGTH) * qCos(_alpha - XY_SEA_ANGLE / 4.0),
             -(_y * scale - (0.5 * XY_SEA_LENGTH) * qSin(_alpha - XY_SEA_ANGLE / 4.0)));
    setPoint(6, _x * scale - (0.5 * XY_SEA_LENGTH) * qCos(_alpha + XY_SEA_ANGLE / 4.0),
             -(_y * scale - (0.5 * XY_SEA_LENGTH) * qSin(_alpha + XY_SEA_ANGLE / 4.0)));
    setPoint(7, _x * scale, -_y * scale);
    setPoint(8, _x * scale - (0.5 * XY_SEA_LENGTH) * qCos(_alpha + XY_SEA_ANGLE / 4.0),
             -(_y * scale - (0.5 * XY_SEA_LENGTH) * qSin(_alpha + XY_SEA_ANGLE / 4.0)));
    setPoint(9, _x * scale + XY_SEA_LENGTH * qCos(_alpha) - (0.5 * XY_SEA_LENGTH) * qCos(_alpha + XY_SEA_ANGLE / 2.0),
             -(_y * scale + XY_SEA_LENGTH * qSin(_alpha) - (0.5 * XY_SEA_LENGTH) * qSin(_alpha + XY_SEA_ANGLE / 2.0)));
    setPoint(10, _x * scale + XY_GROUND_LENGTH * qCos(_alpha) / 2.0, -(_y * scale + XY_GROUND_LENGTH * qSin(_alpha) / 2.0));
}

void Track::saveTrack(float _x, float _y, float _h, unsigned char _sensCount)
{
    /// Сохранине текущей трассы в миссив памяти
    MemoryPoint temp;
    temp.coord = QPointF(_y, _x);
    temp.h = _h;
    temp.time = tGenTrc->tHUpdate;
    temp.sensCount = _sensCount;
    memoryPoints.push_front(temp);

    /// Проверка предельного количества точек в памяти
    if(memoryPoints.count() > GEN_LIMIT_POINTS)
        memoryPoints.removeLast();
}
