#include "AutManager.h"
#include <QFile>
#include <QTextStream>

AutManager::AutManager(TreeItem* tree)
{
	extendMap(tree);
	QList<int> defAut;
	for (int i = 0; i <= m_maxId; i++)
		defAut.append(i);
	m_autList.append(defAut);

	findAutGr();
	getAut();
	writeAuts();
	//writeFile();
}

void AutManager::extendMap(TreeItem* child)
{
	m_maxId = std::max(m_maxId, child->id);

	if (child->n0 == nullptr && child->n1 == nullptr)
		return;

	m_map[child->mark].append(child);
	if (child->n0 != nullptr)
		extendMap(child->n0);
	if (child->n1 != nullptr)
		extendMap(child->n1);
}

void AutManager::findAutGr()
{
	int level = 0;
	for (const auto& gr : m_map)
	{
		if (gr.size() == 1)
			continue;
		
		AutGroup aGr;
		for (auto item : gr)
		{
			group g(qMakePair(0, 0));
			if (item->n0 != nullptr)
				g.first = item->n0->id;
			if (item->n1 != nullptr)
				g.second = item->n1->id;

			aGr.gr.append(g);
		}
		aGr.level = ++level;

		m_autGr.append(aGr);
	}
}

void AutManager::getAut()
{
	int cur_level = 1;
	for (const auto& autGrs : m_autGr)
	{
		for (const auto& autGr : autGrs.gr)
		{
			auto currentAutList = m_autList;
			for (auto &aut : currentAutList)
			{
				std::swap(aut[autGr.first], aut[autGr.second]);
				m_autList.append(aut);
			}
		}
		
	}
}

void AutManager::writeAuts()
{
	QFile file("automorphism.txt");
	file.open(QIODevice::WriteOnly);
	QTextStream outputStream(&file);

	for (const auto& aut : m_autList)
	{
		for (const auto& item : aut)
			outputStream << item << ' ';
		outputStream << endl;
	}

	file.close();
}

//void AutManager::writeFile()
//{
//	// |Aut| = 2*x
//	QFile file("autGroups.txt");
//	file.open(QIODevice::WriteOnly);
//	QTextStream outputStream(&file);
//
//	int count = 1;
//	for (auto it : m_autGr)
//	{
//		for (auto pair : it.gr)
//		{
//			count *= 2;
//			outputStream << "(" << pair.first << ", " << pair.second << ")\n";
//		}
//	}
//
//	outputStream << "|Aut| = " << count;
//	file.close();
//}