#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <errno.h>
//tr2b
//This one should use the buffer getchar and putchar

//requirement:
//takes two operands
//HAVE TO BE THE SAME LENGTH
//FROM CANNOT HAVE DUPLICATE BYTES

int main (int argc, char *argv[])
{
  //only two files allowed
  if(argc!=3)
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
  
  char buf;
  int match=0;
  while (buf!=EOF) {
    buf=getchar();
    int k=0;
    match=0;
    for (;k<lenFrom;k++) {
      if (buf==from[k]) {
	putchar(to[k]);
	match=1;
	break;
      }
    }
    
    if (!match) {
      putchar(buf);
    }
  }
  
  //use getchar and putchar to replace the bytes in from
  
  return 0;
}
