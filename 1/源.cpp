#include "pch.h"
#include <iostream>
#include <cstdlib>
#include <vector>
#include <fstream>
const int maxdist = 9999;

using namespace std;

/*n���ܵĽ����,v�ǳ������,dist�Ǿ���,preǰһ�����,d�ǽ����Ȩֵ*/


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
		for (int i = 2; i <= n; i++)//�ܵĵ�������
		{
			int best = v;
			int temp = maxdist;
			for (int j = 1; j <= n; j++)//�ҵ���С�ľ���
			{
				if (!s[j] && dist[j] < temp)
				{
					temp = dist[j];
					best = j;
				}
			}
			s[best] = true;
			for (int j = 1; j <= n; j++)//����dist��pre
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
			dist[i] = d[v][i];//����ǰ��㵽ÿһ�����ľ���
			if (dist[i] < maxdist)
				pre[i] = v;
			else
				pre[i] = 0;
		}
		dist[v] = 0;
		s[v] = true;
		for (int i = 2; i <= v; i++)//�ܵĵ�������
		{
			int best = n;
			int temp = maxdist;
			for (int j = 1; j <= v; j++)//�ҵ���С�ľ���
			{
				if (!s[j] && dist[j] < temp)
				{
					temp = dist[j];
					best = j;
				}
			}
			s[best] = true;
			for (int j = 1; j <= v; j++)//����dist��pre
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
	cout << "��һ��Ϊ:" << t[i = t.size() - 1] << endl;
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
		cout << "�ļ�Ϊ�գ������³�ʼ��!" << endl;
		file.close();
		ofstream file;
		file.open("D.txt");
		int p, q, len;
		for (int i = 1; i <= l; ++i)
		{
			cin >> p >> q >> len;
			file << p << " " << q << " " << len << " ";
			if (len < d[p][q])       // ���ر�
			{
				d[p][q] = len;      // pָ��q
				d[q][p] = len;      // qָ��p��������ʾ����ͼ
			}
		}
		file.close();
	}
	else {
		cout << "����������Ϣ�ļ�:" << endl;
		ifstream file;
		file.open("D.txt");
		int p, q, len;
		for (int i = 1; i <= l; i++) {
			file >> p >> q >> len;
			if (len < d[p][q])       // ���ر�
			{
				d[p][q] = len;      // pָ��q
				d[q][p] = len;      // qָ��p��������ʾ����ͼ
			}
		}
	}
	vector<int> dist(n + 1), pre(n + 1);
	int choice;
	cout << "����1���в�ѯ·�����������·�ɱ�!" << endl;
	cin >> choice;
	if (choice == 1) {
		int p;
		cout << "������Ҫ��ѯ��·������·�ɱ�:";
		cin >> p;
		for (int b = 1; b <= n; b++) {
			if (p != b) {
				for (int i = 1; i <= b; ++i)
					dist[i] = maxdist;
				Dijkstra(b, p, dist, pre, d);
				cout << "��" << p << "����" << b << "�����·������: " << dist[b] << endl;
				cout << "��" << p << "����" << b << "��·��Ϊ:";
				printpath(pre, p, b);
			}
			else {
				continue;
			}
		}
	}
	//int a, b;
	/*cout << "��������ʼ��:";
	cin >> a;
	cout << "��������ֹ��:";
	cin >> b;
	for (int i = 1; i <= b; ++i)
		dist[i] = maxdist;
	Dijkstra(b, a, dist, pre, d);
	cout << "��" << a << "����" << b << "�����·������: " << dist[b] << endl;
	cout << "��" << a << "����" << b << "��·��Ϊ:";
	printpath(pre, a, b);*/
	/*for (a = 1; a <= n; a++) {
		for (b = 1; b <= n; b++) {
			if (a != b) {
				for (int i = 1; i <= b; ++i)
					dist[i] = maxdist;
				Dijkstra(b, a, dist, pre, d);
				cout << "��" << a << "����" << b << "�����·������: " << dist[b] << endl;
				cout << "��" << a << "����" << b << "��·��Ϊ:";
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
	cout << "������������������";
	cin >> n >> l;
	Create(n, l);
	/*for (int i = 1; i <= b; ++i)
		dist[i] = maxdist;
	Dijkstra(b, a, dist, pre, d);
	cout << "��"<<a<<"����"<<b<<"�����·������: " << dist[b] << endl;
	cout << "��"<<a<<"����"<<b<<"��·��Ϊ:";
	printpath(pre, a, b);*/
	return 0;
}