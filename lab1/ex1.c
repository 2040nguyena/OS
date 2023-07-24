#include <stdio.h>
#include<ctype.h>
#include<math.h>


#define BUFSIZE 100



char buf[BUFSIZE];
int bufp=0;

char square_root[4]={0xE2,0x88,0x9A,0};             //UTF-8 representation of square root
char cube_root[4]={0xE2,0x88,0x9B,0};               //UTF-8 representation of cube root


int getch(void)                                     /* get a (possibly pushed back) character */
{
    return bufp > 0? buf[--bufp]: getchar();
    //if bufp > 0 then return buf[bufp]; bufp -1;
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
    int n=0;
    float power=0;
    double result;
    char *symbol;

    printf("%s\n", square_root);
    while(1)
    {   ch=getch();
        if(ch==EOF)
            break;
        while(isspace(ch))
            ch=getch();

        if(ch==square_root[0])
        {
            ch=getch();
            if(ch==square_root[1])
            {
                ch=getch();
                if(ch==square_root[2])
                {   symbol=square_root;
                    power=1/2.0;
                }

                else if(ch==cube_root[2])
                {   symbol=cube_root;
                    power=1/3.0;
                }
            }
        }
        ch=getch();
        while (isdigit(ch))
    	{
    		n = (n * 10) + (ch - '0');
    		ch = getch();
    	}
    	ungetch(ch);

        result = pow(n,power);
    	printf("%s%d = %lf\n",symbol, n, result);
    	n=0;
    }

    return 0;
}
