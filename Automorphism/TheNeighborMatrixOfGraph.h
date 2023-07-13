#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <queue>
#include <QObject>
#include <QMap>

typedef std::vector<std::vector<int>>  matrix;

class TheNeighborMatrixOfGraph
{
public:
	TheNeighborMatrixOfGraph(const QMap<int, QString>& tree);
	void getMatrix();

protected:
	int diam(const matrix& mat);
	std::vector<int> bfs(const matrix& mat, int s);
	matrix Xdist(const matrix& dist, int diam_g);

protected:
	matrix g;
};

