#include "common.h"
#include "mp3TagEditor.h"
	mp3File :: mp3File(std::string fileName)
	{
		std::string debugMsg;
		if(fileName.empty())
		{
			debugMsg = std::string("Invalid FileName!");
			fatalErrorPrint(debugMsg);
		}
		m_fileName = fileName;
	}
	void mp3File :: openFile()
	{
		
	}
	int mp3File :: parseMetaData()
	{
		return SUCCESS;
	}
	
	metaData* mp3File :: getMetaData()
	{
		return NULL;
	}
