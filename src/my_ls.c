#include "../Header/include.h"
#include "../Header/my_ls.h"

void my_ls(const char *dir, struct Parametre *option) {
    int count_file = 0;
    struct dirent *d;

    DIR *directory = opendir(dir);
    DIR *dir_backup = opendir(dir);
    DIR *dir_d = opendir(dir); 

    if(!directory) {
        if(errno == ENOENT) {
            perror("Directory does not exist");
        }
        else {
            perror("Unable to read directory");
        }
        exit(EXIT_FAILURE);
    }


     
    if (option->op_d)
    {
        if (option->op_l)
        {
            
            while ((d = readdir(dir_d)) != NULL) {
               infoFile(".", d->d_type, dir, &*option);
               break;
            }
            
        }
        else{
            my_putstr("\033[1;34m");
            my_putstr(dir);
            my_putstr("\033[0m");
            my_putstr("\n");
        }
    }
    else{
        //count number of files in directory to alloc tab
        while ((d = readdir(directory)) != NULL) {
            if(!option->op_a && d->d_name[0] == '.') continue;
            count_file++;
        }

        int all_file = count_file;
        const char **file_tab = malloc(count_file * sizeof(void *));
        const char **color_tab = malloc(count_file * sizeof(void *));
        unsigned char *type_tab = malloc(count_file * sizeof(void *));
        
        //insert in tab


        while ((d = readdir(dir_backup)) != NULL && count_file != 0) {
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

        
        if(option->op_R){
            recursive(dir, &*option);
        }
        else if(option->op_l){
            for(int i = 0; i < all_file; i++){
                infoFile(file_tab[i], type_tab[i], dir, &*option);
            }
        }
        else{
            //display sorted
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
    }    
}