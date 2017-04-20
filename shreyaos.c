#include <stdio.h>
#include <string.h>

int fileSystemId = -1;

struct DISK
{
	int diskNum;
	char* diskName;
};

struct FS
{
	struct DISK diskinuse;
	int fileSystemID;
	int location;
};

struct FILEE
{
	char* filename;
	struct FS fs;
};



struct FILEE SFS[100];
struct FS filesystem[100];
struct DISK disk[100];

int createSFS( char* filename, int nbytes)
{

	int i;
	for(i=0;i<=100;i++)
	{

		if(disk[i].diskName== filename)
		{
			break;
		}
		else if (disk[i].diskName== NULL) 
		{
			disk[i].diskName=filename;
			disk[i].diskNum=i;
			break;
		}
	}

	//printf(disk[i].diskName);
	
	for(i=0;i<=100;i++)
	{
		if(filesystem[i].location== NULL)
		{
			filesystem[i].diskinuse=disk[i];
			filesystem[i].fileSystemID=i;
			filesystem[i].location= 64*i; //change
			FILE * f= fopen(filename, "w");
			fprintf(f, "\n" ); //empty superblock.loc=0
			//inode bitmap
			char str[33];
			for (int i=0;i<31;i++)
				str[i]= '0';
			str[32]='\0';
			fprintf(f,str);
			fprintf(f,";");
			fprintf(f,str);
			fprintf(f,";");
			fprintf(f,str);
			fprintf(f,";");
			fprintf(f,str);
			fprintf(f,";");
			fprintf(f,str);
			fprintf(f,";");
			fprintf(f,"\n");
			//fprintf(f, str+";"+ str+ ";" + str+ ";" + str + ";" + str+ "\n");  
			//data bitmap
			char str2[57];
			for (int i=0;i<56;i++)
				str2[i]= '0';
			str2[57]='\0';
			fprintf(f, str2 );
			//5 inode bitmaps
			fprintf(f, "\n" );
			fprintf(f, "\n" );
			fprintf(f, "\n" );
			fprintf(f, "\n" );
			fprintf(f, "\n" );
			//data 
			int j;
			for(j=1;i<=56;i++)
				fprintf(f, "\n" );
			fprintf(f,"End of file system. New file system shall come here. ");
			fclose(f);
			break;
		}

	}
	return filesystem[i].fileSystemID;
	//return 0;
}

void print_inodeBitmaps(int fileSystemId)
{
	FILE *file;
		// get the disk and the location in the disk
		int i,j;
		for(i=0;i<100;i++)
		{
			if(filesystem[i].fileSystemID==fileSystemId)
			{
				j = i;
				//printf("%d",j);
				break;
			}
		}
		//open the disk
		file=fopen(filesystem[j].diskinuse.diskName,"r"); 
		if(file==NULL)
		{
			printf("File System does not exist in the disk");
			return;
		}
		else
		{
			//read line no. loc+2.
			int count=0;
			char line[10000];
			while(fgets(line, sizeof(line),file) )
			{
				//printf("%s",line);
				//strcpy(ans,line);
				//printf("%s", ans);
				if(count== filesystem[j].location+1)
				{
					for(i=0;i<strlen(line);i++)
					{
						if(line[i]!='\n') 
							{
								if(line[i]==';')
									printf("\n");
								else
									printf("%c", line[i]);
							}
					}
					printf("\n");
				}

					count++;
			}
		}

}


void print_FileList(int fileSystemId)
{
	// for (int i=0;i< 100;i++)
	// {
	// 	if(SFS[i]!= '\0')
	// 	{
	// 		printf("%s\n",SFS[i].filename);
	// 	}
	// }
}

void print_dataBitmaps(int fileSystemId)
{
	FILE *file;
		// get the disk and the location in the disk
		int i,j;
		for(i=0;i<100;i++)
		{
			if(filesystem[i].fileSystemID==fileSystemId)
			{
				j = i;
				//printf("%d",j);
				break;
			}
		}
		//open the disk
		file=fopen(filesystem[j].diskinuse.diskName,"r"); 
		if(file==NULL)
		{
			printf("File System does not exist in the disk");
			return;
		}
		else
		{
			//read line no. loc+2.
			int count=0;
			char line[10000];
			while(fgets(line, sizeof(line),file) )
			{
				//printf("%s",line);
				//strcpy(ans,line);
				//printf("%s", ans);
				if(count== filesystem[j].location+2)
				{
					for(i=0;i<strlen(line);i++)
					{
						if(line[i]!='\n') printf("%c", line[i]);
					}
					printf("\n");
				}

					count++;
			}
		}
}

int readData( int disk, int blockNum, void* block)
{
	// find file sytsem. assunimg 0th. find corr diskName.
	int j=0,i,noBytes=0;
	FILE *file;
	file=fopen("disk.txt","r"); 
		if(file==NULL)
		{
			printf("File System does not exist in the disk");
			return;
		}
		else
		{
			//read line no. loc+8.
			int count=0;
			char line[10000];
			while(fgets(line, sizeof(line),file) )
			{
				//printf("%s",line);
				//strcpy(ans,line);
				//printf("%s", ans);
				if(count== filesystem[j].location+7+blockNum)
				{
					for(i=0;i<strlen(line);i++)
					{
						if(line[i]!='\n') 
							{
								printf("%c", line[i]);
								noBytes+=1;
							}
					}
					printf("\n");
				}

					count++;
			}
		}

return noBytes;
}

int writeData( int disk, int blockNum, void* block)
{
	
}

int readFile( int disk, int blockNum, void* block)
{
	
}

int writeFile( int disk, int blockNum, void* block)
{
	
}

int main()
{
	// printf("1. Create a file system.\n2. Add a file to file system.\n3. Read from a file.\n4. Print the bitmaps of inodes in current file system.\n5.Print the bitmaps of datablocks in current file system. \n6.Print all the files in the file system ");
	// int choice; scanf("%d",&choice);
	// switch(choice)
	// {
	// 	case 1 : {printf("Enter diskname: ");char arr[100]; scanf("%s",&arr); printf("Enter no. of bytes you want to allocate to the disk.")  int nBytes; scanf("%d", &nBytes); createSFS(arr,nBytes);}
	// 	case 2 : {}
	// 	case 3 : {}
	// 	case 4 : {printf("Enter the file system id: "); int x; scanf("%d",&x); printf("The following are bitmaps of inodes:\n"); inodeBitmaps(x); break;}
	// 	case 5 : {printf("Enter the file system id: "); int x; scanf("%d",&x); printf("The following are bitmaps of datablocks:\n"); print_dataBitmaps(x); break;} 
	// 	case 6 : {printf("Enter the file system id: "); int x; scanf("%d",&x); printf("The following is the list of files:\n"); print_Filelist(x); break;}
	// 	default: {printf("Error");break;}
	// }
	//printf("here");
//	createSFS("disk.txt",64);
	print_dataBitmaps(0);
	print_inodeBitmaps(0);
	readData(0,1,NULL);
	return 0;
}
