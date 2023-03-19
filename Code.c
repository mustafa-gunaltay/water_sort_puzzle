#include <stdio.h>
#include <stdlib.h>
#include <time.h>


char header[] = {"--1--   --2--   --3--   --4--   --5--\n\n"};

char scores[4][5]; //array that colours of liquids will be stored

int i,j,k; // for loops

int s1,s2; // s1 -> the tube you want to take liquid from				s2 -> the tube you want to add liquid

char colourT1;
int counterT1=0;




void declareFirstScores();
void printTubes();

void choose();
	int error(int s1, int s2);

	void getNumAndCol();
	void emptyTube1(int s1);
	void addTube2(int s2);
	
int checkWin();
	
		
int main() 
{
	
	declareFirstScores();
	
	printTubes();

	while (1)
	{
		choose();
		
		printTubes();
		
		if ( checkWin() == 3 )
		{
			printf("GAME OVER \n\n");
			break;	
		}	
				
	}
	
	return 0;
}



void choose()
{
	
	while (1)
	{
	
	printf("Please choose the tube you want to take liquid from\n");
	scanf("%d",&s1);
	
	printf("Please choose the tube you want to add liquid:\n");
	scanf("%d",&s2);
	
	if (  !( s1>=0 && s1<=5		&&		s2>=0 && s2<=5 ) )
	{
		printf("\n!! Invalid tube number !!\n\n");
		printTubes();
		continue;
	}
	
	if ( error(s1,s2) == 1 )
	{
		printf("\n!! The tube you want to add liquid is full !!\n\n");
		printTubes();
		continue;
	}

	if (error(s1,s2) == 2)
	{
		printf("\n!! The tube you want take liquid from is empty !! \n\n");
		printTubes();
		continue;
	}
	
	
	if ( error(s1,s2) == 3 )
	{
		printf("\n!! The colours of the liquids you want to put on the top are different !! \n\n");
		printTubes();
		continue;
	}
	
	if (error(s1,s2) == 4)
	{
		printf("\n!! Second tube shouldn't overflow !!\n\n");
		printTubes();
		continue;
	}  	
		
		
	getNumAndCol();
	emptyTube1(s1);
	addTube2(s2);
	
	break;
	
	}
	
}




// finding which liquid is on the top by passing space characters and finding how many this liquids are

void getNumAndCol()
{
	
	// finding which liquid is on the top by passing space characters
	
	for (i=0 ; i <= 3 ; i++)
	{
		if (scores[i][s1-1] != ' ')
		{
			colourT1 = scores[i][s1-1]; // colourT1 -> which colour is the liquid
			
			k = i;  //k --> index of liquid on the top of the tube
			break;
		}
	} 
		
	
	//finding how many liquids that are same colours are on the top
	
	counterT1=0; 
		
	for (j = k ; j<=3 ; j++)
	{
		if (scores[j][s1-1] != colourT1)
		{
			break;
		}
		if (scores[j][s1-1] == colourT1)
		{
			counterT1++; // counterT1 -> how many liquids that are same colours are on the top
		}
	}
	
		
}





// empities the tube that liquid is taken from

void emptyTube1(int s1)
{	
	
	if (counterT1 != 1)
	{
		for (i=k ; i <= k + counterT1 -1 ; i++)  
		{
			scores[i][s1-1] = ' ';				
		}	
	}
	else	
	{
		scores[k][s1-1] = ' ';
	}
	
}




// adds liquid into tube 2

void addTube2(int s2)
{
	
	// finding the first space by starting from the bottom	
		
	for (i=3 ; i>=0 ; i--)
	{
		if (scores[i][s2-1] == ' ')
		{
			k = i;
			break;
		}
	}
	

	//adding the liquids from where first space begins from 	
		
	for (j=k ; j>= k - counterT1 + 1  ; j--)
	{
		scores[j][s2-1] = colourT1;
	}
		
}





// returns different numbers that means different errors

int error (int s1, int s2)
{
	 // check if second tube is full		
	
	if (scores[0][s2-1] != ' ')
	{
		return 1;
	}	 
	
	
	// check if first tube is empty
		 	
	if (scores[3][s1-1] == ' ')
	{
		return 2;
	}
	
	 
	 
	// check if colours of liquids are different

	char char1, char2;
	
	if (scores[3][s2-1] == ' ') // if tube is empty we don't need to colours of liquids
	{
		return 0;
	}
	else
	{
		for (i=0 ; i <= 3 ; i++)
		{
			if (scores[i][s1-1] != ' ')
			{
				char1 = scores[i][s1-1]; 
				break;
			}	
		}
		
		for (i=0 ; i <= 3 ; i++)
		{
			if (scores[i][s2-1] != ' ')
			{
				char2 = scores[i][s2-1]; 
				break;
			}	
		}
		
		if (char1 != char2)
		{
			return 3;
		}
		
	} 
	
	
	
	// check if the second tube is going to overflow
	
	
	int spaceCounter=0;		//spaceCounter will calculate how many spaces are there
	
	for (i=0 ; i<=3 ; i++)
	{
		if (scores[i][s2-1] == ' ')
		{
			spaceCounter++;
		}
		
	}
		
		
	getNumAndCol(); 	// getNumAndCol() will calculate how many units of liquids will be added and assign that value into kontrol_1
	
	if (counterT1 > spaceCounter)
	{
		return 4;
	}


	
return 0; // if there are none of these errors it will return 0 which means there are not any error
}





// creates different liquid combinations in first tube , second tube and third tube 

void declareFirstScores()
{
	srand(time(NULL));
	
	int dizi[4][3]; 	// number representation of colours with 0 , 1 and 2		/		0 -> RED	 ,    1 -> GREEN     ,      2 -> BLUE   	
	int x,y;
	
	for(i=0 ; i<=3 ; i++)
	{
		for(j=0 ; j<=2 ; j++)
		{
			dizi[i][j] = -1; // -1 means none of these colours
		}
	}
	
	//assignment of number representations of colours
	
	for (k=0 ; k<=2 ; k++)
	{
		i=4;
		while (i>0)
		{
			x = rand()%4 ;
			y = rand()%3 ;
		
			if(dizi[x][y] != -1)
			{
				i++;
				
			}
			
			if(dizi[x][y] == -1)
			{
			dizi[x][y] = k;
			}

		i--;
			
		}
		
	
	}


	// turning 0 , 1 and 2 into their corresponding colours
	
	for(i=0 ; i<=3 ; i++)
	{
		for(j=0 ; j<=2 ; j++)
		{
			if (dizi[i][j] == 0)
			{
				scores[i][j] = 'R';
			}
			
			if (dizi[i][j] == 1)
			{
				scores[i][j] = 'G';
			}
			
			if (dizi[i][j] == 2)
			{
				scores[i][j] = 'B';
			}
			
		}
		
	}
	
	//filling remaining places with spaces
	
	for (i=0 ; i<=3 ; i++)
	{
		for(j=3 ; j<=4 ; j++)
		{
			scores[i][j] = ' ';
		}
	}
	
}




//prints tubes

void printTubes()
{
	printf("%s",header);
	
	for (i=0 ; i<=3 ; i++)
	{
		
	printf("| %c |   | %c |   | %c |   | %c |   | %c |\n",scores[i][0], scores[i][1], scores[i][2], scores[i][3], scores[i][4] );   //  1	3	5	7			
	
	printf("|---|   |---|   |---|   |---|   |---|\n");
		
	}
}



//checks win

int checkWin()
{
	char charr;
	int subCounter = 0 , mainCounter = 0;
	
	for (i=0 ; i<=4 ; i++)
	{
		subCounter = 0;
		
		charr = scores[0][i];
		
		if (charr == ' ')
		{
			continue;
		}
		for(j=0 ; j<=3 ; j++)
		{
			if(charr == scores[j][i] )
			{
				subCounter++;
			}
		}
		if (subCounter == 4)
		{
			mainCounter++;
		}
		
	}
	return mainCounter;
}








