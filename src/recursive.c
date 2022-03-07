#include "../Header/include.h"

void recursive(const char* dir, struct Parametre *option)
{
    char path[4096];
    struct dirent *d;
    struct dirent *d2;
    DIR *rep;
    DIR *rep2;
    DIR *rep3;
    
    rep = opendir(dir);
    rep2 = opendir(dir);
    rep3 = opendir(dir);
    if (rep == NULL) return;
    
    my_putstr(dir);
    my_putstr(":");
    my_putstr("\n");
    int count_file = 0;

    //count number of files in directory to alloc tab
    while ((d = readdir(rep)) != NULL) {
      if(!option->op_a && d->d_name[0] == '.') continue;
      count_file++;
    }

    int all_file = count_file;
    const char **file_tab = malloc(count_file * sizeof(void *));
    const char **color_tab = malloc(count_file * sizeof(void *));
    unsigned char *type_tab = malloc(count_file * sizeof(void *));
    //insert in tab


    while ((d = readdir(rep3)) != NULL && count_file != 0) {
      if(!option->op_a && d->d_name[0] == '.') continue;
      if(count_file != 0){
          count_file--;
      }

      switch (d->d_type)
      {
      case DT_DIR:
          color_tab[count_file] = "DIR";
          break;
      
      case DT_LNK:
          color_tab[count_file] = "LNK";
          break;

      default:
          color_tab[count_file] = "FILE";
          break;
      }

      type_tab[count_file] = d->d_type;
      file_tab[count_file] = d->d_name;
    }
    //inverse(color_tab, all_file); //count_file is decrementative by default
    //if de trie
    if(option->op_t){
        sortingAndColor(file_tab, all_file, color_tab, type_tab);
        sortbydatetime((char **)file_tab, all_file, (char **)color_tab, type_tab);
    }
    else{
      sortingAndColor(file_tab, all_file, color_tab, type_tab);
    }
        
    if(option->op_r){
      inverse(file_tab, all_file);
      inverse(color_tab, all_file);
      inverseChar(type_tab, all_file);
    }
    

    if(option->op_l){
      for(int i = 0; i < all_file; i++){
          infoFile(file_tab[i], type_tab[i], dir, &*option);
      }
    }
    else{
      for (int i = 0; i < all_file; i++)
      { 
          if((option->op_A && !my_strcmp(file_tab[i], ".")) || (option->op_A && !my_strcmp(file_tab[i], ".."))) continue;
          if(!my_strcmp(color_tab[i], "DIR")){
              my_putstr(FDIR);
          }
          else if(!my_strcmp(color_tab[i], "LNK")){
              if(option->op_L){
                  my_putstr(FFILE);
              }
              else{
                  my_putstr(FLINK);
              }
          }
          else{
              my_putstr(FFILE);
          }
          my_putstr(file_tab[i]);
          my_putstr(FDEFAULT);
          my_putstr("  ");
          if(option->op_1) my_putstr("\n");
      }
      if(!option->op_1) my_putstr("\n");
      my_putstr(FDEFAULT);
    }

    my_putstr("\n");
    while ((d2 = readdir(rep2))!=NULL){
        if (d2->d_type == DT_DIR)
        {
          if (my_strcmp(d2->d_name, ".")!=0 && my_strcmp(d2->d_name, "..")!=0 && d2->d_name[0] != '.')
          {
            my_strcpy(path, dir);
            my_strcat(path,"/");
            my_strcat(path, d2->d_name);
            recursive(path, &*option);
          }
          else if(my_strcmp(d2->d_name, ".")!=0 && my_strcmp(d2->d_name, "..")!=0 && (option->op_A || option->op_a)){
            my_strcpy(path, dir);
            my_strcat(path,"/");
            my_strcat(path, d2->d_name);
            recursive(path, &*option);
          }
        }
    }
    closedir(rep2);
}