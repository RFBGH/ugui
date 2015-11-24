#ifndef __COLOR_H__
#define __COLOR_H__

#include "Common.h"

#define RGBA UINT

#define FormatR(r) (r&0x000000FF)
#define FormatG(g) ((g<<8)&0x0000FF00)
#define FormatB(b) ((b<<16)&0x00FF0000)
#define FormatA(a) ((a<<24)&0xFF000000)

#define SetR(r, rgba) (FormatR(r)|(rgba&0xFFFFFF00))
//((r&0x000000FF)|(colr&0xFFFFFF00))
#define SetG(g, rgba) (FormatG(g)|(rgba&0xFFFF00FF))
//(((g<<8)&0x0000FF00) |(colr&0xFFFF00FF))
#define SetB(b, rgba) (FormatB(b)|(rgba&0xFF00FFFF))
//(((b<<16)&0x00FF0000)|(colr&0xFF00FFFF))
#define SetA(a, rgba) (FormatA(a)|(rgba&0x00FFFFFF))
//(((a<<24)&0xFF000000)|(colr&0x00FFFFFF))

#define GetR(rgba)  (rgba&0x000000FF)
#define GetG(rgba)  ((rgba>>8)&0x000000FF)
#define GetB(rgba)  ((rgba>>16)&0x000000FF)
#define GetA(rgba)  ((rgba>>24)&0x000000FF)

#define RGBA(r, g, b, a) ((FormatA(a)|FormatG(g)|FormatB(b)|FormatA(a))
//(((a<<24)&0xFF000000)|((b<<16)&0x00FF0000)|((g<<8)&0x0000FF00)|(r&0x000000FF))
#define RGB(r, g, b) RGBA(r, g, b, 0xFF)


#endif

