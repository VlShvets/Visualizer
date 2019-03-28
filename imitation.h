#ifndef IMITATION_H
#define IMITATION_H

#include "target.h"

#include <QMap>

#include "TImit.h"

namespace Visualizer
{

/// Класс внутренней имитации
class Imitation
{
public:
    explicit                            Imitation();
    ~Imitation();

    /// Возвращение словаря стационарных объектов
//    inline QMap <int, Stationary>   *getStationary();

    /// Возвращение словаря эталонов
    inline QMap <int, Etalon>       *getEtalons();

    /// Возвращение указателя на статический массив эталонов
    TPubEtalon                      *getTPubEtalon();

    /// Возвращение указателя на статический массив сообщений об эталонах
    TMsgTrc                         *getTMsgTrc();

    /// Вычислительный процесс
    int                             run(const float _currentTime);

private:    
    /// Обновление словаря эталонов
    void                            updateEtalons(const float _currentTime);

    /// --------------------------------------------------
    /// Указатели на объекты классов
    /// --------------------------------------------------

    TImit                   *tImit;         /// Указатель на объект класса имитации
    TPubEtalon              *tPubEtalon;    /// Указатель на статический массив эталонов
    TMsgTrc                 *tMsgTrc;       /// Указатель на статический массив сообщений об эталонах

    /// --------------------------------------------------
    /// Переменные
    /// --------------------------------------------------

    /// Словари параметров стационарных объектов и эталонов
//    QMap <int, Stationary>  stationary;      /// Словарь стационарных объектов   <номер, структура параметров>
    QMap <int, Etalon>      etalons;           /// Словарь эталонов                <номер, структура параметров>
};

/// Возвращение словаря стационарных объектов
//QMap<int, Stationary> *Imitation::getStationary()
//{
//    return &stationary;
//}

/// Возвращение словаря эталонов
QMap <int, Etalon> *Imitation::getEtalons()
{
    return &etalons;
}

}

#endif // IMITATION_H
