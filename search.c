#include <stdio.h>
#include<stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include<dirent.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>


struct stat file_details;
int ListFileDirInfo(char name[], int dirfileflag);
int filestr[50] = {0};
int file_indent = 1;
void display_files(char *path);
struct tm time_access;
void (*funtmp_ptr_displayfile)(char *);
int file_access_path = 0;
int sizeofbyte = 0;
int g_IsFile = 0;


int *tmp_ptr = NULL;
char *g_fileuserpath  =NULL;


int filecntval = 1;
int dircntval = 1;
int g_file_depth = 0;

int IsUser_CheckT = 0;
int ListFileDirInfo(char name[], int dirfileflag)
{
	char tmp[512];
	char softlink[512];
	int softlinkflag = 0;
	char soft_dest[100] = {0};
	char file_indentflag = 0;
	int temp_file_indent = file_indent;

	if(S_ISLNK(file_details.st_mode))
	{
		softlinkflag = 1;
		sprintf(tmp, "%s/%s", g_fileuserpath, name);
		readlink(tmp, soft_dest,100);
		sprintf(softlink, " -> %s", soft_dest);
	}
	if((S_ISDIR(file_details.st_mode) && ((IsUser_CheckT == 1) && (g_IsFile != 2))))
	{
		return 0;
	}
	
	if(dirfileflag == 1)
	{
		file_indentflag = 1;
		tmp_ptr = &filecntval;
	}
	else
	{
		file_indentflag = 0;
		tmp_ptr = &dircntval;
	}
	int permission = 0;
	
	if(file_access_path == 0)
	{
		while(temp_file_indent)
		{
			if(file_indentflag) 
				printf("\t");
			temp_file_indent--;
		}
		if(softlinkflag == 1)
			printf("[%d] %s %s\n",*tmp_ptr, name, softlink);
		else
			printf("[%d] %s \n", *tmp_ptr, name);
		(*tmp_ptr)++;
	}
	else if(file_access_path == 1)
	{
		permission = file_details.st_mode & (S_IRWXU | S_IRWXG | S_IRWXO);
		time_access = *(gmtime(&file_details.st_mtime));
		
		while(temp_file_indent)
		{
			if(file_indentflag) 
				printf("\t");
			temp_file_indent--;
		}
		if(softlinkflag == 1){
			printf("[%d] %s %s %d Bytes, %o %s\n",*tmp_ptr, name, softlink, (int)file_details.st_size, permission, asctime(&time_access));
		}
		else
		{
			printf("[%d] %s %d Bytes, %o %s\n",*tmp_ptr, name, (int)file_details.st_size, permission, asctime(&time_access));
		}
		(*tmp_ptr)++;
	}
	else if(file_access_path == 2)
	{
		if(file_details.st_size <= sizeofbyte)
		{
			while(temp_file_indent)
			{
				if(file_indentflag) 
					printf("\t");
				temp_file_indent--;
			}
			if(softlinkflag == 1)
				printf("[%d] %s %s\n",*tmp_ptr, name, softlink);
			else
				printf("[%d] %s\n",*tmp_ptr, name);
			(*tmp_ptr)++;
		}
	}
	else if(file_access_path == 3)
	{
		if(file_details.st_size <= sizeofbyte)
		{
			while(temp_file_indent)
			{
				if(file_indentflag) 
					printf("\t");
				temp_file_indent--;
			}
			permission = file_details.st_mode & (S_IRWXU | S_IRWXG | S_IRWXO);
			time_access = *(gmtime(&file_details.st_mtime));
			
			if(softlinkflag == 1)
				printf("[%d] %s %s %d Bytes, %o %s\n",*tmp_ptr, name, softlink, (int)file_details.st_size, permission, asctime(&time_access));
			else
				printf("[%d] %s %d Bytes, %o %s\n",*tmp_ptr, name, (int)file_details.st_size, permission, asctime(&time_access));
			(*tmp_ptr)++;
		}
	}
	else if(file_access_path == 4)
	{
		if(strstr((const char *)name, (const char *)filestr))
		{
			while(temp_file_indent)
			{
				if(file_indentflag) 
					printf("\t");
				temp_file_indent--;
			}
			if(softlinkflag == 1)
				printf("[%d] %s %s\n",*tmp_ptr, name, softlink);
			else
				printf("[%d] %s\n",*tmp_ptr, name);
			(*tmp_ptr)++;
		}
	}
	else if(file_access_path == 5)
	{ 
		if(strstr((const char *)name, (const char *)filestr))
		{
			while(temp_file_indent)
			{
				if(file_indentflag) 
					printf("\t");
				temp_file_indent--;
			}
			if(softlinkflag == 1)
				printf("[%d] %s %s %d Bytes, %o %s\n",*tmp_ptr, name, softlink, (int)file_details.st_size, permission, asctime(&time_access));
			else
				printf("[%d] %s %d Bytes, %o %s\n",*tmp_ptr, name, (int)file_details.st_size, permission, asctime(&time_access));
			(*tmp_ptr)++;
		}
	}
	else if(file_access_path == 6)
	{ 
		if((strstr((const char *)name, (const char *)filestr) != NULL) && ((file_details.st_size <= sizeofbyte)))
		{
			if(file_details.st_size <= sizeofbyte)
			{
				while(temp_file_indent)
				{
					if(file_indentflag) 
						printf("\t");
					temp_file_indent--;
				}
				permission = file_details.st_mode & (S_IRWXU | S_IRWXG | S_IRWXO);
				time_access = *(gmtime(&file_details.st_mtime));	
				if(softlinkflag == 1)
					printf("[%d] %s %s\n",*tmp_ptr, name, softlink);
				else
					printf("[%d] %s\n",*tmp_ptr, name);
				(*tmp_ptr)++;
			}
		}
	}
	else if(file_access_path == 7)
	{
		if(((file_details.st_size <= sizeofbyte)) && (strstr((const char *)name, (const char *)filestr) != NULL))
		{
			if(file_details.st_size <= sizeofbyte)
			{
				while(temp_file_indent)
				{
					if(file_indentflag) 
						printf("\t");
					temp_file_indent--;
				}
				permission = file_details.st_mode & (S_IRWXU | S_IRWXG | S_IRWXO);
				time_access = *(gmtime(&file_details.st_mtime));
				
				if(softlinkflag == 1)
					printf("[%d] %s %s %d Bytes, %o %s\n",*tmp_ptr, name, softlink, (int)file_details.st_size, permission, asctime(&time_access));
				else
					printf("[%d] %s %d Bytes, %o %s\n",*tmp_ptr, name, (int)file_details.st_size, permission, asctime(&time_access));
				(*tmp_ptr)++;
			}

		}
	}
}


int main(int argc, char **argv)
{
	struct dirent *de;
	int filecheck = 0;
    static char default_name[10] = {0};
	default_name[0] = '.';
	char start_path[1000] = {0};
	int user_check = 0;
	char dir_info[512];
	
	while((user_check = getopt(argc, argv, "Ss:t:f:")) != -1) 
	{
		switch(user_check) 
		{ 
			case 'S':
				file_access_path |= 1;
				break; 
			case 'f': 
				file_access_path |= (1 << 2);
				filecheck = 1;
				strcpy((char*)filestr,optarg); 
				break;
			case 's': 
				file_access_path |= (1 << 1);
				sizeofbyte = atoi(optarg); 
				break;     
			case 't': 
				file_access_path |= 0;
				IsUser_CheckT = 1;
				if(strcmp("d",optarg) == 0)
					g_IsFile = 2; 
				else if(strcmp("f",optarg) == 0)
					g_IsFile = 1; 
				else
					printf("\n Invalid -t Option %s \n",optarg);                    
				break;                     
		}
	}

	if((optind < argc) && (filecheck == 1))
	{            
		g_file_depth = atoi(argv[optind]);  
		optind++;                
	}

	(argv[optind] == NULL) ? (g_fileuserpath = default_name) : (g_fileuserpath = argv[optind]);

	DIR *dr = NULL;
	if((dr = opendir(g_fileuserpath)) == NULL)
	{
	       return 	printf("Open directory error: '%s'\n", g_fileuserpath);
	}
	funtmp_ptr_displayfile = display_files;
	
	while((de = readdir(dr)) != NULL)
	{
		sprintf(start_path, "%s/%s", g_fileuserpath, de->d_name);
		lstat(start_path, &file_details);
		
		if(strcmp(de->d_name, ".") == 0 || strcmp(de->d_name, "..") == 0)
		{
			continue;
		}
		else if(((de->d_type == DT_REG) || (S_ISLNK(file_details.st_mode))) && (g_IsFile != 2))
		{
			ListFileDirInfo(de->d_name, 2);
		}
		else if((de->d_type == DT_DIR))
		{
			ListFileDirInfo(de->d_name, 2);
			filecntval = 1;
			sprintf(dir_info, "%s/%s", g_fileuserpath, de->d_name);
			if((g_file_depth >= (file_indent)) && (file_access_path >=4))
				funtmp_ptr_displayfile(dir_info);
			else if(file_access_path < 4)
				funtmp_ptr_displayfile(dir_info);
		}

	}



	return 0; 
}
void display_files(char *path)
{
	struct dirent *de;
	char start_path[2048] = {0};
	int tempfile_indent = 0;
	int filecntval_temp = 0;
	
	if(path == NULL)
	{
		printf("Open directory error: '%s'\nPlease provide directory path\n", path);
		return;
	}
	DIR *dr = opendir(path);
	if(dr == NULL)
	{
		printf("Open directory error: '%s'\nPlease provide valid directory\n", path);
		return;
	}
	while((de = readdir(dr)) != NULL)
	{
		sprintf(start_path, "%s/%s", path, de->d_name);
		lstat(start_path, &file_details);
		
		if(strcmp(de->d_name, ".") == 0 || strcmp(de->d_name, "..") == 0)
		{
			continue;
		}
		else if(((de->d_type == DT_REG) || (S_ISLNK(file_details.st_mode))) && (g_IsFile != 2))
		{
			ListFileDirInfo(de->d_name, 1);
		}
		else if((de->d_type == DT_DIR))
		{
			sprintf(start_path, "%s/%s", path, de->d_name);
			lstat(start_path, &file_details);
			ListFileDirInfo(de->d_name, 1);
			tempfile_indent = file_indent;
			file_indent++;
			filecntval_temp = filecntval;
			filecntval = 1;
			if((g_file_depth >= (file_indent+1)) && (file_access_path >=4))
				display_files(start_path);
			else if(file_access_path <=3)
				display_files(start_path);
			file_indent = tempfile_indent;
			filecntval = filecntval_temp;
		}
	}
	return;
}