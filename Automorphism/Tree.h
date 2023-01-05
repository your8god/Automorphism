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
	int id = -1;

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

	void groups(QList<QPair<int, int>>& group)
	{
		auto l = n0, r = n1;
		if (l == nullptr || r == nullptr)
			return;

		if (l->n0 != nullptr && r->n0 != nullptr)
		{
			group.append(qMakePair(l->n0->id, r->n0->id));
			l->n0->groups(group);
			r->n0->groups(group);
		}

		if (l->n1 != nullptr && r->n1 != nullptr)
		{
			group.append(qMakePair(l->n1->id, r->n1->id));
			l->n1->groups(group);
			r->n1->groups(group);
		}
	}
};

class Tree
{

public:
	Tree();
	TreeItem* getTree();

protected:
	void init();
	void addItems(QStringList& items);
	void addInTree(QString& item, TreeItem* parentItem, int level = 1);

	void markNodes(TreeItem* item);

	void writeTree();
	void writeLevel(QMap<int, QString>& listTree, TreeItem* item, int parentId);
	

protected:
	TreeItem* m_root;
	int m_idCounter = -1;
};
