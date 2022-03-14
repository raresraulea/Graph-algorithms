#include<iostream>
#include<fstream>
#include<algorithm>
#include<vector>
#include<queue>
#define NMAX 101
#define ll long long

using namespace std;

ifstream fin("graf_partial_1.in");
ofstream fout("graf_partial_1.out");

int mat[NMAX][NMAX]; //mat adiacenta

int N, M; //nr oduri si nr muchii	

//afis mat de adiacenta cu gradele nodurilor(start = 0) sau fara (start  = 1)
void afis(int start)
{
	for (ll int i = start; i <= N; i++)
	{
		for (ll int j = start; j <= N; j++)
			fout << mat[i][j] << ' ';
		fout << endl;
	}
}
void readFromFile()
{
	fin >> N >> M;
	ll int x, y;
	for(int ct = 0; ct < N; ct++)
	{
		fin >> x >> y;
		if (!mat[x][y])
		{
			mat[x][y] = 1;
			mat[y][x] = 1;
			mat[0][x]++;
			mat[0][y]++;
			mat[x][0]++;
			mat[y][0]++;
		}
	}
}
bool esteBipartit(vector<int> &m1, vector<int> &m2)
{
	queue <int> q;
	vector<int> color(N+1, -1); // vector pentru cele doua "culori" 0 sau 1
	
	q.push(1);
	color[1] = 1;
	m1.push_back(1);

	//BFS
	while (!q.empty())
	{
		int nod = q.front();
		q.pop();
		for (int v = 1; v <= N; v++)
		{
			//exista muchie intre nodul curent si v, dar are aceeasi culoare 
			//adica doua noduri care ar fi trebuit sa fie in aceeasi multime sunt adiacente
			if (mat[nod][v] && color[v] == color[nod]) {
				fout << "NU";
				return false;
			}
			//exista muchie intre nod si v, iar v este necolorat	
			if (mat[nod][v] && color[v] == -1)
			{
				//aleg in care multime va fi introdus nodul explorat curent
				if (color[nod] == 1)
				{
					m2.push_back(v);
				}
				else m1.push_back(v);
				color[v] = (color[nod] + 1) % 2; //0-1 alternativ
				q.push(v);
			}
			
		}
	}
	fout << "DA" << endl;
	sort(m1.begin(), m1.end());
	sort(m2.begin(), m2.end());
	for (auto x : m1)
		fout << x << ' ';
	fout << endl;
	for (auto x : m2)
		fout << x << ' ';
	return true;
}

int main()
{
	vector<int> m1;
	vector<int> m2;
	readFromFile();
	esteBipartit(m1,m2);
}
