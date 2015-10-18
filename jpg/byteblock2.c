#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

//define byte (and its size)
typedef uint8_t  BYTE;

bool isjpg(BYTE block[512]); 

int main(void)
{
    //open card, check for null. 
    FILE* card = fopen("card.raw", "r");
    if (card == NULL)
    {
        printf("could not open card file.");
        return 1; 
    }
    
    //define block
    BYTE block[512];
    int count = 1;
    
    for (int i=0; i < 1953125; i++)
    {
        char filename[7];
        
        fread(&block, sizeof(BYTE), 512, card);
        
        if (isjpg(block))
        {
            sprintf(filename, "%03d.jpg", count);
            printf("%s\n", filename);
            count++;
            
            FILE* newimage = fopen(filename, "w");
            if (newimage == NULL)
            {
                printf("could not create file\n");
                return 2;
            }
            
            fwrite(&block, sizeof(BYTE), 512, newimage);
            
            fread(&block, sizeof(BYTE), 512, card);
            
            while (!isjpg(block))
            {
                fwrite(&block, sizeof(BYTE), 512, newimage);
                
                fread(&block, sizeof(BYTE), 512, card);
                
                if (isjpg(block))
                {
                    fseek(card, sizeof(BYTE)*-512, SEEK_CUR);
                }
            }

                fclose(newimage);

        }

    }
    fclose(card);
}

bool isjpg(BYTE block[512]) 
{
    BYTE jpgheader1 = 0xff;
    BYTE jpgheader2 = 0xd8;
    BYTE jpgheader3 = 0xff;
    BYTE jpgheader4a = 0xe0;
    BYTE jpgheader4b = 0xe1;
    
    return (block[0] == jpgheader1 
            && block[1] == jpgheader2 
            && block[2] == jpgheader3 
            && (block[3] == jpgheader4a || block[3] == jpgheader4b));
}




