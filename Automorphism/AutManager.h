#pragma once
#include "Tree.h"

typedef QMap<QString, QList<TreeItem*>> autMap;
typedef QList<QPair<int, int>> group;

struct AutGroup
{
	QList<group> gr;
	int level;
};

typedef QList<AutGroup> AutGroups;


class AutManager
{
public:
	AutManager(TreeItem* tree);

protected:
	void extendMap(TreeItem* child);
	void findAutGr();

	void getAut();
	//void writeFile();
	void writeAuts();

protected:
	autMap m_map; // key is mark, value is list of items
	AutGroups m_autGr;
	int m_maxId = 0;
	QList<QList<int>> m_autList{};
};

