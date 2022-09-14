#include "isowrapper.h"
#include "com.h"
#include <cstring>
#include <string>
#include <iostream>
#include <cstdio>
#include <cstdlib>


bool ProcIsoMsg::insertDE(  unsigned short DeNum, const std::string& DeValue)
{   
	std::cout 	<< "Adding ASCII field: " 
				<< DeNum 
				<< " with contents: " 
				<< DeValue 
				<< " size: " 
				<< DeValue.size()
				<< "\n" ;
	
	IsoContainer.insert( std::pair< DL_UINT16, std::string >( (DL_UINT16)DeNum, DeValue ) );
	return true;
}

bool ProcIsoMsg::insertDEBin( unsigned short DeNum, DL_UINT8* DeValue, DL_UINT16 len )
{
	std::cout << "Adding BIN field: " << DeNum << "\n" ;
	sPtr tmp(new DL_UINT8(len));
	memcpy( tmp.get(), DeValue, len );
	std::pair< sPtr, DL_UINT16> t = std::make_pair( tmp, len );
	IsoContainerBin.insert( std::pair< DL_UINT16, std::pair< sPtr, DL_UINT16> >( DeNum, t ));
	return true ;
}

bool ProcIsoMsg::insertDEBin( unsigned short DeNum, const std::string& DeValue)
{
	int new_size = DeValue.length();
	DL_UINT8 tmp[1028];
	memset( tmp, 0x00, 1028 );
	szConvertStringToData( DeValue.c_str(), tmp, new_size );	
	insertDEBin( DeNum, tmp, new_size );
	return true;
}

IsoWrapper::IsoWrapper( DL_UINT8* _header , DL_UINT16 _header_size )
{   
	header_size = _header_size;
	std::cout << "Creating IsoWrapper instance" << "\n" ;
	
	if ( header_size > 0 )
	{
		header = new DL_UINT8[ header_size ];
		memcpy( header, _header, header_size );
	}
	clean_buffer();
    DL_ISO8583_DEFS_1993_GetHandler(&isoHandler);     
}

IsoWrapper::~IsoWrapper()
{  
	std::cout << "Removing IsoWrapper instance" << "\n" ;		
	if ( header != nullptr )
		delete [] header;
}

void IsoWrapper::convert_sizetochar( char* ssize, DL_UINT16 size)
{
	char tmp[ 5 ];
	memset( tmp, 0x00, sizeof( tmp ) );
	snprintf( tmp, 5, "%lu", size );
	memcpy( ssize, tmp, 4 );
}

bool IsoWrapper::create_msg(  DL_UINT8* tmp_buffer, DL_UINT16 packedSize )
{

	std::cout << "Header size: " << header_size << "\n";
	if ( header_size > 0 )
	{
		DL_UINT8   tmp_buffer2[ 2*4056 ];
			
		if ( header_size + packedSize <= 2*4056 )
		{
			memcpy( tmp_buffer2, tmp_buffer, packedSize );
			memset( tmp_buffer, 0x00, sizeof( tmp_buffer ) );
			memcpy( tmp_buffer, header, header_size );
			memcpy( tmp_buffer+header_size, tmp_buffer2, packedSize );
			packedSize = packedSize + header_size;
			std::cout << "Message size: " << packedSize << "\n";
			return true;
		}
	}
	else if ( header_size == 0 )
	{
		if ( packedSize <= 2*4056 )
		{
			set_buffer( tmp_buffer, packedSize );
			std::cout << "Message size: " << packedSize << "\n";
			return true;
		}
	}
	return false;
}


// sets the buffer with size s
void IsoWrapper::set_buffer( DL_UINT8* tmp, DL_UINT16 s )
{
	clean_buffer();
	memcpy( msg_buffer, tmp, s );
	msg_buffer_size = s;
}

bool IsoWrapper::copy_to_output(ProcIsoMsg& iso_maps)
{

	DL_UINT8   tmp_buffer[ 2*4056 ];
	DL_UINT16 packedSize;
	memset( tmp_buffer, 0x00, sizeof( tmp_buffer ));
	
	char strtmp[ 516 ];

	DL_ISO8583_MSG_Init(NULL,0,&isoMsg);
	
	const IsoMap& IsoContainer = iso_maps.getAsciiFields();
	const IsoMapBin& IsoContainerBin = iso_maps.getBinFields();

	if ( IsoContainer.empty() == false )
	{
		for( 	auto IsoContainerIterator = IsoContainer.begin(); 
				IsoContainerIterator != IsoContainer.end(); 
				IsoContainerIterator++)
		{   
		 
			 memset( strtmp, 0x00, sizeof( strtmp ));
			 strncpy( strtmp, IsoContainerIterator->second.c_str(), IsoContainerIterator->second.length() );
			 DL_ISO8583_MSG_SetField_Str(   IsoContainerIterator->first, 
											(const unsigned char *)strtmp,
											&isoMsg ); 
		}
	}
	
	if ( IsoContainerBin.empty() == false )
	{

		for( 	auto IsoContainerIterator = IsoContainerBin.begin(); 
				IsoContainerIterator != IsoContainerBin.end(); 
				IsoContainerIterator++)
		{   
			
			 std::cout << IsoContainerIterator->first << "\n";
			 std::cout << IsoContainerIterator->second.first.get() << "\n";
			 std::cout << IsoContainerIterator->second.second << "\n";
			 DL_ISO8583_MSG_SetField_Bin(   IsoContainerIterator->first, 
											IsoContainerIterator->second.first.get(),
											IsoContainerIterator->second.second,
											&isoMsg ); 
		}	
	
	}

	std::cout << "Packing message..." << "\n" ;
	
	if ( DL_ISO8583_MSG_Pack(&isoHandler,&isoMsg,tmp_buffer,&packedSize) < 0 )     
		return false;   
	
	std:: cout << "Creating message..." << "\n";
	
	create_msg( tmp_buffer, packedSize );		
	DL_ISO8583_MSG_Dump(stdout,NULL,&isoHandler,&isoMsg);  
	  
	iso_maps.clean();
	
	DL_ISO8583_MSG_Free(&isoMsg);
	
	return true;
}

bool IsoWrapper::send_to_host( std::string& ip, int port )
{
	DL_UINT8   tmp_buffer[ 2*4056 ];
	DL_UINT16  packedSize = 0;
	memset( tmp_buffer, 0x00, sizeof( tmp_buffer ));
	
	Comm c{ip,port};
	if ( c.send( get_buffer(), get_buffer_size(), tmp_buffer, packedSize ) >= 0 )
	{
		set_buffer( tmp_buffer, packedSize );
	}
	else
	{
		return false;
	}
	return true;
}
 
bool IsoWrapper::copy_from_input( )
{
 	
     DL_ISO8583_MSG_Init(NULL,0,&isoMsg);
	 
	 if ( DL_ISO8583_MSG_Unpack(&isoHandler,msg_buffer,msg_buffer_size,&isoMsg) < 0 )
        return false;
     
	 if ( msg_buffer_size > 2*4056 )
		 return false;
	 
	 try
	 {	 
		DL_OUTPUT_Hex(stdout,NULL,msg_buffer,msg_buffer_size);  
	 } catch( ... )
	 {
		 std::cout << "Error trying to print message" << "\n";
     }
        
     if ( msg_buffer == NULL || msg_buffer_size <= 0 )
     {
         DL_ISO8583_MSG_Free(&isoMsg);
         return false;
     }
     
     DL_ISO8583_MSG_Free(&isoMsg);
     return true;        
}

bool IsoWrapper::parse_bin_msg( const DL_UINT8* msg_buffer_raw, DL_UINT16 size )
{

	 DL_ISO8583_MSG_Init(NULL,0,&isoMsg);
	 
	 if ( DL_ISO8583_MSG_Unpack(&isoHandler,msg_buffer_raw,size,&isoMsg) < 0 )
        return false;
	
	 DL_ISO8583_MSG_Dump(stdout,NULL,&isoHandler,&isoMsg);  
     
     DL_ISO8583_MSG_Free(&isoMsg);
     return true;      
}	





