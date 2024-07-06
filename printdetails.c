
#include "printdetails.h"



void print_details(struct stat file_stat,const char *file_name) {
  printf((S_ISDIR(file_stat.st_mode)) ? "d" : "-");
    printf((file_stat.st_mode & S_IRUSR) ? "r" : "-");
    printf((file_stat.st_mode & S_IWUSR) ? "w" : "-");
    printf((file_stat.st_mode & S_IXUSR) ? "x" : "-");
    printf((file_stat.st_mode & S_IRGRP) ? "r" : "-");
    printf((file_stat.st_mode & S_IWGRP) ? "w" : "-");
    printf((file_stat.st_mode & S_IXGRP) ? "x" : "-");
    printf((file_stat.st_mode & S_IROTH) ? "r" : "-");
    printf((file_stat.st_mode & S_IWOTH) ? "w" : "-");
    printf((file_stat.st_mode & S_IXOTH) ? "x" : "-");

    printf(" %2ld", file_stat.st_nlink);
    printf(" %s", getpwuid(file_stat.st_uid)->pw_name);
    printf(" %s", getgrgid(file_stat.st_gid)->gr_name);
    printf(" %8lld", (long long)file_stat.st_size);

    char time_str[20];
    strftime(time_str, sizeof(time_str), "%b %d %H:%M", localtime(&file_stat.st_mtime));
    printf(" %s", time_str);
    
     //color coding

      if (S_ISDIR(file_stat.st_mode)) {
            printf(" \033[1;34m%s\033[0m",file_name);
        } else if (file_stat.st_mode & S_IXUSR) {
            printf(" \033[1;32m%s\033[0m",file_name);
        } else {
            printf(" %s", file_name);
        }




    

    printf("\n");
}