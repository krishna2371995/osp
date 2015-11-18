#include<stdio.h>
int allfinish(int *finish,int n)
{
	for(int i=0;i<n;i++)
	{
		if(finish[i]==0)
		return 0;
	}
	return 1;
}
int needwork(int *need,int *work,int m)
{
	for(int i=0;i<m;i++)
	{
		if(need[i]>work[i])
		return 0;
	}
	return 1;
}
void safety(int *available,int **need,int **allocation,int n,int m)
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
	printf("work is \n");
	for(int i=0;i<m;i++)
	{
		printf("%d ",work[i]);
	}
	printf("\n");
	for(int i=0;i<=n;i++)
	{
		finish[i]=0;
	}
	while(flag==1)
	{
		flag=0;
		for(int i=0;i<n;i++)
		{
			if(finish[i]==0 && needwork(need[i],work,m))
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
		printf("system is in safe state\n sequence is \n<");
		for(int i=0;i<=z;i++)
		{
			printf("%d,",sequence[i]);
		}
		printf(">\n");
	}
}
int reqst(int *request,int m)
{
	for(int i=0;i<m;i++)
	{
		if(request[i]>0)
		return 1;
	}
	return 0;
}
int reqavail(int *request,int *available,int m)
{
	for(int i=0;i<m;i++)
	{
		if(request[i]>available[i])
		return 0;
	}
	return 1;
}
int reqneed(int *request,int *need,int m)
{
	for(int i=0;i<m;i++)
	{
		if(request[i]>need[i])
		return 0;
	}
	return 1;
}
void resourserequest(int **request,int **need,int **allocation,int *available,int n,int m)
{
	for(int i=0;i<n;i++)
	{
		if(reqst(request[i],m))
		{
			if(reqneed(request[i],need[i],m))
			{
				if(reqavail(request[i],available,m))
				{
					
					for(int j=0;j<m;j++)
					{
						available[j]=available[j]-request[i][j];
						allocation[i][j]=allocation[i][j]+request[i][j];
						need[i][j]=need[i][j]-request[i][j];
					}
				}
				else
				{
					printf("process %d must wait ",i);
				}
			}
			else
			{
				printf("error \n");
			}
		}
	}
	printf("need matrix is \n");
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<m;j++)
		{
			printf("%d ",need[i][j]);
		}
		printf("\n");
	}
	printf("available vector is\n");
	for(int i=0;i<m;i++)
	{
		printf("%d ",available[i]);
	}
	printf("\n");
	safety(available,need,allocation,n,m);
}
int main()
{
	int m,n;
	printf("enter no. of processes\n");
	scanf("%d",&n);
	printf("enter no. of resources\n");
	scanf("%d",&m);
	int *available=new int[m];
	int **max=new int*[n];
	int **allocation=new int*[n];
	int **need=new int*[n];
	int **request=new int*[n];
	for(int i=0;i<n;i++)
	{
		max[i]=new int[m];
		allocation[i]=new int[m];
		need[i]=new int[m];
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
	printf("enter max matrix\n");
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<m;j++)
		{
			scanf("%d",&max[i][j]);
		}
	}
	printf("enter available vector\n");
	for(int i=0;i<m;i++)
	{
		scanf("%d",&available[i]);
	}
	printf("need matrix is \n");
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<m;j++)
		{
			need[i][j]=max[i][j]-allocation[i][j];
			printf("%d ",need[i][j]);
		}
		printf("\n");
	}
	safety(available,need,allocation,n,m);
	printf("enter request additional resources matrix\n");
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<m;j++)
		{
			scanf("%d",&request[i][j]);
		}
	}
	resourserequest(request,need,allocation,available,n,m);
}
/*
5 3
0 1 0
2 0 0
3 0 2
2 1 1
0 0 2
7 5 3
3 2 2
9 0 2
2 2 2
4 3 3
3 3 2
0 0 0
1 0 2
0 0 0
0 0 0
0 0 0
*/
