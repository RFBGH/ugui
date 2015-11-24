#ifndef __TYPE_H__
#define __TYPE_H__

#ifndef STATIC
#define STATIC static
#endif

#ifndef CONST
#define CONST const
#endif

#ifndef UINT 
#define UINT unsigned int
#endif

#ifndef INT
#define INT int
#endif

#ifndef UCHAR
#define UCHAR unsigned char
#endif

#ifndef CHAR
#define CHAR char
#endif

#ifndef USHORT
#define USHORT unsigned short
#endif

#ifndef SHORT
#define SHORT short
#endif

#ifndef PUINT
#define PUINT UINT*
#endif

#ifndef PINT
#define PINT INT*
#endif

#ifndef PUCHAR
#define PUCHAR UCHAR*
#endif

#ifndef PCHAR
#define PCHAR CHAR*
#endif

#ifndef VOID
#define VOID void
#endif

#ifndef PVOID
#define PVOID void*
#endif

#ifndef NULL
#define NULL (void*)0
#endif

#ifndef BOOL
#define BOOL INT
#endif

#ifndef TRUE
#define TRUE (1==1)
#endif

#ifndef FALSE
#define FALSE (1==0)
#endif

#ifndef WORD
#define WORD SHORT
#endif

#ifndef DWORD
#define DWORD UINT
#endif

#ifndef BYTE
#define BYTE UCHAR
#endif

#define HANDLE UINT

#define H2P(h) (VOID*)(h)
#define P2H(p) (UINT)(p)


#endif
