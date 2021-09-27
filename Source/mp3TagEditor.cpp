#include "common.h"
#include "mp3TagEditor.h"
#include <cstring>
	mp3File :: mp3File(std::string fileName)
	{
		/*initialise members*/
		m_id3v1Data = NULL;
		m_metaData = NULL;
		b_hasid3v1Tag = false;
		b_hasid3v2Tag = false;
		
	
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
		
		if(FAILURE == parseMetaData())
		{
			debugMsg = "Failed to parse Meta Data";
			fatalErrorPrint(debugMsg);	
		}
		
		/*display MetaData*/
		displayMetaData();
		
	}
	
	mp3File :: ~mp3File()
	{
		delete m_metaData;
		delete m_id3v1Data;
		m_fileStream.close();
		std::string debugMsg = "Dest invoked";
		debugPrint(debugMsg);
	}
	
	void mp3File :: openFile()
	{
		/*open the file*/
		std::string debugMsg;
		m_fileStream.open(m_fileName, std::ios::binary | std::ios::in | std::ios::out);
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
	    std::ifstream file(m_fileName, std::ios::binary);
	
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
		m_id3v1Data = new id3v1Data();
		
		
		debugMsg = "Size of id3V1";
		debugPrint1(debugMsg,sizeof(id3v1Data));
		
		char buff[128];
		/*copy 128 bytes to id3v1 struct*/
		m_fileStream.read(buff,128);
		
		memcpy(m_id3v1Data,buff,sizeof(id3v1Data));
		
		/*debugMsg = m_id3v1Data->album;
		debugPrint(debugMsg);*/
		
		
		
	}
	
	void mp3File :: displayMetaData()
	{
		if(b_hasid3v1Tag)
		{
			displayid3v1Data();
		}
		
		if(b_hasid3v2Tag)
		{
			displayid3v2Data();
		}
		
		/*metadata displayed.close the filestream*/
		m_fileStream.close();
	}
	
	void mp3File :: displayid3v1Data()
	{
		std::string debugMsg;
		
		debugMsg = "\nTitle: " + std::string(m_id3v1Data->title)+ "\n";
		debugMsg += "Artist: " + std::string(m_id3v1Data->artist)+ "\n";
		debugMsg += "Album: " + std::string(m_id3v1Data->album)+ "\n";
		debugMsg += "Year: " + std::string(m_id3v1Data->year)+ "\n";
		debugMsg += "Comment: " + std::string(m_id3v1Data->comment)+ "\n";
		debugMsg += "ZeroByte: " + std::string(m_id3v1Data->zeroByte)+ "\n";
		debugMsg += "Track: " + std::string(m_id3v1Data->track)+ "\n";
		debugMsg += "Genre: " + std::string(m_id3v1Data->genre)+ "\n";
		debugPrint(debugMsg);
	}
	
	void mp3File :: displayid3v2Data()
	{
		
	}	
	
	int mp3File :: parseMetaData()
	{
		int retVal{FAILURE};
		std :: string identifierString = "TAG";
		std :: string debugMsg = "File Size";
		debugPrint1(debugMsg,m_fileSize);
		
		/*goto 128 bytes from end of file and read 3 bytes*/
		m_fileStream.seekg(m_fileSize - 128,std::ios::beg);
	#if 0	
		debugMsg = "Current pos";
		debugPrint1(debugMsg,m_fileStream.tellg());
	#endif
		
		char *buff = new char[3]();
		m_fileStream.read(buff,3);
		
	#if 0	
		debugMsg = "Bytes read = " + std::string(buff);
		debugPrint(debugMsg);
	#endif	
		if(identifierString == std::string(buff))
		{
			b_hasid3v1Tag = true;
			parseid3v1Data();
			retVal = SUCCESS;
		}
		
		
		delete[] buff;
		return retVal;
	}
	
	int mp3File :: editTag()
	{
		m_fileStream.open(m_fileName,std::ios::binary | std::ios::in |std::ios::out);
		if(b_hasid3v1Tag)
		{
			return editid3v1Tag();	
		}
		else if(b_hasid3v2Tag)
		{
			return editid3v2Tag();
		}
		return FAILURE;
	}
	
	int mp3File :: editid3v1Tag()
	{
		if(!m_fileStream.is_open())
		{
			std::string debugMsg = "File not open!";
			fatalErrorPrint(debugMsg);
		}
		
		/*goto 128 bytes from end of file. +3 to skip "TAG"*/
		m_fileStream.seekp(m_fileSize - 128 + 3,std::ios::beg);
		
		int currPos = m_fileStream.tellp();
		std::string debugMsg = "Curr pos";
		debugPrint1(debugMsg,currPos);
		/*display the options*/
		int choice{0};
		std::cout<<"Choose your option:\n1.Title\n2.Artist\n3.Album\n4.Year\n";
		std::cin>>choice;
		std::cout<<std::endl;
		switch(choice)
		{
			case 1:
				return editTitle();
				break;
			case 2:
				return editArtist();
				break;
			case 3:
				return editAlbum();
				break;
			case 4:
				return editYear();
				break;
			default:
				std::string debugMsg = "Invalid choice!";
				debugPrint(debugMsg);
		}
		return SUCCESS;
	}
	
	int mp3File :: editTitle()
	{
		std::string debugMsg;
		char newTitle[30] = {0};
		std::string userInput;
		std::cout<<"Enter new Title:";
		
		userInput = getUserInput();
		
		
		strncpy(newTitle,userInput.c_str(),sizeof(newTitle) - 1);
		
		int newTitleLength = strlen(newTitle);
		
		/*clear title from struct and update new title*/
		memset(m_id3v1Data->title,0,sizeof(m_id3v1Data->title));
		strncpy(m_id3v1Data->title,newTitle,sizeof(m_id3v1Data->title) - 1);
		debugMsg = "updating new title ''" + std::string(m_id3v1Data->title) + "'";
		debugPrint1(debugMsg,newTitleLength);
		
		
		/*Total 30 bytes,update new Title*/
		m_fileStream.write(m_id3v1Data->title,30);
		m_fileStream.close();
		if(!m_fileStream)
		{
			debugMsg = "Write error!";
			debugPrint(debugMsg);
		}
		
		return SUCCESS;
	}
	
	int mp3File :: editArtist()
	{
		return SUCCESS;
	}
	
	int mp3File :: editAlbum()
	{
		return SUCCESS;
	}
	
	int mp3File :: editYear()
	{
		return SUCCESS;
	}
	
	int mp3File :: editid3v2Tag()
	{
		return SUCCESS;
	}
	
	metaData* mp3File :: getMetaData()
	{
		return NULL;
	}
