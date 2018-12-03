#include "pch.h"
#include <iostream>
#include <cstdlib>
#include <vector>
#include <fstream>
const int maxdist = 9999;

using namespace std;

/*n是总的结点数,v是出发结点,dist是距离,pre前一个结点,d是结点间的权值*/


void Dijkstra(int n, int v, vector<int> &dist, vector<int> &pre, vector<vector<int>> &d)
{
	if (v < n) {
		vector<bool> s(n + 1);
		for (int i = 1; i <= n; i++)
		{
			dist[i] = d[v][i];
			if (dist[i] < maxdist)
				pre[i] = v;
			else
				pre[i] = 0;
		}
		dist[v] = 0;
		s[v] = true;
		for (int i = 2; i <= n; i++)//总的迭代次数
		{
			int best = v;
			int temp = maxdist;
			for (int j = 1; j <= n; j++)//找到最小的距离
			{
				if (!s[j] && dist[j] < temp)
				{
					temp = dist[j];
					best = j;
				}
			}
			s[best] = true;
			for (int j = 1; j <= n; j++)//更新dist和pre
			{
				if (!s[j] && d[best][j] != maxdist)
				{
					int newdist = dist[best] + d[best][j];
					if (newdist < dist[j])
					{
						dist[j] = newdist;
						pre[j] = best;
					}
				}
			}
		}
	}
	if (v > n) {
		vector<bool> s(v + 1);
		for (int i = 1; i <= v; i++)
		{
			dist[i] = d[v][i];//将当前结点到每一个结点的距离
			if (dist[i] < maxdist)
				pre[i] = v;
			else
				pre[i] = 0;
		}
		dist[v] = 0;
		s[v] = true;
		for (int i = 2; i <= v; i++)//总的迭代次数
		{
			int best = n;
			int temp = maxdist;
			for (int j = 1; j <= v; j++)//找到最小的距离
			{
				if (!s[j] && dist[j] < temp)
				{
					temp = dist[j];
					best = j;
				}
			}
			s[best] = true;
			for (int j = 1; j <= v; j++)//更新dist和pre
			{
				if (!s[j] && d[best][j] != maxdist)
				{
					int newdist = dist[best] + d[best][j];
					if (newdist < dist[j])
					{
						dist[j] = newdist;
						pre[j] = best;
					}
				}
			}
		}
	}
}



void printpath(vector<int> pre, int init, int fina)
{
	int temp;
	temp = fina;
	vector<int> t;
	while (fina != init)
	{
		t.push_back(temp);
		temp = pre[fina];
		fina = temp;
	}
	cout << init << "->";
	for (int i = t.size(); i > 1; i--)
	{
		cout << t[i - 1] << "->";
	}
	int i;
	cout << t[0] << endl;
	cout << "下一跳为:" << t[i = t.size() - 1] << endl;
	t.clear();
}




void Create(int n, int l) {
	vector<vector<int>> d(n + 1, vector<int>(n + 1));
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
			d[i][j] = maxdist;
	}
	fstream file;
	int ch;
	file.open("D.txt", ios::in);
	ch = file.get();
	if (file.eof()) {
		cout << "文件为空，需重新初始化!" << endl;
		file.close();
		ofstream file;
		file.open("D.txt");
		int p, q, len;
		for (int i = 1; i <= l; ++i)
		{
			cin >> p >> q >> len;
			file << p << " " << q << " " << len << " ";
			if (len < d[p][q])       // 有重边
			{
				d[p][q] = len;      // p指向q
				d[q][p] = len;      // q指向p，这样表示无向图
			}
		}
		file.close();
	}
	else {
		cout << "已有拓扑信息文件:" << endl;
		ifstream file;
		file.open("D.txt");
		int p, q, len;
		for (int i = 1; i <= l; i++) {
			file >> p >> q >> len;
			if (len < d[p][q])       // 有重边
			{
				d[p][q] = len;      // p指向q
				d[q][p] = len;      // q指向p，这样表示无向图
			}
		}
	}
	vector<int> dist(n + 1), pre(n + 1);
	int choice;
	cout << "输入1进行查询路由器并输出其路由表!" << endl;
	cin >> choice;
	if (choice == 1) {
		int p;
		cout << "输入你要查询的路由器的路由表:";
		cin >> p;
		for (int b = 1; b <= n; b++) {
			if (p != b) {
				for (int i = 1; i <= b; ++i)
					dist[i] = maxdist;
				Dijkstra(b, p, dist, pre, d);
				cout << "点" << p << "到点" << b << "的最短路径长度: " << dist[b] << endl;
				cout << "点" << p << "到点" << b << "的路径为:";
				printpath(pre, p, b);
			}
			else {
				continue;
			}
		}
	}
	//int a, b;
	/*cout << "请输入起始点:";
	cin >> a;
	cout << "请输入终止点:";
	cin >> b;
	for (int i = 1; i <= b; ++i)
		dist[i] = maxdist;
	Dijkstra(b, a, dist, pre, d);
	cout << "点" << a << "到点" << b << "的最短路径长度: " << dist[b] << endl;
	cout << "点" << a << "到点" << b << "的路径为:";
	printpath(pre, a, b);*/
	/*for (a = 1; a <= n; a++) {
		for (b = 1; b <= n; b++) {
			if (a != b) {
				for (int i = 1; i <= b; ++i)
					dist[i] = maxdist;
				Dijkstra(b, a, dist, pre, d);
				cout << "点" << a << "到点" << b << "的最短路径长度: " << dist[b] << endl;
				cout << "点" << a << "到点" << b << "的路径为:";
				printpath(pre, a, b);
			}
			else {
				continue;
			}
		}
	}*/
}






int main()
{
	int n, l;
	cout << "请输入结点数和线数：";
	cin >> n >> l;
	Create(n, l);
	/*for (int i = 1; i <= b; ++i)
		dist[i] = maxdist;
	Dijkstra(b, a, dist, pre, d);
	cout << "点"<<a<<"到点"<<b<<"的最短路径长度: " << dist[b] << endl;
	cout << "点"<<a<<"到点"<<b<<"的路径为:";
	printpath(pre, a, b);*/
	return 0;
}