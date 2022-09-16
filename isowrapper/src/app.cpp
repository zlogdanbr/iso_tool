#include "isowrapper.h"
#include "util.h"
#include <iostream>
#include <string>
#include "csv.h"

void from_csv()
{
    std::string ip = "";
	int port = 0;
	DL_UINT8 header[] = { 0x30,0x30,0x30,0x35 };
	
	csvprocessing csv("msg.txt");
	ProcIsoMsg fields_iso;
	csv.readCSV( fields_iso );
	
	IsoWrapper iso{ header, 4 };
	iso.copy_to_output(fields_iso);
	
	if ( iso.send_to_host( ip, port ) == false )
	{
		std::cout << "Error while sending message" << "\n";
	}
	
	iso.copy_from_input();	
}

void default_transaction()
{
    std::string ip = "";
	int port = 0;
	DL_UINT8 header[] = { 0x30,0x30,0x30,0x35 };
	
	ProcIsoMsg fields_iso;
    fields_iso.insertDE(0,"0200");
    fields_iso.insertDE(2,"234567890123456");
    fields_iso.insertDE(4,"699");
    fields_iso.insertDE(11,"234");
    fields_iso.insertDE(39,"4");
    fields_iso.insertDE(41,"12345");
    fields_iso.insertDE(42,"678901234");
	DL_UINT8 de55[] = { 0x33,0x32,0x33 };
	fields_iso.insertDEBin( 55, de55, 3 );
    fields_iso.insertDE(12,"BLAH BLAH");
	
	IsoWrapper iso{ header, 4 };
    iso.copy_to_output(fields_iso);
	
	if ( iso.send_to_host( ip, port ) == false )
	{
		std::cout << "Error while sending message" << "\n";
	}
	
	iso.copy_from_input();
}


int main( )
{
;
	return 0;
}
