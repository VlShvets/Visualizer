#ifndef IMITATION_H
#define IMITATION_H

#include "target.h"

#include <QMap>

#include "TImit.h"
#include "Poi.h"

namespace Visualizer
{

/// Класс внутренней имитации
class Imitation
{
public:
    explicit                            Imitation();
    ~Imitation();

    /// Возвращение словаря стационарных объектов
//    inline QMap <int, Stationary>       *getStationary();

    /// Возвращение словаря эталонов
    inline const QMap <int, Etalon>     *getEtalons();

    /// Вычислительный процесс
    void                                run(const float _currentTime);

private:
    /// --------------------------------------------------
    /// Указатели на объекты классов
    /// --------------------------------------------------

    TImit                   *tImit;         /// Указатель на объект класса имитации

    /// --------------------------------------------------
    /// Переменные
    /// --------------------------------------------------

    /// Словари параметров стационарных объектов и эталонов
//    QMap <int, Stationary>  stationary;     /// Словарь стационарных объектов   <номер, структура параметров>
    QMap <int, Etalon>      etalons;        /// Словарь эталонов                <номер, структура параметров>
};

/// Возвращение словаря стационарных объектов
//QMap<int, Stationary> *Imitation::getStationary()
//{
//    return &stationary;
//}

/// Возвращение словаря эталонов
const QMap <int, Etalon> *Imitation::getEtalons()
{
    return &etalons;
}

}

#endif // IMITATION_H
