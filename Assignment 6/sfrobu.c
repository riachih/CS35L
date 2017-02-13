#include<stdio.h>
#include <sys/stat.h>
#include<stdlib.h>
#include <unistd.h>
#define SPACE       ' '

//Function to compare unfrobnicated ArrW
//Rewrite the sfrob program you wrote for Homework 5 so that it uses system calls rather than <stdio.h> to read standard input and write standard output. If standard input is a regular file, your program should initially allocate enough memory to hold all the data in that file all at once, rather than the usual algorithm of reallocating memory as you go. However, if the regular file grows while you are reading it, your program should still work, by allocating more memory after the initial file size has been read.

//Your program should do one thing in addition to the Homework 5 program. If successful, it should use the fprintf function to output a line of the following form to standard error before finishing:

//Comparisons: 23451

//keep track of the invocation of frobcmp
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
  //initially allocate enough memory
  //but if the file grows at the same time, code should still work
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
  char cur;
  //int wordcount=0;
  while(read(0, &cur, sizeof(char)) > 0){
    if (count>= initSize) {  //actual size should be count+1
      word=realloc(word, (count+1)*sizeof(char));
      // if (temp1==NULL) {
      //	free(word);
      //	free(ArrW);
      //	ErrorReport();
      //}
      //else {
      //word=temp1;
      //initSize++;
      //}
      // }
    
    word[count]=cur;
        
    //char* temp1 = realloc(word, (count+1) * sizeof(char));
    //word[count]=cur;
    count++;
        
    if(cur == SPACE){  //hit the end of the word
      ArrWCount++;
    }
  }
    
  if(word[count-1]!=SPACE){ //
    word= realloc(word, (count+1)*sizeof(char));
    //if(temp3==NULL)
    //{
    //	free(word);
    //	ErrorReport();
    //}
    // else
    //word=temp3;
    word[count-1] = SPACE;
    count++;
    ArrWCount++;
  }
    
  //after checking boundry in the first place, there would definitely be enough spaces for the word
  //    else//if this is not the end of the word,
  //      {
  //if(temp1==NULL)
  //  {
  //    free(ArrW);
  //    ErrorReport();
  //  }
  //else
  //  {
  //    word=temp1;
  //  }
  //}
  char* temporary=word;
  int k=0;
    
  ArrW=(char**)remalloc(ArrWCount*(sizeof(char*)));
  //if (temp2==NULL) {
  // free(ArrW);
  // ErrorReport();
  //}
  //else {
  //ArrW=temp2;
  // }
    
  for(;k<ArrWCount-1;k++)
    {
      ArrW[k]=temporary;
      while (*temporary!=SPACE) {
	temporary++;
      }
      temporary++;
    }

  qsort(ArrW, ArrWCount, sizeof(char*), cmpwrapper);

  char* hold = NULL;
  int i=0;
  while(i<ArrWCount){
    int j = 0;
    while(ArrW[i][j] != SPACE){
      hold=&((ArrW[i][j]));
      write(1, hold, 1);
      j++;
    }
    *hold=SPACE;
    write(1, hold, 1);
    i++;
  }

  free(word);
  free(ArrW);
  fprintf(stderr, "Comparisons: %d", cmpNum);
}

int main(){
  sfrob();
} 
