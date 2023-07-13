#include <QtCore/QCoreApplication>
#include "Tree.h"
#include "AutManager.h"
#include "TheNeighborMatrixOfGraph.h"

int main(int argc, char *argv[])
{
    //QCoreApplication a(argc, argv);
	Tree t;
	TheNeighborMatrixOfGraph res(t.getNormalTree());
	res.getMatrix();
	//поиск автоморфизмов
	//AutManager a_m(t.getTree());

    //return a.exec();
}
