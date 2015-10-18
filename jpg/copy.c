
//until the next byte is either 0x00 or jpegcheck1

BYTE byte;
fread(&byte, sizeof(BYTE), 1, card);

while (byte != 0x00 || byte 
if (byte == 0x00 || byte == jpeg.jpegcheck1)
{
    fclose(outptr);
    break;
}
else
{
fwrite(&tbyte, sizeof(BYTE), 1, outptr);
}


