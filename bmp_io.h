#ifndef __BMP_IO_H__
#define __BMP_IO_H__

typedef unsigned char byte;
enum ImageFormat {RGB, MONO};

// Now some things for MS compatibility
// Following must be true or code won't work! WORD is 2 bytes,
// DWORD and LONG must be 4 bytes

typedef uint8_t BYTE;               // 1 byte 
typedef uint16_t WORD;     // 2 bytes
typedef uint32_t   DWORD;    // 4 bytes
typedef uint32_t   LONG;     // 4 bytes

int input_bmp(const char *input_filename,
               int  *frame_width,
               int  *frame_height,
               unsigned char **image_data,
							 ImageFormat img_format);
							 
int output_bmp(char* output_filename,
								int frame_width,
								int frame_height,
								unsigned char *m_frame_dat,
								ImageFormat img_format);
#endif								
