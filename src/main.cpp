#include <iostream>
#include <string>
#include <unistd.h>
#include <errno.h>
#include <limits>
#include <sys/stat.h>
#include <fcntl.h>
#include <pwd.h>
#include <cstdio>
#include <stdio.h>
#include <sys/wait.h>
#include <cstring>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/param.h>
#include <vector>
#include <string.h>
#include <queue>
#include <signal.h>
using namespace std;



void handler(int foo){
		if(foo == SIGINT){
				int pid = getpid();
				if(pid == -1){
						perror("pid");
						exit(1);
				}
				if(pid == 0)
						exit(0);
						cout<< endl;
				return;
		}
}




/*
bool flag1 = false;
bool flag2 = false;
bool flag3 = false;
int count1 = 0;
int count2 = 0;
int count3 = 0;
void handle1(int x)
{
		flag1 = true;
		count1++;
}
void handle2(int x)
{
		flag2 = true;
		count2++;

}

void handle3(int x)
{
		flag3 = true;
		count3++;

}


int main()
{
		struct sigaction newact,oldact;

		newact.sa_handler = handle1;
		sigemptyset (&newact.sa_mask);
		newact.sa_flags = SA_SIGINFO;
		if(-1 == sigaction(SIGINT,&newact, NULL)){
				perror("error with ^C");
				exit(1);
		}
		newact.sa_handler = handle2;
		if(-1 == sigaction (SIGQUIT, &newact, NULL)){
				perror("Error with SIGQUIT");
				exit(1);
		}
		newact.sa_handler = handle3;
		if(-1 == sigaction (SIGTSTP, &newact, NULL)){
				perror("Error with SIGTSTP");
				exit(1);
		}

		while(1){
				if(flag3 && (count3 == 3)){


*/

bool isinput(vector<char*> singleInput);

int main(int argc, char **argv){
		struct sigaction newact;

		newact.sa_handler = handler;
		sigemptyset (&newact.sa_mask);
		newact.sa_flags = SA_SIGINFO;
		if(-1 == sigaction(SIGINT,&newact, NULL)){
				perror("error with ^C");
				exit(1);
		}
		newact.sa_handler = handler;
		if(-1 == sigaction (SIGTSTP, &newact, NULL)){
				perror("Error with SIGTSTP");
				exit(1);
		}

	
		struct passwd * pass= getpwuid(getuid());
		if(pass == NULL){
				perror("pass");
				exit(1);
		}
		char *user = pass->pw_name;
		char charhost[100];
		if(-1 == gethostname(charhost, sizeof charhost)){
				perror("host");
				exit(1);
		}
		string host = charhost;	
		
		if(string::npos != host.find('.') ){
				host.resize(host.find('.'));
		}



		string input;
		while(1){
				/////////////////////////////////outputs the user info/////////////////////////////////////
				char cwd[BUFSIZ];
				if(getcwd(cwd, sizeof(cwd)) == NULL){
						perror("cwd");
						exit(1);
				}
				cout << "~" << cwd << ' '
				<< user << '@' << host << ' '
				<< '$' << ' ';
			
				   ////////////////////gets input from user and searches for # ,||, ; , or &&///////////////////
				cin.clear();
				getline(cin, input);
				size_t add = 0;
				size_t search = input.find("#");
				if (search == 0){

						input = " ";
				}
				else if (search > 0){

						input = input.substr(0,search);
				}

				search = 0;
				while (search < input.size()){		//finds the first instance of '&&'
						if (search == 0){
								search = input.find("&&");
						}
						else{
								search = input.find("&&",search+2, 2);
						}
						if(add!=search && search != string::npos ){
								input.replace(search,2," && ");
								add = search + 2;
						}
				}
				search = 0;
				add = 0;
				while(search < input.size()){		//finds the first instance of ';'
						if(search == 0)
								search = input.find(";");
						else
								search = input.find(";",search+1,1);
						if(add!=search && search != string::npos){
								input.replace(search,1," ; ");
								add = search+1;
						}
				}
				search = 0;
				add = 0;
				while(search < input.size()){		//finds the first instance of 'tab'
						if(search == 0)
								search = input.find("\t");

						else
								search = input.find("\t",search+1,1);
						if(add!=search && search != string::npos){
								input.replace(search,1," ");
								add = search+1;
						}
				}
				search = 0;
				add = 0;
				while(search < input.size()){		//finds the first instance of ||
						if(search == 0)
								search = input.find("||");
						else
								search = input.find("||",search+2,2);
						if(add!=search && search != string::npos ){
								input.replace(search,2," || ");
								add = search+2;
						}
				}
				///////////////////////////////parses the input//////////////////////
				if(input.size() != 0){
						vector <char*> comVector;
						char* lots = (char*)input.c_str();
						char* token  = strtok(lots, " ");

						while(token != NULL){			//parses it
								comVector.push_back(token);
								token = strtok(NULL, " ");
						}

						////////////////////////the magical meaty part//////////////////////////

						bool currCom = true;

						bool comOne;

						vector<char*> multInputs;	

						int Operator = 0;










						for(size_t i = 0; i < comVector.size(); ++i){			

								string stringy = comVector.at(i);
								if( stringy.compare("exit")!=0){//tried comVector.at(i) ==0 and it said thats a no no

										if(multInputs.size() !=0 && stringy.compare(";")==0){ 
												currCom = false;
												comOne = isinput(multInputs);
												multInputs.clear();		
										}	
										else if(multInputs.size() != 0 && stringy.compare("||")==0){
												if(currCom == true){
														currCom = false;
														comOne = isinput(multInputs);

												}

												else if(comOne== false){
														comOne = isinput(multInputs);
												}	
												Operator = 2;
												multInputs.clear();

										}

										else if(multInputs.size() != 0 && stringy.compare("&&")==0){
												if(currCom == true){
														comOne = isinput(multInputs);
														currCom = false;
												}

												else if(comOne== true){
														comOne = isinput(multInputs);
												}

												Operator = 1;

												multInputs.clear();


										}
										else{
												if(currCom && comVector.size() == i+1)	{

														multInputs.push_back(comVector[i]);
														comOne = isinput(multInputs);
														i = comVector.size()+1;
												}

												else if(!currCom && comVector.size() == i+1){
														if(!comOne && Operator == 2){	

																multInputs.push_back(comVector[i]);
																comOne = isinput(multInputs);
														}
														else if(comOne && Operator ==2 ){//do nothing
														}


														else if(comOne && Operator == 1){	

																multInputs.push_back(comVector[i]);
																comOne = isinput(multInputs);
														}
														else if(!comOne && Operator ==1){//do nothing
														}


														else{					
																multInputs.push_back(comVector[i]);
																comOne = isinput(multInputs);
														}
														i = comVector.size() + 1;
												}		
												else{						
														multInputs.push_back(comVector[i]);
												}
										}	
								}
								else{
										exit(1);
								}
						}
				}
		}	

		return 0;
}
/////////////////////////forks and compares input with execvp stuffs (mostly given)///////////////////
bool isinput(vector<char*> singleInput){
		/////////////cd/////////////////
				int ret;
		string convString= singleInput[0];

		if(convString.compare("cd") == 0){
				//if((old_path = getenv("PWD")) == -1) {
				//		perror("getenv: PWD");
				//		return -1; 
				//}
				if(singleInput.size() < 2)	{
						if(chdir(getenv("HOME"))== -1){
								//chdir(getenv("HOME"));
								perror("single input cd");
								ret = -1;
						}
				}
				else{
						convString = singleInput[1];
						if(chdir(singleInput[1]) == -1){
								perror("CD");
								ret = -1;
						}
						else{
								ret = 0;
						}
				}
				return ret;
		}


		/*
		   std::string convString= singleInput[0];

		   int ret;
		   if(convString.compare("cd") == 0){

		   char* new_path, * old_path;

		   if((old_path = getenv("PWD")) == NULL) { 
		   perror("getenv: PWD"); 
		   return -1; 
		   }

		   if(singleInput.size() <2) {
		   if((new_path = getenv("HOME")) == NULL) { 
		   perror("getenv: HOME");
		   return -1;
		   }
		   } 
		   else if(singleInput.at(1) =="-") {
		   if((new_path = getenv("OLDPWD"))==NULL) {
		   perror("getenv: OLDPWD"); 
		   return -1;
		   }
		   } else
		   new_path = singleInput.at(1);


		   if(chdir(new_path) != 0) { 
		   perror("chdir"); 
		   return -1;
		   }

// get updated working dir 
if((new_path = getcwd(NULL, 0)) == NULL) { 
perror("getcwd"); 
return -1;
}

// only update env variables if everything else was correct
if(setenv("PWD", new_path, 1) != 0) { 
perror("setenv: PWD");
return -1; 
}
if(setenv("OLDPWD", old_path, 1) != 0) { 
perror("setenv: OLDPWD"); 
return -1; 
}

return 0;
}*/
////////////////////////////////////
int inputSize = singleInput.size()+1;
char **nextInputs = new char*[inputSize];		
for(int a = 0;a < inputSize-1;a++){		
		nextInputs[a] =singleInput[a];
}
nextInputs[inputSize-1] = '\0';
int pid = fork();
if (pid == -1)
{
		perror("fork"); 
		exit(1);
}
else if (pid == 0) 
{
		ret = execvp(nextInputs[0], nextInputs);
		if(-1==ret){
				perror("execvp");
		}

		exit(1); 
}
else 
{
		int value = waitpid(pid,&ret,0);
		if (-1 == value) 
		{                      
				perror("wait");
				exit(1);
		}
		if (ret > 0 )
				return false;


}
if (ret == 0)
		return true;

		else
		return false;
		}


