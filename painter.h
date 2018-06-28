#ifndef PAINTER_H
#define PAINTER_H

#include <QDockWidget>

#include "AboutEtalon.h"
#include "AboutTrack.h"
#include "GraphHeight.h"

class Painter : public Grapher2D
{
    Q_OBJECT

public:
    explicit Painter(QDockWidget *_aboutEtalon, QDockWidget *_aboutTrack, QDockWidget *_graphHeight);
    ~Painter();

    /// Установка эталонов
    void setEtalons(TPubEtalon *_tPubEtalon, double _time);

    /// Установка трасс
    void setTracks(PTPV_TGenTrc *_tGenTrc);

    /// Проверка флага фиксации
    inline bool isFixed();

public slots:
    /// Установка флага фиксации
    inline void setFixed();

    /// Установка флага отображения эталонов
    inline void setVisualEtalon(bool _bEtalon);

    /// Установка флага отображения трасс
    inline void setVisualTrack(bool _bTrack);

    /// Установка флага отображения лидеров групп
    inline void setVisualGroup(bool _bGroup);

    /// Установка флага отображения следа
    inline void setVisualTrace(bool _bTrace);

protected:
    void mousePressEvent(QMouseEvent * _mEvent);
    void mouseMoveEvent(QMouseEvent * _mEvent);
    void mouseReleaseEvent(QMouseEvent * _mEvent);
    void wheelEvent(QWheelEvent * _wEvent);
    void paintEvent(QPaintEvent * _pEvent);

private:
    /// Определение номера эталона под курсором мыши
    int indexOfEtalons(int _posX, int _posY);

    /// Определение номера трассы под курсором мыши
    int indexOfTracks(int _posX, int _posY);

    int numberHighlightedEtalon;    /// Номер выделенного эталона
    int numberSelectedEtalon;       /// Номер выбранного эталона

    int numberHighlightedTrack;     /// Номер выделенной цели
    int numberSelectedTrack;        /// Номер выбранной цели

    bool bFixed;                    /// Флаг фиксации изображения на экране

    QVector <Etalon> etalons;       /// Массив эталонов
    QVector <Track> tracks/*Air*/;      /// Массив воздушных трасс
//    QVector <Track> tracksSurface;  /// Массив поверхностных трасс

    QDockWidget *aboutEtalon;       /// Виджет информации об эталоне
    QDockWidget *aboutTrack;        /// Виджет информации о трассе
    QDockWidget *graphHeight;       /// Виджет отрисовки графика высот
};

bool Painter::isFixed()
{
    return bFixed;
}

void Painter::setFixed()
{
    bFixed = !bFixed;
}

void Painter::setVisualEtalon(bool _bEtalon)
{
    Etalon::setVisual(_bEtalon);
}

void Painter::setVisualTrack(bool _bTrack)
{
    Track::setVisual(_bTrack);
}

void Painter::setVisualGroup(bool _bGroup)
{
    Track::setGroup(_bGroup);
}

void Painter::setVisualTrace(bool _bTrace)
{
    Target::setTrace(_bTrace);
}

#endif // PAINTER_H
