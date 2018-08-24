#ifndef TARGET_H
#define TARGET_H

#include "IMIT_.h"
#include "U_PTPV_.h"

#include "define.h"

#include <QPolygon>

namespace  Visualizer
{

using namespace BIUS_A100;
using namespace IMIT_;
using namespace _PTPV_;

/// Класс параметров целей
class Target : public QPolygon
{
public:
    Target();
    Target(float _x, float _y, float _alpha);
    ~Target();

    /// Установка масштаба символа
    inline static void  setScale(float _scale);

    /// Установка символа
    virtual void        setSymbol() = 0;

    /// Получение координаты точки траетории
    const QPointF       getTrajectoryCoord(int _index) const;

    /// Получение высоты точки траектории
    float               getTrajectoryHeight(int _index) const;

    /// Получение времени точки траектории
    float               getTrajectoryTime(int _index) const;

    /// Получение количества источников сопровождения точки траектории
    int                 getTrajectorySensCount(int _index) const;

    /// Получение количества точек траектории
    inline int          getTrajectoryCount() const;

    /// Очистка массива точек траектории
    inline void         clearTrajectory();

protected:
    /// Установка символа Гипер Звукового Летательного аппарата (Hypersonic aircraft)
    void    setHA(float _x, float _y, float _alpha);

    /// Установка символа Баллистической Цели (Ballistic Goal)
    void    setBG(float _x, float _y, float _alpha);

    /// Установка символа Крылатой Ракеты (Cruise Missile)
    void    setCM(float _x, float _y, float _alpha);

    /// Установка символа Стратегической Авиации (Strategic Aviation)
    void    setSA(float _x, float _y, float _alpha);

    /// Установка символа Надводной Цели (SEA)
    void    setSEA(float _x, float _y, float _alpha);

    /// Установка символа Наземной Цели (GROUND)
    void    setGROUND(float _x, float _y, float _alpha);

    /// --------------------------------------------------
    /// Переменные
    /// --------------------------------------------------

    static float            scale;                 /// Масштаб символа

    /// Точка траектории
    struct Trajectory {
        QPointF coord;  /// Координата
        float h;        /// Радиолокационная высoта
        float time;     /// Время
        int sensCount;  /// Количество источников сопpовождения
    };
    QVector <Trajectory>    trajectory;    /// Динамический массив точек траектории
};

/// Установка масштаба символа
void Target::setScale(float _scale)
{
    scale = _scale;
}

/// Получение количества точек траектории
int Target::getTrajectoryCount() const
{
    return trajectory.count();
}

/// Очистка массива точек траектории
void Target::clearTrajectory()
{
    trajectory.clear();
}

/// Класс параметров эталонов
class Etalon : public Target
{
public:
    Etalon();
    Etalon(TPubEtalon *_tPubEtalon, double _time);
    ~Etalon();

    /// Установка структуры данных эталона
    void setTPubEtalon(TPubEtalon *_tPubEtalon);

    /// Получение структуры данных эталона
    inline TPubEtalon *getTPubEtalon() const;

    /// Сохранение текущей точки эталона в массив точек траектории
    void saveEtalon(double _time = 0.0);

    /// Установка символа
    void setSymbol();

    /// Проверка содержания точки нажатия в полигоне эталона
    bool containsPoint(const QPoint &_pt, Qt::FillRule _fillRule) const;

private:
    /// --------------------------------------------------
    /// Переменные
    /// --------------------------------------------------

    TPubEtalon *tPubEtalon;   /// Указатель на структуру данных эталона
};

/// Получение структуры данных эталона
TPubEtalon *Etalon::getTPubEtalon() const
{
    return tPubEtalon;
}

/// Класс параметров трасс
class Track : public Target
{
public:
    Track();
    Track(PTPV_TGenTrc *_tGenTrc);
    ~Track();

    /// Установка структуры данных трассы
    void setTGenTrc(PTPV_TGenTrc *_tGenTrc);

    /// Получение структуры данных трассы
    inline PTPV_TGenTrc *getTGenTrc() const;

    /// Сохранение текущей трассы в массив точек траектории
    void saveTrack();

    /// Установка символа
    void setSymbol();

    /// Проверка содержания точки нажатия в полигоне эталона
    bool containsPoint(const QPoint &_pt, Qt::FillRule _fillRule) const;

private:
    /// Установка символа Неопределённой Цели SURFACE)
    void setSURFACE(float _x, float _y, float _alpha);

    /// --------------------------------------------------
    /// Переменные
    /// --------------------------------------------------

    PTPV_TGenTrc *tGenTrc;    /// Указатель на структуру данных трассы
};

/// Получение структуры данных трассы
PTPV_TGenTrc *Track::getTGenTrc() const
{
    return tGenTrc;
}

}

#endif // TARGET_H
