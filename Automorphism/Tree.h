#pragma once

#include <QObject>
#include <QMap>

class TreeItem
{
public:
	int level;
	TreeItem* n0;
	TreeItem* n1;
	QString mark;
	int id = 0;

	TreeItem()
	{
		level = 0;
		n0 = nullptr;
		n1 = nullptr;
	}

	TreeItem(int cLevel)
	{
		level = cLevel;
		n0 = nullptr;
		n1 = nullptr;
	}
};

class Tree
{

public:
	Tree();

protected:
	void init();
	void addItems(QStringList& items);
	void addInTree(QString& item, TreeItem* parentItem, int level = 1);

	void markNodes(TreeItem* item);

	void writeTree();
	void writeLevel(QMap<int, QString>& listTree, TreeItem* item, int parentId);
	

protected:
	TreeItem* m_root;
	int m_idCounter = 0;
};
