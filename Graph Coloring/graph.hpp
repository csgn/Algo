#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

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
  GHNode *adj;
};

class Graph
{
private:
  int m_size;
  GVNode **m_root;

public:
  void PrintGraph() const
  {
    if (m_root == nullptr)
      return;

    int i = 0;
    GHNode *walk;

    while (i < m_size)
    {
      std::cout << m_root[i]->id << "(" << m_root[i]->degree << ")"
                << "\t: ";
      walk = m_root[i]->adj;
      while (walk)
      {
        std::cout << walk->id << "\t";
        walk = walk->next;
      }
      std::cout << std::endl;
      i++;
    }
    free(walk);
  }

  void MatrixToGraph(int **M)
  {
    int N;
    GVNode **root;
    GHNode *walk = nullptr;
  }

  void CreateGraphFromFile(const std::string filePath)
  {
    int N, D;
    std::string buffer, line;
    GVNode **graph;
    GHNode *hwalk = nullptr;
    std::ifstream fs(filePath);

    getline(fs, buffer);
    std::stringstream ss(buffer);
    getline(ss, line, ',');
    N = stoi(line);

    graph = new GVNode *[N];
    for (int i = 0; i < N; i++)
    {
      getline(fs, buffer);
      std::stringstream ss(buffer);
      getline(ss, line, ',');

      graph[i] = new GVNode();
      graph[i]->id = stoi(line);

      while (getline(ss, line, ','))
      {
        if (not hwalk)
        {
          graph[i]->adj = new GHNode();
          graph[i]->adj->id = stoi(line);
          hwalk = graph[i]->adj;
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

    m_size = N;
    m_root = graph;
  }

  void SortGraph()
  {
    int i, j;
    for (i = 1; i < m_size; i++)
    {
      j = i;
      while (j > 0 and (m_root[j - 1]->degree < m_root[j]->degree or
                        (m_root[j - 1]->degree == m_root[j]->degree and m_root[j - 1]->id > m_root[j]->id)))
      {
        GVNode *tmp = m_root[j];
        m_root[j] = m_root[j - 1];
        m_root[j - 1] = tmp;
        j--;
      }
    }
  }

  void Colorify(int chromatic)
  {
    SortGraph();

    int M_size = chromatic;
    int A_size = chromatic;
    int D[chromatic], A[chromatic];
    int **M = new int *[chromatic];
    GVNode **root = m_root;
    GHNode *walk = nullptr;

    for (int i = 0; i < M_size; i++)
    {
      M[i] = new int[i];
      D[i] = 0;
      A[i] = i;
    }

    for (int i = 0; i < m_size; i++)
    {
      for (int a = 0; a < chromatic; a++)
        A[a] = a;

      walk = root[i]->adj;
      int index;
      while (walk)
      {
        index = -1;
        for (int x = 0; x < M_size && index == -1; x++)
        {
          for (int y = 0; y < D[x] && index == -1; y++)
          {
            if (M[x][y] == walk->id)
              index = x;
          }
        }

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
  }

  int **GraphToMatrix() const
  {
    int i, j;
    int **M = new int *[m_size];
    GHNode *walk;

    for (i = 0; i < m_size; i++)
    {
      j = 0;
      M[i] = new int[m_root[i]->degree + 1];
      M[i][j] = m_root[i]->id;

      walk = m_root[i]->adj;
      while (walk)
      {
        j++;
        M[i][j] = walk->id;
        walk = walk->next;
      }
    }

    return M;
  }

  void WriteToFile(const std::string fileName)
  {
    int **M = GraphToMatrix();
    int *cols = new int[m_size];
    std::ofstream fs(fileName);

    for (int i = 0; i < m_size; i++)
      cols[i] = m_root[i]->degree + 1;

    fs << m_size << '\n';
    for (int i = 0; i < m_size; i++)
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

    free(M);
    free(cols);
  }
};
