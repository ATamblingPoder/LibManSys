#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<string.h>

void figletize();
void librarian();
void initialize();
void read();
void print_students();
void librarian_options();

int *list_of_ids, number_of_ids = 0;
struct Student{
	int self_id, book_id;
	char name[20], password[20];
};

void librarian_options(){
	printf("\n1. Print all students");
	int choice_librarian_options;
	printf("\nl> ");
	scanf("%d", &choice_librarian_options);
	if(choice_librarian_options)
		print_students();
	else
		printf("Invalid Choice!");
}

void read(){
	FILE *reader;
	reader = fopen("students.dat", "rb");
	struct Student reading_reader;
	while((fread(&reading_reader, sizeof(reading_reader), 1, reader)) != 0){
		number_of_ids += 1;
	}
	printf("\n%d\n", number_of_ids);
	fclose(reader);
}

void print_students(){
	FILE *printer;
	printer = fopen("students.dat", "rb");
	struct Student reading_printer;
	for(int i = 0; i < number_of_ids; i++){
		fread(&reading_printer, sizeof(reading_printer), 1, printer);
		printf("\n%d\t%s\t%d\t%s", reading_printer.self_id, reading_printer.name, reading_printer.book_id, reading_printer.password);
	}
	fclose(printer);
}

void initialize(){
	struct Student first[3];
	first[0].self_id = 123456;
	first[1].self_id = 898595;
	first[2].self_id = 854808;
	first[0].book_id = -1;
	first[1].book_id = -1;
	first[2].book_id = -1;
	strcpy(first[0].name, "Ansh Goel");
	strcpy(first[1].name, "Sparsh Birla");
	strcpy(first[2].name, "Moulik Srivastava");
	strcpy(first[0].password, "anshgoel");
	strcpy(first[1].password, "sparshbirla");
	strcpy(first[2].password, "mouliksrivastava");
	FILE *fPtr;
	fPtr = fopen("students.dat", "rb");
	if(fPtr == NULL){
		FILE *fPtr1;
		fPtr1 = fopen("students.dat", "wb");
		for(int i = 0; i < 3; i++){
			fwrite(&(first[i]), sizeof((first[0])), 1, fPtr1);
		}
		fclose(fPtr1);

	}
	else{
		printf("Exists!");
		fclose(fPtr);
	}
}

void librarian(){
	figletize();
	printf("\n------ In librarian() ------\n");
	char password[] = "librarian123";
	int correct = 1;
	while(correct == 1){
		printf("\nEnter Password: ");
		printf("\nl> ");
		char input[13];
		scanf("%s", input);
		input[12] = '\0';
		char dummy = getchar();
		if(!strcmp(password, input)){
			figletize();
			printf("\nl> Login Successfull.\n");
			librarian_options();
			correct = 0;
		}
		else{
			printf("\n----|| Invalid password! ||----\n");
		}
	}
}


void student(){
	figletize();
	printf("\n------ In student() ------\n");
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
	printf("  Library Management System v 0.0.1\n");
	printf("---------------------------------------------------------\n");
}



int main(){
	initialize();
	read();
	animate();
	figletize();
	printf("  Librarian or Student?");
	printf("\n  \"L\" or \"S\" ");
	char choice;
	int correct = 0;
	while(correct != 1){
		printf("\n$> ");
		scanf("%c", &choice);
		char dummy;
		scanf("%c", &dummy);
		if(choice == 'L' || choice == 'l'){
			librarian();
			correct = 1;
		}
		else if (choice == 'S' || choice == 's'){
			student();
			correct = 1;
		}
		else
			printf("\n+++--- Invalid ---+++\n");
	}	
	return 0;
}