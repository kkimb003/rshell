#include <iostream>
#include <string>
#include <unistd.h>
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

bool isinput(vector<char*> singleInput);

int main(int argc, char **argv){
	
	string input;
	while(1){
/////////////////////////////////outputs the user info/////////////////////////////////////		
		if(getlogin() == NULL){				
			perror("getlogin");
			exit(1);
		}
		char name[BUFSIZ];
		gethostname(name,BUFSIZ);
		cout << getlogin() << "@" << name << "$ ";
/////////////////////gets input from user and searches for # ,||, ; , or &&///////////////////

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
		int status;
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
				status = execvp(nextInputs[0], nextInputs);
			if(-1==status){
				perror("execvp");
			}
			
			exit(1); 
		}
		else 
		{
			int value = waitpid(pid,&status,0);
			if (-1 == value) 
			{                      
				perror("wait");
				exit(1);
			}
			if (status > 0 )
					return false;


		}
		if (status == 0)
				return true;
			
		else
				return false;
		}


