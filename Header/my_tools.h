#ifndef __MY__TOOLS__
#define __MY__TOOLS__

void my_putchar(char c);
void my_putstr(const char *str);
int my_strcmp(const char *s1, const char *s2);
char *my_strcat(char *s1, const char *s2);
char *my_strcpy(char *dest, const char *src);
void sorting(const char **tab, int nb_dir);
void sortingAndColor(const char **tab, int nb_dir, const char **color_tab, unsigned char *type_tab);
int strcasecmp(const char *a, const char *b);
int tolower(int chr);
void inverse(const char **tab, int nb_dir);
void sortbydatetime(char **tab, int nb_dir, char **color_tab, unsigned char *type_tab);
char* reverse_const(const char **str_const);
int my_strlen(const char *str);
int get_mtime(char *filename);
void inverseChar(unsigned char *tab, int nb_dir);
char* my_ultostr(unsigned long value, char *ptr, int base);
char* my_strncpy(char *dest, const char *source, size_t n);
char *my_strtok(char *srcString, char *delim);
unsigned int is_delim(char c, char *delim);
char *my_strchr(const char *s, int c);

#endif
