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
void add_students();
void print_books();
void remove_student();
void assign_book();
int does_it_exist_s(int id_to_check);
int does_it_exist_b(int b_id_to_check);

int *list_of_ids, number_of_ids = 0, number_of_b_ids = 0;
char dummy;
struct Student{
	int self_id, book_id;
	char name[20], password[20];
};

struct Book{
	int id;
	char b_name[50];
};

int does_it_exist_s(int id_to_check){
	FILE *reader_exists;
	reader_exists = fopen("students.dat", "rb");
	struct Student temp_checking_existence;
	while(fread(&temp_checking_existence, sizeof(temp_checking_existence), 1, reader_exists)){
		if(id_to_check == temp_checking_existence.self_id){
			fclose(reader_exists);
			return 1;
		}
	}
	fclose(reader_exists);
	return 0;
}

int does_it_exist_b(int b_id_to_check){
	FILE *reader_exists_b;
	reader_exists_b = fopen("books.dat", "rb");
	struct Book temp_checking_existence_b;
	while(fread(&temp_checking_existence_b, sizeof(temp_checking_existence_b), 1, reader_exists_b)){
		if(b_id_to_check == temp_checking_existence_b.id){
			fclose(reader_exists_b);
			return 1;
		}
	}
	fclose(reader_exists_b);
	return 0;
}

void remove_student(){
	figletize();
	printf("\n-----------------------------------");
	print_students();
	printf("\n-----------------------------------");
	printf("\nEnter Student ID to remove: \nl> ");
	int temp_id_to_remove;
	scanf("%d", &temp_id_to_remove);
	dummy = getchar();
}

void assign_book(){
	print_books();
	printf("\n----------------------------------");
	print_students();
	printf("\n----------------------------------");
	int correct = 0, temp_id, temp_b_id;
	struct Student reading_temp;
	while(!correct){
		printf("\nEnter Student Id: ");
		printf("\nl> ");
		scanf("%d", &temp_id);
		char dummy = getchar();
		correct = does_it_exist_s(temp_id);
	}
	int correct_b = 0;
	struct Book temp_book;
	while(!correct_b){
		printf("\nEnter Book Id: ");
		printf("\nl> ");
		scanf("%d", &temp_b_id);
		char dummy = getchar();
		correct_b = does_it_exist_b(temp_b_id);
	}
	FILE *reader, *writer;
	reader = fopen("students.dat", "rb");
	writer = fopen("temp_students.dat", "wb");
	struct Student temp1, temp2;
	while(fread(&temp2, sizeof(temp2), 1, reader)){
		temp1.self_id = temp2.self_id;
		strcpy(temp1.name, temp2.name);
		strcpy(temp1.password, temp2.password);
		if(temp2.self_id == temp_id){
			temp1.book_id = temp_b_id;
		}
		else
			temp1.book_id = temp2.book_id;
		fwrite(&temp1, sizeof(temp1), 1, writer);
	}
	fclose(reader);
	fclose(writer);
	remove("students.dat");
	rename("temp_students.dat", "students.dat");
}

/*
int in_num(int to_find, int *array_to_search){
	for(int i = 0; i < number_of_ids; i++){
		printf("%d", *(array_to_search + i));
		if(to_find == *(array_to_search + i))
			return 1;
	}
	return 0;
}
*/



void add_students(){
	printf("Enter number of student records to add: ");
	printf("\nl> ");
	int num_add_students;
	scanf("%d", &num_add_students);
	dummy = getchar();
	struct Student adding_adding_students;
	for(int i = 0; i < num_add_students; i++){
		char temp_name[20], temp_password[20];
		int temp_self_id, temp_book_id = -1, temp_id_exists;
		printf("Enter Name: \nl> ");
		fgets(temp_name, 20, stdin);
		temp_name[strcspn(temp_name, "\n")] = 0;
		temp_name[19] = '\0';
		temp_self_id = 0;
		temp_id_exists = 1;
		while(temp_id_exists){
			printf("\nEnter ID: \nl> ");
			scanf("%d", &temp_self_id);
			dummy = getchar();
			temp_id_exists = does_it_exist_s(temp_self_id);
			if(temp_id_exists)
				printf("\n------ ID already exists ------\n");
		}
		printf("\nEnter Student's Password: \nl> ");
		scanf("%s", temp_password);
		dummy = getchar();
		adding_adding_students.self_id = temp_self_id;
		adding_adding_students.book_id = temp_book_id;
		strcpy(adding_adding_students.name, temp_name);
		strcpy(adding_adding_students.password, temp_password);
		FILE *adding_students;
		adding_students = fopen("students.dat", "ab");
		fwrite(&adding_adding_students, sizeof(adding_adding_students), 1, adding_students);
		fclose(adding_students);
	}
}

void librarian_options(){
	printf("\n1. Print all students");
	printf("\n2. Add Students");
	printf("\n3. Show Books");
	printf("\n4. Assign book to student");
	printf("\n5. Remove Student");
	printf("\n0 to exit. ");
	int choice_librarian_options = 1;
	while(choice_librarian_options){
		printf("\nl> ");
		scanf("%d", &choice_librarian_options);
		dummy = getchar();
		if(choice_librarian_options == 1)
			print_students();
		else if(choice_librarian_options == 2)
			add_students();
		else if(choice_librarian_options == 3)
			print_books();
		else if(choice_librarian_options == 4)
			assign_book();
	}
}

void read(){
	FILE *reader;
	reader = fopen("students.dat", "rb");
	struct Student reading_reader;
	while((fread(&reading_reader, sizeof(reading_reader), 1, reader)) != 0){
		number_of_ids += 1;
	}
	int the_ids[number_of_ids];
	fseek(reader, 0, SEEK_SET);
	for(int i = 0; i < number_of_ids; i++){
		fread(&reading_reader, sizeof(reading_reader), 1, reader);
		the_ids[i] = reading_reader.self_id;
	}
	list_of_ids = &the_ids[0];
	printf("\n");
	for(int i = 0; i < number_of_ids; i++)
		printf(" %d ", *(list_of_ids + i));
	printf("\n%d\n", number_of_ids);
	fclose(reader);
	FILE *breader;
	breader = fopen("books.dat", "rb");
	struct Book b_reading_reader;
	while((fread(&b_reading_reader, sizeof(b_reading_reader), 1, breader)) != 0){
		number_of_b_ids += 1;
	}
	printf("\n%d\n", number_of_b_ids);
	fclose(breader);
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

void print_books(){
	figletize();
	FILE *b_printer;
	b_printer = fopen("books.dat", "rb");
	struct Book b_reading_printer;
	for(int i = 0; i < number_of_b_ids; i++){
		fread(&b_reading_printer, sizeof(b_reading_printer), 1, b_printer);
		printf("\n%d\t%s", b_reading_printer.id, b_reading_printer.b_name);
	}
	fclose(b_printer);
}

void initialize(){
	struct Student first[3];
	struct Book b_first[3];
	b_first[0].id = 9999;
	b_first[1].id = 1122;
	b_first[2].id = 8869;
	strcpy(b_first[0].b_name, "Sherlock Holmes");
	strcpy(b_first[1].b_name, "The Alchemist");
	strcpy(b_first[2].b_name, "Murder on The Orient Express");
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
	FILE *bPtr;
	bPtr = fopen("books.dat", "rb");
	if(bPtr == NULL){
		FILE *bPtr1;
		bPtr1 = fopen("books.dat", "wb");
		for(int i = 0; i < 3; i++){
			fwrite(&(b_first[i]), sizeof((b_first[0])), 1, bPtr1);
		}
		fclose(bPtr1);

	}
	else{
		printf("Exists!");
		fclose(bPtr);
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
		dummy = getchar();
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