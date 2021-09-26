#include "common.h"
#include "mp3TagEditor.h"
	mp3File :: mp3File(std::string fileName)
	{
		
		
		std::string debugMsg;
		if(fileName.empty())
		{
			debugMsg = "Invalid FileName!";
			fatalErrorPrint(debugMsg);
		}
		
		/*is .mp3 file?*/
		
		if(fileName.find(".mp3") == std::string::npos)
		{
			debugMsg = "Not an mp3 file!";
			fatalErrorPrint(debugMsg);
		}
		m_fileName = fileName;
		
		//open the file
		openFile();
	}
	
	mp3File :: ~mp3File()
	{
		delete m_metaData;
		m_fin.close();
		std::string debugMsg = "Dest invoked";
		debugPrint(debugMsg);
	}
	
	void mp3File :: openFile()
	{
		/*open the file*/
		std::string debugMsg;
		m_fin.open(m_fileName);
		if(!m_fin.is_open())
		{
			debugMsg = "Unable to open file " + m_fileName;
			fatalErrorPrint(debugMsg);
		}
		else
		{
			debugMsg = "File opened successfully!";
			debugPrint(debugMsg);
		}
	}
	
	int mp3File :: parseMetaData()
	{
		return SUCCESS;
	}
	
	metaData* mp3File :: getMetaData()
	{
		return NULL;
	}
