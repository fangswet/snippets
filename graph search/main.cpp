#include <iostream>
#include <vector>
#include <stack>

using namespace std;

struct Matrix
{
    int* matrix;
    int width;
    
    Matrix(int w): matrix(new int[w * w]()), width(w)
    {}
    
    int& index(int x, int y)
    {
        return matrix[x + width * y];
    }
};

struct Graph
{
    Matrix matrix;
    
    Graph(int width) : matrix(Matrix(width))
    { }
    
    void addEdge(int u, int v, unsigned int weight)
    {
        matrix.index(u, v) = weight;
        matrix.index(v, u) = weight;
    }
    
    void BFS(int start)
    {
        vector<bool> visited(matrix.width, false);
        vector<int> queue { start };
        visited[start] = true;
        
        while (!queue.empty())
        {
            int v = queue[0];
            cout << v << ' ';
            queue.erase(queue.begin());
            
            for (int i = 0; i < matrix.width; i++)
            {
                if (matrix.index(v, i) && !visited[i])
                {
                    queue.push_back(i);
                    visited[i] = true;
                }
            }
        }
    }
    
    void DFS(int start)
    {
        vector<bool> visited(matrix.width, false);
        DFS(start, matrix, visited);
    }
    
    
    
private:
    static void DFS(int start, Matrix& matrix, vector<bool>& visited)
    {
        visited[start] = true;
        cout << start << ' ';
        
        for (int i = 0; i < matrix.width; i++)
        {
            if (matrix.index(start, i) && !visited[i])
                DFS(i, matrix, visited);
        }
    }
};

int main()
{
    auto g = Graph(10);
    g.addEdge(1, 2, 2);
    g.addEdge(2, 4, 3);
    g.addEdge(2, 5, 3);
    g.addEdge(5, 6, 4);
    g.addEdge(6, 3, 5);
    g.addEdge(4, 7, 1);
    g.addEdge(1, 7, 8);
    // technically same as exmaple
    g.BFS(1);
    cout << endl;
    g.DFS(1);

    return 0;
}
