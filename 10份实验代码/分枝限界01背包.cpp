#include<iostream>
#include<queue>
#include<time.h>
#include<windows.h> 
using namespace std;
#define MAXN 25
int n = 7;
int W = 170;
int w[ ]= {0,41,50,49,59,55,57,60};
int v[ ] = {0,442,525,511,593,546,564,617};

int maxv = -9999;
int bestx [MAXN];
int total=1;

struct NodeType
{
	int no;
	int i;
	int w;
	int v;
	int x[MAXN];
	double ub;
};
void bound(NodeType &e );
void EnQueue(NodeType e,queue<NodeType> &qu);
void bfs();
int main()
{
	LARGE_INTEGER fre={0};//储存本机CPU时钟频率
	LARGE_INTEGER startCount={0};
	LARGE_INTEGER endCount = {0};
	QueryPerformanceFrequency(&fre);
	
	bfs();
	printf("分支限界求解结果：\n ");
	for(int i = 1;i<=n;i++)
	  if(bestx[i] == 1)
	    cout<<i<<" ";
	cout<<endl;
	printf("总价值=%d\n",maxv); 
	
	      	QueryPerformanceCounter(&startCount);
		Sleep(1000);
	//结束计时
	QueryPerformanceCounter(&endCount);
	//计算时间差
	double dTimeTake = ((double)endCount.QuadPart - (double)startCount.QuadPart) / (double)fre.QuadPart;
	printf("用时%f\n", dTimeTake);
    return 0;
}

void bound(NodeType &e )
{
	int i =e.i+1;
	int sumw = e.w;
	double sumv = e.v;
	while(i<= n && (sumw + w[i] <= W))
	{
		sumw += w[i];
		sumv+= v[i];
		i++;
	}
	if(i<=n)
	    e.ub = sumv+(W-sumw)*v[i]/w[i];
	else
	    e.ub = sumv; 
}

void EnQueue(NodeType e,queue<NodeType> &qu)
{
	if(e.i==n)
	{
		if(e.v>maxv)
		{
			maxv = e.v;
			for(int j =1;j<=n;j++)
			bestx[j]=e.x[j];
		}
	}
	else qu.push(e);
}

void bfs()
{
	int j;
	NodeType e,e1,e2;
	queue<NodeType> qu;
	e.i = 0;
	e.w = 0;
	e.v = 0;
	e.no = total++;
	for(j = 1;j<=n;j++)
	  e.x[j]=0;
	bound(e);
	qu.push(e);
	while(!qu.empty())
	{
		e = qu.front();
		qu.pop();
		if(e.w+w[e.i+1]<=W)
		{
			e1.no =total++;
			e1.i = e.i+1;
			e1.w = e.w+w[e1.i];
			e1.v = e.v+v[e1.i];
			for(j =1;j<=n;j++)
			   e1.x[j]=e.x[j];
			e1.x[e1.i] =1;
			bound(e1);
			EnQueue(e1,qu);
		}
		e2.no = total++;
		e2.i=e.i+1;
		e2.w=e.w;
		e2.v=e.v;
		for(j =1;j<=n;j++)
		    e2.x[j]=e.x[j];
		e2.x[e2.i]=0;
		bound(e2);
		if(e2.ub>maxv)
		EnQueue(e2,qu);
	}
}
