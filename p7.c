#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>

#include <dirent.h>
#include <stdio.h>
#include <string.h>

/* Created by: Ben Smith
 * Class: CS3060 X01 summer 2021 B1
 * Assignment: Project 7
 */

long long int total_bytes;

void call_files(char *base_file_p, int tabIndex)
{
    char path[1500];
    struct dirent *dirE;
    struct stat sts;
    DIR *dir = opendir(base_file_p);

    if (dir == 0)
        return;

    while ((dirE = readdir(dir)) != NULL)
    {
        if (strcmp(dirE->d_name, ".") != 0 && strcmp(dirE->d_name, "..") != 0)
        {
            //find size of file
           	lstat(dirE->d_name, &sts);
           	total_bytes += sts.st_size;

        	if(dirE->d_type == DT_DIR)
            	printf("%*sdir %s\n" ,tabIndex ,""  ,base_file_p);
            else
            	printf("%*s %d:%s\n"  ,tabIndex ,"" ,sts.st_size ,base_file_p);

            strcpy(path, base_file_p);
            strcat(path, "/");
            strcat(path, dirE->d_name);

            call_files(path, tabIndex+1);
        }
    }

    closedir(dir);
}



int main(int argc, char *argv[])
{
	total_bytes = 0;

	if(argc < 2)
   		call_files(".", 0);
   	else
   		call_files(argv[1], 0);

   	printf("\nTotal file space used: %lli\n", total_bytes);
	
}