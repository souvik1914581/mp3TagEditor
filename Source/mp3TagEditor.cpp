#include "common.h"
#include "mp3TagEditor.h"
#include <cstring>
	mp3File :: mp3File(std::string fileName)
	{
		/*initialise members*/
		
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
		
		
		delete m_id3v1;
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
		
		m_id3v1 = new id3v1();
	
		
		char buff[128] = {0};
		/*copy 128 bytes to id3v1 struct*/
		m_fileStream.read(buff,128);
		
		m_id3v1->updateid3Data(buff);
	}
	
	void mp3File :: displayMetaData()
	{
		if(b_hasid3v1Tag)
		{
			m_id3v1->displayid3Data();
		}
		
		if(b_hasid3v2Tag)
		{
			displayid3v2Data();
		}
		
		/*metadata displayed.close the filestream*/
		m_fileStream.close();
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
	
		
		char *buff = new char[3]();
		m_fileStream.read(buff,3);
		
		
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
		int retVal = FAILURE;
		m_fileStream.open(m_fileName,std::ios::binary | std::ios::in |std::ios::out);
		if(b_hasid3v1Tag)
		{
			retVal =  editid3v1Tag();
				
		}
		else if(b_hasid3v2Tag)
		{
			retVal = editid3v2Tag();
		}
		m_fileStream.close();
		return retVal;
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
	#if 0	
		int currPos = m_fileStream.tellp();
		std::string debugMsg = "Curr pos";
		debugPrint1(debugMsg,currPos);
	#endif
		
		/*display the options*/
		int choice{0};
		
		char *buff = new char[30]();
		std::cout<<"Choose your option:\n1.Title\n2.Artist\n3.Album\n4.Year\n";
		std::cin>>choice;
		std::cout<<std::endl;
		
		std::cout<<"Enter new value:";
		std::string userInput = getUserInput();
		strncpy(buff,userInput.c_str(),29);
		id3TagId tagId = ID3_INVALID_ID;
		switch(choice)
		{
			case 1:
				tagId = ID3_TITLE;	
				break;
			case 2:
				tagId = ID3_ARTIST;
				break;
			case 3:
				tagId = ID3_ALBUM;
				break;
			case 4:
				tagId = ID3_YEAR;
				break;
			default:
				std::string debugMsg = "Invalid choice!";
				debugPrint(debugMsg);
		}
		
		m_id3v1->updateTag(tagId,buff);
		editTagInFile(tagId,buff);
		
		return SUCCESS;
	}
	
	int mp3File :: editTagInFile(id3TagId tagId,const char *newValue)
	{
		int lengthTag{-1};
		int byteOffSet{-1};
		int filePos{-1};
		std::string debugMsg;
		if(newValue == NULL)
		{
			return FAILURE;
		}
		
		lengthTag = m_id3v1->getLengthOfTag(tagId);
		byteOffSet = m_id3v1->getTagOffSet(tagId);
		
		m_fileStream.seekp(byteOffSet,std::ios::cur);
		filePos = m_fileStream.tellp();
		debugMsg = "Editing in file..Curr Pos";
		debugPrint1(debugMsg,filePos);
		
		debugMsg = "Len(Tag)";
		debugPrint1(debugMsg,lengthTag);
		
		/*write to file*/
		m_fileStream.write(newValue,lengthTag);
		
		return SUCCESS;
	}
	
	int mp3File :: editid3v2Tag()
	{
		return SUCCESS;
	}
	
	
	
	
