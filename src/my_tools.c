#include "../Header/include.h"
#include "../Header/my_tools.h"

void my_putchar(char c){
    write(1, &c, 1);
}

void my_putstr(const char *str)
{
    while (*str != '\0'){
        my_putchar(*str);
        str++;
    }
}

int my_strcmp(const char *s1, const char *s2){
    int i = 0;
    
    while(s1[i] == s2[i] && s1[i] && s2[i]){
        i++;
    }

    if(s1[i] == '\0' && s2[i] == '\0'){
        return(0);
    }
    else{
        return(s1[i] - s2[i]);
    } 
}

char *my_strcat(char *s1, const char *s2){
    if((s1 == NULL) && (s2 == NULL))
        return NULL;

    char *start = s1;

    while(*start != '\0')
    {
        start++;
    }

    while(*s2 != '\0')
    {
        *start++ = *s2++;
    }

    *start = '\0';
    return s1;
}

char *my_strcpy(char *dest, const char *src){
    int i = 0;

    while (src[i]) {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
    return (dest);
}

int my_strlen(const char *str){
    int i = 0;

    while (str[i] != '\0')
        i++;
    return (i);
}

char* reverse_const(const char **str_const){
    int c_size = my_strlen(*str_const);
    char *str = calloc(c_size + 1, sizeof *str);
    my_strcpy(str, *str_const);
    char *c_begin = str, *c_end = str + (c_size - 1);

    int i;
    for (i = 0; i < c_size / 2; i++) {
        *c_begin ^= *c_end;
        *c_end ^= *c_begin;
        *c_begin ^= *c_end;

        c_begin++;
        c_end--;
    }

    *str_const = str;
    return str;
    
}

int strcasecmpSort(const char *a, const char *b){
    int b_point = 0; 
    int a_point = 0;

    if(b[0] == 46 && b[1] != 46 && my_strcmp(b, ".")){
        b_point = 1;
       
    }
    if(a[0] == 46 && a[1] != 46 && my_strcmp(a, ".")){
        a_point = 1;
    }

    while (*a && *b) {
        if (tolower(*a) != tolower(*b)){
            break;
        }
        ++a;
        ++b;
    }

    if(b_point == 1 && a_point == 1){
        return *a - *b;
    }
    else if(b_point == 1){
        return *a - *b *10;
    }
    else if(a_point == 1){
        return *a * 10 - *b;
    }
    else{
        return tolower(*a) - tolower(*b);
    }
}

int tolower(int chr){
    return (chr >='A' && chr<='Z') ? (chr + 32) : (chr);    
}

void inverse(const char **tab, int nb_dir){

    for (int i = 0 ; i < nb_dir/2 ; i++){
            const char *temp = tab[i];
            tab[i] = tab[nb_dir - i - 1];
            tab[nb_dir - i - 1 ] = temp;
    }
}

void inverseChar(unsigned char *tab, int nb_dir){

    for (int i = 0 ; i < nb_dir/2 ; i++){
            unsigned char temp = tab[i];
            tab[i] = tab[nb_dir - i - 1];
            tab[nb_dir - i - 1 ] = temp;
    }
}

void sorting(const char **tab, int nb_dir){

    for (int i = 0; i < nb_dir; i++) {
        for (int j = i+1; j < nb_dir; j++){
            if(strcasecmpSort(tab[i], tab[j]) > 0) {
                const char* temp = tab[i]; 
                tab[i] = tab[j];
                tab[j] = temp; 
            }
        }
    }
}

void sortingAndColor(const char **tab, int nb_dir, const char **color_tab, unsigned char *type_tab){

    for (int i = 0; i < nb_dir; i++) {
        for (int j = i+1; j < nb_dir; j++){
            if(strcasecmpSort(tab[i], tab[j]) > 0) {
                const char* temp = tab[i];
                const char* color_temp = color_tab[i];
                unsigned char type_temp = type_tab[i];
                tab[i] = tab[j];
                color_tab[i] = color_tab[j];
                type_tab[i] = type_tab[j];
                tab[j] = temp;
                color_tab[j] = color_temp;
                type_tab[j] = type_temp;
            }
        }
    }
}

int get_mtime(char *filename){
    struct stat status;
    stat(filename, &status);
    return (status.st_mtime);
}

void sortbydatetime(char **tab, int nb_dir, char **color_tab, unsigned char *type_tab){
    char *temp = NULL;
    char *color_temp = NULL;

    for (int i = 0; i < nb_dir; i++){
        for (int j = 0; j < nb_dir; j++){
            if(get_mtime(tab[i]) > get_mtime(tab[j])){
                temp = tab[i];
                color_temp = color_tab[i];
                unsigned char type_temp = type_tab[i];
                tab[i] = tab[j];
                color_tab[i] = color_tab[j];
                type_tab[i] = type_tab[j];
                tab[j] = temp;
                color_tab[j] = color_temp;
                type_tab[j] = type_temp;

            }
        }
    }
}

char* my_ultostr(unsigned long value, char *ptr, int base){
  unsigned long t = 0, res = 0;
  unsigned long tmp = value;
  int count = 0;

  if (NULL == ptr)
  {
    return NULL;
  }

  if (tmp == 0)
  {
    count++;
  }

  while(tmp > 0)
  {
    tmp = tmp/base;
    count++;
  }

  ptr += count;
  
  *ptr = '\0';

  do
  {
    res = value - base * (t = value / base);
    if (res < 10)
    {
      * -- ptr = '0' + res;
    }
  } while ((value = t) != 0);

  return(ptr);
}

char* my_strncpy(char *dest, const char *source, size_t n){
    size_t i;
    for (i = 0; i < n && source[i] != '\0'; i++) {
        dest[i] = source[i];
    }
    dest[i] = '\0';
    return dest;
}

unsigned int is_delim(char c, char *delim){
    while(*delim != '\0')
    {
        if(c == *delim)
            return 1;
        delim++;
    }
    return 0;
}

char *my_strtok(char *srcString, char *delim){
    static char *backup_string;
    if(!srcString)
    {
        srcString = backup_string;
    }
    if(!srcString)
    {
        return NULL;
    }
    while(1)
    {
        if(is_delim(*srcString, delim))
        {
            srcString++;
            continue;
        }
        if(*srcString == '\0')
        {
            return NULL; 
        }
        break;
    }
    char *ret = srcString;
    while(1)
    {
        if(*srcString == '\0')
        {
            backup_string = srcString;
            return ret;
        }
        if(is_delim(*srcString, delim))
        {
            *srcString = '\0';
            backup_string = srcString + 1;
            return ret;
        }
        srcString++;
    }
}

char *my_strchr(const char *s, int c){
    char *isCharFind = NULL;
    //handling null pointer
    if(s != NULL)
    {
        do
        {
            if( *s == (char)c )
            {
                isCharFind = (char*)s;
                break;
            }
        }
        while(*s++);
    }
    return isCharFind;
}
