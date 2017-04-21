#include <stdio.h>
#include <string.h>


int fileSystemId = -1;
char dbitmap[57];



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

struct Super
{
	int no_inodes;
	int no_datablocks;
	int beg_inodes;
	int beg_datablocks;
	int no_files;
	struct FS fss;
};

struct FILEE
{
	char* filename;
	struct FS fs;
	int inodeNum;
};

struct inode
{
	int inodeNum;
	int filesize;
	char* filename;

};


char buffer[1024*4];
struct FILEE SFS[100];
struct FS filesystem[100];
struct DISK disk[100];
struct Super superblock[100];

void defineSuper(int fileSystemId)
{
	int i,j;
	for(i=0;i<=100;i++)
	{
		if(superblock[i].fss.diskinuse.diskName==NULL)
		{
			superblock[i].no_inodes= 160;
			superblock[i].no_datablocks=  56;
			superblock[i].beg_datablocks= 9;
			superblock[i].beg_inodes= 4;
			for(j=0;j<100;j++)
			{
				if(filesystem[j].fileSystemID==fileSystemId)
				{
					printf("here");
					superblock[i].fss.fileSystemID=fileSystemId;
					superblock[i].fss.location=filesystem[j].location;
					superblock[i].fss.diskinuse.diskName= filesystem[j].diskinuse.diskName;
					superblock[i].fss.diskinuse.diskNum= filesystem[j].diskinuse.diskNum;
					FILE *f= fopen(superblock[i].fss.diskinuse.diskName,"w");

					//f<<superblock[i].no_inodes;
 fprintf(f,"%d",160);
// fprintf(f,"%d",superblock[i].no_datablocks);
// fprintf(f,"%d",superblock[i].beg_datablocks);
// fprintf(f,"%d",superblock[i].beg_inodes);
// fprintf(f,"%d",superblock[i].fss.fileSystemID);
// fprintf(f,"%d",superblock[i].fss.location);
// fprintf(f,superblock[i].fss.diskinuse.diskName);
// fprintf(f,"%d\n",superblock[i].fss.diskinuse.diskNum);
 fclose(f);
				}
				break;
			}
		}
		break;
	}

}

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
			//superblock
			superblock[i].no_inodes= 160;
			superblock[i].no_datablocks=  56;
			superblock[i].beg_datablocks= 9;
			superblock[i].beg_inodes= 4;
			superblock[i].fss=filesystem[i];
			fprintf(f,"%d%d%d%d%d%d%d",160,56,9,4,i,filesystem[i].location,superblock[i].fss.diskinuse.diskNum);
			fprintf(f,superblock[i].fss.diskinuse.diskName);

			//defineSuper(i);
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
			str2[56]='\0';
			fprintf(f, str2 );
				fprintf(f, "\n" );
			//5 inode bitmaps
			fprintf(f, "\n" );
			fprintf(f, "\n" );
			fprintf(f, "\n" );
			fprintf(f, "\n" );
			fprintf(f, "\n" );
			//data
			int j;
			for(j=1;j<=56;j++)
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
			printf("File System does not exist in the disk\n");
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
									continue;
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
	for (int i=0;i< 100;i++)
	{
		if(SFS[i].filename!= NULL && SFS[i].fs.fileSystemID==fileSystemId)
		{
			printf("%s\n",SFS[i].filename);
		}
		else
		{
			break;
		}
	}
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
			char ans[57];
			int k=0;
			while(fgets(line, sizeof(line),file) )
			{
				//printf("%s",line);
				//strcpy(ans,line);
				//printf("%s", ans);
				if(count== filesystem[j].location+2)
				{
					for(i=0;i<strlen(line);i++)
					{
						if(line[i]!='\n')
							{
								printf("%c", line[i]);
								ans[k]=line[i];
								k++;
							}
					}
					ans[k]='\0';
					strcpy (dbitmap,ans);
					printf("\n");
				}

					count++;
			}
		}
}


int readData( int Disk, int blockNum, void* block)
{
	// printf("roooo\n" );
	FILE *file;
		// get the disk and the location in the disk
		int i,j;
		for(i=0;i<100;i++)
		{
			if(disk[i].diskNum==Disk)
			{
				j = i;
				//printf("%d",j);
				break;
			}
		}
		//open the disk
		file=fopen(disk[j].diskName,"r");
		if(file==NULL)
		{
			printf("Disk does not exist\n");
			return 0;
		}
		else
		{
			//read line no. loc+2.
			int count=0;
			char line[10000];
			int noBytes;
			while(fgets(line, sizeof(line),file) )
			{
				//printf("%s",line);
				//strcpy(ans,line);
				//printf("%s", ans);
				int u=0;
				if(count== blockNum-1)
				{
					 noBytes= strlen(line);
					for(i=0;i<strlen(line);i++)
					{
						if(line[i]!='\n')
							{
									// printf("%c", line[i]);
									buffer[u]=line[i];
									u++;
							}
					}
					printf("\n");
				}

					count++;
			}
			return noBytes;
}
}
int writeData( int Disk, int blockNum, void* block)
{
//	printf("\n%s",block);
	FILE *file,*temp;
		// get the disk and the location in the disk
		int i,j;
		for(i=0;i<100;i++)
		{
			if(disk[i].diskNum==Disk)
			{
				j = i;
				//printf("%d",j);
				break;
			}
		}
		//open the disk
		file=fopen(disk[j].diskName,"r");
		temp=fopen("temp.txt","w");
		if(file==NULL)
		{
			printf("Disk does not exist\n");
			return 0;
		}
		else
		{
			int count=0;
			char line[10000];
		//	printf("%d",ch);
			while((fgets(line, sizeof(line),file)))
			{
					count++;
					//printf("%d %d\n",line,ch);
					if(count==blockNum)
						{
							fprintf(temp,block);
							fprintf(temp,"\n");
						}

					else
					{//printf("%s\n",line );
							fprintf(temp,line);
						}
			}}
		//	printf("%d\n",ch );
			// int h = fseek(file,by-1,SEEK_SET);
			// fwrite(block,1,strlen(buffer),file);
			rename("temp.txt",disk[j].diskName);
			fclose(file);
			fclose(temp);
			int noBytes = strlen(buffer);
			return noBytes;

}

int readFile( int disk, int blockNum, void* block)
{

}

int writeFile( int Disk, int blockNum, void* block)
{
	int i,j,bitmap;
	for(i=0;i<100;i++)
	{
		if(SFS[i].filename== NULL)
		{
			int fsid= blockNum/64;
			SFS[i].fs.fileSystemID=fsid;
			SFS[i].fs.location= fsid*64;
			SFS[i].fs.diskinuse.diskNum=Disk;
			for(j=0;j<100;j++)
			{
				if(disk[i].diskNum== Disk)
					SFS[i].fs.diskinuse.diskName=disk[i].diskName;
			}
			//set data bitmap to 1.
			//find the 1st 0 in the bitmap string and set it to 1.
			//read the file, read the data bitmap line, create the new string, replace it with the new string.

				dbitmap[blockNum-1]='1';
				printf("%c",dbitmap[blockNum]);
			//location to change bitmap at:
			//int loc= SFS[i].fs.location + 2;
			printf("%s",dbitmap);

			//0 based.
			//we'll do it as well in writeData.
			//update inodes.
			printf("%s",block);
			writeData(Disk,blockNum,block);
		//	printf("%d",fsid+3);
			for(int i=0;i<100;i++)
			{
				buffer[i]=dbitmap[i];
			}
			writeData(Disk,fsid+3,block);
		}
		break;
	}
	return bitmap;
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

	createSFS("disk.txt",64);
		//defineSuper(0);
	print_dataBitmaps(0);
	print_inodeBitmaps(0);
	
	char* block = buffer;
	// strcpy(buffer,"shreya");
	//int K = readData(0,12,block);
	//int t = writeData(0,13,block);
	strcpy(buffer,"SHREYAAA");
	// t = writeData(0,13,block);
int x= writeFile(0,13,block);
strcpy(buffer,"HWLLO");
int t = writeData(0,15,block);
	// printf("%s\n",buffer );
	return 0;
}
