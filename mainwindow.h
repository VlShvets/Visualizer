#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextCodec>

#include "Tool.h"

class TPubEtalonEvent : public QEvent
{
public:
    enum {TPubEtalonType = User + 1};

    TPubEtalonEvent(TPubEtalon *_tPubEtalon, double _time) : QEvent((Type)TPubEtalonType),
        tPubEtalon(_tPubEtalon), time(_time)
    {
    }

    /// Получение структуры данных эталона
    inline TPubEtalon *getTPubEtalon()  {   return tPubEtalon;  }

    /// Получение времени структуры данных эталона
    inline double getTime()             {   return time;        }

private:
    TPubEtalon *tPubEtalon;     /// Структура данных эталона
    double time;                /// Время структуры данных эталона
};

class TGenTrcEvent : public QEvent
{
public:
    enum {TGenTrcType = User + 2};

    TGenTrcEvent(PTPV_TGenTrc *_tGenTrc) : QEvent((Type)TGenTrcType),
        tGenTrc(_tGenTrc)
    {
    }

    /// Получение структуры данных трассы
    inline PTPV_TGenTrc *getTGenTrc()   {   return tGenTrc; }

private:
    PTPV_TGenTrc *tGenTrc;      /// Структура данных трассы
};

class MainWindow : public QMainWindow
{
public:
    MainWindow();
    ~MainWindow();

    void customEvent(QEvent *_event);

    /// Передача в строку состояния времени или количества трасс
    inline void sendToTool(TypeOfInfo _typeOfInfo, double _info);

private:
    AboutEtalon *aboutEtalon;   /// Виджет информации об эталоне
    AboutTrack *aboutTrack;     /// Виджет информации о трассе

    GraphHeight *graphHeight;   /// Виджет отрисовки графика высот
    Painter *painter;           /// Виджет отрисовки координат
    Tool *tool;                 /// Виджет настроек
};

void MainWindow::sendToTool(TypeOfInfo _typeOfInfo, double _info)
{
    tool->showInfo(_typeOfInfo, _info);
}

#endif // MAINWINDOW_H
