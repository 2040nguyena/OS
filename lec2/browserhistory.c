#include<stdio.h>
#include<stdlib.h>

struct Page
{
    char *url;
    struct Page *next;
};
typedef struct Page Page;

Page *AddPage(char *link,Page *start)
{
    Page *p;
    if(start==NULL)
    {
        start=(Page *)malloc(sizeof(Page));
        if(start==NULL)
        {
            printf("memory allocation error");
        }
        else
        {
            start->url=link;
            start->next=NULL;
            return start;
        }
        
    }
    else
    {
        p=(Page *)malloc(sizeof(Page));
        if(p==NULL)
        {
            printf("memory allocation error");
        }
        else
        {
            p->url=link;
            p->next=start;
            start=p;
            return start;          
        }

    }


}
PrintList(Page *start)
{
    while(start!=NULL)
    {
        printf("%s\n",start->url);
        start=start->next;
    }

}

int main()
{
    Page *start=NULL;
    start=AddPage("www.google.com",start);
    start=AddPage("www.stackoverflow.com",start);
    start=AddPage("www.youtube.com",start);

    PrintList(start);

}

