#include "../Header/include.h"
#include "../Header/wich_option.h"

void wich_option(int argc, const char *argv[], struct Parametre *option, const char ***path_tab_out, int *nb_dir) {

    const char **path_tab = 0;

    for(int i = 1; i < argc; i++) {
        if(argv[i][0] == '-') {
            char *p = (char *)(argv[i]+1);
            while(*p) {
                switch (*p)
                {
                case 'a':
                    option->op_a = 1;
                    break;

                case '1':
                    option->op_1 = 1;
                    break;

                case 'A':
                    option->op_a = 1;
                    option->op_A = 1;
                    break;

                case 't':
                    option->op_t = 1;
                    break;

                case 'r':
                    option->op_r = 1;
                    break;
                    
                case 'd':
                    option->op_d = 1;
                    break;

                case 'R':
                    option->op_R = 1;
                    break;
                
                case 'l':
                    option->op_l = 1;
                    break;
                
                case 'L':
                    option->op_L = 1;
                    break;

                default:
                    perror("Unknow option error");
                    exit(EXIT_FAILURE);
                    break;
                }
                p++;
            }
        }
        else if(argv[i][0] != '-') {
            *nb_dir = *nb_dir+1;
        }
    }

    if(*nb_dir == 0){
        path_tab = malloc(sizeof(void *));
        path_tab[0] = ".";
    }
    else{
        path_tab = malloc(*nb_dir * sizeof(void *));
        int j = 0;
        for (int i = 1; i < argc; i++)
        {
            if(argv[i][0] != '-') {
                path_tab[j] = argv[i];
                j++;
            }         
        }
    }

    *path_tab_out = path_tab;

}