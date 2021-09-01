#include <iostream>
#include <vector>
#include <fstream>
#include <utility>
#include <sstream>

using namespace std;

vector<vector<int>>
Parse(ifstream &fs)
{
  vector<vector<int>> D;

  string line;
  string buffer;

  while (getline(fs, line))
  {
    stringstream ss(line);
    vector<int> tmp;

    while (getline(ss, buffer, ';'))
      tmp.push_back(stoi(buffer));

    D.push_back(tmp);
  }

  return D;
}

int **CreateMatrix(vector<vector<int>> &d, const int M, const int N)
{
  int **gmatrix = 0;
  gmatrix = new int *[M];

  for (int i = 0; i < M; i++)
  {
    gmatrix[i] = new int[N];
    for (int j = 0; j < N; j++)
    {
      gmatrix[i][j] = 0;
    }
  }

  for (auto &vtx : d)
  {
    gmatrix[vtx[0]][vtx[1]] = vtx[2];
  }

  return gmatrix;
}

void ShowMatrix(int **gmatrix, int M, int N)
{
  for (int i = 0; i < M; i++)
  {
    for (int j = 0; j < N; j++)
    {
      cout << gmatrix[i][j] << " \t";
    }

    cout << endl;
  }
}

int main(int argc, char const *argv[])
{
  string file = "data.txt";
  ifstream fs(file);

  vector<vector<int>> d = Parse(fs);

  const int M = d[0][0], N = d[0][1];
  d.erase(d.begin() + 0);

  int **gmatrix;
  gmatrix = CreateMatrix(d, M, N);
  ShowMatrix(gmatrix, M, N);

  return 0;
}
