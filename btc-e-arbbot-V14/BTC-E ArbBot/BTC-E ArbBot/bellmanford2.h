#pragma once
#include <vector>
#include <iostream>
#include <algorithm>    // std::max
#include <float.h>

struct edge
{
	int a, b;
	double cost;
};

const double INF = DBL_MAX;

std::vector<edge> createGraph(double** l, int N) {
	std::vector<edge> e;
	for (int k = 0; k < N; ++k) {
		for (int i = 0; i < N; ++i) {
			struct edge *c = (struct edge*) malloc(sizeof(struct edge));
			//create edges
			//l[cur1_num][cur2_num] = -log(w[cur1_num][cur2_num]);
			//l[cur2_num][cur1_num] = -log(w[cur2_num][cur1_num]);
			//printf("l[%d][%d]: %f\n",k, i, l[k][i]);
			if (l[k][i] != INF) {
				c->a = k;
				c->b = i;
				c->cost = l[k][i];
				e.push_back(*c);
			}
		}
	}
	return e;
}

std::vector<int> solve(std::vector<edge>& e, int n, int m, int v)
{
	//n vertices and m edges  and some specified vertex v
	std::vector<double> d(n, 0);
	std::vector<int> path;

	d[v] = 0;
	std::vector<int> p(n);
	int x;
	for (int i = 0; i<n; ++i)
	{
		x = -1;
		for (int j = 0; j<m; ++j)
			if (d[e[j].a] < INF)
				if (d[e[j].b] > d[e[j].a] + e[j].cost)
				{
					d[e[j].b] = max(-INF, d[e[j].a] + e[j].cost);
					p[e[j].b] = e[j].a;
					x = e[j].b;
				}
	}
	if (x == -1)
		//std::cout << "No negative cycle from " << v;
		;
	else
	{
		int y = x;
		for (int i = 0; i<n; ++i)
			y = p[y];

		for (int cur = y; ; cur = p[cur])
		{
			path.push_back(cur);
			if (cur == y && path.size() > 1)
				break;
		}
		reverse(path.begin(), path.end());

		//std::cout << "\nNegative cycle: ";
		//for (size_t i = 0; i<path.size(); ++i)
		//	std::cout << path[i] << ' ';
	}
	return path;
}