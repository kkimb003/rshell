#include <cstdlib>
#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <iostream>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

using namespace std;


//TRY CHDIR()

void printArg(int argc, char **argv){
    for(unsigned int i = 0; i < argc; i++){
        cout << "pos" << i << ": " << argv[i] << endl;
    }
}

void isDirectoryInception(const char* path){
    /*int ret = -1;
    if((ret = chdir(path)) == -1){
        perror("path");
        exit(1);
    }*/

    /*char fullpath = [PATH_MAX+1];
    if( realpath(path, fullpath) == NULL){
        perror("realpath");
        exit(1);
    }*/
    DIR *dir;

    if((dir = opendir(path)) == NULL ){
        perror("opendir");
        exit(1);
    }

    dirent *dirEntry;
    struct stat s;
	string q;
    while ( (dirEntry = readdir(dir) ) != NULL){
    	q = (string)path + '/' + (string)dirEntry->d_name;
        if(-1 == stat(q.c_str(), &s)){
            perror("stat1:");
            exit(1);
        }

        if(S_ISDIR(s.st_mode)){ //case: there is a subdirectory
            if(!strcmp(dirEntry->d_name, ".")) continue;
            if(!strcmp(dirEntry->d_name, "..")) continue;

            //string path_s(path);

            isDirectoryInception(/*dirEntry->d_name*/q.c_str());
        }
        else if(S_ISREG(s.st_mode)){ //case: there is a file
            if(-1 == unlink(q.c_str())){
               perror("unlink");
               exit(1);
            }
        }
    }

    if(-1 == closedir(dir)){
        perror("closedir");
        exit(1);
    }
    if(rmdir(path) == -1)
    	perror("unlink dir");
}

int main(int argc, char** argv){
    //printArg(argc, argv);

    if(argc < 1){
        cout << "no parameters passed in." << endl;
        exit(1);
    }

    if(argv[1][0] == 'r'){
        if(argv[1][1] == 'm'){
            if(argv[2][0] == '-' && argv[2][1] == 'r'){ //directory
                for(unsigned int i = 3; i < argc; i++){
                    struct stat s;
                    if(-1 == stat(argv[i], &s)){
                        perror("stat");
                        exit(1);
                    }

                    isDirectoryInception(argv[i]);

                    /*if(S_ISDIR(s.st_mode)){
                        rmdir(argv[i]);
                    }*/
                }
            }

            else{ //file
                for(unsigned int i = 2; i < argc; i++){
                    if(-1 == unlink(argv[i])){
                        perror("rm");
                        exit(1);
                    }
                }
            }
        }
    }
    else if(argv[1][0] == 'm' && argv[1][1] == 'v'){
        if(argc < 3){
            cout << "too few parameters" << endl;
            exit(1);
        }
        else{
            printArg(argc, argv);
            struct stat s;
            if(-1 == stat(argv[2], &s)){
                perror("stat");
                exit(1);
            }
            if(S_ISREG(s.st_mode)){
                struct stat s1;
                cout << "test1" << endl;
                if(-1 == stat(argv[3], &s1)){
                    link(argv[2], argv[3]);
                    unlink(argv[2]);
                }
                else if(S_ISDIR(s1.st_mode)){
                    cout << "test2" << endl;
                    string slash = "/";
                    const char* slash2 = slash.c_str();
                    strcat(argv[3], slash2);
                    strcat(argv[3], argv[2]);
                    if(-1 == link(argv[2], argv[3])){
                        perror("link");
                        exit(1);
                    }
                    if(-1 == unlink(argv[2])){
                        perror("unlink");
                        exit(1);
                    }
                }
            }
        }
    }
    return 0;
}

