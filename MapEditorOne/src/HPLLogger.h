#ifndef _HPL_LOGGER_
#define _HPL_LOGGER_

#include <cstdio>
#include <iostream>
#include <stdarg.h>
#include <string.h>

#include "map.h"
#include "wad.h"
#include "game_wad.h"
/**
    logger
*/
class HPLLogger
{
private:
    char filename[256];
    FILE *fp;
public:
    HPLLogger(const char* filename_);
    HPLLogger();
    ~HPLLogger();

    //set
    void setFileName(const char* filename_);

    //get
    const char* getFileName();
    
    //open
    //failure->return false
    bool open(bool writable = true);

    //close
    //failure->return false
    bool close();
public:
    //normal printf
    void printf(const char* format, ...);
};

//logger
extern HPLLogger logger;

void logEntry(struct directory_entry *entry, int length, int index);
void logHeader(struct wad_header *header, const char* path);

#endif
