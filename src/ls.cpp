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
#include <pwd.h>
#include <iomanip>
#include <cstdio>
#include <limits.h>
#include <grp.h>
#include <queue>
#include <libgen.h>
#include <fstream>

using namespace std;

bool is_l = false;
bool is_a = false;
bool is_R = false;

/*

   void recursive_listing(char *ptr)
   {

   DIR *dp;
   dirent *d;

   if((dp = opendir(ptr)) == NULL)
   perror("opendir");
   else{
   while((d = readdir(dp)) != NULL)
   {
   if(!strcmp(d->d_name,".") || !strcmp(d->d_name,".."))
   continue;

   if ((d->d_type & DT_DIR)== DT_DIR)
   {
   cout << d->d_name << ":" << endl;
   recursive_listing(d->d_name);	
   }
   else
   cout << d->d_name << endl;
   }
   return;
   }

   }

*/
void printstuff(const vector<char*>& arguments) {

		if (arguments.size() == 0 && is_l){


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
						<< ' ' << s.st_nlink;

				struct passwd *pws;
				pws = getpwuid(s.st_uid);
				if (pws== NULL){
						perror("error");
						exit(1);
				}
				char *ownr = pws->pw_name;

				cout << " " << ownr;
				struct group *grp = getgrgid(s.st_gid);
				if (grp== NULL){
						perror("error");
						exit(1);
				}

				char * grpname = grp -> gr_name;

				cout << " " << grpname<<" "
						<< s.st_size;

				string s_time = ctime(&s.st_mtime);
				cout<< " " << s_time;




		}

		else if(arguments.size()==0 && is_a){
				DIR *dir;
				struct dirent *ent;

				if ((dir = opendir (".")) != NULL) {
						/* print all the files and directories within directory */

						while ((ent = readdir (dir)) != NULL) {
								cout<< ent->d_name<<" ";
						}
						closedir (dir);
				} else {
						/* could not open directory */

						perror ("");
					//	return EXIT_FAILURE;
						exit(1);
				}
		}	







else if(arguments.size() == 0&& is_R){
























}






























//	for(auto i = 0, i < arguments.size(); i++){
for (auto i : arguments) {
		cout<<boolalpha << is_l<<endl;
		DIR *dir;
		struct dirent *ent;
		struct stat mystat;



		if (-1 == stat(i, &mystat)){

				perror(i);
				continue;	


		}



		if(S_ISDIR(mystat.st_mode)){
			
		   if ((dir = opendir (i)) != NULL) {
				while ((ent = readdir (dir)) != NULL) {
						cout<< ent->d_name<<" ";
				}
				closedir (dir);
		} else {
				/* could not open directory */
				   perror ("");
			
				   }


		}





		
		/* print all the files and directories within directory */
		/*
		   		   */

		DIR *mydir;
		struct dirent *myfile;
		
		vector<char*> pushes;
		if(S_ISDIR(mystat.st_mode)){


				if ((mydir = opendir (i)) != NULL) {
						while ((myfile = readdir (mydir)) != NULL) {
								cout<< myfile->d_name<<" ";
						}
						closedir (mydir);

				}
		}

		if (S_ISDIR(mystat.st_mode) && is_R){
				pushes.push_back(i);
		}


		if(is_l){

				if(S_ISDIR(mystat.st_mode)){


						if ((mydir = opendir (i)) != NULL) {
								while ((myfile = readdir (mydir)) != NULL) {
										if( -1 == stat(myfile->d_name, &mystat)){
												perror(myfile->d_name);
												continue;
										}

										//cout << "size = " << s.st_size << endl;

										//cout << "permissions = "
										if (S_ISDIR(mystat.st_mode)){
												cout<< "d";
										}
										else if (S_ISBLK(mystat.st_mode)){
												cout<< "b";
										}
										else if (S_ISFIFO(mystat.st_mode)){
												cout<< "p";
										}
										else if (S_ISSOCK(mystat.st_mode)){
												cout<< "s";
										}
										else if (S_ISLNK(mystat.st_mode)){
												cout<< "l";
										}
										else if (S_ISCHR(mystat.st_mode)){
												cout<< "c";
										}
										else{
												cout<< "-";
										}
										cout
												<< ((S_IRUSR & mystat.st_mode)?"r":"-")
												<< ((S_IWUSR & mystat.st_mode)?"w":"-")
												<< ((S_IXUSR & mystat.st_mode)?"x":"-")
												<< ((S_IRGRP & mystat.st_mode)?"r":"-")
												<< ((S_IWGRP & mystat.st_mode)?"w":"-")
												<< ((S_IXGRP & mystat.st_mode)?"x":"-")
												<< ((S_IROTH & mystat.st_mode)?"r":"-")
												<< ((S_IWOTH & mystat.st_mode)?"w":"-")
												<< ((S_IXOTH & mystat.st_mode)?"x":"-")
												<< ' ' << mystat.st_nlink;

										struct passwd *pws;
										pws = getpwuid(mystat.st_uid);
										if (pws== NULL){
												perror("error");
												exit(1);
										}
										char *ownr = pws->pw_name;

										cout << " " << ownr;
										struct group *grp = getgrgid(mystat.st_gid);
										if (grp== NULL){
												perror("error");
												exit(1);
										}

										char * grpname = grp -> gr_name;

										cout << " " << grpname<<" "
												<< mystat.st_size;

										string s_time = ctime(&mystat.st_mtime);
										cout<< " " << s_time<<endl;

										cout<< myfile->d_name<<" ";











								}
								
								
								
									closedir (mydir);

						}
				}
		}

								
								
								/*
									else{
									if(-1 == 
									cout<<myfile->d_name;
									}
									*/
								/*





								   mydir = opendir(argv[1]);
								   if (opendir(mydir)) 
								   while((myfile = readdir(mydir)) != NULL)
								   {
								//	stat(myfile->d_name, &mystat);    
								//	printf("%d",mystat.st_size);
								if(!strcmp(myfile->d_name,".") || !strcmp(myfile->d_name,".."))
								continue;
								cout<<' '<< myfile->d_name;
								}

*/
								closedir(mydir);
						}

						//	}
		}



		int main(int argc, char** argv)
		{
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

						else{
								arguments.push_back(argv[i]);
								/*

								   if (argc !=1){
								   DIR *mydir;
								   struct dirent *myfile;
								   struct stat mystat;

								   mydir = opendir(argv[1]);
								   if ((opendir(mydir) 
								   while((myfile = readdir(mydir)) != NULL)
								   {
								//	stat(myfile->d_name, &mystat);    
								//	printf("%d",mystat.st_size);
								if(!strcmp(myfile->d_name,".") || !strcmp(myfile->d_name,".."))
								continue;
								cout<<' '<< myfile->d_name;
								//	cout << "poopy"<<endl;
								}
								closedir(mydir);
								}
								*/

						}
				}


				printstuff(arguments);






				if(argc == 1){

						DIR *dp;
						dirent *d;

						if((dp = opendir(".")) == NULL)
								perror("opendir");

						while((d = readdir(dp)) != NULL)
						{
								//	if(
								//	cout<< endl<<d->d_name[0]<<endl;
								//	cout<< sub<<endl;
								//	if(!strcmp(d->d_name[0],".") || !strcmp(d->d_name,".."))
								//			continue;
								if (d->d_name[0] == '.')
										continue;


								cout << d->d_name << " ";
						}





						cout<<endl;



				}


				/*


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
				<< ' ' << s.st_nlink;

				struct passwd *pws;
				pws = getpwuid(s.st_uid);
				if (pws== NULL){
				perror("error");
				exit(1);
				}
				char *ownr = pws->pw_name;

				cout << " " << ownr;
				struct group *grp = getgrgid(s.st_gid);
				if (grp== NULL){
				perror("error");
				exit(1);
				}

				char * grpname = grp -> gr_name;

				cout << " " << grpname<<" "
				<< s.st_size;

				string s_time = ctime(&s.st_mtime);
				cout<< " " << s_time;



				}	

				if(is_R == true){

				recursive_listing((char*)".");	





















}

if (is_a==true){



}

//	cout<< argc<<endl<<argv[1][0]<<endl;

//if(argv[1][0] == 'l'&& argv[1][1]=='s'){
//		cout<< "only ls";
//}


//	if(arg
const char *path = ".";
vector<char *> pathset; 
pathset = getfiles(argc, argv,1);
unsigned i =0;




//opendir(".")

for (int j = 0; j< pathset.size(); j++)

path = pathset.at(i);
//	printa(path,false);i
*/


//	cout<<endl;


return 0;
}
