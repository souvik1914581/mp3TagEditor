#include "id3.h"
#include "common.h"
#include <cstddef>

id3v1 :: id3v1()
{
	m_id3v1Data = new id3v1Data();
}

id3v1 :: ~id3v1()
{
	delete m_id3v1Data;
}

int id3v1 :: updateid3Data(char *buf)
{
	if(buf == NULL)
		return FAILURE;
	memcpy(m_id3v1Data,buf,sizeof(id3v1Data));
	return SUCCESS;
}

void id3v1 :: displayid3Data()
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


const char* id3v1 :: getTag(id3TagId tagId)
{
	std :: string debugMsg;
	char *ptr = (char*)m_id3v1Data;
	int offSet = getTagOffSet(tagId);
	debugMsg = "Offset";
	debugPrint1(debugMsg,offSet);
	
	ptr += offSet;
	return ptr;
}

/*updates local copy of Tag*/
void id3v1 :: updateTag(id3TagId tagId,const char *newValue)
{
	std :: string debugMsg;
	char *ptr = (char*)m_id3v1Data;
	int offSet = getTagOffSet(tagId);
	int lengthTag = getLengthOfTag(tagId);
	debugMsg = "Offset";
	debugPrint1(debugMsg,offSet);
	
	ptr += offSet;
	
	memcpy(ptr,newValue,lengthTag);
	
}

/*returns byte offset of a id3v1 Tag*/
int id3v1 :: getTagOffSet(id3TagId tagId)
{
	int offSet = 0;
	switch(tagId)
	{
		case ID3_TITLE:
			break;
		case ID3_ARTIST:
			offSet = offsetof(id3v1Data,artist);
			break;
		case ID3_ALBUM:
			offSet = offsetof(id3v1Data,album);
			break;
		case ID3_YEAR:
			offSet = offsetof(id3v1Data,year);
			break;
		case ID3_COMMENT:
			offSet = offsetof(id3v1Data,comment);
			break;
		case ID3_ZEROBYTE:
			offSet = offsetof(id3v1Data,zeroByte);
			break;
		case ID3_TRACK:
			offSet = offsetof(id3v1Data,track);
			break;
		case ID3_GENRE:
			offSet = offsetof(id3v1Data,genre);
			break;
		default:
			offSet = FAILURE;
	}
	
	return offSet;
}


int id3v1 :: getLengthOfTag(id3TagId tagId)
{
	int lengthTag = 30;
	switch(tagId)
		{
			case ID3_YEAR:
				lengthTag = 4;
				break;
			case ID3_ZEROBYTE:
			case ID3_TRACK:
			case ID3_GENRE:
				lengthTag = 1;
				break;
			default:
				lengthTag = 30;
		}
		return lengthTag;
}
