#include <cstdio>
#include <cstring>
#include <errno.h>
#include "ImageLoader.h"
#include "Debug.h"
#define BITMAP_TYPE 19778

// Initialize an empty image.
ImageLoader::ImageLoader(void) {
  Reset();
}

// Initializes an image with an image from the disk.
ImageLoader::ImageLoader(const char *filename) {
  Reset();
  LoadBMP(filename);
}

ImageLoader::~ImageLoader(void) {
  if(colors != NULL) {
    delete [] colors;
  }

  if(pixelData != NULL) {
    delete [] pixelData;
  }
}

bool ImageLoader::LoadBMP(const char* filename) {
  FILE *in	= NULL;
  bool result	= false;

  // Open the file for reading in binary mode.
  in = fopen(filename, "rb");
  if(in == NULL) {
    perror("Error");
    Debug::logger->message("\nError Number: %d", errno);
    return false;
  }

  fread(&bmfh, sizeof(BITMAPFILEHEADER), 1, in);

  // Check if this is even the right type of file.
  if(bmfh.bfType != BITMAP_TYPE) {
    perror("Error");
    Debug::logger->message("\nError Number: %d", errno);
    return false;
  }

  fread(&bmih, sizeof(BITMAPINFOHEADER), 1, in);
  width  = bmih.biWidth;
  height = bmih.biHeight;
  bpp    = bmih.biBitCount;

  // TODO: Get this running on 24-bit images too, right now it will seg fault if it is 24-bit.
  // Set the number of colors.
  LONG numColors = 1 << bmih.biBitCount;

  // The bitmap is not yet loaded.
  loaded = false;
  // Make sure memory is not lost.
  if(colors != NULL) {
    delete [] colors;
  }

  if(pixelData != NULL) {
    delete [] pixelData;
  }

  // Load the palette for 8 bits per pixel.
  if(bmih.biBitCount < 24) {
    colors = new RGBQUAD[numColors];
    fread(colors, sizeof(RGBQUAD), numColors, in);
  }

  DWORD size = bmfh.bfSize - bmfh.bfOffBits;

  BYTE *tempPixelData = NULL;
  tempPixelData = new BYTE[size];

  if(tempPixelData == NULL) {
    Debug::logger->message("\nError: Out of memory. Cannot find space to load image into memory.");
    fclose(in);
    return false;
  }
  
  fread(tempPixelData, sizeof(BYTE), size, in);

  result = FixPadding(tempPixelData, size);
  loaded = result;

  delete [] tempPixelData;
  fclose(in);

  return result;
}

bool ImageLoader::FixPadding(BYTE const * const tempPixelData, DWORD size) {
  // byteWidth is the width of the actual image in bytes. padWidth is
  // the width of the image plus the extrapadding.
  LONG byteWidth, padWidth;

  // Set both to the width of the image.
  byteWidth = padWidth = (LONG)((float)width * (float)bpp / 8.0);

  // Add any extra space to bring each line to a DWORD boundary.
  short padding = padWidth % 4 != 0;
  padWidth += padding;

  DWORD diff;
  int offset;
 
  height = bmih.biHeight;
  // Set the diff to the actual image size (without any padding).
  diff = height * byteWidth;
  // allocate memory for the image.
  pixelData = new BYTE[diff];
  
  if(pixelData == NULL) {
    return false;
  }

  // ===================================================================
  // Bitmap is inverted, so the paddind needs to be removed and the
  // image reversed. Here you can start from the back of the file or
  // the front, after the header. The only problem is that some programs
  // will pad not only the data, but also the file size to be divisiaible
  // by 4 bytes.
  // ===================================================================
  if(height > 0) {
    offset = padWidth - byteWidth;
    for(unsigned int i = 0; i < size - 2; i += 4) {
      if((i + 1) % padWidth == 0) {
        i += offset;
      }
      // Now we need to swap the data for it to have the right order.
      *(pixelData + i)		= *(tempPixelData + i + 2); // R
      *(pixelData + i + 1)	= *(tempPixelData + i + 1); // G
      *(pixelData + i + 2)	= *(tempPixelData + i);	    // B
      *(pixelData + i + 3)	= *(tempPixelData + i + 3); // A
    }
  } else {
    // The image is not reserved. Only the padding needs to be removed.
    height = height * -1;
    offset = 0;
    while(offset < height) {
      memcpy((pixelData + (offset * byteWidth)), (tempPixelData + (offset * padWidth)), byteWidth);
      offset++;
    }
  }
  return true;
}

void ImageLoader::Reset(void) {
  width     = 0;
  height    = 0;
  pixelData = NULL;
  colors    = NULL;
  loaded    = false;
}

// Get the alpha channel as an array of bytes.
// The size of the array will return -1 on failure.
BYTE *ImageLoader::GetAlpha() const {
  LONG arraySize = width * height;
  BYTE *array = new BYTE[arraySize];
  
  if(array == NULL) {
    delete [] array;
    return NULL;
  }

  for(long i = 0; i < arraySize; i++) {
    // Jump to the alpha and extract it everytime.
    array[i] = pixelData[i * 4 + 3];
  }
  return array;
}
