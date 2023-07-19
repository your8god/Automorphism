#include "TheNeighborMatrixOfGraph.h"
#include <QFile>
#include <QTextStream>

#define infinity 1e6

TheNeighborMatrixOfGraph::TheNeighborMatrixOfGraph(const QMap<int, QString>& tree) 
{
	int n = tree.size();
	g = matrix(n, std::vector<int>(n, 0));

	for (auto it = tree.begin(); it != tree.end(); it++)
	{
		auto edges = it.value().split(" ");
		edges.removeLast(); // удаляем пустой итем

		for (const auto& item : edges)
			g[it.key()][item.toInt()] = 1;
	}
}

int TheNeighborMatrixOfGraph::diam(const matrix& mat)
{
	int n = mat.size();
	matrix edge(n, std::vector<int>(n, 0));
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
		{
			edge[i][j] = mat[i][j];
			if (!edge[i][j])
				edge[i][j] = infinity;
		}


	for (int k = 0; k < n; k++)
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				if (i != j)
					edge[i][j] = std::min(edge[i][j], edge[i][k] + edge[k][j]);

	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			if (edge[i][j] == infinity)
				edge[i][j] = 0;


	int max = edge[0][1];
	for (int i = 0; i < n; i++)
		for (int j = i + 1; j < n; j++)
			if (edge[i][j] > max)
				max = edge[i][j];

	return max;
}

std::vector<int> TheNeighborMatrixOfGraph::bfs(const matrix& mat, int s)
{
	auto d = std::vector<int>(mat.size(), -1);
	d[s] = 0;
	std::queue<int> q;
	q.push(s);

	while (!q.empty())
	{
		int v = q.front();
		q.pop();

		for (int i = 0; i < mat.size(); i++)
			if (mat[v][i] == 1 && d[i] == -1)
			{
				d[i] = d[v] + 1;
				q.push(i);
			}
	}

	return d;
}

matrix TheNeighborMatrixOfGraph::Xdist(const matrix& dist, int diam_g)
{
	matrix res(dist.size(), std::vector<int>(diam_g, 0));

	for (int i = 0; i < res.size(); i++)
		for (int j = 0; j < diam_g; j++)
			res[i][j] = std::count(dist[i].begin(), dist[i].end(), j + 1);


	for (int i = 0; i < res.size() - 1; i++)
		for (int j = i + 1; j < res.size(); j++)
			for (int k = 0; k < res[j].size(); k++)
			{
				if (res[i][k] < res[j][k])
				{
					std::swap(res[i], res[j]);
					break;
				}
				if (res[i][k] > res[j][k])
					break;
			}

	return res;
}

void TheNeighborMatrixOfGraph::getMatrix()
{
	int diam_g = diam(g);
	matrix d;
	for (int i = 0; i < g.size(); i++)
		d.push_back(bfs(g, i));

	auto x_dist = Xdist(d, diam_g);

	QFile file("x_matrix.txt");
	file.open(QIODevice::WriteOnly);
	QTextStream outputStream(&file);

	for (int i = 0; i < x_dist.size(); i++)
	{
		for (int j = 0; j < x_dist[i].size(); j++)
			outputStream << x_dist[i][j] << " ";
		outputStream << '\n';
	}

	file.close();

}