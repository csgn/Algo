#include <bits/stdc++.h>

using namespace std;


int main()
{
    int i, j, M, N;
    int **vert;
    string buffer;
    string line;
    ifstream fs("data.txt");
    
    getline(fs, buffer);
    stringstream ss(buffer);
    
    // number of node
    getline(ss, line, ' ');
    M = stoi(line);
    
    // number of edges
    getline(ss, line, ' ');
    N = stoi(line);
    
    // Adjacency matrix
    vert = new int*[N];
        
    // node, edge, direction
    int n, e, d;
    for (i = 0; i < M; i++)
    {
        vert[i] = new int[N];
        for (j = 0; j < M; j++)
        {
            getline(fs, buffer);
            stringstream ss(buffer);
            
            // node
            getline(ss, line, ' ');
            n = stoi(line);
            
            // edge
            getline(ss, line, ' ');
            e = stoi(line);
            
            // direction
            getline(ss, line, ' ');
            d = stoi(line);
            
            vert[n][e] = d;
        }
    }
    
    cout << "Adjacency Matrix" << endl;
    for (i = 0; i < M; i++)
    {
        for (j = 0; j < M; j++)
            cout << vert[i][j] << " ";
        cout << endl;
    }
    cout << endl;
    

    int x = 0, y = 0, l = 0, c = 0;
    int *AD = new int[M+1];
    int *AK = new int[N+1];

    for (i = 0; i < M; i++)
    {   
        x = y;
        for (j = 0; j < M; j++)
        {
            if (vert[i][j] == 1)
            {
                AK[l] = j;
                l++;
                y++;
            }
        }
        AD[c] = x;
        c++;
    }
    
    AD[c] = y;
    AK[l] = -1;
    
    cout << "AD:";
    for (i = 0; i < M+1; i++)
        cout << AD[i] << " ";
    
    cout << endl;

    cout << "AK:";
    for (i = 0; i < N+1; i++)
        cout << AK[i] << " ";
    return 0;
}
