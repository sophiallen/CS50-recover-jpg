#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

//define byte (and its size)
typedef uint8_t  BYTE;


//define jpeg header
typedef struct
{
    BYTE  check1;
    BYTE  check2;
    BYTE  check3;
    BYTE  check4;
    
} __attribute__((__packed__))
JPGHEADER;


//prototype function to name file
void printName(int count, char filename[7]);



int main(void)
{
    //open the CF card
    FILE* inptr = fopen("card.raw", "r");
    if (inptr == NULL)
    {
        printf("could not open card file.");
        return 1; 
    }
    
    //identify what a jpeg header should look like (can get rid of this later?)
    JPGHEADER jpg1;
    jpg1.check1 = 0xff;
    jpg1.check2 = 0xd8;
    jpg1.check3 = 0xff;
    jpg1.check4 = 0xe0;
    

    //initialize file name string.
    char filename[7];
    int count = 0;
    
    //iterate through the file
    for (int i=0; i<1953125; i++)
    {

        //read a block, store to buffer
        BYTE buffer[512];
        fread(&buffer, sizeof(BYTE)*512, 1, inptr);
        
        //compare against jpeg header
        if (buffer[1] == jpg1.check1 && buffer[2] == jpg1.check2 && buffer[3] == jpg1.check3)
        {
            //create file name
            printName(count, filename);
            printf("filename\n");
        }
        
        else
        {
        }
    } 
    fclose(inptr);   
}

    

void printName(int count, char name[7])
{
    sprintf(name, "%03d.jpg", count);
}




