/*
   Write a program entab that replaces strings of blanks by the minimum 
   number of tabs and blanks to achieve the same spacing. Use the same tab stops as for detab. 
   When either a tab or a single blank would suffice to reach a tab stop, which should be given 
   preference?  
   */

#include <stdio.h>

#define _GREEN_ "\033[32m"
#define _YELLOW_ "\033[33m"
#define _RESET_ "\033[0m"

#define TAB_SPACE 4
#define MAXLEN 1000

static void copy_string( char* destination, char* source, int len );
static int get_line(char* buffer, int len);
static void remove_trailing_space(char* buffer, int len);
static void detab(char* buffer, int len, int tab_space);
static void print_array(char* buffer);

int main(){
	char buffer[MAXLEN]={0};
	int len=0;

	while( (len = get_line(buffer, MAXLEN)) > 0){
		remove_trailing_space(buffer, len);

		print_array(buffer);

		detab(buffer, len, TAB_SPACE);

		print_array(buffer);
	}
}

static void print_array(char* buffer){
	int count = 0;
	putchar('\n');
	while(buffer[count]!='\0') {
		if(buffer[count] != '\t') {
			printf("%d: %c\n",count, buffer[count]);
		}else{
			printf("%s", _YELLOW_);
			printf("%d: %s\n",count, "\\t");
			printf("%s", _RESET_);
		}
		count++;
	}
}

static void copy_string( char* destination, char* source, int len ){
	int index = 0;
	while(source[index]!='\0' || index < len){
		destination[index] = source[index];
		index++;
	}
}

static int get_line(char* buffer, int len){
	char c=EOF;
	for(len=0 ; (c=getchar())!=EOF && len < (MAXLEN-1) && c != '\n'; len++ ){
		buffer[len] = c;
	}
	buffer[len+1] = '\0';
	return len;
}

static void remove_trailing_space(char* buffer, int len){
	if(buffer[len-1] == ' ' || buffer[len-1] == '\t'){
		printf("%strailing spaces detected, removing them now\n%s",_YELLOW_, _RESET_);
		while (buffer[len-1] == ' ' || buffer[len-1] == '\t') {
			buffer[len-1]='\0';
			len -= 1;
		};
	};
}

static void detab(char* buffer, int len, int tab_space){
	int tab_count = 0;
	int x = 0;
	char out[MAXLEN] = {0}; 
	for(int i=0 ; i <= (len-1) ; i++){
		if(buffer[i] == '\t'){
			tab_count++;
		}
	}
	int temp = tab_count;;
	for(int i = len ; i>=0 ; i--){
		x  = i + temp * (tab_space-1);

		if(buffer[i] != '\t'){
			out[x] = buffer[i];
		}else{
			for(int j=0 ; j<tab_space ; j++){
				out[x-j] = ' ';
			}
			temp--;
		}
		if(temp==0) 
		{
			copy_string(buffer, out, len+tab_count*(tab_space-1));
			break;
		}
	}
}