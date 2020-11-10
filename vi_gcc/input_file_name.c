 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>

 int main(){
     FILE *fp; //file pointer
     char file_name[30]; //for input file name
     int size; //file size
     int count; //print count
     char *buffer; //for stdout
 
     printf("input file name what you want save maximum 29 chars\n");
     scanf("%s", file_name); //input a file name for read
      fp = fopen(file_name, "a+"); //read & write mode, this mode add line aft    er last line
  
     fputs("Korean Polytechinc University\n", fp); //add line
     fputs("Department of Electronics Engineering\n", fp); //add line
     fputs("Embedded SoftWare\n", fp); //add line
     fseek(fp, 0, SEEK_END); //seek for file End
     size = ftell(fp); //file size
 
     buffer = malloc(size + 1); //malloc for buffer +1 is meaning of null
 
     memset(buffer, 0, size + 1);
 
     fseek(fp, 0, SEEK_SET);
        count = fread(buffer, size, 1, fp);
  
      printf("%s", buffer);
      fclose(fp);
      return 0;
  }

