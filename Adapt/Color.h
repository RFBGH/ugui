#ifndef __COLOR_H__
#define __COLOR_H__

#include "Type.h"

#define RGBA UINT

#define FormatR(r) ((r<<16)&0x00FF0000)
#define FormatG(g) ((g<<8)&0x0000FF00)
#define FormatB(b) (b&0x000000FF)
#define FormatA(a) ((a<<24)&0xFF000000)

#define SetR(r, rgba) (FormatR(r)|(rgba&0xFF00FFFF))
#define SetG(g, rgba) (FormatG(g)|(rgba&0xFFFF00FF))
#define SetB(b, rgba) (FormatB(b)|(rgba&0xFFFFFF00))
#define SetA(a, rgba) (FormatA(a)|(rgba&0x00FFFFFF))

#define GetR(rgba)  ((rgba>>16)&0x000000FF)
#define GetG(rgba)  ((rgba>>8)&0x000000FF)
#define GetB(rgba)  (rgba&0x000000FF)
#define GetA(rgba)  ((rgba>>24)&0x000000FF)

#define RGBA_Get(r, g, b, a) (FormatR(r)|FormatG(g)|FormatB(b)|FormatA(a))
#define RGB(r, g, b) RGBA_Get(r, g, b, 0xFF)

#define RGBA_RED    0xFFFF0000
#define RGBA_GREEN  0xFF00FF00
#define RGBA_BLUE   0xFF0000FF
#define RGBA_BLACK  0xFF000000
#define RGBA_WHITE  0xFFFFFFFF

#define MAX_COLOR_FILTER 255
RGBA FilterColor(RGBA start, RGBA end, INT iFilter);

#endif

