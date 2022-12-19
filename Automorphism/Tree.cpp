#include "Tree.h"
#include <QFile>
#include <QTextStream>

Tree::Tree()
{
	m_root = new TreeItem();
	init();
}

void Tree::init()
{
	QFile file("input.txt");
	file.open(QIODevice::ReadOnly);
	QString text = file.readAll().simplified().replace(" ", "");
	auto itemList = text.split(";");
	file.close();

	addItems(itemList);
}

static bool strSort(const QString& s1, const QString& s2)
{
	return (s1.size() < s2.size());
}

void Tree::addItems(QStringList& items)
{
	qSort(items.begin(), items.end(), strSort);
	for (auto& item : items)
		addInTree(item, m_root);

	markNodes(m_root);
	writeTree();
}

void Tree::addInTree(QString& item, TreeItem* parentItem, int level)
{
	QString el = item[level - 1];
	TreeItem* newChild = new TreeItem();
	if (parentItem->id == 0)
		parentItem->id = ++m_idCounter;

	if (el == "0") // кидаем в левую ветку
	{
		if (parentItem->n0 == nullptr)
		{
			newChild = new TreeItem(level);
			parentItem->n0 = newChild;
		}
		else
			newChild = parentItem->n0;
	}
	else if (el == "1") // кидаем в правую ветку
	{
		if (parentItem->n1 == nullptr)
		{
			newChild = new TreeItem(level);
			parentItem->n1 = newChild;
		}
		else
			newChild = parentItem->n1;
	}
	else
		return;

	addInTree(item, newChild, level + 1);
}

void Tree::markNodes(TreeItem* item)
{
	if (item->n0 != nullptr)
		markNodes(item->n0);
	if (item->n1 != nullptr)
		markNodes(item->n1);

	if (item->n0 == nullptr && item->n1 == nullptr) // листы
	{
		item->level = 0;
		item->mark = "0";
	}
	else
	{
		item->mark += item->n0 != nullptr ? QString::number(item->n0->level) : "";
		item->mark += item->n1 != nullptr ? QString::number(item->n1->level) : "";
		item->level = std::max(item->n0 != nullptr ? item->n0->level : 0, item->n1 != nullptr ? item->n1->level : 0) + 1;
	}
}

void Tree::writeTree()
{
	QFile file("outTree.txt");
	file.open(QIODevice::WriteOnly);
	
	QMap<int, QString> map;
	writeLevel(map, m_root, 0);

	QTextStream outputStream(&file);

	for (auto it = map.begin(); it != map.end(); it++)
		outputStream << it.key() << ": " << it.value() << '\n';
	
	file.close();
}

void Tree::writeLevel(QMap<int, QString>& listTree, TreeItem* item, int parentId)
{
	listTree[item->id] = "";
	
	if (parentId != 0)
		listTree[item->id] += QString::number(parentId) + ' ';
	if (item->n0 != nullptr)
	{
		listTree[item->id] += QString::number(item->n0->id) + ' ';
		writeLevel(listTree, item->n0, item->id);
	}
	if (item->n1 != nullptr)
	{
		listTree[item->id] += QString::number(item->n1->id) + ' ';
		writeLevel(listTree, item->n1, item->id);
	}
}