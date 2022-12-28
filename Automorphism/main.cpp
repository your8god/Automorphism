#include <QtCore/QCoreApplication>
#include "Tree.h"
#include "AutManager.h"

int main(int argc, char *argv[])
{
    //QCoreApplication a(argc, argv);
	Tree t;
	AutManager a_m(t.getTree());

    //return a.exec();
}
