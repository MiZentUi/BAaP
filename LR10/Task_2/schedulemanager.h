#ifndef SCHEDULEMANAGER_H
#define SCHEDULEMANAGER_H

#include <cstring>

#include <QTableWidget>

#include "trainroute.h"

class ScheduleManager
{
private:
    QTableWidget *table;
    int trainRoutesSize = 0;
    TrainRoute **trainRoutes = nullptr;
    std::string filter;
    
    void sort();
    void fillTable();
    void deleteTrainRoute(int index);

public slots:
    void itemChanged(QTableWidgetItem *item);

public:
    ScheduleManager(QTableWidget *table);
    ~ScheduleManager();

    void setFilter(std::string filter);
    void setTrainRoutes(TrainRoute **trainRoutes, int size);
    void getTrainRoutes(TrainRoute **&trainRoutes, int &size);
    void deleteSelected();
    void update();
};

#endif // SCHEDULEMANAGER_H