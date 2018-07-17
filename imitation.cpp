#include "imitation.h"

namespace Visualizer
{

/// Класс внутренней имитации
Imitation::Imitation()
{
    tImit = new TImit;
}

Imitation::~Imitation()
{
//    stationary.clear();
    etalons.clear();
}

void Imitation::run(const float _currentTime)
{

}

}
