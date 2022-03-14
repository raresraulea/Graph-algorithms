
#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <list>

using namespace std;

ifstream fin("Text.txt");

int noduriA, noduriB;

void dateIn(vector<pair<int, int>>& LMA, vector<pair<int, int>>& LMB, int &ma, int &mb)
{
	fin >> ma >> mb;
	for (int i = 0; i < ma; i++)
	{
		int x, y;
		fin >> x >> y;
		if (x > y) swap(x, y);
		//cout << x << y << endl;
		LMA.emplace_back(x,y);
		noduriA = max(noduriA, max(x, y));
	}
	for (int i = 0; i < mb; i++)
	{
		int x, y;
		fin >> x >> y;
		if (x > y) swap(x, y);
		LMB.emplace_back(x, y);
		noduriB = max(noduriB, max(x, y));
	}
	sort(LMA.begin(), LMA.end());
	sort(LMB.begin(), LMB.end());
}
bool grafPartial(vector<pair<int, int>>& LMA, vector<pair<int, int>>& LMB, int ma, int mb)
{
	if (noduriA != noduriB) return false;
	for (auto p : LMA)
	{
		if (!binary_search(LMB.begin(), LMB.end(), p))
			return false;
	}
	return true;
}


int main()
{
	vector<pair<int, int>> LMA;
	vector<pair<int, int>> LMB;
	int ma, mb;
	dateIn(LMA, LMB, ma, mb);
	cout << grafPartial(LMA, LMB, ma, mb);
}
