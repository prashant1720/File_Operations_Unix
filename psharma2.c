// Declaring all the header files that are used in the code
#include <stdio.h>
#include <time.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <getopt.h>


// decalring all the functions pointers that are used in the program
typedef void (*function_ptr_captial_S)(char *, int);
typedef void (*function_ptr_small_s)(char *, int, int);
typedef void (*function_ptr_f)(char *, int, char *, int);
typedef void (*function_ptr_S_s_f)(char *, int, int, char *, int);


// declaring all the functions that are used in the program

 void function_one(char *, int);
 void function_two(char *, int, int);
 void function_three(char *, int, char *, int);
 void function_four(char *, int, int, char *, int);
 void function_five(char *, const int );
 


int main(int argc, char *argv[]) {


// Below the address of functions are assigned to there respective function pointers these function pointers are further used to make function calls
     void (*function_ptr_captial_S)(char *,int) = &function_one;
     void (*function_ptr_small_s)(char *, int, int)= &function_two;
     void (*function_ptr_f)(char *, int, char *, int) = &function_three;
     void (*function_ptr_S_s_f)(char *, int, int, char *, int) = &function_four;
     void (*function_ptr_no_arg)(char *,  int) = &function_five;

// Defining the variables that are used in the program
    int Letter_S=0;
    int Letter_s=0;
    int Letter_f=0;
    int operation=0;
    int providesize;
    bool sysfile = false;
    bool dict = false;
    int dict_depth;
    char * loc = NULL;
    char * searching_loc = NULL;


    // looping over the command line arguments to check the entered value and then calling the required function
 

// This is one of the approach to loop through there is another approch to perform this process
// using getopt method and then creating switch cases since switch cases are slow

  for(int j=1;j<argc;j++) {
   

    if(strcmp(argv[j],"-S")==0){
        Letter_S = 1;
        continue;
    }
    else if(strcmp(argv[j],"-s")==0){
        Letter_s = 1;
        providesize = atoi(argv[j+1]);
        j++;
        continue;
    }
    else if(strcmp(argv[j],"-f")==0){
        Letter_f = 1;
        searching_loc = malloc(sizeof(argv[j+1]));
        strcpy(searching_loc,argv[j+1]);
        dict_depth = atoi(argv[j+2]);
        j=j+2;
        continue;
    }
    else if(strcmp(argv[j],"-t")==0){
        operation = 1;
        if(strcmp(argv[j+1],"f")==0){
            sysfile = true;
        }
        else{
            dict=true;
        }
        j=j+1;
        continue;
    }
    else{
        loc = malloc(sizeof(argv[j]));
        strcpy(loc,argv[j]);
    }
    
   
}
// Approach two using getopt method
// reference: https://man7.org/linux/man-pages/man3/readdir.3.html
/*   while(( option = getopt(argc, argv, "s:t:f:S")) != -1 )
        { 
            switch (option){ 
                case 'S':   
                    LetterS =1; 
                    break;
                case 's':
                    Letters =1;
                    break;
                case 'f': 
                    Letterf=1;
                    break;
                case 't':
                    Lettert=1;
                    break;
            }
        }  */


if(loc != NULL){
   printf(" ");
  }
  else{
     loc = malloc(sizeof("."));
    strcpy(loc,".");
  }
  if(Letter_S && Letter_s && Letter_f){
    // here function pointers are used to make the function call
    function_ptr_S_s_f(loc, 0,providesize,searching_loc,dict_depth);
  }
  else if(Letter_S== 1){
    function_ptr_captial_S(loc,0);
  }
  else if(Letter_s == 1){
    function_ptr_small_s(loc,0,providesize);
  }
  else if(Letter_f==1){
    function_ptr_f(loc,0,searching_loc,dict_depth);
  }
  else{
    function_ptr_no_arg(loc,0);
  }

  return -1;
}


// working and explanation for the code



void function_one(char *loc_dic, const int rt)
{
    char *rs;
    char file_pt[1000];
    struct dirent *dt;
    DIR *dir = opendir(loc_dic);
    struct stat file_info;
    if (!dir)
        return;

    while ((dt = readdir(dir)) != NULL)
    {
        int x = rt;
        if (strcmp(dt->d_name, ".") != 0 && strcmp(dt->d_name, "..") != 0)
        {
            stat(dt->d_name, &file_info);
            int size = (int)file_info.st_size;
            int permission  = file_info.st_mode;
            if (dt->d_type != DT_REG){
                size=0;
            }
             for(int i=0;i<x;i++){
                    printf(" ");
                }
                printf("%s(%d:%o:%ld)\n",dt->d_name,size,permission,file_info.st_atime);
            strcpy(file_pt, loc_dic);
            strcat(file_pt, "/");
            strcat(file_pt, dt->d_name);
            function_one(file_pt, rt + 2);
        }
    }
    closedir(dir);
}



void function_two(char *loc_dic, const int rt,int providedsize)
{
    char *rs;
    char file_pt[1000];
    struct dirent *dt;
    DIR *dir = opendir(loc_dic);
    struct stat file_info;
    if (!dir)
        return;

    while ((dt = readdir(dir)) != NULL)
    {
        int x = rt;
        if (strcmp(dt->d_name, ".") != 0 && strcmp(dt->d_name, "..") != 0)
        {
            stat(dt->d_name, &file_info);
            int size = (int)file_info.st_size;
            int permission  = file_info.st_mode;
            if (dt->d_type != DT_REG){
                size=0;
            }
            if(providedsize<=size){
                for(int i=0;i<x;i++){
                    printf(" ");
                }
                printf("%s(%d:%o:%ld)\n",dt->d_name,size,permission,file_info.st_atime);
            }
            strcpy(file_pt, loc_dic);
            strcat(file_pt, "/");
            strcat(file_pt, dt->d_name);
            function_two(file_pt, rt + 2,providedsize);
        }
    }
    closedir(dir);
}

void function_three(char *loc_dic, const int rt,char* searching_loc,int dict_depth)
{
    char *rs;
    char file_pt[1000];
    struct dirent *dt;
    DIR *dir = opendir(loc_dic);
    struct stat file_info;
    if (!dir)
        return;

    while ((dt = readdir(dir)) != NULL)
    {
        int x = rt;
        if (strcmp(dt->d_name, ".") != 0 && strcmp(dt->d_name, "..") != 0)
        {
            stat(dt->d_name, &file_info);
            int size = (int)file_info.st_size;
            int permission  = file_info.st_mode;
            if (dt->d_type != DT_REG){
                size=0;
            }
            rs = strstr(dt->d_name, searching_loc);
            if(rs && rt<=dict_depth+1){
                for(int i=0;i<x;i++){
                    printf(" ");
                }
                printf("%s(%d:%o:%ld)\n",dt->d_name,size,permission,file_info.st_atime);
            }
            strcpy(file_pt, loc_dic);
            strcat(file_pt, "/");
            strcat(file_pt, dt->d_name);
            function_three(file_pt, rt + 2,searching_loc,dict_depth);
        }
    }
    closedir(dir);
}

void function_four(char *loc_dic, const int rt, int providedsize,char* searching_loc,int dict_depth)
{
    char *rs;
    char file_pt[1024];
    struct dirent *dt;
    DIR *dir = opendir(loc_dic);
    struct stat file_info;
    if (!dir)
        return;

    while ((dt = readdir(dir)) != NULL)
    {
        int x = rt;
        if (strcmp(dt->d_name, ".") != 0 && strcmp(dt->d_name, "..") != 0)
        {
            stat(dt->d_name, &file_info);
            int size = (int)file_info.st_size;
            int permission  = file_info.st_mode;
            if (dt->d_type != DT_REG){
                size=0;
            }
            rs = strstr(dt->d_name, searching_loc);
            if(rs && size <= providedsize && rt<=dict_depth+1){
                for(int i=0;i<x;i++){
                    printf(" ");
                }
                printf("%s(%d:%o:%ld)\n",dt->d_name,size,permission,file_info.st_atime);
            }
            strcpy(file_pt, loc_dic);
            strcat(file_pt, "/");
            strcat(file_pt, dt->d_name);
            function_four(file_pt, rt + 2,providedsize,searching_loc,dict_depth);
        }
    }
    closedir(dir);
}


void function_five(char *loc_dic, const int rt)
{
    char *rs;
    char file_pt[1024];
    struct dirent *dt;
    DIR *dir = opendir(loc_dic);
    struct stat file_info;

    // checking if the directory exist if not returning out
    if (dir!=NULL){
        printf(" ");
    }
    else{
        printf("directory could not be found");

         return;

    }
       
// using readdir function to read through the directory
    while ((dt = readdir(dir)) != NULL)
    {
        int x = rt;
        if (strcmp(dt->d_name, ".") != 0 && strcmp(dt->d_name, "..") != 0)
        {
            stat(dt->d_name, &file_info);
            int size = (int)file_info.st_size;
            int permission  = file_info.st_mode;
            if (dt->d_type != DT_REG){
                size=0;
            }
             for(int i=0;i<x;i++){
                    printf(" ");
                }
                printf("%s\n",dt->d_name);
            strcpy(file_pt, loc_dic);
            strcat(file_pt, "/");
            strcat(file_pt, dt->d_name);
            function_five(file_pt, rt + 2);
        }
    }
    closedir(dir);
}
