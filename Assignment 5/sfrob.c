#include<stdio.h>
#include <sys/stat.h>
#include<stdlib.h>
#include <unistd.h>
#define SPACE       ' '

//Function to compare unfrobnicated ArrW
int cmpNum=0;

int frobcmp(char const *a, char const *b)
{
    cmpNum++;
  const char *ptr1 = *(const char **)a; 
  const char *ptr2 = *(const char **)b;
  for ( ; ; ptr1++, ptr2++)
    {
      int num1 = (int)*ptr1;
      int num2 = (int)*ptr2;
        
      if (num1 == 32 && num2 == 32)
	return 0;
      else if (num2 == 32 ||((num1 ^42) > (num2 ^42)) )
	return 1;
      else if (num1 == 32 ||((num1 ^42) < (num2 ^42)) )
	return -1;
    }
}     

int cmpwrapper(const void *a, const void *b)
{
  return frobcmp(a, b);
}

void ErrorReport()
{
  fprintf(stderr, "Error");
  exit(1);
}

void sfrob(){
  struct stat fileStat;
  if (fstat(0,&fileStat) < 0) {
    ErrorReport();
  }
  int initSize=sizeof(char*);
  if (S_ISREG(fileStat.st_mode)) {
    int initSize=fileStat.st_size;
  }
  char* word=(char*)malloc(initSize *sizeof(char));
  char** ArrW=(char**)malloc(0);
  
  int count=0;
  int ArrWCount=0;
  char cur=getchar();
  char prev=SPACE;
 
 while(read(0, &cur, sizeof(char)) > 0){
    if(cout>=initSize){
    word = realloc(word, (count+1) * sizeof(char));
    }
    word[count]=cur;
    count++;
    if(cur == SPACE){
      char** temp2 = realloc(ArrW, (ArrWCount+1)*sizeof(char*));
      if(temp2==NULL)
	{
	  free(ArrW);
	  ErrorReport();
	}
      else{
	ArrW=temp2;
	ArrW[ArrWCount] = word;
	ArrWCount++;
	word=NULL;
	word = (char *) malloc(sizeof(char));
	count = 0;
      }
    }
    else
      {
	if(temp1==NULL)
	  {
	    free(ArrW);
	    ErrorReport();
	  }
	else
	  {
	    word=temp1;
	  }
      }

    if(cur != EOF)
      prev = cur;
    cur=getchar();
  }
     
  if(prev != SPACE&&cur==EOF){
    word[count] = SPACE;
    char** temp3 = realloc(ArrW, (ArrWCount+1)*sizeof(char*));
    if(temp3==NULL)
      {
	free(ArrW);
	ErrorReport();
      }
    else
      ArrW=temp3;
    ArrW[ArrWCount] = word;
    ArrWCount++;
  }
  qsort(ArrW, ArrWCount, sizeof(char*), cmpwrapper);
  int i=0;
  while(i<ArrWCount){
    int j = 0;
    while(ArrW[i][j] != SPACE){
      putchar(ArrW[i][j]);
      j++;
    }
    putchar(SPACE);
    i++;
  }
  
  free(ArrW);
}

int main(){
  sfrob();
} 
