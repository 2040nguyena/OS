/**
 * COSC 3250 - Project 1
 * Explain briefly the functionality of the program.
 * @author Justin Nguyen
 * Instructor Sabirat Rubya
 * TA-BOT:MAILTO ducan.nguyen@marquette.edu
 */


#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

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


void currencyPrinter(){
	int c;
	long conv;
	float x = 0;
	unsigned long result;
	int total = 0;
	int result1;
	int input;
	int a = 0;
	//printf("===Currency Converter===\n");
	while(1){
		c = getch();
        if(c=='\n')
            continue;
		if(c == EOF){
			break;
		}
		while(isspace(c)){
			c=getch();
		}
		if(c == USD[0]){
			//printf("checkpoint0");
			printUSD();
			conv = 1000;
        }
		else if(c == EUR[0]){
			//printf("CHeckpoint1");
            c = getch();
            if(c == EUR[1]){
				//printf("CHeckpoint2");
                c = getch();
                if(c == EUR[2]){
					//printf("CHeckpoint3");
					printEur();
                    //printUSD();
                    conv = 897;
                }
                else if(c==Rupee[2])
                {
					//printf("CHeckpoint4");
                    //printUSD();
					printRupee();
                    conv = 70845;
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
				printPound();
				conv = 766;
			}
			else if (c==Yen[1]) {
				//printf("CHeckpoint7");
				//printUSD();
				printYen();
				conv = 109940;
			}
			else
            {
                printf("\nERROR: Unexpected input %d\n",c);
				//return 0;
            }
		}
		else{
			//printf("Checkpoint10");
			printf("\nERROR: Unexpected input %d\n",c);
			printf("$%d = $%d\n", a, a);
			//printf("TOTAL = %d\n", a);
			break;
			//return 0;
		}
	
	c = getch();
	while(isdigit(c)){
	  	x = (x*10) + (c - '0');
		c = getch();
	 }
	ungetch(c);
	input = (int)x;
	result = (x*1000)/conv;
	result1 = (int)result;
	printf("%d = %s%d\n", input, USD, result1);
	total = result + total;
	//printf("\nTotal:%f ", total);
	x = 0;
	}
	printf("TOTAL = %s%d\n ",USD, total);
	//return 1;
}




int main(){
	//loop which calls methods
	//total up return usd values
	//printf("Hello World\n");
       //characterPrinter();
	printf("===Currency Converter===\n");
    currencyPrinter();

	// int x = 0;
	// char c;
	// while(isdigit){
	// 	x = (x*10) + (c - '0');
	// 	c = getch();
	// }
	// c = ungetch();
	return 0;
}
