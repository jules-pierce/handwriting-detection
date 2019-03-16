/******
Put a bmp header on rgb or luma data.  Remember, each scanline is padded
to a 4 byte boundary, and scanlines are stored bottom to top, BGR order.
The input data to be output is stored in top-to-bottom RGB order...our 
preferred ordering.
*******/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <string.h>
#include <fcntl.h>
#include <stdint.h>
#include <sys/param.h>

#include "bmp_io.h"

#define BI_RGB 0

typedef struct{
	uint16_t bfType;
	int32_t  bfSize;
	uint16_t  bfReserved1;
	uint16_t  bfReserved2;
	int32_t bfOffBits;
} BITMAPFILEHEADER;	

typedef struct{
	uint32_t	biSize;
	int32_t	biWidth;
	int32_t	biHeight;
	uint16_t	biPlanes;
	uint16_t	biBitCount;
	uint32_t	biCompression;
	uint32_t	biSizeImage;
	int32_t	biXPelsPerMeter;
	int32_t	biYPelsPerMeter;
	uint32_t	biClrUsed;
	uint32_t	biClrImportant;
} BITMAPINFOHEADER;

int output_bmp(char* output_filename,
								int frame_width,
								int frame_height,
								byte *m_frame_dat,
								ImageFormat img_format)
{
	int scanlineWidth;
	int r, g, b;
	int i, j;
	FILE *fdes = NULL;
	byte *imageData = NULL;
	BITMAPFILEHEADER bmfh;
	BITMAPINFOHEADER bmih;
	
	// For BITMAPFILEHEADER
	byte bfType1, bfType2;
	uint16_t bfReserved1, bfReserved2;
	int32_t bfSize, bfOffBits;

	// For BITMAPINFOHEADER
	uint32_t biSize, biCompression, biSizeImage, biClrUsed, biClrImportant;
	uint16_t biPlanes, biBitCount;
	int32_t biWidth, biHeight, biXPelsPerMeter, biYPelsPerMeter;

	fdes = fopen(output_filename, "wb");
	if( fdes == NULL ){
		fprintf(stderr, "output_bmp: unable to open file %s\n", output_filename);
		return(-1);
	}

	// Align scanlines to 4 byte boundary
	if( (3 * frame_width) % 4 == 0 ){
		scanlineWidth = 3 * frame_width;
	}	else {
		scanlineWidth = 3 * frame_width + (4 - (3 * frame_width) % 4);
	}

	imageData = (byte *)malloc(scanlineWidth * sizeof(byte) );
	if( imageData == NULL ){
		fprintf(stderr, "output_bmp: unable to malloc\n");
		if( fdes != NULL ) fclose(fdes);
		return(-1);
	}

	/*** Write the BMP file header ***/
	bfType1 = 0x42;      // The character 'B' and 'M' in little endian
	bfType2 = 0x4D;      // The character 'B' and 'M' in little endian
	bfSize = 54 + frame_height * scanlineWidth;  // Total image size
	bfReserved1 = 0;   // Always 0
	bfReserved2 = 0;   // Always 0
	bfOffBits = 54;    // Bytes from start of header to pic data


	fwrite(&bfType1, sizeof(bfType1), 1, fdes);
	fwrite(&bfType2, sizeof(bfType2), 1, fdes);
	fwrite(&bfSize,  sizeof(bfSize), 1, fdes);
	fwrite(&bfReserved1, sizeof(bfReserved1), 1, fdes);
	fwrite(&bfReserved2, sizeof(bfReserved2), 1, fdes);
	fwrite(&bfOffBits, sizeof(bfOffBits), 1, fdes);
	
	biSize = 40;             // size of bmfh structure (always 40)
	biWidth = frame_width;   // cols in picture
	biHeight = frame_height; // rows in picture
	biPlanes = 1;            // always 1, ignore
	biBitCount = 24;         // bits per pixel
	biCompression = BI_RGB;  // compression type: "none"
	biSizeImage = 0;         // size of image data in bytes: 0 OK for BI_RGB

	         // these two normally set to zero and ignored
	biXPelsPerMeter = 0;     // desired display dimensions in x direction
	biYPelsPerMeter = 0;     // desired display dimensions in y direction
	biClrUsed = 0;           // number of colors in color table, 0 for
	                         // 24 bits per pixel
	biClrImportant = 0;      // application dependent, normally set to 0

	fwrite(&biSize, sizeof(biSize), 1, fdes);
	fwrite(&biWidth, sizeof(biWidth), 1, fdes);
	fwrite(&biHeight, sizeof(biHeight), 1, fdes);
	fwrite(&biPlanes, sizeof(biPlanes), 1, fdes);
	fwrite(&biBitCount, sizeof(biBitCount), 1, fdes);
	fwrite(&biCompression, sizeof(biCompression), 1, fdes);
	fwrite(&biSizeImage, sizeof(biSizeImage), 1, fdes);
	fwrite(&biXPelsPerMeter, sizeof(biXPelsPerMeter), 1, fdes);
	fwrite(&biYPelsPerMeter, sizeof(biYPelsPerMeter), 1, fdes);
	fwrite(&biClrUsed, sizeof(biClrUsed), 1, fdes);
	fwrite(&biClrImportant, sizeof(biClrImportant), 1, fdes);

	/******* Do the output *******/
	// Convert from our order to the BMP file order
	for(i = frame_height - 1; i >= 0; i--){
		for(j = 0; j < frame_width; j++){

			if( img_format == MONO ){
				r = g = b = m_frame_dat[i*frame_width + j];
			}
			else{
				r = m_frame_dat[i*3*frame_width + 3*j];
				g = m_frame_dat[i*3*frame_width + 3*j + 1];
				b = m_frame_dat[i*3*frame_width + 3*j + 2];
			}	

			imageData[3*j]     =  b ;
			imageData[3*j + 1] =  g ;
			imageData[3*j + 2] =  r ;
		}
		fwrite(imageData, scanlineWidth, 1, fdes);
	}

	free(imageData);
	fclose(fdes);
	return(0);
}
