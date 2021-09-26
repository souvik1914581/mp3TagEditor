#include <iostream>
#include <stdlib.h>

#include "common.h"
#include "mp3TagEditor.h"
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char** argv) {
	if(argc < 3)
	{
		std::cout<< "Insufficient args!"<<std::endl;
		exit(EXIT_FAILURE);
	}
	std::string userOption = std::string(*(argv + 1));
	std::string fileName = std::string(*(argv + 2));
	
	std::cout<<"Mode : "<<userOption <<"\nFileName:"<<fileName<<std::endl;
	mp3File m_mp3File(fileName);
	
	
	
	
	
	
	
	return 0;
}
