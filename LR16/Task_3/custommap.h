#ifndef CUSTOMMAP_H
#define CUSTOMMAP_H

#include <QStandardItemModel>

#include "map.h"

template <typename K, typename V>
class CustomMap : public Map<K, V>
{
private:
    void fillModel(std::shared_ptr<typename Map<K, V>::Node> node,
                   QStandardItem *modelItem);

public:
    CustomMap();

    QStandardItemModel *toModel();
};

template <typename K, typename V>
void CustomMap<K, V>::fillModel(std::shared_ptr<typename Map<K, V>::Node> node,
                                QStandardItem *modelItem)
{
    if (node != nullptr)
    {
        auto *nodeItem = new QStandardItem('{' + node->entry.first + ": " +
                                           node->entry.second + '}');
        nodeItem->setFlags(nodeItem->flags()
                               .setFlag(Qt::ItemIsSelectable, false)
                               .setFlag(Qt::ItemIsEnabled, false)
                               .setFlag(Qt::ItemIsEditable, false));
        fillModel(node->left, nodeItem);
        fillModel(node->right, nodeItem);
        modelItem->appendRow(nodeItem);
    }
}

template <typename K, typename V>
CustomMap<K, V>::CustomMap() : Map<K, V>()
{}

template <typename K, typename V>
QStandardItemModel *CustomMap<K, V>::toModel()
{
    auto *model = new QStandardItemModel();
    fillModel(this->getRoot(), model->invisibleRootItem());
    return model;
}

#endif  // CUSTOMMAP_H