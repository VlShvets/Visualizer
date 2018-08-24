#include "target.h"
#include "target.h"

namespace Visualizer
{

float Target::scale = (float) GEN_ZOOM / XY_MEASURE;

/// Класс параметров целей
Target::Target() : QPolygon(6)
{
}

/// Класс параметров целей
Target::Target(float _x, float _y, float _alpha) : QPolygon(6)
{
    setCM(_x, _y, _alpha);
}

Target::~Target()
{
}

/// Получение координаты точки траетории
const QPointF Target::getTrajectoryCoord(int _index) const
{
    if(_index < 0 || _index > trajectory.count())
        exit(1);

    return trajectory[_index].coord;
}

/// Получение высоты точки траектории из памяти
float Target::getTrajectoryHeight(int _index) const
{
    if(_index < 0 || _index > trajectory.count())
        exit(1);

    return trajectory[_index].h;
}

/// Получение времени точки траектории
float Target::getTrajectoryTime(int _index) const
{
    if(_index < 0 || _index > trajectory.count())
        exit(1);

    return trajectory[_index].time;
}

/// Получение количества источников сопровождения точки траектории
int Target::getTrajectorySensCount(int _index) const
{
    if(_index < 0 || _index > trajectory.count())
        exit(1);

    return trajectory[_index].sensCount;
}


/// Установка символа Гипер Звукового Летательного аппарата (Hypersonic aircraft)
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

/// Установка символа Баллистической Цели (Ballistic Goal)
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

/// Установка символа Крылатой Ракеты (Cruise Missile)
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

/// Установка символа Стратегической Авиации (Strategic Aviation)
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

/// Установка символа Надводной Цели (SEA)
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

/// Установка символа Наземной Цели (GROUND)
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

/// Класс параметров эталонов
Etalon::Etalon() : Target()
{
}

/// Класс параметров эталонов
Etalon::Etalon(TPubEtalon *_tPubEtalon, double _time) : Target()
{
    setTPubEtalon(_tPubEtalon);
    saveEtalon(_time);
    Etalon::setSymbol();
}

Etalon::~Etalon()
{
    /// Очищение указателя на структуру данных эталона
    tPubEtalon = nullptr;
}

/// Установка структуры данных эталона
void Etalon::setTPubEtalon(TPubEtalon *_tPubEtalon)
{
    if(_tPubEtalon == nullptr || _tPubEtalon->visual == EU_NO)
    {
        tPubEtalon = nullptr;
        return;
    }

    /// Обновление данных эталона
    tPubEtalon = _tPubEtalon;
}

/// Сохранение текущей точки эталона в массив точек траектории
void Etalon::saveEtalon(double _time)
{
    if(tPubEtalon == nullptr || tPubEtalon->visual == EU_NO)
        return;

    /// Сохранине текущей точки в миссив точек траектории
    Trajectory temp;
    temp.coord = QPointF(tPubEtalon->y, tPubEtalon->x);
    temp.h = tPubEtalon->h;
    temp.time = _time;
    trajectory.push_front(temp);

    /// Проверка предельного количества точек в траектории
    if(trajectory.count() > GEN_LIMIT_POINTS)
        trajectory.removeLast();
}

/// Установка символа
void Etalon::setSymbol()
{
    if(tPubEtalon == nullptr)
        return;

    if(tPubEtalon->ObjClass == UOC_AIR)
    {
        if(tPubEtalon->TO == EU_TVO_HS_AIRCRAFT)
            setHA(tPubEtalon->y, tPubEtalon->x, qAtan2(tPubEtalon->vx, tPubEtalon->vy));
        else if(tPubEtalon->TO == EU_TVO_ROCKET_BALL)
            setBG(tPubEtalon->y, tPubEtalon->x, qAtan2(tPubEtalon->vx, tPubEtalon->vy));
        else if (tPubEtalon->TO == EU_TVO_ROCKET_CR)
            setCM(tPubEtalon->y, tPubEtalon->x, qAtan2(tPubEtalon->vx, tPubEtalon->vy));
        else
            setSA(tPubEtalon->y, tPubEtalon->x, qAtan2(tPubEtalon->vx, tPubEtalon->vy));
    }
    else if(tPubEtalon->ObjClass == UOC_SEA)
    {
        setSEA(tPubEtalon->y, tPubEtalon->x, qAtan2(tPubEtalon->vx, tPubEtalon->vy));
    }
    else if(tPubEtalon->ObjClass == UOC_GROUND)
    {
        setGROUND(tPubEtalon->y, tPubEtalon->x, qAtan2(tPubEtalon->vx, tPubEtalon->vy));
    }
}

/// Проверка содержания точки нажатия в полигоне эталона
bool Etalon::containsPoint(const QPoint &_pt, Qt::FillRule _fillRule) const
{
    QPolygon temp(*(dynamic_cast <const QPolygon *> (this)));

    if(tPubEtalon != nullptr && tPubEtalon->ObjClass == UOC_AIR)
    {
        temp.remove(1);
        temp.remove(4);
    }
    else if(tPubEtalon != nullptr && tPubEtalon->ObjClass == UOC_GROUND)
    {
        temp.remove(0);
        temp.remove(1);
        temp.remove(2);
    }

    return temp.containsPoint(_pt, _fillRule);
}

/// Класс параметров трасс
Track::Track() : Target()
{
}

/// Класс параметров трасс
Track::Track(PTPV_TGenTrc *_tGenTrc) : Target()
{
    setTGenTrc(_tGenTrc);
    saveTrack();
    Track::setSymbol();
}

Track::~Track()
{
    /// Очищение указателя на структуру данных трассы
    tGenTrc = nullptr;
}

/// Установка структуры данных трассы
void Track::setTGenTrc(PTPV_TGenTrc *_tGenTrc)
{
    if(_tGenTrc == nullptr || _tGenTrc->tXYUpdate == 0.0)
    {
        tGenTrc = nullptr;
        return;
    }

    /// Обновление данных трассы
    tGenTrc = _tGenTrc;
}

/// Сохранение текущей трассы в массив точек траектории
void Track::saveTrack()
{
    if(tGenTrc == nullptr || tGenTrc->tXYUpdate == 0.0)
        return;

    /// Сохранине текущей точки в миссив точек траектории
    Trajectory temp;
    temp.coord = QPointF(tGenTrc->y, tGenTrc->x);
    temp.h = tGenTrc->h;
    temp.time = tGenTrc->tHUpdate;
    temp.sensCount = tGenTrc->sensCount;
    trajectory.push_front(temp);

    /// Проверка предельного количества точек в траектории
    if(trajectory.count() > GEN_LIMIT_POINTS)
        trajectory.removeLast();
}

/// Установка символа
void Track::setSymbol()
{
    if(tGenTrc == nullptr)
        return;

    if(tGenTrc->objClass == UOC_AIR)
    {
        if(tGenTrc->TO == EU_TVO_HS_AIRCRAFT)
            setHA(tGenTrc->y, tGenTrc->x, qAtan2(tGenTrc->vX, tGenTrc->vY));
        else if(tGenTrc->TO == EU_TVO_ROCKET_BALL)
            setBG(tGenTrc->y, tGenTrc->x, qAtan2(tGenTrc->vX, tGenTrc->vY));
        else if (tGenTrc->TO == EU_TVO_ROCKET_CR)
            setCM(tGenTrc->y, tGenTrc->x, qAtan2(tGenTrc->vX, tGenTrc->vY));
        else
            setSA(tGenTrc->y, tGenTrc->x, qAtan2(tGenTrc->vX, tGenTrc->vY));
    }
    else if(tGenTrc->objClass == UOC_SEA)
        setSEA(tGenTrc->y, tGenTrc->x, qAtan2(tGenTrc->vX, tGenTrc->vY));
    else if(tGenTrc->objClass == UOC_GROUND)
        setGROUND(tGenTrc->y, tGenTrc->x, qAtan2(tGenTrc->vX, tGenTrc->vY));
    else
        setSURFACE(tGenTrc->y, tGenTrc->x, qAtan2(tGenTrc->vX, tGenTrc->vY));
}

/// Проверка содержания точки нажатия в полигоне эталона
bool Track::containsPoint(const QPoint &_pt, Qt::FillRule _fillRule) const
{
    QPolygon temp(*(dynamic_cast <const QPolygon *> (this)));

    if(tGenTrc != nullptr && tGenTrc->objClass == UOC_AIR)
    {
        temp.remove(1);
        temp.remove(4);
    }
    else if(tGenTrc != nullptr && tGenTrc->objClass == UOC_GROUND)
    {
        temp.remove(0);
        temp.remove(1);
        temp.remove(2);
    }
    else if(tGenTrc != nullptr && tGenTrc->objClass == UOC_SURFACE)
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

/// Установка символа Неопределённой Цели SURFACE)
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

}
