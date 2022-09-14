#ifndef ISO_WRAPPER_CLASS
#define ISO_WRAPPER_CLASS

#include "isolibwrapper.h"
#include <map>
#include <string>
#include <memory>
#include "util.h"

typedef std::shared_ptr<DL_UINT8> sPtr;
typedef std::map<unsigned short,std::string> IsoMap;
typedef std::map<unsigned short, std::pair< sPtr, DL_UINT16> > IsoMapBin;

class ProcIsoMsg final {
public:
	explicit ProcIsoMsg(){};
	~ProcIsoMsg(){};

	// Inserts a string ANSI C null terminated to ISO field to the message
    bool insertDE( 	unsigned short DeNum, 
					const std::string& DeValue);
	
	// Inserts a binary field to ISO field to the message
	bool insertDEBin( 	unsigned short DeNum, 
						DL_UINT8* DeValue, 
						DL_UINT16 len );
						
	bool insertDEBin( 	unsigned short DeNum, 
						const std::string& DeValue);
							
						
	const IsoMap& getAsciiFields() const { return IsoContainer;};
	const IsoMapBin& getBinFields() const { return IsoContainerBin;};
	
	void clean()
	{
		EraseIsoContainer();
		EraseIsoContainerBin();
	};
		
private:

    void operator =(const ProcIsoMsg& ) = delete;
    ProcIsoMsg( const ProcIsoMsg& ) = delete;  
	
	// structures used to hold DEs
    IsoMap IsoContainer;
	IsoMapBin IsoContainerBin;
		
    void EraseIsoContainer(){ IsoContainer.erase( IsoContainer.begin(), IsoContainer.end() ); };    
	void EraseIsoContainerBin(){ IsoContainerBin.erase( IsoContainerBin.begin(), IsoContainerBin.end() ); };	

};

class IsoWrapper final {
public:

    explicit IsoWrapper(	DL_UINT8* _header, 
							DL_UINT16 _header_size);
							
    virtual ~IsoWrapper();
	
		// Prepares the message to be sent by copying to the output buffer
    bool copy_to_output(ProcIsoMsg& iso_maps);
	
	// Sends the message to the output
	bool send_to_host(	 std::string& ip, 
						 int port );
	
	// Copies the incoming message to the internal buffer
    bool copy_from_input();
	
	// Given a raw message prints the fields of this message
	bool parse_bin_msg( 	const DL_UINT8* msg_buffer_raw, 
							DL_UINT16 size );   
	
	void clean_header()
	{
		if ( header != nullptr )
			delete [] header;
		header_size = 0;
	};
	
private:
    void operator =(const IsoWrapper& ) = delete;
    IsoWrapper( const IsoWrapper& ) = delete;  
	
	// cleans the buffers
	void clean_buffer()
	{
		memset( msg_buffer, 0x00, sizeof( msg_buffer ) );
		msg_buffer_size = 0;
	};
	
	void convert_sizetochar( char* ssize, DL_UINT16 size);
	
	// sets the buffer with size s
	void set_buffer( DL_UINT8* tmp, DL_UINT16 s );
	
	// Adds a header to the output message
	bool create_msg( 	
						DL_UINT8* tmp_buffer, 
						DL_UINT16 packedSize );
	
	// accessors to tbe buffers
	DL_UINT8* get_buffer(){ return msg_buffer; };
	DL_UINT16& get_buffer_size(){ return msg_buffer_size;};
	
	DL_UINT8           msg_buffer[ 2*4056 ];
	DL_UINT16          msg_buffer_size = 0;   

	DL_UINT8* header;
	DL_UINT16 header_size;
	
	DL_ISO8583_HANDLER isoHandler;
	DL_ISO8583_MSG     isoMsg;
};





#endif
