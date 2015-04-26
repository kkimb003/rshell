#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>
#include <vector>
#include <string>
#include <algorithm>
#include <cstddef>

using namespace std;

int main(int argc, char** argv)
{
	bool is_l = false;
	bool is_a = false;
	bool is_R = false;
	vector<char*> arguments;
	



	for (int i = 1; i < argc; i++){
			if (argv[i][0] == '-'){
					size_t argvlen = strlen(argv[i]);
					if(argvlen == 1){
							arguments.push_back(argv[i]);
						
					}
					else{
							for (size_t j = 1; j<argvlen; j++){
									if(argv[i][j] == 'a'){
											is_a = true;
											cout << "is_a"<<endl;
									}
									else if(argv[i][j]=='l'){
											is_l = true;
											cout << "is_l"<< endl;
									}
									else if(argv[i][j]=='R'){
											is_R = true;
											cout << "is_R"<<endl;
									}
									else{
											perror("error in first for loop");
											exit(1);
									}
							}
					}
			}

	}









	if(is_l == true){
	struct stat s;
 	stat(".", &s);

	//cout << "size = " << s.st_size << endl;

	//cout << "permissions = "
	if (S_ISDIR(s.st_mode)){
			cout<< "d";
	}
	else if (S_ISBLK(s.st_mode)){
			cout<< "b";
	}
	else if (S_ISFIFO(s.st_mode)){
			cout<< "p";
	}
	else if (S_ISSOCK(s.st_mode)){
			cout<< "s";
	}
	else if (S_ISLNK(s.st_mode)){
			cout<< "l";
	}
	else if (S_ISCHR(s.st_mode)){
			cout<< "c";
	}
	else{
			cout<< "-";
	}
	cout
	<< ((S_IRUSR & s.st_mode)?"r":"-")
	<< ((S_IWUSR & s.st_mode)?"w":"-")
	<< ((S_IXUSR & s.st_mode)?"x":"-")
	<< ((S_IRGRP & s.st_mode)?"r":"-")
	<< ((S_IWGRP & s.st_mode)?"w":"-")
	<< ((S_IXGRP & s.st_mode)?"x":"-")
	<< ((S_IROTH & s.st_mode)?"r":"-")
	<< ((S_IWOTH & s.st_mode)?"w":"-")
	<< ((S_IXOTH & s.st_mode)?"x":"-")
	<< endl;

	}																	

	cout<< argc<<endl<<argv[1][0]<<endl;

if(argv[1][0] == 'l'&& argv[1][1]=='s'){
		cout<< "only ls";
}


//	if(arg

	return 0;
}
