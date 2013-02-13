#include <stdio.h>
#include <string.h>

void printMatrix (int * matrix, int size);
//void wtc ( ) 

int main( int argc, char * argv [])
{
	int opt;
	char * filename ; 
	int n; // # of vertice 
	int p; // number of processes or thread
	int from, to ;
	int i, j;

	//argv[1];
	filename =  argv[2];
	
	printf(" %s \n", filename);
	FILE * fread = fopen( filename, "r" );

	fscanf ( fread ,"%d", &p );
	//printf (" p = %d \n", p);
	fscanf ( fread,"%d", &n );
	//printf (" n = %d \n", n);	

	int matrix[n][n];
	for(i =0 ; i< n; i++ )
		for(j =0; j <n ; j++)
			matrix[i][j] = 0;
	
	while( !feof(fread))
	{
		fscanf( fread,"%d %d", &from, &to);
	 	//printf(" %d %d  \n", from, to);
		matrix[from-1][to-1] = 1;
	}
		
	fclose(fread);
	
	// output 
	//for( i = 0; i < n; i++)
	//{
	//	for( j= 0; j < n; j++)
	//		printf("%d ", matrix[i][j]);
	//	printf("\n");
 	//}

	//******** BEGIN TO SOLVE THE PROBLEM ***********************
	
	// first, create a copy of the given matrix
	int result[n][n];

	for( i =0 ; i < n; i++)
		for ( j =0; j <n; j++)
			result[i][j] = matrix[i][j];



	// secondly, compute the transitive closure
	// i think we can improve more 
	int k;
	for ( k = 0; k < n; k++)
	{
		for ( i = 0; i < n; i++)
		{
			if ( result[i][k])
			{
				for ( j = 0; j < n ; j++)
					// imporve here, use an if instead of an OR statement
					result[i][j] = ( result[i][j] || result[k][j] );
			}						
		}
	}

	// print the result
	
	printMatrix ( result, n);

return(0);

}

void printMatrix( int  * matrix, int size)
{
	int i, j;
	for (i= 0; i < size ; i++)
	{
		for ( j = 0; j < size; j++)
			printf ( "%d ", matrix[size*i +j] );
		printf("\n");

	}
}
