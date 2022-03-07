#include "../Header/include.h"

int main(int argc, const char *argv[])
{

    const char **path_tab = 0;
    int nb_dir = 0;

    struct Parametre option;
    option.op_a = 0;
    option.op_1 = 0;
    option.op_A = 0;
    option.op_t = 0;
    option.op_r = 0;
    option.op_d = 0;
    option.op_R = 0;
    option.op_l = 0;
    option.op_L = 0;

    const char *dirPath = argv[argc-1];

    if(argc == 1){
        wich_option(argc, argv, &option, &path_tab, &nb_dir);
        sorting(path_tab, nb_dir);  
        my_ls(path_tab[0], &option);
    }
    else if (argc == 2){
        if (argv[1][0] == '-'){ //if option passed
            wich_option(argc, argv, &option, &path_tab, &nb_dir);
            sorting(path_tab, nb_dir);
            my_ls(path_tab[0], &option);
        }
        else { //check if the directory exist
            wich_option(argc, argv, &option, &path_tab, &nb_dir);
            sorting(path_tab, nb_dir);
            my_ls(path_tab[0], &option);
        }
    }
    else if(argc > 2){
        if (argv[1][0] == '-'){
            wich_option(argc, argv, &option, &path_tab, &nb_dir);
            if(dirPath[0] == '-'){
                my_ls(".", &option);
            }
            else {
                sorting(path_tab, nb_dir);
                for(int i = 0; i < nb_dir; i++) {
                    if(nb_dir != 1){
                        my_putstr(path_tab[i]);
                        my_putstr(":\n");
                    }
                    my_ls(path_tab[i], &option);
                    if(i != nb_dir-1){
                        my_putstr("\n");
                    }
                }
            }
        }
        else {
            wich_option(argc, argv, &option, &path_tab, &nb_dir);
            sorting(path_tab, nb_dir);
            for(int i = 0; i < nb_dir; i++) {
                if(nb_dir != 1){
                    my_putstr(path_tab[i]);
                    my_putstr(":\n");
                }
                my_ls(path_tab[i], &option);
                if(i != nb_dir-1){
                    my_putstr("\n");
                }
            }
        }
    }

    free(path_tab);
    return 0;
}