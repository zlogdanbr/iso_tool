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

void RBC_S_LATAM_157()
{
    std::string ip = "10.99.168.162";
	int port = 9813;
	DL_UINT8 header[] = { 0x30,0x30,0x30,0x35 };
	
	ProcIsoMsg fields_iso;
    fields_iso.insertDE(0,"0200");
    fields_iso.insertDE(2,"5898980136578785");
	fields_iso.insertDE(3,"12000");	
    fields_iso.insertDE(4,"10000");
	fields_iso.insertDE(7,"511231444");
    fields_iso.insertDE(11,"580805");
	fields_iso.insertDE(12,"191444");
	fields_iso.insertDE(13,"511");	
	fields_iso.insertDE(15,"512");
    fields_iso.insertDE(18,"6011");
	fields_iso.insertDE(22,"901");
	fields_iso.insertDE(25,"2");
	fields_iso.insertDE(32,"6601090");
	fields_iso.insertDE(35,"375898980136578785=31121200470800000101");
	fields_iso.insertDE(37,"013200580805");
	fields_iso.insertDE(41,"8732ATM ");
	fields_iso.insertDE(42,"900000000000000");
	fields_iso.insertDE(43,"RBL TRINCITY MALL #1   TRINCITY      TTT");
	fields_iso.insertDE(49,"780");
	fields_iso.insertDE(52,"F06A3B30652F1E92");
	fields_iso.insertDE(53,"2");

	
	IsoWrapper iso{ header, 4 };
    iso.copy_to_output(fields_iso);
	
	// if ( iso.send_to_host( ip, port ) == false )
	// {
		// std::cout << "Error while sending message" << "\n";
	// }
	
	// iso.copy_from_input();
}

int main( )
{
	//RBC_S_LATAM_157();
	from_csv();
	return 0;
}
