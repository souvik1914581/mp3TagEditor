#ifndef ID3_H
#define ID3_H

#define ID3V1_MAX_SIZE 128

typedef enum id3Version{
	ID3_INVALID = -1,
	ID3_V1,
	ID3_V12,
	ID3_V2
}id3Version;

/*ID3v1 classes and methods*/
typedef enum id3TagId{
	ID3_INVALID_ID = -1,
	ID3_TITLE,
	ID3_ARTIST,
	ID3_ALBUM,
	ID3_YEAR,
	ID3_COMMENT,
	ID3_ZEROBYTE,
	ID3_TRACK,
	ID3_GENRE
}id3TagId;

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

typedef class id3v1
{
	private:
		id3v1Data *m_id3v1Data;
	public:
		id3v1();
		~id3v1();
		int updateid3Data(char *buf);
		const char * getTag(id3TagId tagId);
		void updateTag(id3TagId tagId,const char *newValue);
		void displayid3Data();
		int getTagOffSet(id3TagId tagId);
		int getLengthOfTag(id3TagId tagId);
}id3v1;

/*ID3v2 classes and objects*/

#endif
