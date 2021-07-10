#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

FILE * rhymer (FILE * fin);
char ** poem_arr_edit (FILE * fin, int * num_str);
int comparator (const void * val1, const void * val2);

long sizef; /*File size*/

int main (int argc, char * argv[]){
  
	FILE * fin = fopen(argv[1], "r");
	if (fin == NULL){
		perror("Fopen error ");
		return 1;
	}   
 
	FILE * fout = 0;
	printf("Before rhymer\n");
	fout = rhymer(fin);
 
	return 0;
}   

FILE * rhymer (FILE * fin){  
	char ** poem_arr = NULL;
	int num_str = 0;

	poem_arr = poem_arr_edit(fin, &num_str);
	qsort(poem_arr, num_str, sizeof(char * ), comparator);
	
	char * buf = (char *)malloc(sizef + 1);
	for (int i = 0; i <= num_str; i++){
		strcpy(buf, poem_arr[i]);
		strcat(buf, "\n");
	}

	buf[sizef] = '\0';

	FILE * fout = fopen("result.txt", "w");
	if (fout == NULL){
		perror("Fopen error ");
		return NULL;
	}

	if (fwrite(buf, 1, sizef + 1, fout) != sizef + 1){
		perror("Fwrite error ");
		return NULL;
	}
	
	free(buf);
	free(poem_arr);
	
	return fout;
}   
 
char ** poem_arr_edit (FILE * fin, int * num_str){

	if (fseek(fin, 0, SEEK_END) == -1){
		perror("Fseek error "); 
		return NULL;
	}
 
	extern long sizef;
	sizef = ftell(fin);
	if (sizef == -1){
		perror("Ftell error ");
		return NULL;
	}
 	
	char * poem_buf = (char *) malloc(sizef + 1);
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
	poem_buf[sizef] = '\0';	

	int i = 0; 
	for (i = 0; i <= sizef; i++)
		if (poem_buf[i] == '\n')
			(*num_str)++;
	
	char * ch_start = 0;
	char * ch_end = 0;
	ch_start = poem_buf;
	char ** poem_arr = (char **)malloc(*num_str * sizeof(char * ));
	for (i = 0; i <= *num_str; i++){

		ch_end = strchr(ch_start, '\n');
		if (ch_end == NULL)
			ch_end = poem_buf + *num_str;
		poem_arr[i] = (char *)malloc(ch_end - ch_start + 1);

		if (poem_arr[i] == NULL){
			perror("Malloc error ");
			return NULL;
		}
		
		strncpy(poem_arr[i], ch_start, ch_end - ch_start);
		*(poem_arr[i] + (ch_end - ch_start) + 1) = '\0';	/*strcat(poem_arr[i], '\0');*/
		printf("%s\n", poem_arr[i]);
		ch_start = ch_end + 1;
	}

	free(poem_buf);

	return poem_arr;
}

int comparator (const void * val1, const void * val2){

	char * str1 = (char*)val1;
	char * str2 = (char*)val2;

	int len1 = strlen(str1);
	int len2 = strlen(str2);

	int i = 1;
	int j = 1;

	for (; i <= len1 && j <= len2; i++, j++){
		while (!isalpha(*(str1 + len1 - i))){
			i++;
			if (i == len1)
				return -1;
		}

		while (!isalpha(*(str2 + len2 - j))){
			j++;
			if (j == len2)
				return 1;
		}

		if (*(char*)(str1 + len1 - i)  == *(char*)(str2 + len2 - j))
			continue;
		else
			if (*(char*)(str1 + len1 - i) < *(char*)(str2 + len2 - j))
				return -1;
			else
				return 1;	
	}
}


