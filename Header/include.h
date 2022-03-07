#ifndef __INCLUDE__
#define __INCLUDE__

#define FFILE "\e[1;32m"
#define FDIR "\e[0;34;42m"
#define FLINK "\e[1;36m"
#define FDEFAULT "\e[0m"

#include <stdio.h>
#include <dirent.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <limits.h>


#include "struct.h"
#include "my_ls.h"
#include "my_tools.h"
#include "wich_option.h"
#include "recursive.h"
#include "stats_ls.h"

#endif