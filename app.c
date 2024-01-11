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


int main2(){
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


typedef struct{
  char fieldName[50];
  // field Type soon.

} Field;

typedef struct{
  char tableName[50];
  char tableFileName[50];
  Field fields[10]; //for now max of 10 fields,
  int fieldCount;
  int lastID;

} tableMetaData;


void writeTableMetadata(FILE *file, tableMetaData *metadata){
  fwrite(metadata, sizeof(tableMetaData),1,file);
}

void readTableMetada(FILE *file, tableMetaData *metadata){
//  fread();

}


void addTableMetadata(const char *header_file,tableMetaData *metadata){
  FILE *file = fopen(header_file,"ab");
  if (!file){
    perror("Error opening header file");
    return;
  }
    fwrite(metadata, sizeof(tableMetaData), 1, file);


  fclose(file);

}


void createNewTable(const char *header_file){
  tableMetaData metadata;
  printf("Enter table name: ");
  scanf("%49s",metadata.tableName);

  printf("Enter table file name: ");
  scanf("%49s",metadata.tableFileName);

  printf("How many fields: ");
  scanf("%d",&metadata.fieldCount);

  for (int i = 0; i < metadata.fieldCount; ++i){
    printf("Enter %d field name: ",i+1);
    scanf("%49s",metadata.fields[i].fieldName);

  }
  
  metadata.lastID = 0;
  addTableMetadata(header_file, &metadata);
  FILE *table_file = fopen(metadata.tableFileName, "wb");

  if (!table_file){
    perror("Error creating table file.");
    return ;
  }
  fclose(table_file);

}






int main(){
  printf("Do you want to create a new table? (y/N) ");
  char new_table_q[2];
  scanf("%s",new_table_q);
  if (strcmp(new_table_q,"y") == 0){
    printf("Create New Table mofo");
    createNewTable("header.bin");

  }
  else {
    printf("No New Table mofo");
  }

  return 0;

}


