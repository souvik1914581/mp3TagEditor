#ifndef MP3TAGEDITOR_HPP
#define MP3TAGEDITOR_HPP

/*MP3 Tag Editor Classes*/
#include <iostream>
#include <fstream>
typedef enum id3Version{
	ID3_INVALID = -1,
	ID3_V1,
	ID3_V11,
	ID3_V12,
	ID3_V2
}id3Version;

typedef class metaData{
	public:
		std::string title;
		std::string artist;
		std::string album;
		int year;
		std::string genre;
		std::string duration;
		std::string comment;
		std::string rating;
}metaData;

typedef class mp3File{
	private:
		std::string m_fileName;
		std::fstream m_fin;
		metaData *m_metaData;
	public:
		mp3File(std::string fileName);
		void openFile();
		int parseMetaData();
		metaData* getMetaData();
				
}mp3File;

#endif
