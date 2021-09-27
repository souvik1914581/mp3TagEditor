#ifndef MP3TAGEDITOR_HPP
#define MP3TAGEDITOR_HPP

/*MP3 Tag Editor Classes*/
#include <iostream>
#include <fstream>
#include "id3.h"


typedef class mp3File{
	private:
		std::string m_fileName;
		int m_fileSize;
		std::fstream m_fileStream;
		id3v1 *m_id3v1;
		bool b_hasid3v1Tag;
		bool b_hasid3v2Tag;
		
		/*methods*/
		void parseid3v1Data();
		/*editing methods*/
		int editTagInFile(id3TagId tagId,const char *newValue);
		
		/*display Methods*/
		void displayid3v2Data();
		
	public:
		mp3File(std::string fileName);
		~mp3File();
		void openFile();
		int getFileSize();
		int parseMetaData();
		
		void displayMetaData();
	
		/*editing methods*/
		int editTag();
		
		int editid3v1Tag();
		int editid3v2Tag();		
}mp3File;

#endif
