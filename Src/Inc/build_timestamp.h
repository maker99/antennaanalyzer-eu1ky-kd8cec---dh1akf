#ifndef BUILD_TIMESTAMP
#warning Mercurial failed. Repository not found. Firmware revision will not be generated. 
#define HGREV N/A 
#define BUILD_TIMESTAMP "2020-06-15 17:49 UT"
#define HGREVSTR(s) stringify_(s)
#define stringify_(s) #s
#endif
