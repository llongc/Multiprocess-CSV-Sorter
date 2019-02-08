/*****
*
*	Define structures and function prototypes for your sorter
*
*
*
******/
#ifndef _scannerCSVsorter_h
#define _scannerCSVsorter_h

struct head{
	int index;
	struct head* next;
	char** values; 
};

struct head* bigbang(struct head*, int, int, int);
struct head*  initialize(struct head*, int);
void install_data(int, struct head*, char*);
void clean_space(char*);
void free_struct(struct head*);
void handler(char *, char *, char *, char*);
void simpleCSV(char *, char *, char *, char*);
void walk_through(char*, char *, char *);
	
	
int chk_dig(char *);
char * rev_white(char *);	
int compare(char *, char *);
void merge (char ** , int , int , int );
void mergesort( char ** , int , int );
void print_array(char **  , int );
char ** serach(struct head* , int);

#endif

//Suggestion: define a struct that mirrors a record (row) of the data set


//Suggestion: prototype a mergesort function

