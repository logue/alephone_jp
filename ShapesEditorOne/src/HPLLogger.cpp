#include "HPLLogger.h"

//cannot use file's name over 256 length
const int FILE_NAME_LENGTH = 256;

const int BUFFER_SIZE_MAX = 1024;

HPLLogger::HPLLogger(const char* filename_)
{
    this->fp = NULL;
    setFileName(filename_);
}
HPLLogger::HPLLogger()
{
    this->fp = NULL;
    filename[0] = '\0';
}
HPLLogger::~HPLLogger()
{
    if(this->fp)close();
}

void HPLLogger::setFileName(const char* filename_)
{
    strcpy(this->filename, filename_);
}
const char* HPLLogger::getFileName()
{
    return (const char*)this->filename;
}
//open
//failure->return false
bool HPLLogger::open(bool writable)
{
    if(strcmp(filename, "") == 0){
        return false;
    }
    if(this->fp){
        if(close())return false;
    }

    char type[10];
    if(writable){
        strcpy(type, "w");
    }else{
        strcpy(type, "r");
    }
    this->fp = fopen(this->filename, type);

    if(!this->fp){
        return false;
    }
    return true;
}

//close
//failure->return false
bool HPLLogger::close()
{
    int result = fclose(this->fp);
    return result == 0 ? true : false;
}

///////////////////////
void HPLLogger::printf(const char* format, ...)
{
	//reformat
	char message[BUFFER_SIZE_MAX];

	//analyze parameters
	va_list maker;
	va_start( maker, format);
	//vsprintf_s( message, nBUF_MAX,buf, maker);
	vsprintf(message, format, maker);

    fprintf(this->fp, message);
    fflush(this->fp);
}
void logEntry(struct directory_entry *entry, int length, int index)
{
    logger.printf("entry data\n");
    logger.printf("length:%d\n", length);
    logger.printf("entry.length:%d\n", entry->length);
    logger.printf("index:%d\n", index);
    logger.printf("entry.index:%d\n", entry->index);
    logger.printf("entry.offset_to_start:%d\n\n", entry->offset_to_start);
}
void logHeader(struct wad_header *header, const char* path)
{
    logger.printf("loading map[%s]'s header\n", path);
    logger.printf("app_spec_dir_dat_size:%d\n", header->application_specific_directory_data_size);
    logger.printf("checksum:%d\n", header->checksum);
    logger.printf("data_version:%d\n", header->data_version);
    logger.printf("entry_base_size:%d\n", header->directory_entry_base_size);
    logger.printf("entry_header_size:%d\n", header->entry_header_size);
    logger.printf("filename:%s\n", header->file_name);
    logger.printf("parent_checksum:%d\n", header->parent_checksum);
    logger.printf("version:%d\n", header->version);
    logger.printf("wad_count:%d\n\n", header->wad_count);

}

