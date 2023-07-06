// TheNeighborMatrixOfGraph.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <queue>

#define infinity 1e6

typedef std::vector<std::vector<int>>  matrix;

int diam(const matrix& mat)
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

std::vector<int> bfs(const matrix& mat, int s)
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

matrix Xdist(const matrix& dist, int diam_g)
{
	matrix res(dist.size(), std::vector<int>(diam_g, 0));

	for (int i = 0; i < res.size(); i++)
		for (int j = 0; j < diam_g; j++)
			res[i][j] = std::count(dist[i].begin(), dist[i].end(), j + 1);

	
	for (int i = 0; i < res.size() - 1; i++)
		for (int j = i + 1; j < res.size(); j++)
		{
			if (res[i][0] < res[j][0])
				std::swap(res[i], res[j]);
			if (res[i][0] == res[j][0])
				for (int k = 1; k < res[i].size(); k++)
					if (res[i][k] < res[j][k])
					{
						std::swap(res[i], res[j]);
						break;
					}
		}

	return res;
}

int main()
{
	setlocale(LC_ALL, "Russian");

	std::cout << "Введите размер матрицы: ";
	int n;
	std::cin >> n;
	std::cout << "Введите матрицу: " << std::endl;
	matrix g(n, std::vector<int>());

	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
		{
			int a;
			std::cin >> a;
			g[i].push_back(a);
		}

	int diam_g = diam(g);
	std::cout << "Диаметр графа = " << diam_g << std::endl;

	matrix d;
	for (int i = 0; i < g.size(); i++)
		d.push_back(bfs(g, i));

	std::cout << "Расстояние от i до остальных: " << std::endl;
	for (int i = 0; i < d.size(); i++)
	{
		for (int j = 0; j < d.size(); j++)
			std::cout << d[i][j] << " ";
		std::cout << std::endl;
	}

	auto x_dist = Xdist(d, diam_g);

	std::cout << "Результат" << std::endl;
	for (int i = 0; i < x_dist.size(); i++)
	{
		for (int j = 0; j < x_dist[i].size(); j++)
			std::cout << x_dist[i][j] << " ";
		std::cout << std::endl;
	}

	system("pause");
}
