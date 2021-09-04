#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

struct GHNode
{
  int id;
  GHNode *next;
};

struct GVNode
{
  int id;
  int degree;
  int size;
  GHNode *link;
};

struct GRAPH
{
  int size;
  GVNode **root;
};

void printGraph(GRAPH *graph)
{
  int i = 0;
  GHNode *walk;

  while (i < graph->size)
  {
    cout << graph->root[i]->id << "(" << graph->root[i]->degree << ")"
         << "\t: ";
    walk = graph->root[i]->link;
    while (walk)
    {
      cout << walk->id << "\t";
      walk = walk->next;
    }
    cout << endl;
    i++;
  }

  free(walk);
}

void writeToFile(int **M, int r, int *cols, const string fileName)
{
  ofstream fs(fileName);

  for (int i = 0; i < r; i++)
  {
    for (int j = 0; j < cols[i]; j++)
    {
      if (j == cols[i] - 1)
        fs << M[i][j];
      else
        fs << M[i][j] << ",";
    }
    fs << '\n';
  }
}

GRAPH *createGraph(string file)
{
  int N, D;
  string buffer, line;
  GVNode **graph;
  GHNode *hwalk = nullptr;
  GRAPH *createdGraph = new GRAPH();
  ifstream fs(file);

  getline(fs, buffer);
  stringstream ss(buffer);
  getline(ss, line, ',');
  N = stoi(line);
  getline(ss, line, ',');
  D = stoi(line);

  graph = new GVNode *[N];
  for (int i = 0; i < N; i++)
  {
    getline(fs, buffer);
    stringstream ss(buffer);
    getline(ss, line, ',');

    graph[i] = new GVNode();
    graph[i]->id = stoi(line);

    while (getline(ss, line, ','))
    {
      if (not hwalk)
      {
        graph[i]->link = new GHNode();
        graph[i]->link->id = stoi(line);
        hwalk = graph[i]->link;
      }
      else
      {
        hwalk->next = new GHNode();
        hwalk->next->id = stoi(line);
        hwalk = hwalk->next;
      }

      graph[i]->degree++;
    }

    hwalk = nullptr;
  }

  hwalk = nullptr;
  free(hwalk);

  createdGraph->size = N;
  createdGraph->root = graph;
  return createdGraph;
}

void sortGraph(GRAPH *graph)
{
  int j;
  for (int i = 1; i < graph->size; i++)
  {
    j = i;
    while (j > 0 and (graph->root[j - 1]->degree < graph->root[j]->degree or
                      (graph->root[j - 1]->degree == graph->root[j]->degree and graph->root[j - 1]->id > graph->root[j]->id)))
    {
      GVNode *tmp = graph->root[j];
      graph->root[j] = graph->root[j - 1];
      graph->root[j - 1] = tmp;
      j--;
    }
  }
}

int find(int **M, int *D, int M_size, int id)
{
  for (int i = 0; i < M_size; i++)
  {
    for (int j = 0; j < D[i]; j++)
    {
      if (M[i][j] == id)
        return i;
    }
  }

  return -1;
}

void colorifyGraph(GRAPH *graph, const int colorCount)
{
  GVNode **root = graph->root;

  int n = graph->size;
  int D[colorCount] = {0, 0, 0}, A[colorCount] = {0, 1, 2};
  int **M = new int *[colorCount];
  GHNode *walk = nullptr;

  int M_size = colorCount;
  int A_size = colorCount;

  for (int i = 0; i < M_size; i++)
    M[i] = new int[i];

  for (int i = 0; i < n; i++)
  {
    A[0] = 0;
    A[1] = 1;
    A[2] = 2;
    walk = root[i]->link;
    while (walk)
    {
      int index = find(M, D, M_size, walk->id);
      if (index != -1)
        A[index] = -1;

      walk = walk->next;
    }

    int a_index = -1;
    for (int l = 0; l < A_size; l++)
    {
      if (A[l] != -1)
      {
        a_index = l;
        break;
      }
    }
    if (a_index != -1)
    {
      M[a_index][D[a_index]] = root[i]->id;
      D[a_index]++;
    }
  }

  for (int i = 0; i < M_size; i++)
  {
    cout << i << ": ";
    for (int j = 0; j < D[i]; j++)
      cout << M[i][j] << " ";
    cout << endl;
  }

  writeToFile(M, M_size, D, "coloringGraph.txt");
}

int **graphToMatrix(GRAPH *graph)
{
  int i, j;
  int **M = new int *[graph->size];

  GHNode *walk;
  for (i = 0; i < graph->size; i++)
  {
    j = 0;
    M[i] = new int[graph->root[i]->degree + 1];
    walk = graph->root[i]->link;
    M[i][j] = graph->root[i]->id;
    j++;

    while (walk)
    {
      M[i][j] = walk->id;
      walk = walk->next;
      j++;
    }
  }

  return M;
}

int main(int argc, char **argv)
{
  GRAPH *graph;
  graph = createGraph(argv[1]);

  cout << "GRAPH" << endl
       << "====================================" << endl;
  printGraph(graph);

  sortGraph(graph);
  cout << endl
       << "SORTED GRAPH" << endl
       << "====================================" << endl;
  printGraph(graph);

  cout << endl
       << "COLORIFY GRAPH" << endl
       << "====================================" << endl;
  colorifyGraph(graph, stoi(argv[2]));

  int **M = graphToMatrix(graph);
  int *cols = new int[graph->size];
  for (int i = 0; i < graph->size; i++)
    cols[i] = graph->root[i]->degree + 1;

  writeToFile(M, graph->size, cols, "sortedgraph.txt");

  return 0;
}
