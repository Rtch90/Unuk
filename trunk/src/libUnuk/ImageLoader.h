// ===================================================================
// This image loader will read in a 32-bit bitmap.
// ===================================================================

#ifndef _IMAGELOADER_H_
#define _IMAGELOADER_H_

typedef unsigned char	BYTE;
typedef int		LONG;
typedef unsigned int	DWORD;
typedef unsigned short	WORD;

// Provides general information about the file.
typedef struct __attribute__ ((__packed__)) tagBITMAPFILEHEADER {
  WORD	bfType;
  DWORD	bfSize;
  WORD	bfReserved1;
  WORD	bfReserved2;
  DWORD	bfOffBits;
} BITMAPFILEHEADER, *PBITMAPFILEHEADER;

// The information header provides information specific to the image data.
typedef struct __attribute__ ((__packed__)) tagBITMAPINFOHEADER {
  DWORD	biSize;
  LONG  biWidth;
  LONG 	biHeight;
  WORD	biPlanes;
  WORD	biBitCount;
  DWORD biCompression;
  DWORD biSizeImage;
  DWORD biXPelsPerMeter;
  DWORD biYPelsPerMeter;
  DWORD biCLRUsed;
  DWORD biCLRImportant;
} BITMAPINFOHEADER, *PBITAPINFOHEADER;

// Color palette.
typedef struct __attribute__ ((__packed__)) tagRGBQUAD {
  BYTE rbgBlue;
  BYTE rgbGreen;
  BYTE rgbRed;
  BYTE rgbReserved;
} RGBQUAD;

class ImageLoader {
public:
  ImageLoader(void);
  ImageLoader(const char *filename);

  virtual ~ImageLoader(void);
  
  bool LoadBMP(const char *filename);
  BYTE *GetAlpha(void) const;
  
  LONG 	   GetHeight(void)  	const { return height;    }
  RGBQUAD  *GetColors(void) 	const { return colors;    }
  bool     GetLoaded(void)  	const { return loaded;    }
  BYTE 	   *GetPixelData(void)  const { return pixelData; }
  LONG	   GetWidth(void)	const { return width;     }

private:
  BITMAPFILEHEADER  bmfh;
  BITMAPINFOHEADER  bmih;
  RGBQUAD	    *colors;
  BYTE		    *pixelData;
  bool		    loaded;
  LONG		    width;
  LONG		    height;
  WORD		    bpp;

  // Private methods.
  void Reset(void);
  bool FixPadding(BYTE const * const tempPixelData, DWORD size);
};

#endif
