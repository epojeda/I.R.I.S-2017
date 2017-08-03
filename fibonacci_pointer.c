#include <stdio.h>

int main()
{
	const int N = 20; 
	int i;
	int *arr = new int[N];

	*arr = 0;
	*(arr+1) = 1;
	for (i = 2; i<N; i++)
	{
		*(arr + i) = *(arr+i-1) + *(arr+i-2);		
	}

	for (i=0; i<N; i++)
	{
		printf("%d\n", *(arr+i));
	}

	return 0;
}
