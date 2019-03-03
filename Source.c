#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <conio.h>

void heading(void);
void instructions(void);
void game(void);
void printStack(int[], int[], int[], int);
void printDisk(int[], int, int);
void rodLabelling(int);
void scoreBar(int, int, int);
int switchCommand(int[], int[], int, int);

static int moves;      //global static ints declared 
static int moveCheck;      //moves and moveCheck both initialized (only once) to 0

void main()
{
	int choice1, choice2;
label1:    //label
	system("cls");     // labelled statement
	heading();
	puts("Enter 0 to read instructions or 1 to play the game:");
	if (!scanf_s("%d", &choice1))     
                  /*scanf_s waits for input from user. As soon as \n is detected, 
                  scanf_s returns 0 or 1 according to input data type. It returns
                  0 whenever the data specifier does not match data type of input*/
	{
		scanf_s("%*[^\n]");    
                 /*scanf_s does not ask for an input again here, instead it reads the
                 already scanned illegal input.
                 %*[^\n] scans everything until a \n and discards it so that next call
                 of scanf_s function can wait for input from user.
                 Data Specifier: negated scanset [^characters] is used. It scans
                 everything until characters within [^...] reached
                 Sub Specifier: starting asterisk * is used. It reads data from stream
                 but does not store it */
		printf("\n Invalid Input. <Press any key to re-enter>");
		_getch();
		goto label1;   
           /*compiler goes back to the labelled statement below java1 giving the user a
           chance to input again*/
	}
	switch (choice1)
	{
	case(0):    //case when user chose to read instructions
	label2:
		system("cls");
		heading();
		instructions();
		puts("\nEnter -1 to exit the game or enter 1 to play the game.\n");
		if (!scanf_s("%d", &choice2))      
                     /*if input is a character or a string, give user chance
                     to input again*/
		{
			scanf_s("%*[^\n]");
			printf("\n Invalid Input. <Press any key to re-enter>");
			_getch();
			goto label2;
		}
		if (choice2 == -1)      //if user chose to exit the game, break from the switch-case
			break;
		else if (choice2 == 1);       
                  /*if user chose to play the game do not break from the switch
                  -case as the next case controls the game*/
		else if (choice2 != -1 && choice2 != 1)      
                         /*else if wrong integral input, give user chance
                         to input again*/
		{
			puts("Invalid Input. <Press any key to re-enter>");
			_getch();
			goto label2;
		}
	case(1):    //case when user chose to play the game
		game();
		break;
	default:    //default case when wrong integral input is given by user
		puts("Invalid Input. <Press any key to re-enter>");
		_getch();
		goto label1;
	}
	system("pause");
}

void heading(void)
{
	puts("**********************************************************");
	puts("                     TOWER OF HANOI");
	puts("**********************************************************");
	puts("");
}

void instructions(void)
{
	puts("                 Game Instructions");
	puts("                *******************");
	puts("\nDESCRIPTION:");
	puts("The Tower of Hanoi is a mathematical puzzle. It ");
	puts("consists of three rods and a number of disks of ");
	puts("different sizes, which can slide onto any rod.The");
	puts("puzzle starts with the disks in a neat stack in ");
	puts("ascending order of size on one rod, the smallest ");
	puts("at the top, thus making a conical shape.");
	puts("\nOBJECTIVE:");
	puts("The objective of the puzzle is to move the entire ");
	puts("stack to the destination rod (rod 3), obeying the ");
	puts("following simple rules: ");
	puts("1.Only one disk can be moved at a time.");
	puts("2.Each move consists of taking the upper disk from ");
	puts("  one of the stacks and placing it on top of ");
	puts("  another stack");
	puts("3.No disk may be placed on top of a smaller disk.");
	puts("\nCOMMANDS:");
	puts("To move the disk from one rod to the other enter a ");
	puts("two digit number with its 1st digit representing ");
	puts("the rod from which the disk is to be moved and the");
	puts("2nd digit representing the rod to which the disk ");
	puts("is to be moved to.");
	puts("e.g to move the disk from rod 1 to 2, enter 12.");
	puts("\nNOTE");
	puts("This game is limited to a minimum of 2 disks and ");
	puts("a maximum of 9 disks.");
}

void game(void)
{
	int a[10] = { 0, 1, 22, 333, 4444, 55555, 666666, 7777777, 88888888, 999999999 };
	int b[10] = { 0 };      //initialized controlling arrays
	int c[10] = { 0 };
	int n;     //total no. of disks 'n' initializes to 0 only once
label3:
	system("cls");
	heading();
	while (1)    //infinite loop until break statement found
	{
		puts("Enter the Number of Discs you want to play with.");
		if (!scanf_s("%d", &n))
		{
			scanf_s("%*[^\n]");
			printf("\n Invalid Input. <Press any key to re-enter>");
			_getch();
			goto label3;
		}
		if (n>1 && n<10)    //break the loop if no. of disks lie within the allowed range 
			break;
		else     //give user chance to input again if no. of disks do not lie within the allowed range
		{
			system("cls");
			heading();
			puts("You can only play with at least 2 or at most 9 disks.\n");
			continue;
		}
	}
label4:
	system("cls");
	printStack(a, b, c, n);     // call function printStack to print the initial stack
	while (1)     //infinite loop until the break statement is found
	{
		static int g;    //a check integer g initializes to 0 only once
		if (g == 1)
		{
			puts("\nYou cannot place a larger disk on a smaller disk.\n\nEnter your command below:\n");
			g--;     //decrement in g to make it equal to 0
		}
		else if (g == -1)
		{
			puts("\nThere is no disk to displace.\n\nEnter your command below:\n");
			g++;     //increment in g to make it equal to 0
		}
		else
			puts("\nEnter your command below:\n");
		int d;
		if (!scanf_s("%d", &d))     //if input is a character or a string give user chance to input again
		{
			scanf_s("%*[^\n]");
			printf("\n Invalid Input. <Press any key to re-enter>");
			_getch();
			goto label4;
		}
		puts("");
		switch (d)     //input cases
		{
		case (12):
			g = switchCommand(a, b, n, g);    // call function switchCommand
			printStack(a, b, c, n);       // call function printStack to print the stack after switching
			break;
		case (13):
			g = switchCommand(a, c, n, g);
			printStack(a, b, c, n);
			break;
		case (21):
			g = switchCommand(b, a, n, g);
			printStack(a, b, c, n);
			break;
		case (23):
			g = switchCommand(b, c, n, g);
			printStack(a, b, c, n);
			break;
		case (31):
			g = switchCommand(c, a, n, g);
			printStack(a, b, c, n);
			break;
		case (32):
			g = switchCommand(c, b, n, g);
			printStack(a, b, c, n);
			break;
		default:      //default case if ser input wrong integral input
			system("cls");
			printStack(a, b, c, n);
			puts("\nInvalid Input.");
			break;
		}
		if (c[1] == 1)  
          /*if the stack has been completely made on 3rd rod,
          user wins and program ends*/
		{
			int a = 1;
			printf("\nYou win. %c\n", a);     //ascii value: 1      character: smilie
			break;
		}
	}
}

void printStack(int a[], int b[], int c[], int n)   //function to print the stacks
{
	heading();
	for (int i = 1; i <= n; i++)    // i controls the row number, n is the total no. of rows
	{       //function printDisk called for printing each disk row wise one by one
		printDisk(a, n, i);     //print the ith disk of rod 1 controlled by array a
		printDisk(b, n, i);     //print the ith disk of rod 2 controlled by array b
		printDisk(c, n, i);     //print the ith disk of rod 3 controlled by array c
		puts("");     //new line for next row if any
	}
	rodLabelling(n);    //call function rodLabelling
	puts("");
	scoreBar(moves, moveCheck, n);    //call function scoreBar
	puts("");
}

void printDisk(int m[], int n, int i)
{
	if (m[i] == 0)    
          /*if there is no non zero element (i.e. only the rod) to print, print n spaces,
          the element m[i] i.e. 0 and further n spaces covering a total of 2n+1 space*/
	{
		for (int j = 1; j <= n; j++)
			printf(" ");
		printf("%d", m[i]);
		for (int j = 1; j <= n; j++)
			printf(" ");
	}
	else     
     /*else print n-m[i] space, the element m[i], the element m[0] i.e. 0, the element m[i]
     and further n spaces covering a total of 2n+1 space*/
	{
		for (int j = 1; j <= n - m[i] % 10; j++)
			printf(" ");
		printf("%d%d%d", m[i], m[0], m[i]);     //this line prints a disk on the rod
		for (int j = 1; j <= n - m[i] % 10; j++)
			printf(" ");
	}
}

void rodLabelling(int n)
{
	/*print a line under the rods covering
  a total space of 3*(2*n+1) */
	for (int j = 1; j <= 6 * n + 3; j++)
		printf("_");
	puts("");
	for (int rod = 1; rod <= 3; rod++)      //total space 3*(2n+1)
	{
		/*print rod number "rod" and a line to its left and right
    covering a total space of 2n+1 */
		for (int j = 1; j <= n; j++)
			printf("_");
		printf("%d", rod);
		for (int j = 1; j <= n; j++)
			printf("_");
	}
}

void scoreBar(int moves, int movesCheck, int n)
{
	puts("");
	printf("MOVES: %d", moves);
	int sp = 4;    
         /*sp has been initialized as an int to 4. On printing sp using data specifier c,
         the integral value sp carries is read as ascii number and its associated character
         is printed.              ascii value: 4      character: ♦ (diamond)*/
	if (moves <= pow(2, n) - 1)
		printf("    .%c%c%c.", sp, sp, sp);
	else if (moves > pow(2, n) - 1 && moves < (pow(2, n) - 1) * 2)
		printf("    .%c%c .", sp, sp);
	else
		printf("    .%c  .", sp);
	puts("");
	int score = 1000 * n - moves - movesCheck;
	printf("SCORE: %d", score);
}

int switchCommand(int x[], int y[], int n, int g)     
                          /*switch values such that the rod moves from
                          disk controlled by x[] to disk controlled by y[]*/
{
	int m = moves;
	if (x[n] == 0)    //if the rod is empty, do not switch and decrement check int g
	{
		g--;
		system("cls");
	}
	else
	{
		for (int i = 1; i <= n; i++)    //i controls rod disk x[i] to be moved
		{
			int check = 0;    
              /*initialized to 0. Check if switching has yet occurred or if allowed.
              Switching is not allowed if user tries to place a larger disk on
              a smaller disk*/
			if (x[i] != 0)    //the disk of the rod to be moved should be non zero 
			{
				for (int k = 0; k < n; k++)    //k contols the position n-k of the rod elemet y[n-k]
				{
					if (y[n - k] == 0)     
                     /*the position to be move to should be empty
                     (only zero element, no disk present)*/
					{
						if (x[i] < y[n - k + 1] || k == 0)     
                               /*if disk to be displaced is smaller than
                               the disk it is to be placed on or the disk
                               to be displaced is to be placed on the low
                               most position, switch*/
						{
							int temp;
							temp = x[i];
							x[i] = y[n - k];
							y[n - k] = temp;
							moves++;
						}
						else    //else donot switch and increment check int g since switching not allowed
							g++;
						check++;      //increment check
						break;
					}
				}

			}
			if (check != 0)    
               /*if switching has occurred or not allowed, no need to further run
               the loop, break from the loop*/
			{
				system("cls");
				break;
			}
		}
	}
	if (m == moves)    //check if switching did not occur but user had given an input
		moveCheck++;
	return g;   // return check value g
}
