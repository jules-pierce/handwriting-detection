#!/usr/bin/env python
import os
import sys
import numpy as np
import struct as st
import math

#############################
# Main program starts here
#############################
#notes in picture on phone
#check for program that reads training pics

def output_bmp (filename, rows, cols, array):

    fd1 = open (filename, 'wb')
    
    if cols%4 == 0:
        scanlineWidth = cols * 3
    else:
        scanlineWidth = 3 * cols + (4 - (3*cols)%4)

    imageData = np.zeros (scanlineWidth, np.uint8)
    #bmp header
    bfType1 = np.zeros(1, np.uint8)
    bfType1 = 0x42 #The character 'B' and 'M' in little endian
    bfType2 = np.zeros(1, np.uint8)
    bfType2 = 0x4D #The character 'b' and 'm' in little endian
    bfSize = np.zeros(1, np.int32)
    bfSize = 54 + rows * scanlineWidth #total image size
    bfReserved1 = np.zeros(1, np.uint16)
    bfReserved1 = 0 #Always 0
    bfReserved2 = np.zeros(1, np.uint16)
    bfReserved2 = 0 #Always 0
    bfOffBits = np.zeros(1, np.int32)
    bfOffBits = 54 #Bytes from start of header to pic data
    
    fd1.write (st.pack ("B", bfType1))
    fd1.write (st.pack ("B", bfType2))
    fd1.write (st.pack ("i", bfSize))
    fd1.write (st.pack ("H", bfReserved1))
    fd1.write (st.pack ("H", bfReserved2))
    fd1.write (st.pack ("i", bfOffBits))
    
    biSize = np.zeros(1, np.uint32)
    biSize = 40 #size of bmfh structure, always 40
    biWidth = np.zeros(1, np.int32)
    biWidth = cols
    biHeight = np.zeros(1, np.int32)
    biHeight = rows
    biPlanes = np.zeros(1, np.uint16)
    biPlanes = 1 #Always 1, ignore
    biBitCount = np.zeros(1, np.uint16)
    biBitCount = 24 #bits per pixel
    biCompression = np.zeros(1, np.uint32)
    biCompression = 0 #compression type: "none"
    biSizeImage = np.zeros(1, np.uint32)
    biSizeImage = 0 #size of image data in bytes
    biXPelsPerMeter = np.zeros(1, np.int32)
    biXPelsPerMeter = 0 #desired siplay dimensions in x direction, usually 0
    biYPelsPerMeter = np.zeros(1, np.int32)
    biYPelsPerMeter = 0 #desired display dimensions in y direction, usually 0
    biClrUsed = np.zeros(1, np.uint32)
    biClrUsed = 0 #number of colors in color table, 0 for 24 bits/pixel
    biClrImportant = np.zeros(1, np.uint32)
    biClrImportant = 0 #application dependent, usually 0
    
    fd1.write (st.pack("I",biSize))
    fd1.write (st.pack("i",biWidth))
    fd1.write (st.pack("i",biHeight))
    fd1.write (st.pack("H",biPlanes))
    fd1.write (st.pack("H",biBitCount))
    fd1.write (st.pack("I",biCompression))
    fd1.write (st.pack("I",biSizeImage))
    fd1.write (st.pack("i",biXPelsPerMeter))
    fd1.write (st.pack("i",biYPelsPerMeter))
    fd1.write (st.pack("I",biClrUsed))
    fd1.write (st.pack("I",biClrImportant))
    
    #Output actual picture
    #convert from our order to BMP order
    for i in range (rows-1, -1, -1):
        for j in range (int(cols)):
            r = array [i * cols + j]
            g = array [i * cols + j]
            b = array [i * cols + j]

            imageData [3*j] = b
            imageData [3*j+1] = g
            imageData [3*j+2] = r
        fd1.write (imageData)
    
    #x = np.uint32(1)
    fd1.close()
#use output_bmp.c to output
#output y value for r, g, and b
#var definition of certain type: var = np.uint32(1)



if len(sys.argv) != 2:
    print "usage is: " + sys.argv[0] + " input.jpg"
    sys.exit(0)

#convert picture to bmp format
os.system ("sips -s format bmp " + sys.argv[1] + " --out mid.bmp")
os.system ("sips -Z 512 mid.bmp")

#open bmp and read in the header
fd = open ("mid.bmp", 'rb')
data = bytearray (fd.read(28))
reverse_order = 0

cols = data[18] + 256*data[19] + 256**2*data[20] + 256**3*data[21]
print "cols"
print cols

rows = data[22] + 256*data[23] + 256**2*data[24] + 256**3*data[25]
if rows > 2**16:
    reverse_order = 1
    rows = 2**32 - rows

print "rows"
print rows

offset = data[10] + 256*data[11] + 256**2*data[12] + 256**3*data[13]

#read and store the pixel values
pixels = np.zeros (rows * cols, np.uint8)

extra_bytes = (4-(3*cols)%4)%4

fd.read (offset - 28)

for i in range (rows):
    if reverse_order==1: temp = i * cols
    else : temp = (rows - 1 - i) * cols
    for j in range (cols):
        data = bytearray (fd.read(3))
        b = data[0]
        g = data [1]
        r = data [2]
        yf = 0.299*r + 0.587*g + 0.114*b
        y = int( round (yf))
        if y < 0: pixels[temp+j] = 0
        elif y > 255: pixels[temp + j] = 255
        else: pixels[temp+j] = y
    fd.read (extra_bytes)

histogram = np.zeros (256)
for i in range (rows):
    for j in range (cols):
        histogram [pixels [i*cols + j]] += 1

neighbors = 6 #number of neighbors used to average the histogram, if not an even number it rounds
for i in range (255):
    sum = 0
    n = 0
    for j in range (neighbors/2):
        if i > j:
            sum += histogram [i-j]
            n += 1
        if 255-i > j:
            sum += histogram [i+j]
            n += 1
    sum -= histogram [i]
    n -= 1
    sum /= n
    print sum
    histogram [i] = sum

for i in range (255):
    if histogram[i+1] < histogram [i]:
        peak = i
        break

thresh = 2 * peak

#output_bmp ("one.bmp", rows, cols, pixels)
#sys.exit()
#locate where the actual picture is
first_row = 10000
last_row = 0
first_col = 10000
last_col = 0
for i in range (rows):
    for j in range (cols):
        if pixels [i*cols + j] <= thresh:
            if i < first_row: first_row = i
            elif i > last_row: last_row = i
            if j < first_col: first_col = j
            elif j > last_col: last_col = j

print "first_row", first_row, "last_row", last_row
print "first_col", first_col, "last_col", last_col

"""
print "first_row"
print first_row
print "first_col"
print first_col
print "last_row"
print last_row
print "last_col"
print last_col
"""

if first_row >= 5: first_row = first_row - 5
if last_row <= rows - 5: last_row = last_row + 5
if first_col >= 5: first_col = first_col - 5
if last_col <= cols - 5: last_col = last_col + 5

row_range = last_row - first_row
col_range = last_col - first_col

if row_range > col_range:
    diff = row_range - col_range
    first_col = first_col - math.ceil(float(diff)/2)
    last_col = last_col + diff/2

elif col_range > row_range:
    diff = col_range - row_range
    first_row = first_row - math.ceil(float(diff)/2)
    last_row = last_row + diff/2

row_range = last_row - first_row
col_range = last_col - first_col

print "row_range", row_range, "col_range", col_range


if row_range != col_range:
    print "Error: rows not equal to cols"

if first_row < 0:
    first_row = 0
    print "Error: out of bounds in cropping first_row"

if first_col < 0:
    first_col = 0
    print "Error: out of bounds in cropping first_col"

if last_row > rows:
    last_row = rows
    print "Error: out of bounds in cropping last_row"

if last_col > cols:
    last_col = cols
    print "Error: out of bounds in cropping last_col"


#create new square picture, with just the picture we need
pixels_new = np.zeros (row_range * col_range, np.uint8)

for i in range (int(row_range)):
    for j in range (int(col_range)):
        pixels_new [i * col_range + j] = pixels [(first_row * cols) + (i * cols) + first_col + j]
print "row_range", row_range, "col_range", col_range

for i in range (int(row_range*col_range)):
    pixels_new[i] = 255 - pixels_new[i]

output_bmp ("out.bmp", int(row_range), col_range, pixels_new)

os.system ("sips -Z 28 out.bmp")

os.system ("./bmp2ts out.bmp outts")

fd.close()














