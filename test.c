int offsetValue = ceil(n/p);
	int count;
	 
	for ( count = 0; count < p ; count++)// run for number of threads
	{	
		if (fork()== 0)
		{
			printf("Process started\n");
			for( k= 0; k < n; k++)
			{ 
				for ( i = count* offsetValue; (i < (count+1)*offsetValue) && (i < n) ; i++)
				{
					
					if ( result[i][k])			
					{	
						for ( j = 0; j < n ; j++)
							result[i][j] = ( result[i][j] || result[k][j] );
						
					}
				}
			}
			printf("Process exited\n");
			exit(0);								
		}
		else
		{
			wait(NULL);
		}
		
	}

