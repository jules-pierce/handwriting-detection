#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <unistd.h>

int mi(int row, int col, int num_cols){
	return( row*num_cols + col );
}

int ri(int row, int col, int num_cols){
	return( row*3*num_cols + 3*col );
}

int gi(int row, int col, int num_cols){
	return( row*3*num_cols + 3*col + 1 );
}

int bi(int row, int col, int num_cols){
	return( row*3*num_cols + 3*col + 2 );
}

unsigned int absdiff( unsigned char a, unsigned char b ){
	if( a < b ) return b-a; else return a-b;
}

unsigned int squarederror( unsigned char a, unsigned char b ){
	return ((int)a - (int)b) * ((int)a - (int)b);
}

unsigned char clip_double( double a ){
	double b;
	unsigned char retval;

	b = floor( a + 0.5 );

	if( b >= 255 ) retval = 255;
	else if( b <= 0 ) retval = 0;
	else retval = (unsigned char) b;

	return retval;
}
