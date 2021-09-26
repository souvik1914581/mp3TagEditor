#include "common.h"
#include "mp3TagEditor.h"
	mp3File :: mp3File(std::string fileName)
	{
		std :: string identifierString = "TAG";
		
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
		
		/*get File Size*/
		m_fileSize = getFileSize();
		
		debugMsg = "File Size";
		debugPrint1(debugMsg,m_fileSize);
		
		/*goto 128 bytes from end of file and read 3 bytes*/
		m_fileStream.seekg(m_fileSize - 128,std::ios::beg);
		
		debugMsg = "Current pos";
		debugPrint1(debugMsg,m_fileStream.tellg());
		
		
		char *buff = new char[3];
		m_fileStream.read(buff,3);
		
		debugMsg = "Bytes read = " + std::string(buff);
		debugPrint(debugMsg);
		
		if(identifierString == std::string(buff))
		{
			b_hasid3v1Tag = true;
			parseid3v1Data();
		}
		
	}
	
	mp3File :: ~mp3File()
	{
		delete m_metaData;
		m_fileStream.close();
		std::string debugMsg = "Dest invoked";
		debugPrint(debugMsg);
	}
	
	void mp3File :: openFile()
	{
		/*open the file*/
		std::string debugMsg;
		m_fileStream.open(m_fileName);
		if(!m_fileStream.is_open())
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
	
	int mp3File :: getFileSize()
	{
		std::streampos fsize = 0;
	    std::ifstream file(m_fileName, std::ios::binary );
	
	    fsize = file.tellg();
	    file.seekg( 0, std::ios::end );
	    fsize = file.tellg() - fsize;
	    file.close();
	
	    return fsize;
	}
	
	void mp3File :: parseid3v1Data()
	{
		std :: string debugMsg = "Parsing id3v1.Current pos";
		debugPrint1(debugMsg,m_fileStream.tellg());
		m_id3v1Data = new id3v1Data;
		
		debugMsg = "Size of id3V1";
		debugPrint1(debugMsg,sizeof(id3v1Data));
		
		char buff[128];
		/*copy 128 bytes to id3v1 struct*/
		m_fileStream.read(buff,128);
		
		memcpy(m_id3v1Data,buff,sizeof(id3v1Data));
		
		debugMsg = m_id3v1Data->album;
		debugPrint(debugMsg);
		
	}
	
	int mp3File :: parseMetaData()
	{
		return SUCCESS;
	}
	
	metaData* mp3File :: getMetaData()
	{
		return NULL;
	}
