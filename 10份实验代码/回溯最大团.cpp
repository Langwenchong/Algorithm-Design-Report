#include <bits/stdc++.h>
using namespace std;

const int maxnum = 250;
bool a[maxnum][maxnum]; //图的邻接矩阵
bool x[maxnum];         //当前解
int cn;                 //当前团的顶点数
int bestn;              //当前的最优解
int n;                  //图G的顶点数
int e;                  //图G的边数

void traceback(int i)
{
    int j;
    if (i > n)
    {
        bestn = cn;
        cout << bestn << endl;
        for (j = 1; j <= n; j++)
        {
            if (x[j])
            {
                cout << j << " ";
            }
        }
        cout << endl;
        return;
    }

    bool ok = true;
    for (j = 1; j < i; j++)
    {
        if (x[j] && !a[j][i]) //i与j不相连，左子树不展开
        {
            ok = false;
            break;
        }
    }
    if (ok) //进入左子树
    {
        cn++;
        x[i] = true;
        traceback(i + 1);
        cn--; //为展开右子树做准备
    }
    if (cn + n - i > bestn) //剪枝策略
    {
        x[i] = false;
        traceback(i + 1);
    }
}

int main()
{
    int i, u, v;
    memset(a, false, sizeof(a));
    memset(x, false, sizeof(x));
    cin >> n >> e;
    char c = 'e';
    for (i = 0; i < e; i++)
    {
        cin >> c >> u >> v;
        a[u][v] = true;
        a[v][u] = true;
    }
    cn = bestn = 0;
    traceback(1);
    system("pause");
    return 0;
}
