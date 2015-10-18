/**
 * recover.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Recovers JPEGs from a forensic image.
 */

#include <stdio.h>
#include <cs50.h>
#include <stdlib.h>
#include <stdint.h>

//define byte size
typedef uint8_t  BYTE;

//define jpeg header
typedef struct
{
    BYTE  jpgcheck1;
    BYTE  jpgcheck2;
    BYTE  jpgcheck3;
    BYTE  jpgcheck4;
} __attribute__((__packed__))
JPGHEADER;

int main(void)
{
    //open the CF card
    FILE* card = fopen("card.raw", "r");
    if (card == NULL)
    {
        printf("could not open card file.");
        return 1; 
    }
    //identify what a jpeg header should look like (can get rid of this later?)
    JPGHEADER jpeg;
    jpeg.jpgcheck1 = 0xff;
    jpeg.jpgcheck2 = 0xd8;
    jpeg.jpgcheck3 = 0xff;
    jpeg.jpgcheck4 = 0xe0;
    
    int count = 1;
    
    //iterate through the file.
    for (int i=0; i<1953125; i++)
    {   
        
        
         //read the first four bytes
        JPGHEADER header;
        fread(&header, sizeof(JPGHEADER), 1, card);
        
        //if it's the start of a jpeg
        if (header.jpgcheck1 == jpeg.jpgcheck1 && header.jpgcheck2 == jpeg.jpgcheck2)
        {
            printf("match # %d, i= %d, seek_cur %ld\n", count, i, ftell(card));
            count ++;
            fseek(card, 508*sizeof(BYTE), SEEK_CUR);
        }
        
        //if it's not a jpeg, go to next block.
        else
        {
            fseek(card, 508*sizeof(BYTE), SEEK_CUR);
        }
        
    }
    
    //close the CF card
    fclose(card);   
}



