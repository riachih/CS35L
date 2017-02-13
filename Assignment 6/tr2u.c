#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
//tr2u
//This one should use the buffer getchar and putchar

//Write a C program tr2u.c that uses read and write to transliterate bytes,
// instead of using getchar and putchar. The nbyte arguments to read 
//and write should be 1, so that the program reads and writes single bytes at a time.

int main (int argc, char *argv[])
{
  //only two files allowed
  if(argc>3)
    {
      fprintf(stderr,"Only takes 2 files");
      return 1;
    }
  else if (argc==1)
    {
      fprintf(stderr,"NEED: two more arguments");
      return 1;
    }
  else if (argc==2)
  {
      fprintf(stderr,"NEED: one more arguments");
      return 1;
    }
  
  char* from=argv[1];
  char* to=argv[2];
  
  int lenFrom=strlen(from);
  int lenTo=strlen(to);
  
  //have to be the same length
  if(lenFrom!=lenTo)
    {
      fprintf(stderr,"From and to have be of the same length");
      return 1;
    }
  
  //from cannot have duplicate bytes
  int i=0;
  int j=1;
  for (;i<lenFrom;i++) {
    for(;j<lenFrom;j++)
      {
	if (from[i]==to[j]) {
	  fprintf(stderr,"From cannot have duplicate bytes");
	  return 1;
	}
      }
  }
  int match;
  char buf;
  while(read(0,&buf, 1))
    {
      match=0;
      int i=0;
      for(i = 0; i < strlen(from); i++)
	{
	  if(buf == from[i])
	    {
	      buf= to[i];
	      write(1,&buf,1);
	      match= 1;
	      break;
	    }
	}
      if(!match)
	{
	  write(1,&buf,1);
	}
       }
  return 0;
  //use getchar and putchar to replace the bytes in from
 }
