#include <stdio.h>
#include <stdlib.h>
#include <string.h>
   
FILE * rhymer (FILE * fin);
char ** poem_arr_edit (FILE * fin);
   
int main (int argc, char * argv[]){
  
	FILE * fin = fopen(argv[1], "r");
	if (fin == NULL){
		perror("Fopen error ");
		return 1;
	}   
 
	FILE * fout = 0;
	fout = rhymer(fin);
 
	return 0;
}   

FILE * rhymer (FILE * fin){  
	char ** poem_arr = poem_arr_edit(fin);
}   
 
char ** poem_arr_edit (FILE * fin){
	
	if (fseek(fin, 0, SEEK_END) == -1){
		perror("Fseek error "); 
		return NULL;
	}
 
	long sizef = 0;
	sizef = ftell(fin);
	if (sizef == -1){
		perror("Ftell error ");
		return NULL;
	}
 
	char * poem_buf = (char*) malloc(sizeof + 1);
	if (poem_buf == NULL){
		perror("Malloc error ");
		return NULL;
	}
 
	if (fseek(fin, 0, SEEK_SET) == -1){
		perror("Fseek error ");
		return NULL;
	}

	if (fread(poem_buf, 1, sizef, fin) != sizef) {
		perror("Fread error ");
		return NULL;
	}

	int num_str = 0;
	int i = 0; 
	for (i = 0; i <= sizef; i++)
		if (poem_buf[i] == '\n')
			num_str++;
	
	char * poem_arr[num_str];
	char * ch = 0;
	for (i = 0; i <= num_str; i++){
		ch = strchr(poem_buf, '\n');
		strncpy(poem_arr[i], poem_buf, ch - poem_buf);
		*(poem_arr[i] + (ch - poem_buf) + 1) = '\0';		/*strcat(poem_arr[i], '\0');*/
		poem_buf = ch;
	}
	
	return poem_arr;
}

