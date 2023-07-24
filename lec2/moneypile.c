/**
 * COSC 3250 - Project 2
 * Explain briefly the functionality of the program.
 * @author Justin Nguyen
 * Instructor Sabirat Rubya
 * TA-BOT:MAILTO ducan.nguyen@marquette.edu
 */

#include <stdio.h>
#include <stdlib.h>
#define BUFSIZE 100



char buf[BUFSIZE];
int bufp=0;

int getch(void)                                     /* get a (possibly pushed back) character */
{
    return bufp > 0? buf[--bufp]: getchar();
}

void ungetch(int c) /* push character back on input */
{
    if (bufp >= BUFSIZE)
    {
        printf("ungetch: too many characters\n");
    }
    else
    {
        buf[bufp++] = c;
    }

}
unsigned char EUR[] = {0xE2, 0x82, 0xAC,0x00};
unsigned char USD[] = {0x24,0x00};
unsigned char Pound[] = {0xC2, 0xA3,0x00};
unsigned char Yen[] = {0xC2, 0xA5,0x00};
unsigned char Rupee[] = {0xE2, 0x82, 0xB9,0x00};
void printEur(){
	printf("%s", EUR);
}
void printUSD(){
	printf("%s", USD);
}
void printPound(){
	printf("%s", Pound);
}
void printYen(){
	printf("%s", Yen);
}
void printRupee(){
	printf("%s", Rupee);
}
void characterPrinter(){

	int c = getchar();

	while(c!= EOF){ //blah
		putchar(c);
		c = getchar();
}
}

struct moneyPile{
    //char *currency;
    int money[5];
    int index;
    struct moneyPile *next;

};

typedef struct moneyPile pile;
pile* addToPile(pile *start, int n){
    //Create start of linked list if nothing is there

    //If something is there, connect them 
    if(start == NULL){
        start = (pile*) malloc(sizeof(pile));
        if (start == NULL){
            printf("memory allocation error");
            exit(0);
        }
        else{
        start -> money[0] = n;
        start -> index = 1;
        start -> next = NULL;
        return start;
        }
    }
    else{
        if(start -> index == 5){
            pile *node = (pile *)malloc(sizeof(pile));
            if(node == NULL){
                printf("Memory Allocation Error");
                exit(0);
            }
            node -> money[0] = n;
            node -> index = 1;
            node -> next = start;
            start = node;
            return start;
        }
        else{
            start -> money[start -> index] = n; 
            start -> index++;
            return start;

        }
        //if l to r, loop until linked list node-> next == NULL
        
        //adding to front

        // pile *node = (pile *)malloc(sizeof(pile));
        // if (node == NULL){
        //     printf("memory allocation error");
        // }
        // node -> currency = c;
        // //node -> money = n;
        // int i = 0;
        // for (i; i <5; i++){
        //     node -> money[i] = n;
        // }
        // node -> index = i;
        // node -> next = start;
        // return node;
    }
}
    pile *dolpile = NULL;
    pile *eurpile = NULL;
    pile *pndpile = NULL;
    pile *rupeepile = NULL;
    pile *yenpile = NULL;

  void printUSpile(pile *start){
            int z;
            if(start != NULL){
                z = start -> index;}
            //for (z = start -> index; z >0; z--){
            while(start != NULL){
                z--;
                printf("%s%d\n",USD, start -> money[z]);
                if(z <=0){
                    start = start->next;
                    if(start != NULL){
                    z = start -> index;}
                }
                }
            }
 void printEURpile(pile *start){
            int z;
            if(start != NULL){
                z = start -> index;}
            //int z = start -> index;
            //for (z = start -> index; z >0; z--){
            while(start != NULL){
                //int z = start -> index;
                z--;
                printf("%s%d\n",EUR, start -> money[z]);
                if(z <=0){
                    start = start->next;
                    if(start != NULL){
                    z = start -> index;}
                }
                
                }
            }
  void printPNDpile(pile *start){
            int z;
            if(start != NULL){
                z = start -> index;}
            while(start != NULL){
                 //int z = start -> index;
                z--;
                printf("%s%d\n",Pound, start -> money[z]);
                if(z <=0){
                    start = start->next;
                    if(start != NULL){
                    z = start -> index;}
                }
                }
            }           
 void printYENpile(pile *start){
            int z;
            if(start != NULL){
                z = start -> index;}
            while(start != NULL){
                 //int z = start -> index;
                z--;
                printf("%s%d\n",Yen, start -> money[z]);
                if(z <=0){
                    start = start->next;
                    if(start != NULL){
                    z = start -> index;}
                }
                }
            }
 void printRUPEEpile(pile *start){
            int z;
            if(start != NULL){
                z = start -> index;}
            while(start != NULL){
                 //int z = start -> index;
                z--;
                printf("%s%d\n",Rupee, start -> money[z]);
                if(z <=0){
                    start = start->next;
                    if(start != NULL){
                    z = start -> index;}
                }
                }
            }
int main(){
    // pile *dolpile = NULL;
    // pile *eurpile = NULL;
    // pile *pndpile = NULL;
    // pile *rupeepile = NULL;
    // pile *yenpile = NULL;
    printf("=== Virtual Money Pile ===\n");
    int c;
    int amount;
	long conv;
	float x = 0;
	unsigned long result;
	int total = 0;
	int result1;
	int input;
	int a = 0;
    while(1){
		c = getch();
        if(c=='\n')
            continue;
		// if(c == EOF){
        //     printf("\nVirtual %s pile: \n", USD);

        //     printf("\nVirtual %s pile: \n", Pound);
        //     printf("\nVirtual %s pile: \n", Yen );
        //     printf("\nVirtual %s pile: \n", EUR);
        //     printf("\nVirtual %s pile: \n", Rupee);
		// 	break;
		// }
		while(isspace(c)){
			c=getch();
		}
		if(c == USD[0]){
			//printf("checkpoint0");
            scanf("%d", &amount);
            printf("Putting %s%d in %s pile.\n", USD, amount, USD);
            dolpile = addToPile(dolpile, amount);
			//conv = 1000;
        }
		else if(c == EUR[0]){
			//printf("CHeckpoint1");
            c = getch();
            if(c == EUR[1]){
				//printf("CHeckpoint2");
                c = getch();
                if(c == EUR[2]){
					//printf("CHeckpoint3");
                    scanf("%d", &amount);
                    printf("Putting %s%d in %s pile.\n", EUR, amount, EUR);
                    eurpile = addToPile(eurpile, amount);
                    
                    //printUSD();
                    //conv = 897;
                }
                else if(c==Rupee[2])
                {
					//printf("CHeckpoint4");
                    //printUSD();
                    scanf("%d", &amount);
                    printf("Putting %s%d in %s pile.\n", Rupee, amount, Rupee);
					//printRupee();
                    rupeepile = addToPile(rupeepile, amount);
                    //conv = 70845;
                }
                else
                {
                    printf("\nERROR: Unexpected input %d\n",c);
					//return 0;
                }
            }
        }
		else if (c == Pound[0]){
			//printf("CHeckpoint5");
			c = getch();
			if(c == Pound[1]){
				//printf("CHeckpoint6");
				//printUSD();
                scanf("%d", &amount);
                printf("Putting %s%d in %s pile.\n", Pound, amount, Pound);
				//printPound();
                pndpile = addToPile(pndpile, amount);
				//conv = 766;
			}
			else if (c==Yen[1]) {
				//printf("CHeckpoint7");
				//printUSD();
                scanf("%d", &amount);
                printf("Putting %s%d in %s pile.\n", Yen, amount, Yen);
				//printYen();
                yenpile = addToPile(yenpile, amount);
				//conv = 109940;
			}
			else
            {
                printf("\nERROR: Unexpected input %d\n",c);
				//return 0;
            }
		}
        else if(c == EOF){
            //printf("CHECK4");
            printf("\nVirtual %s pile: \n", USD);
           // printf("CHECK4");
            printUSpile(dolpile);
            printf("\nVirtual %s pile: \n", Pound);
            printPNDpile(pndpile);
            printf("\nVirtual %s pile: \n", Yen );
            printYENpile(yenpile);
            printf("\nVirtual %s pile: \n", EUR);
            printEURpile(eurpile);
            printf("\nVirtual %s pile: \n", Rupee);
            printRUPEEpile(rupeepile);
			break;
		}
		else{
			//printf("Checkpoint10");
			printf("\nERROR: Unexpected input %d\n",c);
			printf("$%d = $%d\n", a, a);
			//printf("TOTAL = %d\n", a);
			break;
			//return 0;
		}
	
	//  c = getch();
	//  while(isdigit(c)){
	//    	x = (x*10) + (c - '0');
	//  	c = getch();
	//   }
	//  ungetch(c);
	// input = (int)x;
	// result = (x*1000)/conv;
	// result1 = (int)result;
	// printf("%d = %s%d\n", input, USD, result1);
	// total = result + total;
	// //printf("\nTotal:%f ", total);
	// x = 0;
	}

    
    return 0;

}
//