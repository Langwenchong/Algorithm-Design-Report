#include <iostream>
#define MAXN 30
using namespace std;
void Solution_DFS(int TotalWeight, int RestWeight, int x[], int i, int n, int m, int w[]);
//回溯法解决子集和数问题
int main()
{
    int n, m;
    while (cin >> n >> m)
    {
        int w[MAXN] = {0};
        int RestWeight = 0;
        for (int i = 1; i <= n; i++)
        {
            int temp;
            cin >> temp;
            w[i] = temp;
            RestWeight += temp;
        }
        int x[MAXN] = {0};
        Solution_DFS(0, RestWeight, x, 1, n, m, w);
    }
    system("pause");
    return 0;
}
void Solution_DFS(int TotalWeight, int RestWeight, int x[], int i, int n, int m, int w[])
{
    if (i > n)
    {
        if (TotalWeight == m)
        {
            for (int i = 1; i <= n; i++)
                cout << x[i] << " ";
            cout << endl;
        }
    }
    else
    {
        if (TotalWeight + w[i] <= m)
        {
            x[i] = 1;
            Solution_DFS(TotalWeight + w[i], RestWeight - w[i], x, i + 1, n, m, w);
        }
        if (TotalWeight + RestWeight > m)
        {
            x[i] = 0;
            Solution_DFS(TotalWeight, RestWeight - w[i], x, i + 1, n, m, w);
        }
    }
}