```
//1)Write a C program to create a new text file and write "Hello, World!" to it
#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
int main()
{
	int fd;
	int bytesread;
	fd=open("new.txt",O_WRONLY|O_CREAT,0666);
	char buf[32]={0};
	fgets(buf,32,stdin);
	bytesread=write(fd,buf,(sizeof(buf)-1))>0;
	close(fd);
}```
* * * *  * * * *  * * * * * * * * * * * * * * * * * * ** * * * * **  * * * * *
2) Develop a C program to open an existing text file and display its contents?
#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
int main()
{
	int fd=open("new.txt",O_RDONLY);
	char buf[32];
	int bytesread;
	while((bytesread=read(fd,buf,sizeof(buf)-1))>0)
	{
			
		buf[bytesread]='\0';
		printf("%s",buf);	
	}
	
	close(fd);
}/*
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
    int fd = open("new.txt", O_RDONLY);
    if (fd < 0) {
        perror("open failed");
        return 1;
    }

    char buf[32];
    ssize_t bytesread;

    // Read and display until EOF
    while ((bytesread = read(fd, buf, sizeof(buf) - 1)) > 0) {
        buf[bytesread] = '\0';  // Null-terminate to treat as string
        printf("%s", buf);
    }

    close(fd);
    return 0;
}*/

**************************************************************************************

3)//3Implement a C program to create a new directory named "Test" in the current 
//directory?
#include<stdio.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<stdlib.h>
int main()
{
	int status;
	status = system("mkdir Test");
	//status=mkdir("Test",0777);
	if(status==0)
	{
		printf("Directory test created successfully\n");
	}
	else
	{
		printf("not created");
	}
}

***********************************************************************************************

4)Write a C program to check if a file named "sample.txt" exists in the current directory?
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>

int main()
{
	char *filename=(char*)malloc(100*sizeof(char));
	scanf("%s",filename);
	if(access(filename,F_OK)==0)
	{
		printf("%s file exist",filename);
	}
	else
	{
		printf("%s is not exist",filename);
	}
}

***********************************************************************************************

5)//Develop a C program to rename a file from "oldname.txt" to "newname.txt"
#include<stdio.h>
int main()
{
	if(rename("new.txt","new1.txt")==0)
	{
		printf("renamed successfully\n");
	}
	else
	{
		printf("not renamed\n");
	}
}

**************************************************************************************************

6)//Implement a C program to delete a file named "delete_me.txt"?
#include<stdio.h>
int main()
{
	if(remove("new1.txt")==0)
	{
		printf("deleted\n");
	}
	else
	{
		printf("not deleted");
	}
}

************************************************************************************

7)//Write a C program to copy the contents of one file to another?

#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
int main()
{
	int fd=open("1.c",O_RDONLY,0666);
	int fd1=open("file.txt",O_CREAT|O_WRONLY,0666);
	int bytesread;
	char buf[32];
	while((bytesread=read(fd,buf,31))>0)
	{
		buf[bytesread]='\0';
		write(fd1,buf,bytesread);
	}
	close(fd);
	close(fd1);
}

*******************************************************************************

8)// Develop a C program to move a file from one directory to another?
#include<stdio.h>
int main()
{
	char *src="/home/breddy1/lsp/files/new.txt";
	char *dst="/home/breddy1/lsp/files/Test/new.txt";
	if((rename(src,dst))==0)
	{
		printf("moved");
	}
	else
	{
		printf("not moved");
	}

}

***************************************************************************************

9)//Implement a C program to list all files in the current directory?
#include<stdio.h>
int main()
{
	execl("/bin/ls","ls",NULL);
}

*****************************************************************************************

10)//10. Write a C program to get the size of a file named "file.txt"?
#include<stdio.h>
#include<sys/stat.h>

int main()
{
	const char *filename = "file.txt";
	struct stat st;
	if(stat(filename,&st)==0)
	{
		printf("Size of %s: %ld bytes\n", filename, st.st_size);
	}
	else
	{
		perror("stat");
	}
}

*********************************************************************************************

11)// Develop a C program to check if a directory named "Test" exists in the current directory?
#include<stdio.h>
#include<sys/stat.h>
#include<sys/types.h>

int main()
{
	const char *dir_name="Test";
	struct stat st;
	if(stat(dir_name,&st)==0 && S_ISDIR(st.st_mode))
	{
		printf("%s directory is present\n",dir_name);
	}
	else
	{
		printf("%s directory not prresent\n",dir_name);
	}
}

*************************************************************************************************

12)// Implement a C program to create a new directory named "Backup" in the parent directory?
#include<stdio.h>
#include<stdlib.h>
#include<sys/stat.h>

int main()
{
	const char *file="../Backup";
	if(mkdir(file,0777)==0)
	{
		printf("%s created in parent directory\n",file);
	}
	else
	{
		printf("not created");
	}
}

***********************************************************************************************************

13)#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#include <unistd.h>
void listFilesRecursively(const char *basePath);

int main() {
    char basePath[100];

    printf("Enter directory path: ");
    scanf("%s", basePath);

    printf("Files and directories under %s:\n", basePath);
    listFilesRecursively(basePath);

    return 0;
}
void listFilesRecursively(const char *basePath)
{
	char path[1000];
	struct dirent *dp;
	DIR *dir=opendir(basePath);
	while((dp=readdir(dir))!=NULL)
	{
		if(strcmp(dp->d_name,".")==0 || strcmp(dp->d_name,"..")==0)
			continue;

		snprintf(path,sizeof(path),"%s/%s",basePath,dp->d_name);
		printf("%s\n",path);


		struct stat statbuf;
		if(stat(path,&statbuf)==0 && S_ISDIR(statbuf.st_mode))
			listFilesRecursively(path);
		
	}

closedir(dir);
}

*******************************************************************************************

14)//. Develop a C program to delete all files in a directory named "Temp"?
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>

int main() {
    const char *dirName = "./Test"; // Current directory's "Temp" folder
    struct dirent *entry;
    DIR *dir = opendir(dirName);

    if (dir == NULL) {
        perror("Unable to open directory");
        return 1;
    }

    char path[1024];

    while ((entry = readdir(dir)) != NULL) {
        // Skip . and ..
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;

        snprintf(path, sizeof(path), "%s/%s", dirName, entry->d_name);

        struct stat statbuf;
        if (stat(path, &statbuf) == 0) {
            if (S_ISREG(statbuf.st_mode)) {
                if (remove(path) == 0) {
                    printf("Deleted file: %s\n", path);
                } else {
                    perror("Failed to delete file");
                }
            }
        }
    }

    closedir(dir);
    return 0;
}

***********************************************************************************************

15)//Implement a C program to count the number of lines in a file named "data.txt"?
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
    int fd = open("new.txt", O_RDONLY);
    if (fd < 0) {
        perror("File open failed");
        return 1;
    }

    int line_count = 0;
    char buf[32];
    int bytesread;

    while ((bytesread = read(fd, buf, sizeof(buf))) > 0) {
        for (int i = 0; i < bytesread; i++) {
            if (buf[i] == '\n') {
                line_count++;
            }
        }
    }

    close(fd);
    printf("Total lines in data.txt: %d\n", line_count);
    return 0;
}

*********************************************************************************************************

16)//Write a C program to append "Goodbye!" to the end of an existing file named "new.txt"?
#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>

int main()
{
	int fd=open("new.txt",O_WRONLY|O_APPEND);
	char buf[]="Good Bye";
	int bytes_read=write(fd,buf,sizeof(buf)-1);
	close(fd);
}

******************************************************************************************************

17)//17. Implement a C program to change the permissions of a file named "file.txt" to read only?
#include<stdio.h>
#include<sys/stat.h>

int main()
{
	char *filename="file.txt";
	if(chmod(filename,0444)==0)
	{
		printf("permissions of %s changed to read_only mode\n",filename);
	}
	else
	{
		printf("chmod failed");
	}
}

**********************************************************************************************************

18)// Write a C program to change the ownership of a file named "file.txt" to the user "user1"?
#include<stdio.h>
#include<unistd.h>
#include<pwd.h>
#include<sys/types.h>

/*int main()
{
	char *filename="file.txt";
	char *new_owner="user1";
	struct passwd *pw=getpwnam(new_owner);
	if(chown(filename,pw->pw_uid,-1)==0)
	{
		printf("ownership of file %s changed to %s\n",filename,new_owner);
	}
}*/
#include <stdio.h>
#include <unistd.h>
#include <pwd.h>
#include <sys/types.h>
#include <stdlib.h>  // for exit()

int main() {
    const char *filename = "file.txt";
    const char *new_owner = "user1";

    // Step 1: Get user details
    struct passwd *pw = getpwnam(new_owner);
    if (pw == NULL) {
        perror("getpwnam"); // Error if user not found
        exit(EXIT_FAILURE);
    }

    // Step 2: Change ownership
    if (chown(filename, pw->pw_uid, -1) == 0) {
        printf("Ownership of file '%s' changed to '%s'\n", filename, new_owner);
    } else {
        perror("chown"); // Print error if chown fails
        exit(EXIT_FAILURE);
    }

    return 0;
}

***************************************************************************************************************

19)//Develop a C program to get the last modified timestamp of a file named "file.txt"?
#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<time.h>
#include<sys/types.h>
#include<sys/stat.h>
int main()
{
	char *filename="file.txt";
	struct stat st;
	if(stat(filename,&st)==0)
	{
		printf("last modified of file '%s' time is  %s",filename,ctime(&st.st_mtime));
	}
}

**************************************************************************************************

20) Implement a C program to create a temporary file and write some data to it?
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main() {
    char template[] = "/tmp/tempfileXXXXXX";  // Template for mkstemp

    // Create and open a unique temporary file
    int fd = mkstemp(template);

    printf("Temporary file created: %s\n", template);

    // Write data to the file
    const char *data = "Temporary file content from system programming.\n";
    if (write(fd, data, strlen(data)) == -1) {
        perror("write");
        close(fd);
        unlink(template); // Remove file manually if needed
        return 1;
    }

    // Optional: read back data
    lseek(fd, 0, SEEK_SET);  // Move file pointer to beginning
    char buffer[100];
    int n = read(fd, buffer, sizeof(buffer) - 1);
    if (n >= 0) {
        buffer[n] = '\0';
        printf("Read from file: %s", buffer);
    }

    // Clean up
    close(fd);
    unlink(template); // Manually delete the temp file

    return 0;
}


*******************(OR)***********************************************
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main()
{
	char temp[]="/tmp/tempfileXXXXXX";//creates a file in /temp.here 6 XXXXXX are mandatory
	int fd=mkstemp(temp);//creates and opens a new unique temporary file
	char buf[]="hello my name is bharathi";
	int bytes=write(fd,buf,strlen(buf));
	lseek(fd,0,SEEK_SET);//rewinds to starting point
	char buf1[bytes+1];
	int bytesread=read(fd,buf1,sizeof(buf1)-1);
	buf1[bytesread]='\0';
	printf("%s",buf1);
	close(fd);
	sleep(5);	
	unlink(temp);//unlink manually.mkstemp won't delete temp file manually
}

*******************************************************************************************

21)//21. Write a C program to check if a given path refers to a file or a directory?
#include<stdio.h>
#include<unistd.h>
#include<sys/stat.h>
#include<sys/types.h>
int main()
{
	 char path[100];
	scanf("%s",path);
	struct stat buf;
	if(stat(path,&buf)==0)
	{
		if(S_ISREG(buf.st_mode))
		{
			printf("'%s' is regular file\n",path);
		}
		else if(S_ISDIR(buf.st_mode))
		{
			printf("'%s' is directory",path);
		}
		else
		{
			printf("neither file nor directory\n");
		}
	}
}

***********************************************************************************************************


22)// Develop a C program to create a hard link named "hardlink.txt" to a file named "source.txt"?
#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
int main()
{
	char *src1="source.txt";
	char *src2="hardlink.txt";

	if(link(src1,src2)==0)
	{
		printf("hard link created\n");
	}
	else
		{
			perror("hardlink error");
		}
}

******************************************************************************************************

23)// Implement a C program to read and display the contents of a CSV file named "data.csv"?
#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>

int main()
{
	int fd=open("my.csv",O_RDONLY);
	char buf[32]={0};
	int bytesread;
	while((bytesread=read(fd,buf,sizeof(buf)-1))>0)
	{
		write(STDOUT_FILENO,buf,bytesread);
	}
	close(fd);
}

********************************************************************************************

24)#include<stdio.h>
#include<unistd.h>
/*int main()
{
	char buf[100];
	if(getcwd(buf,sizeof(buf))!=NULL)
	{
		printf("'%s' is current working directory",buf);
	}
}*/
//in lsp
int main()
{
	char buf[100];
	int len=readlink("/proc/self/cwd",buf,sizeof(buf)-1);
	if(len==-1)
	{
		perror("readlink failed");
	}
	buf[len]='\0';
	printf("%s",buf);
}

*****************************************************************************************************

25) Develop a C program to get the size of a directory named "Documents"?
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>

int main() {
    const char *dirname = "Documents";
    DIR *dir;
    struct dirent *entry;
    struct stat fileStat;
    char filepath[1024];
    long long total_size = 0;

    // Open the directory
    dir = opendir(dirname);
    if (dir == NULL) {
        perror("Failed to open directory");
        return 1;
    }

    // Read entries inside the directory
    while ((entry = readdir(dir)) != NULL) {
        // Skip "." and ".."
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;

        // Build the full path to the file
        snprintf(filepath, sizeof(filepath), "%s/%s", dirname, entry->d_name);

        // Get file status
        if (stat(filepath, &fileStat) == -1) {
            perror("stat failed");
            continue;
        }

        // Only count regular files (not directories)
        if (S_ISREG(fileStat.st_mode)) {
            total_size += fileStat.st_size;
        }
    }

    closedir(dir);

    printf("Total size of files in '%s': %lld bytes\n", dirname, total_size);

    return 0;
}




