#include <bits/stdc++.h>

using namespace std;

#define MAXN 130     //邻接矩阵值
#define INF 0x3f3f3f //无限大值

int m[MAXN][MAXN]; //邻接矩阵

int bestN = 0; //已知的当前最大团数

struct Node
{
    int level;   //层数
    int cn;      //当前的已选节点数量
    int upbound; //un,就是最理想情况团的大小
    Node *parent;
    int isLeft;                                                         //是否是左展开节点
    Node(int _level, int _cn, int _upbound, Node *_parent, int _isLeft) //初始化赋值函数
    {
        level = _level;     //节点层数
        cn = _cn;           //当前已选择的节点数
        upbound = _upbound; //上界，即产生的最大团数
        parent = _parent;   //父节点
        isLeft = _isLeft;
    }
};

struct cmp
{
    bool operator()(Node *n1, Node *n2)
    {
        return n1->upbound < n2->upbound; // 规定比较规则为比较上界，制定活结点表排列规则
    }
};

priority_queue<Node *, vector<Node *>, cmp> pq; //初始化活结点表，权重是最大贪心团数值

bool constrain(Node *cNode) //用来判断左展开节点是否和已选的节点全部相连
{
    int tmp[MAXN];
    int n = cNode->level;
    tmp[n] = 1;
    while (cNode->parent != NULL)
    {
        tmp[cNode->level - 1] = cNode->isLeft ? 1 : 0;
        cNode = cNode->parent;
    }

    for (int i = 1; i <= n; i++)
    {
        if (tmp[i])
        {
            for (int j = 1; j <= n; j++)
            {
                if (i == j)
                    continue;
                if (tmp[j] && !m[i][j])
                    return false;
            }
        }
    }

    return true;
}

void maxGroupPrior(int n)
{
    // 初始化
    Node *root = new Node(1, 0, n, NULL, false);
    pq.push(root);

    Node *bestNode = NULL;

    // 开始广度搜索
    while (!pq.empty())
    {
        // 队首
        Node *cNode = pq.top();
        pq.pop(); //每次都取队首元素

        if (cNode->level == n + 1)
        {
            bestN = cNode->cn;
            bestNode = cNode;
            break;
        }

        // 左判约束
        if (constrain(cNode))
        {

            // 新建可行节点
            Node *tmp1 = new Node(cNode->level + 1, cNode->cn + 1, n - cNode->level + cNode->cn + 1, cNode, true);

            if (cNode->cn + 1 > bestN)
            {
                bestN = cNode->cn + 1;
                bestNode = tmp1;
            }
            // 将该节点加入优先队列
            pq.push(tmp1);
        }

        // 右判界
        if (cNode->upbound > bestN)
        {
            // 新建可行节点
            Node *tmp2 = new Node(cNode->level + 1, cNode->cn, n - cNode->level + cNode->cn, cNode, false);

            if (cNode->cn > bestN) //是否满足un>bestn
            {
                bestN = cNode->cn;
                bestNode = tmp2;
            }
            // 将该节点加入优先队列
            pq.push(tmp2);
        }
    }

    // 输出最优解
    cout << bestN << endl;
    while (bestNode->parent != NULL)
    {
        if (bestNode->isLeft)
        {
            cout << 1 << " ";
        }
        else
        {
            cout << 0 << " ";
        }
        bestNode = bestNode->parent;
    }
}

int main()
{
    int n, e;
    cin >> n >> e;
    //初始化邻接矩阵为零矩阵
    memset(m, 0, sizeof(m));
    for (int i = 0; i < e; i++)
    {
        int index1, index2;
        char c = 'e';
        cin >> c >> index1 >> index2;
        m[index1][index2] = 1; //赋值边
        m[index2][index1] = 1;
    }
    maxGroupPrior(n);
    system("pause");
    return 0;
}