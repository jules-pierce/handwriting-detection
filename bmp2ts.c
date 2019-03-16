#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

#include "imgstuff.h"
#include "bmp_io.h"

int main(int argc, const char * argv[]) {
    int cols, rows;
    unsigned char *picdat;
    FILE *outdes = NULL;
    int mag_num;
    int num_items;
    unsigned char word[4];
    int temp;

	if( argc != 3 ){
		printf("usage is: %s pic.bmp out_file\n", argv[0] );
		exit(1);
	}	

    input_bmp (argv[1], &cols, &rows, &picdat, MONO);
    //getting an error that this has no matching function call?
    outdes = fopen(argv[2], "wb");
    
    word [0] = 0x00;
    word [1] = 0x00;
    word [2] = 0x08;
    word [3] = 0x03;
    fwrite (word, sizeof (unsigned char), 4, outdes);
    
    num_items = 1;
    word [0] = 0x00;
    word [1] = 0x00;
    word [2] = 0x00;
    word [3] = 0x01;
    fwrite (word, sizeof (unsigned char), 4, outdes);
    
    if (rows != 28 || cols != 28){
        fprintf (stderr, "error: wrong size image, must be 28 x 28\n");
        exit (0);
    }
    
    //define word for rows
    word [0] = 0x00;
    word [1] = 0x00;
    word [2] = 0x00;
    word [3] = 0x1C;
    fwrite (word, sizeof (unsigned char), 4, outdes);
    
    //define word for cols
    fwrite (word, sizeof (unsigned char), 4, outdes);
    
    fwrite (picdat, sizeof (unsigned char), rows * cols, outdes);
    
    free (picdat);
    fclose (outdes);
}
