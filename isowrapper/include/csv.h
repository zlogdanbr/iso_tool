#ifndef _CSV_ISO_PROC
#define _CSV_ISO_PROC

#include "isowrapper.h"
#include <fstream>
#include <iostream>

class csvprocessing {

public:	
	csvprocessing(const std::string& _filename );
	~csvprocessing();
	int readCSV( ProcIsoMsg& iso );
	
private:
	std::string filename;
};

#endif