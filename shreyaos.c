#include <stdio.h>
#include <string.h>


int fileSystemId = -1;
int inodenumber =-1;
char dbitmap[57];
char ibitmap[161];
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
struct inode
{
	int inodeNum;
	struct FS fs;
	char* filename;
	int datablock;
};
struct FILEE
{
	char* filename;
	struct FS fs;
	int inodeNum;
};




char buffer[1024*4];
struct FILEE Files[100];
struct FS filesystem[100];
struct DISK disk[100];
struct inode Inode[160];
int createFiles( char* filename, int nbytes)
{

	int i;
	for(i=0;i<=100;i++)
	{
		Inode[i].inodeNum=-1;
		filesystem[i].location=-1;
		Files[i].filename="-1";
		disk[i].diskName="-1";
	}
	for(i=0;i<=100;i++)
	{

		if(disk[i].diskName== filename)
		{
			break;
		}
		else if (disk[i].diskName== "-1")
		{
			disk[i].diskName=filename;
			disk[i].diskNum=i;
			break;
		}
	}

	//printf(disk[i].diskName);

	for(i=0;i<=100;i++)
	{
		if(filesystem[i].location== -1)
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
			//fprintf(f,";");
			fprintf(f,str);
			//fprintf(f,";");
			fprintf(f,str);
			//fprintf(f,";");
			fprintf(f,str);
			//fprintf(f,";");
			fprintf(f,str);
			//fprintf(f,";");
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
			int count=0,k=0;
			char ans[161];
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
								{
									printf("%c", line[i]);
									ans[k]=line[i];
									k++;
								}
							}

					}
					ans[k]='\0';
					strcpy (ibitmap,ans);
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
		if(Files[i].filename!= -1 && Files[i].fs.fileSystemID==fileSystemId)
		{
			printf("%s\n",Files[i].filename);
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

		if(file==NULL )
		{
			printf("Diskk does not exist\n");
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
							strcpy(buffer,line);
						}
			}
		}

			fclose(file);

			int noBytes = strlen(buffer);
			return noBytes;

}
int writeData( int Disk, int blockNum, void* block)
{
	//printf("block num : %d\n",blockNum );
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
		if(file==NULL || temp==NULL)
		{
			printf("Diskk does not exist\n");
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
void writedata( int Disk, int blockNum, void* str)
{
	//printf("block num : %d\n",blockNum );
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
		if(file==NULL || temp==NULL)
		{
			printf("Diskk does not exist\n");
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
							strcat(line,str);
							fprintf(temp,line);
					//	fprintf(temp,"\n");
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

int readFile( int disk,int iNumofFile, void* block)
{
	int i;
	for(i=0;i<100;i++)
	{
		if(Inode[i].inodeNum==iNumofFile)
		{
			readData(disk,Inode[i].datablock,block);
			printf("read huya ? %s\n",buffer );
		}
	}
}

int writeFile( int Disk, int blockNum, void* block)
{
	int i,j,bitmap;
	for(i=0;i<100;i++)
	{
				if(Inode[i].inodeNum==-1)
				{
					int fsid= blockNum/64;
					Inode[i].fs.fileSystemID=fsid;
					Inode[i].fs.location= fsid*64;
					Inode[i].fs.diskinuse.diskNum=Disk;
					for(j=0;j<100;j++)
					{
						if(disk[i].diskNum== Disk)
							Inode[i].fs.diskinuse.diskName=disk[i].diskName;
					}
					Inode[i].inodeNum=++inodenumber;
					// printf("%d\n",Inode[i].inodeNum );
					// printf("%d\n",i );
					ibitmap[i]='1';

					writeData(Disk,fsid+2,ibitmap);
					char str[100],s1[20],s2[20],s3[20],s4[20],s5[20];
					sprintf(str,"%d",Inode[i].inodeNum);

					strcat(str," ");
					// //filename
					sprintf(s1,"%d",Inode[i].fs.fileSystemID);
					 strcat(str,s1);strcat(str," ");
					sprintf(s2,"%d",Inode[i].fs.location);
					 strcat(str,s2);strcat(str," ");
					 sprintf(s3,"%d",	Inode[i].fs.diskinuse.diskNum);
					 strcat(str,s3);strcat(str," ");
					//  sprintf(s4,"%d",Inode[i].fs.diskinuse.diskName);
					 strcat(str,Inode[i].fs.diskinuse.diskName);strcat(str," ");
					 Inode[i].datablock = blockNum;
					 sprintf(s5,"%d",Inode[i].datablock);
					 strcat(str,s5);
					 strcat(str,";");


					//  strcpy(buffer,str);
					//printf("%s %d\n","ye lo :",(i/32)+4 );
					printf("%s\n","This should print the whole inode" );
					printf("%s\n",str );
					//writeData(Disk,(i/32)+4,str);
					 writedata(Disk,(i/32)+4,str);
						//printf("heyy : %s\n",ibitmap);
						break;
				}
			}
	for(i=0;i<100;i++)
	{

			// int inodeNum;
			// int filesize;
			// int datblock;
			// char[100] filename;

			//set data bitmap to 1.
			//find the 1st 0 in the bitmap string and set it to 1.
			//read the file, read the data bitmap line, create the new string, replace it with the new string.
			if(Files[i].filename== "-1")
			{
				int fsid= blockNum/64;
				Files[i].fs.fileSystemID=fsid;
				Files[i].fs.location= fsid*64;
				Files[i].fs.diskinuse.diskNum=Disk;
				for(j=0;j<100;j++)
				{
					if(disk[i].diskNum== Disk)
						Files[i].fs.diskinuse.diskName=disk[i].diskName;
				}
				dbitmap[blockNum-1]='1';
		//		printf("%c",dbitmap[blockNum]);
			//location to change bitmap at:
			//int loc= Files[i].fs.location + 2;
			//printf("%s",dbitmap);

			//0 based.
			//we'll do it as well in writeData.
			//update inodes.
			// printf("%s",block);
			writeData(Disk,blockNum,block);
		//	printf("%d",fsid+3);
			for(int i=0;i<100;i++)
			{
				buffer[i]=dbitmap[i];
			}
			writeData(Disk,fsid+3,block);
			break;
		}

	}
	return bitmap;
}

int main()
{
	// printf("1. Create a file system.\n2. Add a file to file system.\n3. Read from a file.\n4. Print the bitmaps of inodes in current file system.\n5.Print the bitmaps of datablocks in current file system. \n6.Print all the files in the file system ");
	// int choice; scanf("%d",&choice);
	// switch(choice)
	// {
	// 	case 1 : {printf("Enter diskname: ");char arr[100]; scanf("%s",&arr); printf("Enter no. of bytes you want to allocate to the disk.")  int nBytes; scanf("%d", &nBytes); createFiles(arr,nBytes);}
	// 	case 2 : {}
	// 	case 3 : {}
	// 	case 4 : {printf("Enter the file system id: "); int x; scanf("%d",&x); printf("The following are bitmaps of inodes:\n"); inodeBitmaps(x); break;}
	// 	case 5 : {printf("Enter the file system id: "); int x; scanf("%d",&x); printf("The following are bitmaps of datablocks:\n"); print_dataBitmaps(x); break;}
	// 	case 6 : {printf("Enter the file system id: "); int x; scanf("%d",&x); printf("The following is the list of files:\n"); print_Filelist(x); break;}
	// 	default: {printf("Error");break;}
	// }
	//printf("here");
	createFiles("disk.txt",64);
// 	print_dataBitmaps(0);
// 	print_inodeBitmaps(0);
	char* block = buffer;
// 	// strcpy(buffer,"shreya");
// 	//int K = readData(0,12,block);
// 	//int t = writeData(0,13,block);
// 	strcpy(buffer,"SHREYAAA");
// 	// t = writeData(0,13,block);
// int x= writeFile(0,13,block);
//
// strcpy(buffer,"HELLO");
// print_dataBitmaps(0);
// print_inodeBitmaps(0);
//  x= writeFile(0,14,block);
//  strcpy(buffer,"Joo");
//  print_dataBitmaps(0);
//  print_inodeBitmaps(0);
//  x= writeFile(0,18,block);
//  print_dataBitmaps(0);
//  print_inodeBitmaps(0);

int i;
for(i=0;i<33;i++)
{
	printf("%d\n",i );
	strcpy(buffer,"HELLO");
	print_dataBitmaps(0);
	print_inodeBitmaps(0);
	int 	x= writeFile(0,i+9,block);
}
int y=readFile(0,17,block);

//int t = writeData(0,15,block);
	// printf("%s\n",buffer );
	return 0;
}
