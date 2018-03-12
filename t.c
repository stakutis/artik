
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BASE_GPIO_DIR "/sys/class/gpio/"

int main(int argc, char **argv) {
  FILE *fd;
  char fName[200];
  int pin;
  int result;
  char *command;
  char *in_or_out;
  int loop=1;

  if (argc<3) {
    printf("Syntax: artik pin direction in|out\n");
    printf("    or: artik pin get/'a value to set' [loop]\n");
    return 0;
  }
  
  pin=atoi(argv[1]);
  command=argv[2];
  if (strcmp(command,"direction")==0) in_or_out=argv[3];
  if (argc==4) loop=atoi(argv[3]);

  if (strcmp(command,"direction")==0) {
    printf("Will do a DIRECTION!\n");
    if (strcmp(in_or_out,"in")!=0 && strcmp(in_or_out,"out")!=0) {
      printf("Need either the word 'in' or 'out'!\n");
      return -1;
    }
    printf("First requesting the pin by writing to export");
    sprintf(fName,"%sexport",BASE_GPIO_DIR);
    fd=fopen(fName,"w");
    printf("fName:%s Export fd is %d\n",fName,fd);
    result=fprintf(fd,"%d\n",pin);
    printf("Result of the export write: %d to fName:%s to pin:%d\n",result,fName,pin);
    fclose(fd);
    printf("Doing a set for %s\n",in_or_out);
    sprintf(fName,"%sgpio%d/direction",BASE_GPIO_DIR,pin);
    printf("fname %s in_or_out:%s\n",fName,in_or_out);
    fd=fopen(fName,"w");
    printf("fName:%s fd:%d\n",fName,fd);
    result=fprintf(fd,"%s\n",in_or_out);
    printf("Done, result:%d!",result);
    return 0;
  }
  printf("hi\n");
  if (strcmp(command,"get")==0) {
    char value[100];
    printf("will do a get of pin %d loop:%d\n",pin,loop);
    sprintf(fName,"%sgpio%d/value",BASE_GPIO_DIR,pin);
    while (loop) {
      fd=fopen(fName,"r");
      value[1]=0;
      fread(value,1,1,fd);
      fclose(fd);
      printf("Value:%s\n",value);
      loop--;
      if (loop) {
	sleep(1);
	fseek(fd,0,SEEK_SET);
      }
    }
    return 0;
  }  

  if (strcmp(command,"get")!=0) {
    printf("Appears we are going to SET a value to the pin!\n");
    sprintf(fName,"%sgpio%d/value",BASE_GPIO_DIR,pin);
    printf("Will write %s to %s\n",command,fName);
    fd=fopen(fName,"w");
    printf("FD is %d\n",fd);
    result=fprintf(fd,"%s\n",command);
    printf("Result of write is %d\n",result);
    fclose(fd);
    return 0;
  }
  
  printf("Unknown command!");
  return -1;
  /*


  
  fd=fopen("/sys/class/gpio/export","w");
  printf("hi fd:%d\n",fd);
  fprintf(fd,"1\n");
  */
}
