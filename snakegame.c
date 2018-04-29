#include<stdio.h>
#include<malloc.h>
#include<conio.h>
#define width 30
#define height 30
static int score=0;
static char c='d';
struct NODE
{
    int x;
    int y;
    char value;
    struct NODE *next;
};

struct FOOD
{
    int x;
    int y;
    char value;
};

typedef struct NODE node;
typedef struct FOOD food;

void createSnake(node **head,node **tail)
{
    node *n=(node*)malloc(sizeof(node));
    n->value='A';
    n->x=10;
    n->y=10;
    *head=n;

    node *n1=(node*)malloc(sizeof(node));
    n1->value='#';
    n1->x=10;
    n1->y=9;
    n->next=n1;

    node *n2=(node*)malloc(sizeof(node));
    n2->value='#';
    n2->x=10;
    n2->y=8;
    n1->next=n2;

    node *n3=(node*)malloc(sizeof(node));
    n3->value='#';
    n3->x=10;
    n3->y=7;
    n2->next=n3;

    node *n4=(node*)malloc(sizeof(node));
    n4->value='#';
    n4->x=10;
    n4->y=6;
    n3->next=n4;
    n4->next=NULL;
    *tail=n4;
}

void setMatrix(char a[height][width])
{
    int i,j;
    char star='*',space=' ';
    for(i=0;i<height;i++)
    {
        for(j=0;j<width;j++)
        {
            if(j==0 || j==width-1)
            {
                a[i][j]=star;
            }
            else if(i==0 || i==height-1)
            {
                a[i][j]=star;
            }
            else
            {
                a[i][j]=space;
            }
        }
    }
}

food generateFood(char a[height][width],node **head)
{
    food Food;
    Food.x=rand()%(width-2)+1;
	Food.y=rand()%(height-2)+1;
	Food.value='@';
    node *ptr;
    ptr=*head;
    while(ptr)
    {
        if(Food.x==ptr->x || Food.y==ptr->y)
        {
            Food.x=rand()%(width-2)+1;
            Food.y=rand()%(height-2)+1;
        }
        ptr=ptr->next;
    }
    return Food;
}

void moveValueToMatrix(char a[height][width],node **head,food Food)
{
    node *ptr;
    ptr=*head;
    while(ptr!=NULL)
    {
        a[ptr->x][ptr->y]=ptr->value;
       // printf("%c %d %d\n",ptr->value,ptr->x,ptr->y);
        ptr=ptr->next;
    }
    a[Food.x][Food.y]=Food.value;
    //printf("%c %d %d\n",Food.value,Food.x,Food.y);
}

void moveSnakeToScreen(char a[height][width])
{
    int i,j;
    //printf("\n\n\n");
    for(i=0;i<height;i++)
    {
        for(j=0;j<width;j++)
        {
            printf("%c",a[i][j]);
        }
        printf("\n");
    }
   printf("\n SCORE : %d\n\n",score);
}

void swapValue(node *ptr,int i,int j)
{
    if(ptr==NULL)
        return;
    int m,n;
    m=ptr->x;
    n=ptr->y;
    ptr->x=i;
    ptr->y=j;
    swapValue((ptr)->next,m,n);

}

void moveUp(node **head)
{
    node *ptr=*head;
    int m,n;
    m=ptr->x;
    n=ptr->y;
    ptr->x=ptr->x-1;
    if(ptr->x==0)
    {
        ptr->x=height-1;
    }
    swapValue((*head)->next,m,n);
}

void moveDown(node **head)
{
    int m,n;
    node *ptr=*head;
    m=ptr->x;
    n=ptr->y;
    ptr->x=ptr->x+1;
    if(ptr->x==height-1)
    {
        ptr->x=0;
    }
    swapValue((*head)->next,m,n);
}

void moveRight(node **head)
{
    int m,n;
    node *ptr=*head;
    m=ptr->x;
    n=ptr->y;
    ptr->y=ptr->y+1;
    if(ptr->y==width-1)
    {
        ptr->y=0;
    }
    swapValue((*head)->next,m,n);
}

void moveLeft(node **head)
{
    int m,n;
    node *ptr=*head;
    m=ptr->x;
    n=ptr->y;
    ptr->y=ptr->y-1;
    if(ptr->y==0)
    {
        ptr->y=width-1;
    }
    swapValue((*head)->next,m,n);
}

void moveSnakeDefault(char c,node **head)
{
    switch(c)
    {
            case 'a':
            //case 'A':
                if(c!='d' )
                {
                    moveLeft(head);
                }
                break;

            case 'd':
           // case 'D':
                if( c!='a')
                {
                    moveRight(head);
                 }
                break;

            case 'w':
           // case 'W':
                if( c!='z')
                {
                    moveUp(head);
                }
                break;

            case 'z':
           // case 'Z':
               if( c!='w')
                {
                    moveDown(head);
                }
                break;

    }
}

void increaseLength(node **tail)
{
    node *new=(node*)malloc(sizeof(node));
    new->value='#';
    new->next=NULL;
    (*tail)->next=new;
    new->x=(*tail)->x;
    new->y=(*tail)->y;
    *tail=new;

}

food eatFood(node **head,node **tail,food Food,char a[height][width])
{
    food food1;
    node *ptr;
    ptr=*head;
    if(Food.x==ptr->x && Food.y==ptr->y)
    {
        score+=10;
        food1=generateFood(a,head);
        increaseLength(tail);
        return food1;
    }
}

void checkStrike(node **head)
{
    node *ptr=(*head)->next;
    while(ptr)
    {
        if((*head)->x==ptr->x && (*head)->y==ptr->y)
        {
            system("cls");
            printf("GAMEOVER!!!");
            exit(0);
        }
        ptr=ptr->next;
    }
}

void storeMatrixToFile(node **head,food Food,int score,char c) //,int score)
{
    node *ptr=*head;
    FILE *fp;
    fp=fopen("snake_game_record.txt","w");
    fprintf(fp,"%c %d %d\n",Food.value,Food.x,Food.y);
    fprintf(fp,"%d\n",score);
    fprintf(fp,"%c\n",c);
    while(ptr)
    {
        fprintf(fp,"%c %d %d\n",ptr->value,ptr->x,ptr->y);
        ptr=ptr->next;
    }
    fclose(fp);
}

food getMatrixFromFile(char a[height][width],node **head,node **tail)
{
    food Food;
    char gap,val,iteration;
    int X,Y,count=0,s;
    FILE *fptr;
    node *list;
    fptr=fopen("snake_game_record.txt","r");
    fscanf(fptr,"%c %d %d",&val,&X,&Y);
    Food.value=val;
    Food.x=X;
    Food.y=Y;
    gap=getc(fptr);
    fscanf(fptr,"%d",&s);
    score=s;
    gap=fgetc(fptr);
    fscanf(fptr,"%c",&iteration);
    c=iteration;
    gap=fgetc(fptr);
    while(fscanf(fptr,"%c %d %d",&val,&X,&Y)!=EOF)
    {

        gap=getc(fptr);
        node *temp=(node*)malloc(sizeof(node));
        temp->x=X;
        temp->y=Y;
        temp->value=val;
        temp->next=NULL;
        if(count==0)
        {
            *head=temp;
            list=temp;
            count++;
        }
        else
        {
           list->next=temp;
           *tail=temp;
           list=temp;
        }
    }

    setMatrix(a);
	system("cls");
	moveValueToMatrix(a,head,Food);
	moveSnakeToScreen(a);
	return Food;
}

void pressKey(char a[height][width],node **head,node **tail,food Food)
{
    char ch;
    while(1)
    {
        switch(ch=getch())
        {
            case 'a':
                if(c!='d')
                {
                    moveLeft(head);
                    c=ch;
                }
                break;

            case 'd':
                if( c!='a')
                {
                    moveRight(head);
                    c=ch;
                }
                break;

            case 'w':
                if( c!='z')
                {
                    moveUp(head);
                    c=ch;
                }
                break;

            case 'z':
               if( c!='w')
                {
                    moveDown(head);
                    c=ch;
                }
                break;

            case 'x':
            case 'X':
                storeMatrixToFile(head,Food,score,c);
                printf("\n Your Game Has been SAVED");
                exit(0);
                break;

            default:
                moveSnakeDefault(c,head);
                break;
        }
        system("cls");
        setMatrix(a);
        Food=eatFood(head,tail,Food,a);
        moveValueToMatrix(a,head,Food);
        moveSnakeToScreen(a);
        checkStrike(head);
    }
}

int main()
{
    char choice;
    char a[height][width];
    node *head=NULL;
    node *tail=NULL;
    food Food,oFood;
    printf("\n Enter N if you want to start a New Game ");
    printf("\n Enter O if you want to start Old Game ");
    scanf("%c",&choice);
    switch(choice)
    {
        case 'N':
        case 'n':
            createSnake(&head,&tail);
            setMatrix(a);
            Food=generateFood(a,&head);
            moveValueToMatrix(a,&head,Food);
            moveSnakeToScreen(a);
            pressKey(a,&head,&tail,Food);
            break;
        case 'o':
        case 'O':
            oFood=getMatrixFromFile(a,&head,&tail);
			pressKey(a,&head,&tail,oFood);
            break;
        default:
            printf(" \n Invalid Value Inserted");
    }
    return 0;
}
