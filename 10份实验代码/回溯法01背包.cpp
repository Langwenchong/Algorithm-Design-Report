#include<iostream> 
#include<time.h>
#include<windows.h>
#define MAXN 25
using namespace std;
int n = 7;
int W = 170;
int w[ ]= {0,41,50,49,59,55,57,60};
int v[ ] = {0,442,525,511,593,546,564,617};
int x[MAXN];
int maxv;

void dfs(int i, int tw,int tv,int op[]);
void display();

int main()
{
	LARGE_INTEGER fre={0};//储存本机CPU时钟频率
	LARGE_INTEGER startCount={0};
	LARGE_INTEGER endCount = {0};
	QueryPerformanceFrequency(&fre);
	
	int op[MAXN];
	dfs(1,0,0,op);
	display();
	
	  	QueryPerformanceCounter(&startCount);
		Sleep(1000);
	//结束计时
	QueryPerformanceCounter(&endCount);
	//计算时间差
	double dTimeTake = ((double)endCount.QuadPart - (double)startCount.QuadPart) / (double)fre.QuadPart;
	printf("用时%f\n", dTimeTake);
	return 0;
}

void dfs(int i, int tw,int tv,int op[])
{
	if(i>n)
	{
		if(tw <=W && tv >maxv)
		{
			maxv  = tv;
			for(int j=1;j<=n;j++)
			{
			 x[j] = op[j];	
			}
		}
	}
	else 
	{
		if(tw+w[i] <= W)
		{ 
		op[i] = 1;
		dfs(i+1,tw+w[i],tv+v[i],op);
     	}
		op[i]=0;
		dfs(i+1,tw,tv,op);
	}
}

void display()
{
	int i;
	printf("回溯求解结果\n");
	printf("选取的物品："); 
	for(i =1;i<=n;i++)
	   if(x[i] == 1)
	   cout<<i<<" ";
	   cout<<endl; 
    printf("总重量=%d,总价值=%d\n",W,maxv);
}
