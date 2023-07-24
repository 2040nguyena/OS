#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

unsigned char EUR[] = {0xE2, 0x82, 0xAC, 0x00};
void printEur(){
	printf("This is a Eur sign %s\n", EUR);
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

	while(c= getchar(), c!= EOF){
		putchar(c);
		if(c == 'a'){
			printf("\nThe letter a was found\n");		
}	
		else if(c == 'b'){
			printf("\nThe letter b was found\n");

}
		else{
			printf("\nNeither was found\n");
}	
	c = getchar();
}
}
int main(){
	//loop which calls methods
	//total up return usd values
	//printf("Hello World\n");
       //characterPrinter();
    currencyPrinter();
	//printEur();
	//currencyPrinter();
	return 0;
}
