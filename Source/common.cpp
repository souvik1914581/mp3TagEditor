#include "common.h"

void debugPrint(std::string &Msg)
{
	std::cout<<Msg<<std::endl;
}

void debugPrint1(std::string &Msg,int param)
{
	std::cout<<Msg<<" param = "<<param<<std::endl;
}

void fatalErrorPrint(std::string &Msg)
{
	std::cout<<"Fatal Error: "<<Msg<<std::endl;
	exit(EXIT_FAILURE);
}
