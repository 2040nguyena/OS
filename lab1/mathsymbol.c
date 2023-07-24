#include <stdio.h>
#include<ctype.h>
#include<math.h>

#define BUFSIZE 100

char buf[BUFSIZE];
int bufp=0;

char square_root[4]={0xE2,0x88,0x9A,0};             //UTF-8 representation of √
char cube_root[4]={0xE2,0x88,0x9B,0};               //UTF-8 representation of ∛


int getch(void) /* get a (possibly pushed back) character */
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

int main()
{
    char ch;
    int n=0;    //n will calculate the number from the numeric characters
    float power=0;  //either 1/2 or 1/3 based on symbol
    double result;  //pow(n,power)
    char *symbol;   //use for printing square or cube root
    
    while(1)
    {   ch=getch();
        if(ch==EOF)
            break;
        //skip whitespaces
        if(isspace(ch)){
            ch=getch();
        }
        //handle symbol
        if(ch==square_root[0])
        {
            ch=getch();
            if(ch==square_root[1])
                ch=getch();
                if(ch==square_root[2])
                    symbol = square_root;
                    power = 1/2.0;
                else{
                    symbol = cube_root
                    power = 1/3.0
                }
        }
    }

        //handle digits with getch() and ungetch()
        //n=?
        ch=getch();
        while(isdigit(ch)){
            n=(n*10)+(ch-'0');
            ch=getch();
        }
        ungetch(ch);
        result = pow(n,power);
    	printf("%s%d = %lf\n",symbol, n, result);
    	n=0;
    }
    getch();
    return 0;
}
