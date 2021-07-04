#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define INPUTSIZE 400
#define DELIMITER " "


char *word_list[INPUTSIZE];
char input[INPUTSIZE];

void print_to_screen();
void get_input();
void replace();
int count();
void write_to_file();


int main(){
	int valid_tweet = 0,choice = 0;

	printf("Please Enter 1  2  3 \n 1. Convert Input\n 2. Add short-forms \n 3. Exit \nInput: ");
	scanf("%d",&choice);
	printf("\n");
	switch (choice){
		case 1:
			get_input();
			printf("\nReplacing words to short-forms...\n");
			replace();
			valid_tweet = count();
			if( valid_tweet <= 140){
				print_to_screen();
			}
			else{
				printf("\n\nWords replaced to short-forms. The replaced tweet is still greater the 140 characters. \n\nPLease decrease the input string. ");
			}
			break;

		case 2:
			write_to_file();
			printf("Done.");
			break;
		
		case 3:
			break;

		default:
			printf("Select Either 1  2  3");
			break;
	}
	return 0;
}

void get_input(){
	int i = 0;

	printf("Enter Input: \n");
	fflush(stdin);
	fscanf(stdin,"%400[^\n]",input);

	word_list[i] = strtok(input,DELIMITER);
	while(word_list[i]!=NULL){

   		word_list[++i] = strtok(NULL,DELIMITER);
	}
}

void replace(){
	FILE *file;
	char text[20],text2[20];
	int count = 0,i=0;
	file= fopen("shorts.txt","rt");

	while(fscanf(file,"%s %s",text,text2)==2){
		i = 0;

		while (word_list[i]!=NULL){

			if (strcmp(text2,word_list[i]) == 0 ){
				strcpy(word_list[i],text);		
			}
			i++;	
		}	
	}

    fclose(file);
}
int count(){
	int count = -1, i = 0;
	while(word_list[i]!=NULL){
		count += 1;
		count += strlen(word_list[i++]);
		if(count > 140){
			break;
		}
	}
	return count;
}

void write_to_file(){
	char short_form[10],long_form[25];
	FILE *file2;

	printf("Enter the short-form: ");
	scanf("%s",&short_form);
	printf("\nEnter the short-form: ");
	scanf("%s",&long_form);

	file2 = fopen("shorts.txt", "a");

	if(file2==NULL){
		printf("\nError opening File");
	}
	else{
		fprintf(file2,"\n%s %s\n",short_form,long_form);
	}
	fclose(file2);

}

void print_to_screen(){
	int i=0;
	printf("\nTweet to copy: \n");
	while(word_list[i]!=NULL){
		printf("%s ",word_list[i++]);
	}
	printf("\n\n\n");

}
