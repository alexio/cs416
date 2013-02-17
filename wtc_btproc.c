/*Bag of Tasks*/

void bagOfTask(struct row* boolMatrix, struct row* warPath, int numOfElements)
{
	int i, j, k;
	struct Queue *tempQ = createQueue(numOfElements);
	
	for(i = 0 ; i<numOfElements; i++)
	{
		for(j = 0; j < numOfElements; j++)
		{
			warPath[i].edgeNums[j] = boolMatrix[i].edgeNums[j];
		}
		enqueue(i);
	}
	for(k = 0; k < numOfElements ; k++)
	{
		for(i = 0 ; i < numOfElements ; i++)
		{
			while(tempQ->size > 0){
				
				for(j = 0; j < numOfElements; j++){
					a[i][j]=a[i][j]||(a[i][k] && a[k][j]);
				}
				temp->size--;
			}
		}
	}
}
