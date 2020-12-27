#include <iostream>
using namespace std;
//动态规划解决矩阵乘法链问题
const int INT_MAX=2147483647;
const int MAXN=10;
void Solution(int *r,int Length,int m[][MAXN],int s[][MAXN]);
void POMCWP(int s[][MAXN],int i,int j);//Acronyms Print Optimal Matrix Chain With Parentheses
int main()
{
   int n;
   while(cin>>n)
   {
	   int r[MAXN]={0};
	   for(int i=0;i<n+1;i++)
	   {
		   int temp;
		   cin>>temp;
		   r[i]=temp;
	   }
	   int m[MAXN][MAXN],s[MAXN][MAXN];
	   Solution(r,n+1,m,s);
	   cout<<"Minimum: ";
	   cout<<m[1][n]<<endl;
	   cout<<"Order: ";
	   POMCWP(s,1,n);
   }
   system("pause");
   return 0;
}
void Solution(int *r,int Length,int m[][MAXN],int s[][MAXN])
{
	int q,n=Length-1;
	for(int i=1;i<=n;i++) m[i][i]=0;
	for(int l=2;l<=n;l++)
	{
		for(int i=1;i<=n-l+1;i++) 
		{
			int j=i+l-1;
			m[i][j]=INT_MAX;
			for(int k=i;k<=j-1;k++)
			{
				q=m[i][k]+m[k+1][j]+r[i-1]*r[k]*r[j];
				if(q<m[i][j])
				{
					m[i][j]=q;
					s[i][j]=k;
				}
			}
		}
	}
}
void POMCWP(int s[][MAXN],int i,int j)
{
	if(i == j) cout<<"M"<<i;
	else
	{
		cout<<"(";
		POMCWP(s,i,s[i][j]);
		POMCWP(s,s[i][j]+1,j);
		cout<<")";
	}
}