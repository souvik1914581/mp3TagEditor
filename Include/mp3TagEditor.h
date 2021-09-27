#ifndef MP3TAGEDITOR_HPP
#define MP3TAGEDITOR_HPP

/*MP3 Tag Editor Classes*/
#include <iostream>
#include <fstream>
typedef enum id3Version{
	ID3_INVALID = -1,
	ID3_V1,
	ID3_V12,
	ID3_V2
}id3Version;

typedef struct id3v1Data{
	char title[30];
	char artist[30];
	char album[30];
	char year[4];
	char comment[30];
	char zeroByte[1];
	char track[1];
	char genre[1];
}id3v1Data;

typedef class metaData{
	public:
		id3Version m_id3Version;
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
		int m_fileSize;
		std::fstream m_fileStream;
		id3v1Data *m_id3v1Data;
		metaData *m_metaData;
		bool b_hasid3v1Tag;
		bool b_hasid3v2Tag;
		
		/*editing functions*/
		int editTitle();
		int editArtist();
		int editAlbum();
		int editYear();
		
	public:
		mp3File(std::string fileName);
		~mp3File();
		void openFile();
		int getFileSize();
		int parseMetaData();
		metaData* getMetaData();
		void parseid3v1Data();
		void displayMetaData();
		void displayid3v1Data();
		void displayid3v2Data();
		
		/*editing methods*/
		int editTag();
		int editid3v1Tag();
		int editid3v2Tag();		
}mp3File;

#endif
