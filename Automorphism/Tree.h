#pragma once

#include <QObject>

class TreeItem
{
public:
	int level;
	TreeItem* n0;
	TreeItem* n1;
	//TreeItem* parent;
	QString mark;

	TreeItem()
	{
		level = 0;
		n0 = nullptr;
		n1 = nullptr;
	}

	TreeItem(int cLevel/*, QString cName, TreeItem* cParent*/)
	{
		level = cLevel;
		//parent = cParent;
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

protected:
	TreeItem* m_root;
};
