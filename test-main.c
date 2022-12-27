#include<stdio.h>
#include<time.h>
#include<stdlib.h>

void teacher(){
	printf("In teacher!");
//	char password[] = "librarian123";
	char password = 'l';
	printf("  Enter Password: ");
	printf("\nt> ");
//	char input[13];
//	scanf("%s", input);
//	fgets(input, 13, stdin);
	char input;
	scanf("%c", &input);
	if(input == password){
		printf("\n  Same Password!");
	}
	else
		printf("Different password!");
}

void student(){
	printf("In Student!");
}

void animate(){
	struct timespec ts = {.tv_sec = 0, .tv_nsec = 2.5e7};
	for(int i = 0; i < 100;i++){
		nanosleep(&ts, NULL);
		printf("\e[2;2H\e[2J");
		printf("\\");
		printf("\e[2;2H\e[2J");
		printf("|");
		printf("\e[2;2H\e[2J");
		printf("/");
		printf("\e[2;2H\e[2J");
		printf("-");
	}
}

void figletize(){
	printf("\e[1;1H\e[2J");
	char figlet[] = "  _     _ _     __  __             ____            \n | |   (_) |__ |  \\/  | __ _ _ __ / ___| _   _ ___ \n | |   | | '_ \\| |\\/| |/ _` | '_ \\\\___ \\| | | / __|\n | |___| | |_) | |  | | (_| | | | |___) | |_| \\__ \\\n |_____|_|_.__/|_|  |_|\\__,_|_| |_|____/ \\__, |___/\n                                         |___/";
	printf("%s\n", figlet);
}



int main(){
	animate();
	figletize();
	printf("  Library Management System v 0.0.1\n");
	printf("---------------------------------------------------------\n");
	printf("  Teacher or Student?");
	printf("\n  \"T\" or \"S\" ");
	char choice;
	int correct = 0;
	while(correct != 1){
		printf("\n$> ");
		scanf("%c", &choice);
		char dummy;
		scanf("%c", &dummy);
		if(choice == 'T' || choice == 't'){
			teacher();
			correct = 1;
		}
		else if (choice == 'S' || choice == 's'){
			student();
			correct = 1;
		}
		else{
			printf("\n+++--- Invalid ---+++\n");
//			correct = 0;
		}
	}	
	return 0;
}