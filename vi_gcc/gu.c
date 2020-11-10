   #include <stdio.h>
   
   int main(){
       int dan = 0;
       do {
           printf("Input dan\n");
           scanf("%d",&dan);
           if (dan == 0) {
               return 0;
          } else if(dan>9 || dan < 0){
              printf("Wrong input...(0:quit, 2~9: dan    )\n");
              continue;
          }
          for(int i=1; i<10; i++){
              printf("%d x %d = %d\n",dan, i, dan * i    );
          }
      }
      while (dan != 0);
      return 0;
  }      