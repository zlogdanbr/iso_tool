#ifndef _UTIL_FUNCS
#define _UTIL_FUNCS

#include "isolibwrapper.h"
#include <cstring>
#include <string>
#include <iostream>
#include <cstdio>
#include <cstdlib>

inline
unsigned char* szConvertStringToData( 	const char* stringbuffer, 
										unsigned char* hexbuffer, 
										int size )
{
	int i = 0;
	for( i = 0 ; i < size/2 ; i++  )
	{
		char buf[3];
		memset(buf,0,3);
		memcpy(buf,&stringbuffer[2*i],2);
		buf[2] = 0;
		hexbuffer[ i ] = strtol( buf, nullptr, 16 );
	}
	return hexbuffer;
}


/************************************************************************************
*unsigned char* sConvertHexBin2String(unsigned char ch, unsigned char* buffer)
* description: Originally the data is binary, thus to print it in a file we must convert
*			   it to an ASCII representation of this array of bytes. This convertion is not literal,
*			   because each nibble of the bin values is converted to an ASCII byte. The output is
*			   twice as big as the input. This method actually converts each nibble of a byte to
*			   its ascii representation.
* INPUT:		A char
* OUTPUT:	 	2 byte ASCII array representation
* RETURNS:	    Pointer of the first byte of this array ( includes NULL terminator )
*************************************************************************************/
inline
unsigned char* sConvertHexBin2String(	unsigned char ch, 
										unsigned char* buffer)
{
  char tmp[3];
  memset(tmp,0,3);
  if ( (ch&0x0F) == 0 )
  {
	if ( ch == 0x00 )
	{
		tmp[0] = 0x30;
		tmp[1] = 0x30;
		tmp[2] = 0x00;
	}
	else
	{
		snprintf(tmp, 3, "%x",ch);
		if ( tmp[1] == 0 )
			tmp[1] = 0x30;
	}
  }
  else
  if ( ((ch&0xF0)<<4) == 0 )
  {
	char cfix = 0x00;
	snprintf(tmp,3,"%x",ch);
	cfix = tmp[0];
	tmp[0] = 0x30;
	tmp[1] = cfix;
  }
  else
		snprintf(tmp,3,"%x",ch);
  memcpy(buffer,tmp,3);	
  return buffer;  
}

/************************************************************************************
* int iConvertBinArray2String( char* bBindata, 
*												 int iDataSize,
*												 char* szDataString )
* description: Originally the data is binary, thus to print it in a file we must convert
*			   it to an ASCII representation of this array of bytes. This convertion is not literal,
*			   because each nibble of the bin values is converted to an ASCII byte. The output is
*			   twice as big as the input
* INPUT:		Original data buffer and its size
* OUTPUT:	 	New buffer	
* RETURNS:	    returns 0 OK else 1
*************************************************************************************/
inline
int iConvertBinArray2String(	char* bBindata, 
								int iDataSize,
								char* szDataString ) 
{	

	if (( bBindata == nullptr )||(szDataString) == nullptr )
		return 1;

	for(int i = 0; i < iDataSize ; i++)
	{
		char tmp[3];
		memset(tmp,0,3);
		sConvertHexBin2String((unsigned char)bBindata[i],(unsigned char*)tmp);
		memcpy((szDataString+2*i),tmp,2);
	}

	return 0;
}

#endif