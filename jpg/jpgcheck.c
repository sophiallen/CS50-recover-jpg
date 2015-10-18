#include <stdio.h>

bool isjpg(BYTE block[4]) 
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
