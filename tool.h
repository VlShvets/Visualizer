#ifndef TOOL_H
#define TOOL_H

#include <QCheckBox>
#include <QSlider>
#include <QPushButton>
#include <QLCDNumber>
#include <QStyle>

#include "Painter.h"

enum TypeOfInfo     /// Тип передаваемой информации
{
    Time,           /// Текущее время
    TrackAir,       /// Количество воздушных трасс
    TrackSurface    /// Количество поверхностных трасс
};

class Tool : public QWidget
{
    Q_OBJECT

public:
    explicit Tool(Painter *_painter);
    ~Tool();

    /// Отображение полученной информации в строке состояния
    void showInfo(TypeOfInfo _typeOfInfo, double _info);

private slots:
    /// Изменение иконки на кнопке фиксации отображения
    inline void changePushButtonFixedIcon();

private:
    QLabel      *time;              /// Текущее время
    QLCDNumber  *countTrcAir;       /// Текущее количество воздушных трасс
    QLCDNumber  *countTrcSurface;   /// Текущее количество поверхностных трасс
    QPushButton *pbFixed;           /// Кнопка фиксации отображения
    QLCDNumber  *maxCountTrc;       /// Максимальное количество трасс

    Painter     *painter;           /// Виджет отрисовки координат
};

void Tool::changePushButtonFixedIcon()
{
    pbFixed->setIcon(style()->standardIcon(painter->isFixed() ? QStyle::SP_MediaPlay : QStyle::SP_MediaPause));
}

#endif // TOOL_H
