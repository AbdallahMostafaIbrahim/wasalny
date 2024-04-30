#ifndef LOADER_H
#define LOADER_H

#include "map.h"

class Loader
{
public:
    Loader();
    void saveMap(Map m);
    Map loadMap();
};

#endif // LOADER_H
