#include <stdio.h>
#include <stdlib.h>

struct FILEE
{
	char* filename;
	int fileSystemID;
	int diskNum;
	char* diskName;
	int location;
};
struct FILEE SFS[100];
void print_inodeBitmaps(int fileSystemID);

void print_inodeBitmaps(int fileSystemID)
{
	FILE *file;
		// get the disk and the location in the disk
		int i,j;
		for(i=0;i<100;i++)
		{
			if(SFS[i].fileSystemID==fileSystemID)
			{
				j = i;
				break;
			}
		}
		//open the disk
		file=fopen(SFS[j].filename,"r");
		if(file==NULL)
		{
			printf("File System does not exist in the disk");
			return;
		}
		else
		{
			int count=0;
			char *str=NULL;
			size_t bytes = 0;
			ssize_t read ;
			char map[160];
			int k=0;
			while((read=getline(&str,&bytes,file))!=-1)
			{
				count++;
				if(count==SFS[j].location)
				{
					int y;
					for(y=0;y<sizeof(str)/sizeof(char);y++)
					{	
						if(str[y]==';')
							continue;
						else
						{
							map[k]=str[y];
							k++;
						}
					}
				}
			}
			print("%s",str);
		}

}

