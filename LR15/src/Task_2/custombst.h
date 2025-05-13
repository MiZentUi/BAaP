#ifndef CUSTOMBST_H
#define CUSTOMBST_H

#include <QStandardItemModel>
#include <vector>

#include "bst.h"

template <typename K, typename V>
class CustomBST : public BST<K, V>
{
private:
    void fillModel(typename BST<K, V>::Node *node, QStandardItem *modelItem);

public:
    CustomBST();

    QStandardItemModel *toModel();
    V getValueByMiddleKey(K *key = nullptr);
};

template <typename K, typename V>
void CustomBST<K, V>::fillModel(typename BST<K, V>::Node *node,
                                QStandardItem *modelItem)
{
    if (node != nullptr)
    {
        auto *nodeItem = new QStandardItem(QString::number(node->key));
        nodeItem->setFlags(nodeItem->flags()
                               .setFlag(Qt::ItemIsSelectable, false)
                               .setFlag(Qt::ItemIsEnabled, false)
                               .setFlag(Qt::ItemIsEditable, false));
        nodeItem->appendRow(new QStandardItem(node->value));
        fillModel(node->left, nodeItem);
        fillModel(node->right, nodeItem);
        modelItem->appendRow(nodeItem);
    }
}

template <typename K, typename V>
CustomBST<K, V>::CustomBST() : BST<K, V>()
{}

template <typename K, typename V>
QStandardItemModel *CustomBST<K, V>::toModel()
{
    auto *model = new QStandardItemModel();
    fillModel(this->getRoot(), model->invisibleRootItem());
    return model;
}

template <typename K, typename V>
V CustomBST<K, V>::getValueByMiddleKey(K *key)
{
    std::vector<std::pair<K, V>> nodes;
    this->inorderTraversal(nodes);
    if (!nodes.empty())
    {
        K middle_key = (nodes[0].first + nodes[nodes.size() - 1].first) / 2;
        std::pair<K, V> middleKeyNode = nodes[0];
        for (size_t i = 1; i < middle_key; i++)
        {
            if (std::abs(nodes[i].first - middle_key) <
                std::abs(middleKeyNode.first - middle_key))
            {
                middleKeyNode = nodes[i];
            }
            if (std::abs(nodes[i - 1].first - middle_key) <
                std::abs(nodes[i].first - middle_key))
            {
                break;
            }
        }
        if (key != nullptr)
        {
            *key = middleKeyNode.first;
        }
        return middleKeyNode.second;
    }
    *key = 0;
    return V();
}

#endif  // CUSTOMBST_H
