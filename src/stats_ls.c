#include "../Header/include.h"
#include "../Header/stats_ls.h"
#include <string.h>

char* isLink(const char * fileName, unsigned long size){
    char *buf;
    ssize_t nbytes, bufsiz;

    bufsiz = size + 1;

    if (size == 0)
        bufsiz = PATH_MAX;

    buf = malloc(bufsiz);
    if (buf == NULL) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    nbytes = readlink(fileName, buf, bufsiz);
    if (nbytes == -1) {
        perror("readlink");
        exit(EXIT_FAILURE);
    }
    char * sortie;
    sortie = malloc(bufsiz);

    my_strncpy(sortie, (const char *)buf, 60);

    if(my_strchr(sortie, ':')){
        my_strtok(sortie, ":");
    }
    my_strcat(sortie, "\0");

    return sortie;
}

char* FilePermission(const long perm, unsigned char type)
{
	char * result = malloc(11 * sizeof(char));

    switch (type) {
    case DT_DIR:  result[0] = 'd'; break;
    case DT_LNK:  result[0] = 'l'; break;
    default: result[0] = '-'; break;
    }
    
    // Permissions user 
    result[1] = perm & S_IRUSR? 'r':'-';
    result[2] = perm & S_IWUSR? 'w':'-';
    result[3] = perm & S_IXUSR? 'x':'-';
    // Permissions group
    result[4] = perm & S_IRGRP? 'r':'-';
    result[5] = perm & S_IWGRP? 'w':'-';
    result[6] = perm & S_IXGRP? 'x':'-';
    // Permissions Other
    result[7] = perm & S_IROTH? 'r':'-';
    result[8] = perm & S_IWOTH? 'w':'-';
    result[9] = perm & S_IXOTH? 'x':'-';
    result[10] = '\0';
    return result;
}

char* get_time(const long file_time){
// Get file time
	struct tm * ptr_time;
	char * chaine = malloc(20 * sizeof(char));
	ptr_time = localtime(&file_time);
	char month[12][7] = {"Jan\0", "Feb.\0", "Mar\0", "Apr\0", "May\0", "Jun\0",
							"Jul\0", "Aug\0", "Sep\0", " Oct", "Nov\0", "Dec\0"};

	// Convert all datas to string, month, day, hour, minute
    my_strcpy(chaine, (const char*)month[ptr_time->tm_mon]);
    my_strcat(chaine, " ");
    char* buf_int;
    char buffer[256];
    buf_int = my_ultostr(ptr_time->tm_mday, buffer, 10);
    my_strcat(chaine, (const char*)buf_int);
    my_strcat(chaine, " ");
    buf_int = my_ultostr(ptr_time->tm_hour, buffer, 10);
    my_strcat(chaine, (const char*)buf_int);
    my_strcat(chaine, ":");
    buf_int = my_ultostr(ptr_time->tm_min, buffer, 10);
    my_strcat(chaine, (const char*)buf_int);

	return chaine;
}

const char* getUser(uid_t uid)
// Get user name from uid
{
    struct passwd *pws;
    pws = getpwuid(uid);
    return pws->pw_name;
}

const char* getGroup(gid_t gid)
// Get group from gid
{
    struct group *grp;
    grp = getgrgid(gid);
    return grp->gr_name;
}

size_t infoFile(const char* filename, unsigned char type, const char* dir, struct Parametre *option) {
	char * finalString = malloc(256 * sizeof(char));
    struct stat st;


    char buf[PATH_MAX] = {0}; 

    my_strcat(buf, dir);
    my_strcat(buf, "/");
    my_strcat(buf, filename);
    stat(buf, &st);

    // Permissions and type of file dir, file, link
	char * perm;
    perm = FilePermission(st.st_mode, type);
    
    // link number
    //"%ld ", (long) st.st_nlink
    // User
	const char * user;
	user = getUser(st.st_uid);
	//"%s ", user)
    // Group
	const char * group;
	group = getGroup(st.st_gid);
	//"%s ", group
    // file size
    //"%lu ", st.st_size
    // last modif
	char * timeInfo;
    timeInfo = get_time(st.st_mtime);
    // File name
    //"%s\n", filename
    char * finalName = malloc(256 * sizeof(char));
    char * name;
    char * myColor;
    char check, first;
    first = perm[0];
    check = perm[3];

    if(first == 'd'){
        myColor = FDIR;
        my_strcpy(finalName, filename);
    }
    else if(first == 'l'){
        if(option->op_L){
            myColor = FFILE;
            my_strcpy(finalName, filename);
        }
        else{
            myColor = FLINK;
            name = isLink(buf, st.st_size);
            const char* arrow = " -> ";
            my_strcpy(finalName, filename);
            my_strcat(finalName, arrow);
            my_strcat(finalName, name);
        }  
    }
    else if(check == 'x'){
        myColor = FFILE;
        my_strcpy(finalName, filename);
    }
    else{
        myColor = FFILE;
        my_strcpy(finalName, filename);
    }

	// print final string
    my_strcpy(finalString, (const char*)perm);
    const char* space = " ";
    my_strcat(finalString, space);
    char* buf_int;
    char buffer[256];
    buf_int = my_ultostr(st.st_nlink, buffer, 10);
    my_strcat(finalString, (const char*)buf_int);
    my_strcat(finalString, space);
    my_strcat(finalString, user);
    my_strcat(finalString, space);
    my_strcat(finalString, group);
    my_strcat(finalString, space);
    char buffer2[256];
    buf_int = my_ultostr((unsigned long)st.st_size, buffer2, 10);
    my_strcat(finalString, buf_int);
    my_strcat(finalString, space);
    my_strcat(finalString, timeInfo);
    my_strcat(finalString, space);
	
    if (option->op_d)
    {
        my_putstr(finalString);
        my_putstr("\033[1;34m");
        my_putstr(dir);
        myColor = FDEFAULT;
        my_putstr(myColor);
        my_putstr("\n");
    }
    else if(!(option->op_A && !my_strcmp(filename, ".")) && !(option->op_A && !my_strcmp(filename, ".."))){
        my_putstr(finalString);
        my_putstr(myColor);
        my_putstr(finalName);
        myColor = FDEFAULT;
        my_putstr(myColor);
        my_putstr("\n");
    }

	
	free(perm);
	free(timeInfo);
	free(finalString);
    free(finalName);
    return 0;
}