#include<iostream>
#include <time.h>
#include<windows.h>
using namespace std;
#define max(x,y) ((x)>(y)?(x):(y))
#define MAXN 25                       
#define MAXW 800                    
int n = 15;
int W = 750;
int w[ ]= {0,70,73,77,80,82,87,90,94,98,106,110,113,115,118,120};
int v[ ] = {0,135,139,149,150,156,163,173,184,192,201,210,214,221,229,240};

int dp[MAXN][MAXW];
int x[MAXN];
int maxv;     

void Knap();          
void Buildx();         

int main()
{
		LARGE_INTEGER fre={0};//储存本机CPU时钟频率
	LARGE_INTEGER startCount={0};
	LARGE_INTEGER endCount = {0};
	QueryPerformanceFrequency(&fre);
	
	Knap();
    Buildx();
    printf("动态规划求解结果\n");
    printf("选取的物品："); 
	for(int i =1;i<=n;i++)
	{
	 if(x[i] == 1)
	  printf("%d ",i);
	  } 
	printf("\n");
	printf("总共价值 = %d\n",maxv); 
	
	  	QueryPerformanceCounter(&startCount);
		Sleep(1000);
	//结束计时
	QueryPerformanceCounter(&endCount);
	//计算时间差
	double dTimeTake = ((double)endCount.QuadPart - (double)startCount.QuadPart) / (double)fre.QuadPart;
	printf("用时%f\n", dTimeTake);
	return 0;
}

void Knap()
{
	int i,r;
	for( i =0;i<=n;i++)
	dp[i][0] = 0;
	for(r = 0;r<= W;r++)
     dp[0][r] = 0;
    for(i = 1;i<=n; i++)
    {
    	for(r =1;r<=W;r++)
    	if(r < w[i])
    	  dp[i][r] =dp[i-1][r];
    	  else 
    	  dp[i][r]  = max(dp[i-1][r],dp[i-1][r-w[i]]+v[i]);
	}
 } 

void Buildx()
{
	int  i =n;
	int r = W;
	maxv = 0; 
	while(i>=0)
	{
		if(dp[i][r]!= dp[i-1][r])
		{
			x[i] = 1;
			maxv += v[i];
			r = r - w[i];
		}
		else x[i] = 0;
		i--;
	}
}
