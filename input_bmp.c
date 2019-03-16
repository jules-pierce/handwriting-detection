/******
Input the string of the filename to open.
This routine returns the frame_width, frame_height, and
a pointer to the raw rgb data as a one dimensional array.
Data is stored left-to-right, top-to-bottom in RGB order 

For RGB images, there are 3 bytes per pixel in the allocated array, 
for MONO images there is one byte per pixel in the allocated array.  
It is up to the calling program to free the
pointer to image_data, i.e., call free(image_data) when done
with the picture.

Returns -1 if an error is detected, 0 else
******/	 

#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/stat.h>

#include "bmp_io.h"

int input_bmp(const char *input_filename,
               int  *frame_width,
               int  *frame_height,
               byte **image_data,
							 ImageFormat img_format)
{
	struct stat my_stat;
	int scanline_width;
	int i, j, temp, bytes_per_pixel;
	byte *bmp_frame = NULL;
	byte r, g, b;
	FILE *fdes = NULL;
	int y;
	int num_read;
	byte *picdat = NULL;
	int32_t num_rows, num_cols, offset, bmp_image_size, bpp;
	int32_t bmihdr_size; // bitmapinfo header size
	int REVERSE_ORDER = 0;

	stat( input_filename, &my_stat );
	fdes = fopen(input_filename, "rb");
	if( fdes == NULL ){
		fprintf(stderr, "input_bmp: unable to open %s\n", input_filename);
		if( fdes != NULL ) fclose(fdes);
		if( bmp_frame != NULL ) free(bmp_frame);
		return(-1);
	}

	bmp_frame = (byte *)malloc(my_stat.st_size);
	if( bmp_frame == NULL ){
		fprintf(stderr, "input_bmp: unable to malloc (location 1)\n");
		if( fdes != NULL ) fclose(fdes);
		if( bmp_frame != NULL ) free(bmp_frame);
		return(-1);
	}

	num_read = fread(bmp_frame, 1, my_stat.st_size, fdes);
	if( num_read != my_stat.st_size ){
		fprintf(stderr, "input_bmp: unable to read enough data\n");
		if( fdes != NULL ) fclose(fdes);
		if( bmp_frame != NULL ) free(bmp_frame);
		return(-1);
	}
	else fclose( fdes );

	bmp_image_size = *(int32_t*)&bmp_frame[2];
	offset =         *(int32_t*)&bmp_frame[10];

	bmihdr_size =  *(int32_t*)&bmp_frame[14];
	num_cols =     *(int32_t*)&bmp_frame[18];
	num_rows =     *(int32_t*)&bmp_frame[22];
	bpp      =     *(int16_t*)&bmp_frame[28];
	bytes_per_pixel = bpp / 8;

	/*
	fprintf(stderr, "bmihdr_size = %d\n", bmihdr_size);
	fprintf(stderr, "offset = %d  num_cols = %d  num_rows = %d  bpp = %d\n",
	       offset, num_cols, num_rows, bpp);
	fprintf(stderr, "bytes_per_pixel = %d\n", bytes_per_pixel);
	*/

	// Convert rows to positive if it was negative
	if( num_rows < 0 ){
		num_rows = -num_rows;
		REVERSE_ORDER = 1;
	}
	
	// Allocate memory for the picture that will be returned to the calling
	// function
	if(img_format == MONO ){
	  picdat = (byte*)malloc(num_rows*num_cols);
	}	
	else{ 
	  picdat = (byte*)malloc(3*num_rows*num_cols);
	}	
	if(picdat == NULL){
		fprintf(stderr, "input_bmp: unable to malloc (location 2)\n");
		if( fdes != NULL ) fclose(fdes);
		if( bmp_frame != NULL ) free(bmp_frame);
		return(-1);
	}

	// Prepare to read in the data and then read it in
	// Take account of whether data is stored top to bottom or bottom to top
	// Take into account bmp "multiple of 4" requirements
	// Finally, convert the incoming RGB data to MONO if needed

	if( bytes_per_pixel == 3 ){
		if( (3 * num_cols) % 4 == 0 ){
			scanline_width = 3 * num_cols;
		}
		else{
			scanline_width = 3 * num_cols + (4 - (3 * num_cols) % 4);
		}
	}
	else if( bytes_per_pixel == 4 ){ 
		scanline_width = 4 * num_cols;
	}
	else{
		fprintf(stderr, "input_bmp: unsupported number of bytes per pixel\n");
		exit(1);
	}

	for(i = 0; i < num_rows; i++){
		if( REVERSE_ORDER ){
			temp = offset + i * scanline_width;
		}
		else{
			temp = offset + (num_rows - 1 - i) * scanline_width;
		}	
		for(j = 0; j < num_cols; j++){
			b = bmp_frame[temp + bytes_per_pixel*j];         /* B */
			g = bmp_frame[temp + bytes_per_pixel*j + 1];     /* G */
			r = bmp_frame[temp + bytes_per_pixel*j + 2];     /* R */
			if( img_format == MONO ){
				y = (int) floor(
				   0.299*(float)r + 0.587*(float)g + 0.114*(float)b + 0.5
					       );
				if( y > 255 ) y = 255;
				if( y < 0 ) y = 0;
				picdat[i*num_cols + j] = (byte)y;
			}
			else{
				picdat[i*num_cols*3 + 3*j] = r;       /* R */
				picdat[i*num_cols*3 + 3*j + 1] = g;   /* G */
				picdat[i*num_cols*3 + 3*j + 2] = b;   /* B */
			}
		}
	}

	*frame_width = num_cols;
	*frame_height = num_rows;
	*image_data = picdat;

  free( bmp_frame );
	return(0);
}
