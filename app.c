#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct{
  int id;
  char data[100];
} Record;


void write_file_header(FILE *file){
  char header[1000];
  memset(header,0,sizeof(header));
  const char *headerInfo = "HHEADER MASTERHEADER MASTERHEADER MASTERHEADER MASTEREADER MASTER";
  strncpy(header, headerInfo, strlen(headerInfo));

  fwrite(header, sizeof(header), 1, file);
//  fclose(file);

}



void writeTableHeader(FILE *file){
  

}


void write_record(FILE *file, Record *record){
  fwrite(&(record ->id), sizeof(record->id),1,file);
  fwrite(record ->data , sizeof(char),sizeof(record->data),file);

}

void read_record(FILE *file, Record *record){
  fread(&(record->id), sizeof(record->id), 1, file);
  fread(record->data, sizeof(char), sizeof(record->data), file);
}


int main(){
  FILE *file = fopen("data.bin","wb+");
  if (!file){
    perror("Err openin file");
    return EXIT_FAILURE;
  } 

 write_file_header(file);
 Record record = {
     2000, "new RECORDDDLUGMA LUGMNA!!!!"
  };

  write_record(file, &record);

 Record record2 = {
     2, "RECORD @!!!!"
  };

  write_record(file, &record2);


 Record record3 = {
     6969, "LAST LIGMA"
  };

  write_record(file, &record3);

  printf("%lu\n",sizeof(record));
  printf("%lu\n",sizeof(record2));
  printf("%lu\n",sizeof(record3));




  Record rRecord;
  fseek(file, 1208,SEEK_SET);
  read_record(file, &rRecord);

  printf("id: %d, dat: %s",rRecord.id,rRecord.data);



  fclose(file);

  return 0;
}
