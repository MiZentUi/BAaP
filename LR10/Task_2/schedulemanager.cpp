#include "schedulemanager.h"

ScheduleManager::ScheduleManager(QTableWidget *table) : table(table) {}

ScheduleManager::~ScheduleManager()
{
    if (trainRoutes != nullptr)
    {
        for (int i = 0; i < trainRoutesSize; i++)
            delete trainRoutes[i];
        delete[] trainRoutes;
    }
}

void ScheduleManager::setFilter(std::string filter)
{
    this->filter = filter;
}

void ScheduleManager::setTrainRoutes(TrainRoute **trainRoutes, int size)
{
    if (this->trainRoutes != nullptr)
    {
        for (int i = 0; i < trainRoutesSize; i++)
            delete this->trainRoutes[i];
        delete[] this->trainRoutes;
    }
    this->trainRoutes = trainRoutes;
    trainRoutesSize = size;
}

void ScheduleManager::getTrainRoutes(TrainRoute **&trainRoutes, int &size)
{
    trainRoutes = this->trainRoutes;
    size = trainRoutesSize;
}

void ScheduleManager::update()
{
    sort();
    fillTable();
}

void ScheduleManager::sort()
{
    for (int i = 1; i < trainRoutesSize; i++)
        for (int j = trainRoutesSize - i - 1; j < trainRoutesSize - 1 && trainRoutes[j] != nullptr && trainRoutes[j + 1] != nullptr && trainRoutes[j]->getSortString() > trainRoutes[j + 1]->getSortString(); j++)
            std::swap(trainRoutes[j], trainRoutes[j + 1]);
}

void ScheduleManager::fillTable()
{
    table->setRowCount(1);
    int rc = 1;
    int rowIndex = 0;
    for (int i = 0; i < trainRoutesSize; i++)
        if ((filter.empty() || QString::fromStdString(trainRoutes[i]->getSearchString()).toLower().contains(QString::fromStdString(filter).toLower())) && trainRoutes[i] != nullptr)
        {
            table->setRowCount(++rc);
            for (int j = 0; j < TrainRoute::FIELDS_COUNT; j++)
                if (trainRoutes[i] != nullptr)
                    table->setItem(rowIndex, j, new QTableWidgetItem(QString::fromStdString((*trainRoutes[i])[j])));
            table->setItem(rowIndex, table->columnCount() - 1, new QTableWidgetItem(QString::number(i)));
            rowIndex++;
        }
    for (int i = 0; i < table->columnCount(); i++)
        table->setItem(rowIndex, i, new QTableWidgetItem(""));
}

void ScheduleManager::deleteSelected()
{
    for (QTableWidgetItem *item : table->selectedItems())
        if (!table->item(item->row(), table->columnCount() - 1)->text().isEmpty())
            deleteTrainRoute(table->item(item->row(), table->columnCount() - 1)->text().toInt());
    update();
}

void ScheduleManager::deleteTrainRoute(int index)
{
    if (index >= trainRoutesSize)
        return;
    // delete trainRoutes[index];
    // trainRoutes[index] = nullptr;
    for (int i = index; i < trainRoutesSize - 1; i++)
        trainRoutes[i] = trainRoutes[i + 1];
    // delete trainRoutes[trainRoutesSize - 1];
    // trainRoutes[trainRoutesSize - 1] = nullptr;
    trainRoutesSize--;
}

void ScheduleManager::itemChanged(QTableWidgetItem *item)
{
    if (table->item(item->row(), table->columnCount() - 1) == nullptr || !item->isSelected())
        return;
    item->setSelected(false);
    if (!table->item(item->row(), table->columnCount() - 1)->text().isEmpty())
    {
        int train_index = table->item(item->row(), table->columnCount() - 1)->text().toInt();
        if (trainRoutes[train_index] != nullptr)
            (*trainRoutes[train_index])[item->column()] = item->text().toStdString();
    }
    else
    {
        TrainRoute **newTrainRoutes = new TrainRoute *[trainRoutesSize + 1]{};
        if (trainRoutes != nullptr)
        {
            std::memcpy(newTrainRoutes, trainRoutes, trainRoutesSize * sizeof(TrainRoute *));
            delete[] trainRoutes;
            trainRoutes = nullptr;
        }
        trainRoutes = newTrainRoutes;
        trainRoutesSize++;
        trainRoutes[trainRoutesSize - 1] = new TrainRoute();
        (*trainRoutes[trainRoutesSize - 1])[item->column()] = item->text().toStdString();
    }
    update();
}