#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <string>
#include <fstream>

#include "trainroute.h"

class FileManager
{
private:
    std::string filename;

public:
    FileManager();
    FileManager(std::string filename);

    std::string getFilename();
    void setFilename(std::string filename);
    bool getTrainRoutes(TrainRoute **&trainRoutes, int &size);
    bool save(TrainRoute **trainRoutes, int size);
    bool save(std::string filename, TrainRoute **trainRoutes, int size);
};

#endif // FILEMANAGER_H