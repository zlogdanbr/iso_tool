# iso_tool
Wrapper over Oscar Sanderson ISO C Lib: https://oscarsanderson.com/iso-8583/

I have converted Oscar Sanderson ISO C Lib to be built at LINUX/UNIX using a makefile and wrote a C++ wrapper to work with it.
Still, very embrionary.

It is still only working under Linux, but you can try to build it with GCC ( MingGW ) and good luck trying to finding a version of this compiler that works well under Windows.
Oscar, has a Visual Studio project, however, and under Windows, it is maybe better to use it and add my code, if you wish.

When I stopped working with this, I was having trouble mixing ASCII data elements and binary data elements.

