#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct{
  int id;
  char data[100];
} Record;


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

void writeRecord(FILE *table_file, Record *record, tableMetaData *metadata){
  metadata->lastID++;
  record->id = metadata->lastID;
  fwrite(&(record->id),sizeof(record->id),1,table_file);
  fwrite(record->data,sizeof(char), sizeof(record->data),table_file);

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
  /*
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
  */

  Record record = {
    .data = "Hello",
  };

  

  return 0;

}


