#ifndef TARGET_H
#define TARGET_H

#include <QPolygon>

#include "define.h"

#include "IMIT_.h"
#include "U_PTPV_.h"

using namespace BIUS_A100::IMIT_;
using namespace BIUS_A100::_PTPV_;

class Target : public QPolygon
{
public:
    Target();
    Target(float _x, float _y, float _alpha);
    ~Target();

    /// Установка масштаба символа
    inline static void setScale(float _scale);

    /// Установка символа
    virtual void setSymbol() = 0;

    /// Получение координат точки траетории из памяти
    const QPointF getMemoryCoord(int _index) const;

    /// Получение высоты точки траектории из памяти
    float getMemoryHeight(int _index) const;

    /// Получение времени точки траектории из памяти
    double getMemoryTime(int _index) const;

    /// Получение количества источников сопровождения точки траектории из памяти
    unsigned char getMemorySensCount(int _index) const;

    /// Установка флага отображения следа
    inline static void setTrace(bool _bTrace);

    /// Проверка флага отображения следа
    inline static bool isTrace();

    /// Получение количества точек траектории в памяти
    int getCountPoints();

    /// Очистка памяти точек траектории
    inline void clearMemoryPoints();

protected:
    /// Установка символа Гипер Звукового Летательного аппарата (Hypersonic aircraft)
    void setHA(float _x, float _y, float _alpha);

    /// Установка символа Баллистической Цели (Ballistic Goal)
    void setBG(float _x, float _y, float _alpha);

    /// Установка символа Крылатой Ракеты (Cruise Missile)
    void setCM(float _x, float _y, float _alpha);

    /// Установка символа Стратегической Авиации (Strategic Aviation)
    void setSA(float _x, float _y, float _alpha);

    /// Установка символа Надводной Цели (SEA)
    void setSEA(float _x, float _y, float _alpha);

    /// Установка символа Наземной Цели (GROUND)
    void setGROUND(float _x, float _y, float _alpha);

    static float scale;     /// Масштаб символа
    static bool bTrace;     /// Флаг отображения следа

    struct MemoryPoint {                    /// Точка траектории
        QPointF coord;                      /// Координата
        float h;                            /// Радиолокационная высoта
        double time;                        /// Время
        unsigned char sensCount;            /// Количество источников сопpовождения
    };
    QVector <MemoryPoint> memoryPoints;     /// Хранящиеся в памяти точки
};

void Target::setScale(float _scale)
{
    scale = _scale;
}

void Target::setTrace(bool _bTrace)
{
    bTrace = _bTrace;
}

bool Target::isTrace()
{
    return bTrace;
}

void Target::clearMemoryPoints()
{
    memoryPoints.clear();
}

/// Класс эталонов

class Etalon : public Target
{
public:
    Etalon();
    Etalon(TPubEtalon *_tPubEtalon, double _time);
    ~Etalon();

    /// Установка структуры данных эталона
    void setTPubEtalon(TPubEtalon *_tPubEtalon, double _time);

    /// Получение структуры данных эталона
    inline TPubEtalon *getTPubEtalon();

    /// Установка символа
    void setSymbol();

    /// Проверка содержания точки нажатия в полигоне эталона
    bool containsPoint(const QPoint &_pt, Qt::FillRule _fillRule) const;

    /// Установка флага отображения эталонов
    inline static void setVisual(bool _bEtalon);

    /// Проверка флага отображения эталонов
    inline static bool isVisual();

private:
    /// Сохранение эталона в массив точек траектории
    void saveEtalon(float _x, float _y, float _h, double _time = 0.0);

    static bool bEtalon;        /// Флаг отображения эталонов

    TPubEtalon *tPubEtalon;     /// Структура данных эталона
};

TPubEtalon *Etalon::getTPubEtalon()
{
    return tPubEtalon;
}

void Etalon::setVisual(bool _bEtalon)
{
    bEtalon = _bEtalon;
}

bool Etalon::isVisual()
{
    return bEtalon;
}

/// Класс трасс

class Track : public Target
{
public:
    Track();
    Track(PTPV_TGenTrc *_tGenTrc);
    ~Track();

    /// Установка структуры данных трассы
    void setTGenTrc(PTPV_TGenTrc *_tGenTrc);

    /// Получение структуры данных трассы
    inline PTPV_TGenTrc *getTGenTrc();

    /// Установка символа
    void setSymbol();

    /// Проверка содержания точки нажатия в полигоне эталона
    bool containsPoint(const QPoint &_pt, Qt::FillRule _fillRule) const;

    /// Установка флага выбора только лидеров групп
    inline static void setGroup(bool _bGroup);

    /// Проверка флага выбора только лидеров групп
    inline static bool isGroup();

    /// Установка флага отображения трасс
    inline static void setVisual(bool _bTrack);

    /// Проверка флага отображения трасс
    inline static bool isVisual();

private:
    /// Установка символа Неопределённой Цели SURFACE)
    void setSURFACE(float _x, float _y, float _alpha);

    /// Сохранение трассы в массив точек траектории
    void saveTrack(float _x, float _y, float _h, unsigned char _sensCount = 0);

    static bool bTrack;     /// Флаг отображения трасс
    static bool bGroup;     /// Флаг выбора только лидеров групп

    PTPV_TGenTrc *tGenTrc;  /// Структура данных трассы
};

PTPV_TGenTrc *Track::getTGenTrc()
{
    return tGenTrc;
}

void Track::setGroup(bool _bGroup)
{
    bGroup = _bGroup;
}

bool Track::isGroup()
{
    return bGroup;
}

void Track::setVisual(bool _bTrack)
{
    bTrack = _bTrack;
}

bool Track::isVisual()
{
    return bTrack;
}

#endif // TARGET_H
