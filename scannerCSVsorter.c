#include<stdlib.h>
#include<stdio.h>
#include<dirent.h>
#include<unistd.h>
#include<stdbool.h>
#include<string.h>
#include<limits.h>
#include"scannerCSVsorter.h"
/*
struct head{
	int index;
	struct head* next;
	char** values; 
};
*/
struct head* first_row;
int col_num = 0;
void handler(char *, char*, char *, char *);
void simpleCSV(char*, char*, char*, char*);
void walk_through(char*,char*,char*);
static int count = 0;
int output = false;
struct head*  initialize(struct head* row,int col_num){
	int a;
	row = (struct head* )malloc(sizeof(struct head));

	row->values = (char**)malloc(sizeof(char*)*col_num);
	int i;
	for(i = 0;i < col_num; i++){
		row->values[i]=(char*)malloc(sizeof(char)*1000);
	}
	return row;
}

void install_data(int col_num, struct head* row, char* line){
	char* field;
	char* cp = strdup(line);
	int i = 0;
	while((field = strsep(&cp,","))!= NULL){
		char n[1000];
		strcpy(n, field);
		//printf("when strcpy(n, field), the value of field is %s, n is %s\n", field, n);
		if(field[0]=='\"' && field[strlen(field)-1] != '\"'){
			char * f = strsep(&cp, ",");
			while(f[strlen(f)-1]!= '\"'){
				strcat(n,",");
				strcat(n, f);
				f = strsep(&cp, ",");
			}
			strcat(n, ",");
			strcat(n, f);
		}
		//printf("the ele is %s\n", n);
		strcpy(row->values[i],n);
		i++;
	}
	if (col_num != (i)){
		fprintf(stderr,"error: not enough output\n");
		exit(0);
	}
	row -> next = NULL;
	//free(cp);
}

void clean_space(char* pt){
	while(pt && *pt =='\040') pt++;
}

void free_struct(struct head* row){
	int i;
	for(i = 0; i<col_num;i++){
		free(row->values[i]);
	}
	free(row->values);
	//free(row);

}

void clean_dir(char * target, int num){
	char temp [10001];
	char temp2 [10001];
	int len = num;
	strcpy(temp, target);
	if(target[0] == '/'){
	//nothing
	}else if(target[0] != '.'){
		len = num + 2;
		sprintf(temp, "./%s", target);
	}
	strcpy(temp2, temp);
	if(temp[len-1] != '/'){
		sprintf(temp2, "%s/", temp);
	}
	strcpy(target, temp2);	

return;
}

int main(int argc, char** argv){
	int i, j, k;
	int int_d = 0, out_d = 0;
//input directary, output directary, col_name
	char * inp_dir;
	char * out_dir;
	char * col_name;
	int inp = 0, out = 0, col = 0;	

//trying to get current directary
	char cwd [10000];
	getcwd(cwd, sizeof(cwd));
	int cwd_len = strlen(cwd);

//if the number of parameter in command line is   
	if(argc == 2||argc == 6||argc==4||argc==1||argc > 7){
		fprintf(stderr,"error\n");		
		exit(0);
	}
		
// if the number of parameter in command line is 2
	if(argc == 3){
		if(strcmp(argv[1], "-c")!=0){
		fprintf(stderr,"error\n");		
		exit(0);
		}

	col_name = (char*)malloc((strlen(argv[2])*2)*sizeof(char));
	strcpy(col_name, argv[2]);
	int_d = cwd_len;
	out_d = cwd_len;
	inp_dir = (char*)malloc(10001*sizeof(char));
	strcpy(inp_dir, cwd);
	out_dir = (char*)malloc(10001*sizeof(char));
	strcpy(out_dir, cwd);
	}	

// if the number of parameter in command line is 4

	if(argc == 5){

	char flag;
	for(i = 1; i < 5; i = i + 2){

		if(strcmp(argv[i], "-c")==0){
			flag = 'c';
		}else if(strcmp(argv[i], "-d")==0){
			flag = 'd';
		}else if(strcmp(argv[i], "-o")==0){
			output = true;
			flag = 'o';
		}else{
			flag = 'k';
		}

		switch(flag){
	
		case 'c':
			col_name = (char*)malloc((strlen(argv[i+1])*2)*sizeof(char));
			strcpy(col_name, argv[i+1]);
			col++;
			break;
		case 'o':
			out_d = strlen(argv[i+1]);
			out_dir = (char*)malloc((strlen(argv[i+1])*2)*sizeof(char));
			strcpy(out_dir, argv[i+1]);
			out++;
			break;
		case 'd':
			int_d = strlen(argv[i+1]);
			inp_dir = (char*)malloc((strlen(argv[i+1])*2)*sizeof(char));
			strcpy(inp_dir, argv[i+1]);
			inp++;
			break;
		default:
			fprintf(stderr,"error\n");		
			exit(0);
			}
		}

		if(inp == 0){
			inp_dir = (char*)malloc(10001*sizeof(char));
			strcpy(inp_dir, cwd);
			inp++;
			int_d = cwd_len;
		}
		if(out == 0){
			out_dir = (char*)malloc(10001*sizeof(char));
			strcpy(out_dir, inp_dir);
			out++;
			out_d = int_d;
		}
		if(inp != 1 || out != 1 || col != 1){
			fprintf(stderr,"error\n");		
			exit(0);
		}

	}

// if the number of parameter in command line is 6

	if(argc == 7){
		out = 0;
		inp = 0;
		col = 0;
		char flag;
	for(i = 1; i < 7; i = i + 2){

		if(strcmp(argv[i], "-c")==0){
			flag = 'c';
		}else if(strcmp(argv[i], "-d")==0){
			flag = 'd';
		}else if(strcmp(argv[i], "-o")==0){
			output = true;
			flag = 'o';
		}else{
			flag = 'k';
		}

		switch(flag){
	
		case 'c':
			col_name = (char*)malloc((strlen(argv[i+1])*2)*sizeof(char));
			strcpy(col_name, argv[i+1]);
			col++;
			break;
		case 'o':
			out_d = strlen(argv[i+1]);
			out_dir = (char*)malloc((strlen(argv[i+1])*2)*sizeof(char));
			strcpy(out_dir, argv[i+1]);
			out++;
			break;
		case 'd':
			int_d = strlen(argv[i+1]);
			inp_dir = (char*)malloc((strlen(argv[i+1])*2)*sizeof(char));
			strcpy(inp_dir, argv[i+1]);
			inp++;
			break;
		default:
			fprintf(stderr,"error\n");		
			exit(0);
			}
		}

		if(inp == 0){
			inp_dir = (char*)malloc(10001*sizeof(char));
			strcpy(inp_dir, cwd);
			inp++;
			int_d = cwd_len;
		}
		if(out == 0){
			out_dir = (char*)malloc(10001*sizeof(char));
			strcpy(out_dir, inp_dir);
			out++;
			out_d = int_d;
		}
		if(inp != 1 || out != 1 || col != 1){
			fprintf(stderr,"error\n");		
			exit(0);
		}

	}
//handle the format of the directrayt
	clean_dir(inp_dir, int_d);
	clean_dir(out_dir, out_d);


	if(access(out_dir, F_OK) != -1 && access(inp_dir, F_OK)!= -1){
	}else{
	fprintf(stderr, "error\n");
	exit(0);
	}	



	//printf("col_name = %s, inp_dir = %s, out_dir = %s\n", col_name, inp_dir, out_dir);
//	if(output == true) printf("o found\n");

	

///////////////////////////////////////////////////////////////////////
//	char cd[1024];
//	getcwd(cd,sizeof(cd));
//	printf("*******%s\n",cd);
	printf("Initial PID: %d\n",getpid());	
	printf("PIDS of all child processes: ");
	fflush(stdout);
	
	walk_through(inp_dir,out_dir,col_name);
	printf("\n");
	wait(NULL);
	printf("Total number of processes: %d\n",count);
	fflush(stdout);
	return 0;	



/////////////////////////////////////////////////////////////////////

	

	free(col_name);
	free(inp_dir);
	free(out_dir);
return 0;
}


void handler(char * file_name, char * input, char * out_path, char * target){

	char * file_type = strrchr(file_name, '.');
	if(file_type == NULL) return;
	if(strstr(file_name, "-sorted-") != NULL) return;
	if(strcmp(file_type, ".csv") != 0) return;

	simpleCSV(file_name,input, out_path, target);

return;
}




void simpleCSV(char * file_name, char* input, char * out_path, char * target){
	FILE * fp;
	FILE * fp2;
	char temp_buffer [10000] = "";
	char file[10001]="";
	strcpy(file,input); 
	strcat(file,file_name);
	//printf("[simpleCSV] input is %s\n",file);	
	fp = fopen(file, "r");
	char new_name [10000] = "";
	int i;
	//initialize col_name array for column heads and alloc space
	char** col_name;
	col_name = (char**)malloc(sizeof(char*)*1000);
	for(i = 0; i <1000;i++){
		col_name[i]=(char*)malloc(sizeof(char)*1000);
	}
	i = 0;


	char buffer[1000];
	//get the name of column from csv
	fgets(buffer,1000,fp);
	char* pt;
	//split and store them in col_name
	pt = strtok(buffer,",");
	 col_num = 0;
	while(pt){
		col_num++;
		col_name[i]=pt;
		pt = strtok(NULL,",");
		//get rid of space
		clean_space(pt);
		i++;
	}
	pt = col_name[col_num-1];
	size_t ln = strlen(pt)-1;
	if(pt[ln]=='\n') pt[ln] = '\0';
	col_name[col_num-1] = pt;
	
	//check if col_name exist
	bool isSame=false;
	int index=0;
	for(i=0;i<col_num;i++){
		if(strcmp(target,col_name[i])==0){
			isSame=true;
			index = i;
			break;
		}
	}
	if(isSame==false) {
		fprintf(stderr,"error: col cannot be found\n");
		exit(0);
	}
	char* col = (char*)malloc(sizeof(char)*10000);
	strcpy(col,col_name[0]);
	for(i=1;i<col_num;i++){
		strcat(col,",");
		strcat(col,col_name[i]);
	}	
	

	//install data
	struct head* temp;
	first_row = NULL;
	temp = NULL;
	int j=0;
	while(fgets(buffer,1000,fp)){
		
		struct head* row;
		row = initialize(row,col_num);
		j++;
		row->index = j;
		install_data(col_num,row,buffer);
		
		pt = row->values[col_num-1];
		int ln = strlen(pt)-1;
		if(pt[ln]=='\n') {
		pt[ln]='\0';}
		row->values[col_num-1]=pt;
		if(first_row == NULL){
			first_row = row;
			temp = row;
		} else {
			temp -> next = row;
			temp = temp -> next;
		}
		

	}


	file_name[strlen(file_name)-4] = '\0';
	sprintf(new_name, "%s%s%s.csv", file_name, "-sorted-", target);
	sprintf(temp_buffer, "%s%s", out_path, new_name);
	//printf("[outpath]: %s\n",temp_buffer);
	fp2 = fopen(temp_buffer, "w");
	
	fprintf(fp2, "%s", col);

	free(col_name);
	int row_tail = j;

	///////////////////////////////////////////////////
	//////////////merge sort here///////////////////
	////////////////////////////////////////////////
	first_row = bigbang(first_row, row_tail, col_num, index);


	struct head* ptr;
	struct head* tmp;
	ptr = first_row;
	char* n = (char*)malloc(sizeof(char)*10000);
	
	for(j = 0; j < row_tail-1; j++){
		tmp = ptr ->next;
		strcpy(n,ptr->values[0]);
		for(i = 1; i<col_num;i++){
			strcat(n,",");
			strcat(n,ptr->values[i]);
		}
		fprintf(fp2, "%s\n", n);
		ptr = tmp;
	
	}
	strcpy(n, tmp->values[0]);
	for(i=1; i<col_num;i++){
		strcat(n,",");
		strcat(n,tmp->values[i]);
	}
	fprintf(fp2, "%s\n", n);	

	struct head* pointer;
	struct head* tpr;
	pointer = first_row;
	free(n);
	for(j = 0; j < row_tail-1; j++){
		//fflush(stdout);
		tpr = pointer->next;
		free_struct(pointer);
		pointer = tpr;
	}
	free_struct(tpr);
	fclose(fp);
	fclose(fp2);
	return;
}



void walk_through(char* dir,char* out_dir,char* col_name){
	struct dirent * entry;
	DIR *dr;
	if(!(dr=opendir(dir))){
		printf("cannot open dir\n");
		return;
	}
	
	while ((entry=readdir(dr))!=NULL){
		int fd[2];
		pipe(fd);
		if(entry->d_type==DT_DIR){
			if(strcmp(entry->d_name,".")==0){
				continue;
			} else if(strcmp(entry->d_name,"..")==0){
				continue;
			} else {
				int pid = fork();
				if(pid == 0){
					close(fd[0]);
					count++;
					if(count == 1) printf("%d",getpid());
					else printf(",%d",getpid());
					//printf("[dir]count is %d, name is %s\n",count,entry->d_name);
					fflush(stdout);
					char subdir[10001];
					strcpy(subdir,dir);
					strcat(subdir,entry->d_name);
					strcat(subdir,"/");
					char subout[10001];
					strcpy(subout,out_dir);
					//printf("------[before subout], input path is %s, outpath is %s\n",subdir,subout);
					if(output == false){
						strcat(subout,entry->d_name);
						strcat(subout,"/");
					}
					//printf("-----[after subout], input path is %s, outpath is %s\n",subdir, subout);
					walk_through(subdir,subout,col_name);
					write(fd[1],&count,sizeof(count));
					_exit(0);
				} else {
					close(fd[1]);
					read(fd[0],&count,sizeof(count));
					wait(NULL);

				}
			}
			
		}
	}
	closedir(dr);
	dr=opendir(dir);
	while ((entry=readdir(dr))!=NULL){
		int fd[2];
		pipe(fd);
	  //since Francisco said count every file
			//char* file_type = strrchr(entry->d_name,'.');
		if(entry->d_type==DT_REG){		//if(strcmp(file_type,".csv")==0){
		int pid = fork();
		if(pid == 0){
			close(fd[0]);
			count++;
			write(fd[1],&count,sizeof(count));
			if(count == 1) printf("%d",getpid());
			else printf(",%d",getpid());
			//printf("[file]count is %d, name is %s\n",count, entry->d_name);
			fflush(stdout);
			//printf("[handler] handle in outpath %s\n",out_dir);
			handler(entry->d_name,dir,out_dir,col_name);
			_exit(0);					
		} else {
			close(fd[1]);
			read(fd[0],&count,sizeof(count));
			wait(NULL);
		}
			//}
		}
	}
	closedir(dr);
}
