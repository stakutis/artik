
#include <stdio.h>

typedef  struct  {
  int fish;
   int soup;
   int unk;
} mystructtypedef;

static mystructtypedef myvar = {
  .fish = 5,
  .soup = 66
};


int main(int argc, char *argv[]) {
  printf("myvarh:%d\n",myvar.fish);
  printf("myvar unk:%d\n",myvar.unk);
}
