#include <stdio.h>
#include <cs50.h>


void printName(int count, char name[4]);

int main(void)
{
    char name[7];
    
    for (int i=1; i<17; i++)
    {
    printName(i, name);
    printf("%s\n", name);
    }
}
    
void printName(int count, char name[7])
{
    sprintf(name, "%03d.jpg", count);
}


