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
	int cntMonoGr = 0;
	for (const auto& gr : m_map)
	{
		if (gr.size() == 1)
		{
			cntMonoGr++; //counts groups, that have one element
			continue;
		}
		
		AutGroup aGr;
		for (auto item : gr)
		{
			group g;
			QPair<int, int> mG;
			if (item->n0 != nullptr)
				mG.first = item->n0->id;
			if (item->n1 != nullptr)
				mG.second = item->n1->id;

			//group childGr;
			item->groups(g);
			g.append(mG);
			aGr.gr.append(g);
		}
		aGr.level = ++level;

		m_autGr.append(aGr);
	}

	if (cntMonoGr == 1) // it's the root
	{
		AutGroup aGr;
		group g;
		QPair<int, int> mG;
		auto item = m_map.last().first();

		mG.first = item->n0->id;
		mG.second = item->n1->id;

		item->groups(g);
		g.append(mG);
		aGr.gr.append(g);
		aGr.level = ++level;
		m_autGr.append(aGr);
	}
}

void AutManager::getAut()
{
	for (const auto& autGrs : m_autGr)
	{
		for (const auto& autGr : autGrs.gr)
		{
			auto currentAutList = m_autList;
			for (auto &aut : currentAutList)
			{
				for (const auto& pair : autGr)
				{
					std::swap(aut[pair.first], aut[pair.second]);
					//m_autList.append(aut);
				}
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