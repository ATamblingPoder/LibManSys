#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<string.h>

void clear();
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
void add_books();
//void remove_book();
void print_requests();
void approve_request();
void remove_request();
int does_it_exist_s(int id_to_check);
int does_it_exist_b(int b_id_to_check);
int does_it_exist_r(int r_id_to_check);
void request_a_book(int students_current_id);
void return_a_book(int students_current_id);
void student_options();
int check_password(char password_to_check[]);
int students_current_id;
char student_current_password[20];

int *list_of_ids, number_of_ids = 0, number_of_b_ids = 0, number_of_requests = 0;
char dummy;
struct Student{
	int self_id, book_id;
	char name[20], password[20];
};

struct Book{
	int id;
	char b_name[50];
};

struct Requests{
	int b_id, self_id;
};

void return_a_book(int students_current_id){
	int is_book_issued;
	struct Student checking_if_issued;
	FILE *checkingissuance;
	checkingissuance = fopen("students.dat", "rb");
	while(fread(&checking_if_issued, sizeof(checking_if_issued), 1, checkingissuance)){
		if(checking_if_issued.self_id == students_current_id){
			is_book_issued = checking_if_issued.book_id;
		}
	}
	fclose(checkingissuance);
	if(is_book_issued == -1){
		figletize();
		printf("\n!!!!!!!!!!!!!!!!!!- YOU HAVE NO BOOK ISSUED -!!!!!!!!!!!!!!!!!\n");
	}
	else{
		FILE *bookreading, *bookwriting;
		bookreading = fopen("students.dat", "rb");
		bookwriting = fopen("temp_students.dat", "wb");
		struct Student tid1, tid2;
		while(fread(&tid1, sizeof(tid1), 1, bookreading)){
			tid2.self_id = tid1.self_id;
			strcpy(tid2.name, tid1.name);
			strcpy(tid2.password, tid1.password);
			printf("\n%d", tid1.book_id);
			if(tid1.self_id == students_current_id){
				tid2.book_id = -1;
			}
			else
				tid2.book_id = tid1.book_id;
			fwrite(&tid2, sizeof(tid2), 1, bookwriting);
		}
		fclose(bookwriting);
		fclose(bookreading);
		remove("students.dat");
		rename("temp_requests.dat", "students.dat");
	}
}

void request_a_book(int students_current_id){
	if(does_it_exist_r(students_current_id)){
		figletize();
		printf("\n!!!!!!!!!- YOUR ARE ALREADY IN THE REQUESTS DATABASE -!!!!!!!!\n");
	}
	else{
		print_books();
		int chosen_book = 0;
		while(!does_it_exist_b(chosen_book)){
			printf("\nEnter BookID to request: \ns> ");
			scanf("%d", &chosen_book);
			dummy = getchar();
			if(!does_it_exist_b(chosen_book))
				printf("\nBook doesnt exist in database. ");
		}
		FILE *rwriter;
		rwriter = fopen("requests.dat", "ab");
		struct Requests temp_requests;
		temp_requests.self_id = students_current_id;
		temp_requests.b_id = chosen_book;
		fwrite(&temp_requests, sizeof(temp_requests), 1, rwriter);
		fclose(rwriter);
	}

}

int check_password(char password_to_check[]){
	char correct_password[20];
	FILE *passchecker;
	struct Student passchecking;
	passchecker = fopen("students.dat", "rb");
	while(fread(&passchecking, sizeof(passchecking), 1, passchecker)){
		if(passchecking.self_id == students_current_id){
			strcpy(correct_password, passchecking.password);
		}
	}
	fclose(passchecker);
	return !strcmp(correct_password, password_to_check);
}

void student(){
	figletize();
	int does_my_id_exist = 0;
	while(!does_my_id_exist){
		printf("\nEnter Your ID: \ns> ");
		scanf("%d", &students_current_id);
		dummy = getchar();
		does_my_id_exist = does_it_exist_s(students_current_id);
		if(!does_my_id_exist)
			printf("\nNo Such ID in the database");
	}
	int correct_password_entered = 0;
	while(!correct_password_entered){
		printf("\nEnter Your Password \ns> ");
		scanf("%s", student_current_password);
		dummy = getchar();
		student_current_password[strcspn(student_current_password, "\n")] = 0;
		correct_password_entered = check_password(student_current_password);
		if(!correct_password_entered){
			printf("\n!!!!!!!!!!!!!!!!!- WRONG PASSWORD -!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
		}
	}
	student_options();

}

void student_options(){
	figletize();
	int choice_student = 1;
	while(choice_student){
		printf("\nEnter Choice");
		printf("\n1. View Available Books");
		printf("\n2. Request a book");
		printf("\n3. Return your book");
		printf("\n0 to exit.");
		printf("\ns> ");
		scanf("%d", &choice_student);
		dummy = getchar();
		if(choice_student == 1)
			print_books();
		else if(choice_student == 2)
			request_a_book(students_current_id);
		else if(choice_student == 3)
			return_a_book(students_current_id);
	}
}

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

int does_it_exist_r(int r_id_to_check){
	FILE *reader_exists_r;
	reader_exists_r = fopen("requests.dat", "rb");
	struct Requests temp_checking_existence_r;
	while(fread(&temp_checking_existence_r, sizeof(temp_checking_existence_r), 1, reader_exists_r)){
		if(r_id_to_check == temp_checking_existence_r.self_id){
			fclose(reader_exists_r);
			return 1;
		}
	}
	fclose(reader_exists_r);
	return 0;
}

void print_requests(){
//	figletize();
	read();
	FILE *printer_request;
	printer_request = fopen("requests.dat", "rb");
	struct Requests reading_requests;
	printf("\n----------------------- REQUESTS -----------------------------\n");
	printf("\nBook ID\t\tStudent ID");
	while(fread(&reading_requests, sizeof(reading_requests), 1, printer_request)){
		printf("\n%d\t\t%d",reading_requests.b_id, reading_requests.self_id);
	}
	fclose(printer_request);
	printf("\n--------------------------------------------------------------\n");
}

void approve_request(){
	figletize();
	print_requests();
	printf("\n-- ASSIGN BOOK TO STUDENT THEN REMOVE REQUEST --\n");
}

void remove_request(){
	figletize();
	print_requests();
	int student_id_to_remove, does_student_exist = 0;
	while(!does_student_exist){
		printf("\nEnter Student ID for whose request has to be removed: ");
		printf("\nl> ");
		scanf("%d", &student_id_to_remove);
		dummy = getchar();
		does_student_exist = does_it_exist_r(student_id_to_remove);
		if(!does_student_exist)
			printf("\nEither invalid StudentID or Student has no requested books\n");
	}
	struct Requests temp_to_edit, temp_to_write;
	FILE *to_read, *to_write;
	to_read = fopen("requests.dat", "rb");
	to_write = fopen("temp_requests.dat", "wb");
	while(fread(&temp_to_edit, sizeof(temp_to_edit), 1, to_read)){
		if(temp_to_edit.self_id != student_id_to_remove){
			temp_to_write.self_id = temp_to_edit.self_id;
			temp_to_write.b_id = temp_to_edit.b_id;
			fwrite(&temp_to_write, sizeof(temp_to_write), 1, to_write);
		}
	}
	fclose(to_read);
	fclose(to_write);
	remove("requests.dat");
	rename("temp_requests.dat", "requests.dat");
}

void remove_student(){
	figletize();
	printf("\n-------------------------------------------------------------\n");
	print_students();
	printf("\n-------------------------------------------------------------\n");
	int temp_id_to_remove_exists = 0, temp_id_to_remove;
	while(!temp_id_to_remove_exists){
		printf("\nEnter Student ID to remove: \nl> ");
		scanf("%d", &temp_id_to_remove);
		dummy = getchar();
		temp_id_to_remove_exists = does_it_exist_s(temp_id_to_remove);
		if(!temp_id_to_remove_exists)
			printf("\n Student ID not in database. ");
	}
	printf("\nID TO REMOVE IS %d\n", temp_id_to_remove);
	struct Student tempid1, tempid2;
	FILE *reading, *writing;
	reading = fopen("students.dat", "rb");
	writing = fopen("temp_students.dat", "wb");
	while(fread(&tempid1, sizeof(tempid1), 1, reading)){
		if(tempid1.self_id != temp_id_to_remove){
			tempid2.self_id = tempid1.self_id;
			tempid2.book_id = tempid1.book_id;
			strcpy(tempid2.name, tempid1.name);
			strcpy(tempid2.password, tempid1.password);
			fwrite(&tempid2, sizeof(tempid2), 1, writing);
		}
	}
	fclose(reading);
	fclose(writing);
	remove("students.dat");
	rename("temp_students.dat", "students.dat");

}
/*
void remove_book(){
	figletize();
	printf("\n-----------------------------------");
	print_books();
	printf("\n-----------------------------------");
	int temp_b_id_to_remove_exists = 0, temp_b_id_to_remove;
	while(!temp_b_id_to_remove_exists){
		printf("\nEnter Book ID to remove: \nl> ");
		scanf("%d", &temp_b_id_to_remove);
		dummy = getchar();
		temp_b_id_to_remove_exists = does_it_exist_b(temp_b_id_to_remove);
		if(!temp_b_id_to_remove_exists)
			printf("\n Book ID not in database. ");
	}
	printf("\nID TO REMOVE IS %d\n", temp_b_id_to_remove);
	struct Book tempbid1, tempbid2;
	FILE *breading, *bwriting;
	breading = fopen("books.dat", "rb");
	bwriting = fopen("temp_books.dat", "wb");
	while(fread(&tempbid1, sizeof(tempbid1), 1, breading)){
		if(tempbid1.id != temp_b_id_to_remove){
			tempbid2.id = tempbid1.id;
			strcpy(tempbid2.b_name, tempbid1.b_name);
			fwrite(&tempbid2, sizeof(tempbid2), 1, bwriting);
		}
	}
	fclose(breading);
	fclose(bwriting);
	remove("books.dat");
	rename("temp_books.dat", "books.dat");

}
*/

void assign_book(){
	print_requests();
	printf("\n--------------------------------------------------------------\n");
	int correct = 0, temp_id, temp_b_id;
	struct Student reading_temp;
	while(!correct){
		printf("\nEnter Student Id: ");
		printf("\nl> ");
		scanf("%d", &temp_id);
		char dummy = getchar();
		correct = does_it_exist_s(temp_id);
	}
	print_books();
	int correct_b = 0;
	struct Book temp_book;
	while(!correct_b){
		printf("\nEnter Book Id: ");
		printf("\nl> ");
		scanf("%d", &temp_b_id);
		char dummy = getchar();
		correct_b = does_it_exist_b(temp_b_id);
		if(!correct_b)
			printf("\n!!!!!!- BOOK DOES NOT EXIST IN DATABASE -!!!!!!\n");
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

void add_students(){
	printf("\nEnter number of student records to add: ");
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
				printf("\n!!!!!!!!!!!!!!!!- ID ALREADY EXISTS -!!!!!!!!!!!!!!!!!!!!!!!\n");
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

void add_books(){
	read();
	print_books();
	printf("Enter number of books to add: ");
	printf("\nl> ");
	int num_add_books;
	scanf("%d", &num_add_books);
	dummy = getchar();
	struct Book adding_adding_books;
	for(int i = 0; i < num_add_books; i++){
		char temp_b_name[50];
		int id, temp_b_id_exists;
		printf("Enter Name: \nl> ");
		fgets(temp_b_name, 50, stdin);
		temp_b_name[strcspn(temp_b_name, "\n")] = 0;
		temp_b_name[49] = '\0';
		id = 0;
		temp_b_id_exists = 1;
		while(temp_b_id_exists){
			printf("\nEnter ID: \nl> ");
			scanf("%d", &id);
			dummy = getchar();
			temp_b_id_exists = does_it_exist_b(id);
			if(temp_b_id_exists)
				printf("\n!!!!!!!!!!!!!!!!- ID ALREADY EXISTS -!!!!!!!!!!!!!!!!!!!!!!!\n");
		}
		adding_adding_books.id = id;
		strcpy(adding_adding_books.b_name, temp_b_name);
		FILE *adding_books;
		adding_books = fopen("books.dat", "ab");
		fwrite(&adding_adding_books, sizeof(adding_adding_books), 1, adding_books);
		fclose(adding_books);
	}
}

void librarian_options(){
	int choice_librarian_options = 1;
	while(choice_librarian_options){
		printf("\n1. Print all students");
		printf("\n2. Add Students");
		printf("\n3. Show Books");
		printf("\n4. Assign book to student");
		printf("\n5. Remove Student");
		printf("\n6. Add Books");
//		printf("\n7. Remove Book");
		printf("\n7. View Book Requests");
		printf("\n8. Approve Book Requests");
		printf("\n9. Remove Book Request");
		printf("\n0 to exit. ");
		printf("\nl> ");
		scanf("%d", &choice_librarian_options);
		dummy = getchar();
		if(choice_librarian_options == 1){
			figletize();
			print_students();
		}
		else if(choice_librarian_options == 2){
			figletize();
			add_students();
			figletize();
		}
		else if(choice_librarian_options == 3){
			figletize();
			print_books();
		}
		else if(choice_librarian_options == 4){
			figletize();
			assign_book();
		}
		else if(choice_librarian_options == 5){
			figletize();
			remove_student();
		}
		else if(choice_librarian_options == 6){
			figletize();
			add_books();
		}
		else if(choice_librarian_options == 7){
			figletize();
			print_requests();}
		else if(choice_librarian_options == 8){
			figletize();
			approve_request();
		}
		else if(choice_librarian_options == 9){
			figletize();
			remove_request();
		}
	}
}

void read(){
	number_of_ids = 0;
	number_of_b_ids = 0;
	number_of_requests = 0;
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
	fclose(reader);
	FILE *breader;
	breader = fopen("books.dat", "rb");
	struct Book b_reading_reader;
	while((fread(&b_reading_reader, sizeof(b_reading_reader), 1, breader)) != 0){
		number_of_b_ids += 1;
	}
	fclose(breader);
	struct Requests counting_requests;
	FILE *rreader;
	rreader = fopen("requests.dat", "rb");
	while(fread(&counting_requests, sizeof(counting_requests), 1, rreader)){
		number_of_requests += 1;
	}
	fclose(rreader);
}

void print_students(){
	read();
//	figletize();
	printf("\n---------------------- STUDENTS ------------------------------\n");
	FILE *printer;
	printer = fopen("students.dat", "rb");
	struct Student reading_printer;
	for(int i = 0; i < number_of_ids; i++){
		fread(&reading_printer, sizeof(reading_printer), 1, printer);
		printf("\n%d\t%s\t%d", reading_printer.self_id, reading_printer.name, reading_printer.book_id);
	}
	fclose(printer);
	printf("\n--------------------------------------------------------------\n");
}

void print_books(){
//	figletize();
	read();
	printf("\n-------------------------- BOOKS -----------------------------\n");
	FILE *b_printer;
	b_printer = fopen("books.dat", "rb");
	struct Book b_reading_printer;
	for(int i = 0; i < number_of_b_ids; i++){
		fread(&b_reading_printer, sizeof(b_reading_printer), 1, b_printer);
		printf("\n%d\t%s", b_reading_printer.id, b_reading_printer.b_name);
	}
	fclose(b_printer);
	printf("\n--------------------------------------------------------------\n");
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
	FILE *rPtr;
	struct Requests reqs[2];
	reqs[0].self_id = 123456;
	reqs[1].self_id = 854808;
	reqs[0].b_id = 1122;
	reqs[1].b_id = 8869;
//	strcpy(reqs[0].b_name, "The Boy with The Striped Pajamas");
//	strcpy(reqs[1].b_name, "Nothing Ventured");
	rPtr = fopen("requests.dat", "rb");
	if(rPtr == NULL){
		FILE *rrPtr;
		rrPtr = fopen("requests.dat", "wb");
		for(int i = 0; i < 2; i++)	
			fwrite(&(reqs[i]), sizeof(reqs[i]), 1, rrPtr);
		fclose(rrPtr);
	}
	else
		fclose(rPtr);
}

void librarian(){
	figletize();
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
			printf("\n!!!!!!!!!!!!!!!!- INVALID PASSWORD -!!!!!!!!!!!!!!!!!!!!!!!!\n");
		}
	}
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
	clear();
//	printf("\e[1;1H\e[2J");
	char figlet[] = "  _     _ _     __  __             ____            \n | |   (_) |__ |  \\/  | __ _ _ __ / ___| _   _ ___ \n | |   | | '_ \\| |\\/| |/ _` | '_ \\\\___ \\| | | / __|\n | |___| | |_) | |  | | (_| | | | |___) | |_| \\__ \\\n |_____|_|_.__/|_|  |_|\\__,_|_| |_|____/ \\__, |___/\n                                         |___/";
	printf("%s\n", figlet);
	printf("  Library Management System v 0.0.1\n");
	printf("--------------------------------------------------------------\n");
}

void clear(){
    #if defined(__linux__) || defined(__unix__) || defined(__APPLE__)
        system("clear");
    #endif

    #if defined(_WIN32) || defined(_WIN64)
        system("cls");
    #endif
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
			printf("\n!!!!!!!!!!!!!!!!!- INVALID CHOICE -!!!!!!!!!!!!!!!!!!!!!!!!!\n");
	}	
	return 0;
}