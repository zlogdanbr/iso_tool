// -----------------------------------------------------
// http://www.cs.binghamton.edu/~steflik/cs455/rawip.txt
//------------------------------------------------------

#include "com.h"
#include <iostream>

Comm::Comm( const std::string& IPHost, const int& port )
{
    this->IPHost = IPHost;
    this->port = port;   
}

int Comm::send( const DL_UINT8* outmsg, DL_UINT16& no, DL_UINT8* inmsg , DL_UINT16& ni )
{
    int sockfd = 0, portno = 0;
       
    if ( outmsg == nullptr || inmsg == nullptr || no < 0 || ni < 0 )
    {
        std::cout << "ERROR Buffer error" << std::endl;
        return -1;
    }
	else
	{
		char tmp[ 4096 ];
		memset( tmp, 0x00, sizeof( tmp ) );
		
		iConvertBinArray2String( (char*)outmsg, no, tmp );
		std::cout << "Message sent with size: " << no << "\n";
		std::cout << "First char " <<tmp[0] << "\n";
		
		for(int i = 0; i < no ; i++ )
		{
			if ( tmp[i] = 0x00 )
			{
				std::cout << "*" ;
			}
			else
			{
				std::cout << tmp[i] ;
			}
		}
	}
    
    sockfd = socket( AF_INET, SOCK_STREAM, 0 );
    if (sockfd < 0)
    {
        std::cout << "ERROR opening socket" << std::endl;
        return -1;
    }
    
    server = gethostbyname(this->IPHost.c_str());
    if ( server == nullptr ) {
        std::cout << "ERROR, no such host" << std::endl;
        return -1;
    }   

    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy( (char *)server->h_addr,  (char *)&serv_addr.sin_addr.s_addr,server->h_length);
    serv_addr.sin_port = htons(this->port);  
    
    if (connect(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr)) < 0) 
    {
        std::cout << "ERROR connecting" << std::endl;
        return -1;
    }
    
    no = write(sockfd,(char*)outmsg, no );
    if ( no < 0) 
    {
         std::cout << "ERROR writing to socket" << std::endl;
         return -1;
    }
    
    char largebuffer[ 2*4096 ];
	std::cout << "Message sent, waiting response... " << std::endl;
    
    ni = read( sockfd, largebuffer, 2*4096 );
	
	std::cout << "Read: " << ni << " bytes." << std::endl;
    
    if ( ni < 0 ) 
    {
         std::cout << "ERROR reading from socket: " << ni << std::endl;
         return -1;
    }
    else
    {
        if ( ( largebuffer[0] + largebuffer[1] + largebuffer[2] + largebuffer[3]) == 0x00 )
        {
            std::cout << "ERROR Invalid output message."<< std::endl;
            std::cout << "ERROR Host did not understand format."<< std::endl;
            return 0;
        }
        else
        {
            std::cout << "Read " << ni << " bytes from socket."<< std::endl;
        }
    }
	
    memcpy(  inmsg, largebuffer, ni);
    
    return ni;

}
