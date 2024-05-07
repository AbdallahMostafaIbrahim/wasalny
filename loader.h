#ifndef LOADER_H
#define LOADER_H

#include "map.h"
#include <QFile>


class Loader
{
public:
    Loader();
    static void init();
    static void saveMap(Map m);
    static Map loadMap();
private:

  static  QFile* file;
};


#endif // LOADER_H
