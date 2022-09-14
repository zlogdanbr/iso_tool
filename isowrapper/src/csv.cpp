#include "csv.h"

csvprocessing::csvprocessing(const std::string& _filename )
{
	this->filename = _filename;
}

csvprocessing::~csvprocessing()
{
}

int csvprocessing::readCSV( ProcIsoMsg& iso )
{
	std::ifstream myFile;
	myFile.open(filename, std::ios_base::in);

	if (myFile.is_open())
	{
        std::cout << "File " << filename << " is open" << std::endl;
		while (myFile.good())
		{
			std::string Line;            
			getline(myFile, Line);

			if (Line.length() == 0)
			{
				break;
			}

			int pos = 0;
            
            if ( Line[0] == 'b' )
            {
                pos = Line.find(',', 1 );
                int field = std::stoi( Line.substr( 1, pos) );
                std::string value = Line.substr( pos+1, Line.size()-1);   
                iso.insertDEBin( field, value );                
            }
            else if ( Line[0] == '#' )
            {
                continue;
            }
            else
            {
                pos = Line.find(',', 0);
                int field = std::stoi( Line.substr( 0, pos) );
                std::string value = Line.substr( pos+1, Line.size()-1);
                iso.insertDE( field, value );
            }
		}
        std::cout << "File " << filename << " is being closed" << std::endl;
		myFile.close();
	}
	else
	{
        std::cout << "File " << filename << " does not exist" << std::endl;
		return -1;
	}

	return 0;
}
