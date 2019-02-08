#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>
#include"scannerCSVsorter.h"


////////////////////////////////////////////////////
//check if this number is digit
////////////////////////////////////////////////////

int chk_dig(char a[]){
	

	int num = strlen(a);
	int i, jud = 0;
	for(i = 0; i < num; i++){
	
	if(a[i] == '.' && jud == 0){
	jud = 1;
	continue;
	}
	else if(a[i] < '0' || a[i] > '9'){
	return 0;
	}
	}

return 1;	
}


//remove all the white sapce from the head
//but also this function also automaticly identity if there is a 
//comma in the string and remvoe " inthe start and end 
//////////////////////////////////////////////
char * rev_white(char target[]){
	char temp2[1000] = "";
	char temp[1000] = "";
	char temp3[1000] = "";
	int i, jud = 0, comma = 0, count = 0;
	for(i = 0; i < strlen(target); i++){
		if(target[i] == ','){
			comma = 1;
		}
		if(target[i] == ' ' && jud == 0){
		continue;
		}else{
		jud = 1;
		temp[count] = target[i];
		count++;
		}	
	}

	// if there is a comma in the string
	if(comma == 1){
		for(i = 0; i < strlen(temp) - 2; i++){
			temp2[i] = temp[i+1];
		}

	jud = 0; count = 0;
	
	//remove all the white space from temp2
	for(i = 0; i < strlen(temp2); i++){
		if(temp2[i] == ' ' && jud == 0){
		continue;
		}else{
		jud = 1;
		temp3[count] = temp2[i];
		count++;
		}
	}
	
	target= temp3;
	return target;
	}

	target= temp;
return target;
}




//////////////////////////////////////////////////////////////////////////////////////
//function compare return 1 if a > b, return 0 if a <= b
//this function will handle the diffrent data type automatially
//if it is string it will compare they in the way of strcmp 
//if the input data files has diffferent data type, this function will return error
////////////////////////////////////////////////////////////////////////////////////

int compare(char c[], char d[]){
	double A, B;
	char a[1000];
	char b[1000];
	
	if(strcmp(c,"")==0 && strcmp(d, "") == 0){
	return 0;
	}else if(strcmp(c, "") == 0){
	return 1;
	}else if(strcmp(d, "")==0){
	return 0;
	}

//	printf("c=  %s, d = %s", c, d);

	strcpy(a, rev_white(c));
	strcpy(b, rev_white(d));

// 	if the two string are not the same data type.
	if(chk_dig(a) != chk_dig(b)){
	
		if(strcmp(a, b)>0){
			return 0;
		}else{
			return 1;
		}

	
	}else if(chk_dig(a) == 1){

	sscanf(a, "%lf", &A);
	sscanf(b, "%lf", &B);

		if(A < B){
		return 1;
		}else{
		return 0;
		}

	}else if(chk_dig(a) == 0){

		if(strcmp(a, b)>0){
			return 0;
		}else{
			return 1;
		}

	}
return 0;
}


/////////////////////////////////////////////////////////////////////////////
// this is  the merge algorith the only difference from regular algorithm
// is that I replace the comprison into my own comparing function.
// //////////////////////////////////////////////////////////////////////////
void merge (char ** arr, int l, int r, int m ){

	int size = sizeof(arr)/sizeof(arr[0]);
	int i = 0,j = 0,k = 0;
	int temp1 = m - l + 1;
	int temp2 = r - m;

	char ** left = malloc(temp1 * sizeof(char*));
	for(i = 0; i < temp1; i++){
	left[i] = malloc(1000 * sizeof(char));
	}

	char ** right = malloc(temp2 * sizeof(char*));
	for(i = 0; i < temp2; i++){
	right[i] = malloc(1000 * sizeof(char));
	}

	
	for(i = 0; i < temp1; i++){
		left[i] = arr[l + i];
	}	
	for(i = 0; i < temp2; i++){
		right[i] = arr[m + i + 1];
	}

	i = 0;
	k = l;

	while(i < temp1 && j < temp2){
		if(compare(left[i], right[j])){
			arr[k] = left[i];
			i++;
		}
		else
		{
			arr[k] = right[j];
			j++;
		}
		k++;
	}
	

	while(i < temp1){
		arr[k] = left[i];
		i++;
		k++;

	}

	while(j < temp2){
		arr[k] = right[j];
		j++;
		k++;
	}
return;
}

// this is sorting by recurrsion
 void mergesort( char ** arr, int l, int r){

	if(l < r){

		int m = l + (r - l)/2;

		mergesort(arr, l, m);
		mergesort(arr, m + 1, r);

		merge(arr, l, r, m);

		}

return;
}

void print_array(char **  A, int size){
	int i;
	for(i = 0; i < size; i++){
		if(strcmp(A[i], "")==0) {
			printf("NULL ");
			continue;
		}			
	printf("%s ", A[i]);
	}
	printf("\n");
}

////////////////////////////////////////////////////////////////////////////////
//this will traverse into table and return the string array of num_th row 
///////////////////////////////////////////////////////////////////////////////
/*
char ** serach(struct head* table, int num){
	struct head* ptr = table;
	int i;
	for(i = 0; i < num; i++){
		ptr = ptr->next;
	}
	
return ptr->values;
}
*/
char ** search(struct head* table, int row){
	int i;
	char ** temp;
	struct head*ptr = table;

	for(i = 0; i < row; i++){
		ptr = ptr->next;
	}

	temp = ptr->values;

return temp; 
}

//............................................................................................................................................
//this the main fucntion the will be used in simpleCSVsorter.c file, takes four arguments, table is the pointer of its table, the deep is
//the number of rows in target table, col_num is the number of columns in the table. the tar_index is the num_th column the we will sort upon
//
//	structure:
//		table->row1 -> string_array 
//			|
//  		       row2 -> string_array
//			|
//		       row3 -> string_array
//			|
//			.
//			.
//			.
//
//............................................................................................................................................
struct head * bigbang(struct head* table, int deep, int col_num, int tar_index){
	
	// innitializing a temp array for storing the data of target column in the table
	int i, j;


	char ** target = malloc(deep * sizeof(char*));
	char ** origin = malloc(deep * sizeof(char*));
	int * jud = malloc(deep * sizeof(int));	

	for(i = 0; i < deep; i++){
	target[i] = malloc(1000 * sizeof(char));
	origin[i] = malloc(1000 * sizeof(char));
	jud[i] = 0;
	}
	//copy the data from target column to temp array
	struct head * ptr;
	ptr = table;
	
	for(i = 0; i < deep; i++){
	target[i] = ptr->values[tar_index];
	origin[i] = ptr->values[tar_index];
	ptr = ptr->next;
	}
			
	mergesort(target, 0, deep - 1);

	struct head* output;
	output = initialize(output, col_num);
	struct head* ptrt = output;

	
		
	for(i = 0; i < deep; i++){
		for(j = 0; j < deep; j++){
			if(target[i] == NULL && origin[j] == NULL && jud[j] == 0){
			break;
			}
			else if(strcmp(target[i], origin[j]) == 0 && jud[j] == 0){						break;
			}
		}
			
		jud[j] = 1;
		ptrt->next = initialize(ptrt, col_num);	
		ptrt->values =  search(table, j);
		ptrt = ptrt->next;
	
	}
	
	//free here
	
	ptrt = NULL;
	ptr = table; 
	
	while(ptr!=NULL){
	ptrt = ptr;
	ptr = ptr->next;
	free(ptrt);
	}

	free(target);
	free(origin);
	free(jud);

return output;
}



/*

int main(int argc, char *argv[]){

	char * arr[] = { "      1.111", NULL, "       12.3", "2.3", NULL, "2.2"};
	int arr_size = sizeof(arr)/sizeof(arr[0]);

	printf("original arr\n");
	print_array(arr, arr_size);

	mergesort(arr, 0, arr_size - 1);
	
	printf("sorted array\n");
	print_array(arr, arr_size);

	return 0;
}
*/



