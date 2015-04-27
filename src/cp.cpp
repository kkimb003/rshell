#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <fstream>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include "Timer.h"

using namespace std;

int main(int argc, char** argv){
    Timer t1;
    Timer t2;
    Timer t3;
    
    //Status of the directory
    struct stat inStat;
    struct stat outStat;
    
    //ERROR CHECKS
    int argument = 0;
    if( argc < 3){
        cout << "Error, not enough arguments";
        exit(1);
    }
    if(stat(argv[1], &inStat) == -1){
        perror(argv[1]);
        exit(1);
    }
    if(stat(argv[2], &outStat) != -1){
        printf("File already exists");
        exit(1);
    }
    if(S_ISDIR(outStat.st_mode)){
        printf("Cannot copy to directory\n");
        exit(1);
    }

    //========Method 1============
    if(argument == 0 ){
        t1.start();
        ifstream inFile (argv[1]);
        ofstream outFile (argv[2]);
        char c;
        while(inFile.get(c))
            outFile << c;
        double etime;
        printf("read/stream at a time:\n");
        t1.elapsedWallclockTime(etime);
        printf("Wall clock: %f\n", etime);
        t1.elapsedUserTime(etime);
        printf("User clock: %f\n", etime);
        t1.elapsedSystemTime(etime);
        printf("System clock: %f\n", etime);
    //============================================
    }else if(argument == 2){//=======Method 2===========
        t2.start();
        int fd1 = open(argv[1], O_RDONLY);
        if(fd1 == -1) {
            perror(argv[1]);
            exit(1);
        }
        int fd2 = creat(argv[2], outStat.st_mode);
        if(fd2 == -1) {
            perror(argv[2]);
        exit(1);
        }
        char c;
        int rret = read(fd1, &c, 1);
        while (rret) {
            if (write(fd2, &c, rret) == -1) {
                perror("write");
                exit(1);
            }
        rret = read(fd1, &c, 1);
        }
        if (close(fd1) == -1) {
            perror("close fd1");
            exit(1);
        }
        if (close(fd2) == -1) {
            perror("close fd2");
            exit(1);
        }
        double etime;
        printf("read/write 1 char at a time:\n");
        t2.elapsedWallclockTime(etime);
        printf("Wall clock: %f\n", etime);
        t2.elapsedUserTime(etime);
        printf("User clock: %f\n", etime);
        t2.elapsedSystemTime(etime);
        printf("System clock: %f\n", etime);

    //=========================================
    }else if(argument == 3|| argument == 1){//======Method 3=========
        t3.start();
        int iF = open(argv[1],O_RDONLY);
        int oF = creat(argv[2], outStat.st_mode);
        if(iF<0){
            perror("In File Error");
            exit(1);
        }if(oF<0){
            perror("Out File Error");
            exit(1);
        }       
        int size;
        char c[BUFSIZ];
        if(-1 == (size = read(iF, c, sizeof(c)))){
            perror("Read error");
            exit(1);
        }
        while(size > 0){
            if(-1 == write(oF, c, size)){
                perror("Write error");
                exit(1);
            }
            if(-1 == (size = read(iF, c, sizeof(c)))){
                perror("Read error");
                exit(1);
            }
        }
        if(-1 == close(iF)){
            perror("Close error");
            exit(1);
        }
        if(-1 == close(oF)){
            perror("Close error");
            exit(1);
        }
        double etime;
        printf("read/buffer char at a time:\n");
        t3.elapsedWallclockTime(etime);
        printf("Wall clock: %f\n", etime);
        t3.elapsedUserTime(etime);
        printf("User clock: %f\n", etime);
        t3.elapsedSystemTime(etime);
        printf("System clock: %f\n", etime);
    }else{
        cout <<"Method does not exist" << endl;
        exit(1);
    }

        return 0;
}
