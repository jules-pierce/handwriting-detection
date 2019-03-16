#ifndef __IMGSTUFF_H__
#define __IMGSTUFF_H__

int mi(int row, int col, int num_cols);
int ri(int row, int col, int num_cols);
int gi(int row, int col, int num_cols);
int bi(int row, int col, int num_cols);
unsigned int absdiff(unsigned char a, unsigned char b);
unsigned int squarederror(unsigned char a, unsigned char b);
unsigned char clip_double( double a );
							 
#endif								
