    
    // iterate over infile's scanlines
    for (int row = 0, biHeight = abs(bi.biHeight); row < biHeight; row++)
    {
        // iterate over pixels in scanline
        for (int pixel = 0; pixel < bi.biWidth; pixel++)
        {
            // temporary storage
            RGBTRIPLE triple;

            // read RGB triple from infile
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
            
            for (int pduplicates = 0; pduplicates < n; pduplicates++)
            {
            // write RGB triple to outfile
            fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
            }
        }

        // skip over padding, if any
        fseek(inptr, padding, SEEK_CUR);

        // then add it back (to demonstrate how)
        for (int k = 0; k < padding; k++)
        {
            fputc(0x00, outptr);
        }
