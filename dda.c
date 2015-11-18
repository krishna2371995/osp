#include<stdio.h>
int alloc(int *allocation,int m)
{
	for(int i=0;i<m;i++)
	{
		if(allocation[i]!=0)
		return 1;
	}
	return 0;
}
int reqwork(int *request,int *work,int m)
{
	for(int i=0;i<m;i++)
	{
		if(request[i]>work[i])
		return 0;
	}
	return 1;
}
int allfinish(int *finish,int n)
{
	for(int i=0;i<n;i++)
	{
		if(finish[i]==0)
		return 0;
	}
	return 1;
}
void deadlock(int *available,int **allocation,int **request,int n,int m)
{
	int flag=1;
	int *work,*finish,*sequence;
	work=new int[m];
	sequence=new int[n];
	int z=-1;
	finish=new int[n];
	for(int i=0;i<m;i++)
	{
		work[i]=available[i];
	}
	for(int i=0;i<n;i++)
	{
		if(alloc(allocation[i],m))
		finish[i]=0;
		else
		finish[i]=1;
	}
	while(flag==1)
	{
		flag=0;
		for(int i=0;i<n;i++)
		{
			if(finish[i]==0 && reqwork(request[i],work,m))
			{
				flag=1;
				for(int j=0;j<n;j++)
				work[j]=work[j]+allocation[i][j];
				finish[i]=1;
				sequence[++z]=i;
			}
		}
	}
	if(allfinish(finish,n))
	{
		printf("system is not in deadlock  state\n sequence is \n<");
		for(int i=0;i<=z;i++)
		{
			printf("%d,",sequence[i]);
		}
		printf(">\n");
	}
	else
	{
		printf("system is in deadlock state\n");
	}
}
int main()
{
	int m,n;
	printf("enter no. of processes\n");
	scanf("%d",&n);
	printf("enter no. of resources\n");
	scanf("%d",&m);
	int *available=new int[m];
	int **allocation=new int*[n];
	int **request=new int*[n];
	for(int i=0;i<n;i++)
	{
		allocation[i]=new int[m];
		request[i]=new int[m];
	}
	printf("enter allocation matrix\n");
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<m;j++)
		{
			scanf("%d",&allocation[i][j]);
		}
	}
	printf("enter REQUEST matrix\n");
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<m;j++)
		{
			scanf("%d",&request[i][j]);
		}
	}
	printf("enter available vector\n");
	for(int i=0;i<m;i++)
	{
		scanf("%d",&available[i]);
	}
	deadlock(available,allocation,request,n,m);	
}
/*
5 3
0 1 0
2 0 0
3 0 3
2 1 1
0 0 2
0 0 0
2 0 2
0 0 1
1 0 0
0 0 2
0 0 0
*/
