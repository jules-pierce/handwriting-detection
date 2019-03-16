
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>

#include "imgstuff.h"
#include "bmp_io.h"
//#define DEBUG

int main(int argc, char *argv[] )
{
    unsigned char word[4];
    unsigned char *picdat;
    FILE *fd_in;
    FILE *fd_out;
    int junk;
    int rows, cols;
    int i, j;
    int pic_num;
    
    if (argc != 4){
        fprintf (stderr, "error usage is: %s input_file output_file pic_num\n", argv[0]);
        exit (0);
    }

    fd_in = fopen (argv [1], "rb");
    fd_out = fopen (argv[2], "wb");
    pic_num = atoi (argv[3]);
    
    fread (word, sizeof (unsigned char), 4, fd_in);
    fprintf (stderr, "%2d %2d %2d %2d\n", word[0], word[1], word[2], word[3]);
    junk = (int)word[3] + (((int)word[2])<<8) + (((int)word[1])<<16) + (((int)word[0])<<24);
    fprintf (stderr, "magic number = %d\n", junk);
    
    fread (word, sizeof (unsigned char), 4, fd_in);
    junk = (int)word[3] + (((int)word[2])<<8) + (((int)word[1])<<16) + (((int)word[0])<<24);
    fprintf (stderr, "number of images = %d\n", junk);
    
    fread (word, sizeof (unsigned char), 4, fd_in);
    rows = (int)word[3] + (((int)word[2])<<8) + (((int)word[1])<<16) + (((int)word[0])<<24);
    fprintf (stderr, "rows = %d\n", rows);
    
    fread (word, sizeof (unsigned char), 4, fd_in);
    cols = (int)word[3] + (((int)word[2])<<8) + (((int)word[1])<<16) + (((int)word[0])<<24);
    fprintf (stderr, "cols = %d\n", cols);
    
    picdat = (unsigned char*) malloc (rows * cols * sizeof (unsigned char));
    
    for (i = 0; i <= pic_num; i++){
        fread (picdat, sizeof (unsigned char), rows * cols, fd_in);
    }
    output_bmp (argv[2], cols, rows, picdat, MONO);
    
    fclose (fd_in);
    fclose (fd_out);
    free (picdat);
}


