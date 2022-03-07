#ifndef __STATS__LS__
#define __STATS__LS__

char* isLink(const char * fileName, unsigned long size);
char* FilePermission(const long perm, unsigned char type);
char* get_time(const long file_time);
const char* getUser(uid_t uid);
const char* getGroup(gid_t gid);
size_t infoFile(const char* filename, unsigned char type, const char* dir, struct Parametre *option);

#endif