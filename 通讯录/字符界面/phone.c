#include <stdio.h>
#include "sqlite3.h"
int select_callback(void * data, int col_count, char ** col_values, char ** col_Name){
   // 每条记录回调一次该函数,有多少条就回调多少次
  int i;
  for( i=0; i < col_count; i++){
    printf( "%s = %s\t", col_Name[i], col_values[i] == 0 ? "NULL" : col_values[i] );
  }
  printf("\n");
  return 0;
}`
int success(void *data,int col_count,char **col_values,char ** col_Name){
   printf("Sucessfully\n");
   return 0;
}
int main(int argc, char const *argv[])
{    
	 int choice=0;
	  
	 char tablename[64]="";
	 char *errmsg="";
	 sqlite3 *db;
	 int ret=sqlite3_open("a.db",&db);
	 if(ret!=SQLITE_OK){
	 	perror("sqlite_open error\n");
	 	return 0;
	 }
	 printf("**************************************************************\n");
         printf("*                         welcome!                           *\n");
	 printf("**************************************************************\n");
	 printf("*   press 1 :create Data_table(input the name of data_table) *\n");
	 printf("*   press 2 :Add new connecter                               *\n");
         printf("*   press 3 :check the messages                              *\n");
	 printf("*   press 4: delete the message about someone                *\n");
         printf("*   press 5: Change the message about someone                *\n");
         printf("*   press 0: exit!                                           *\n");
         printf("**************************************************************\n");
         printf("input the cmd>");
         scanf("%d",&choice);
          do{
        if(choice==1){
               printf("input the new table_name:");
     	       scanf("%s",tablename);
     	       printf("\n");
	       //组包
	       char cmd[64]="";
	       sprintf(cmd,"create table \'%s\' (name text, tel text ,addr text);",tablename);
	        //发包(给数据库发包，)
	       sqlite3_exec(db,cmd,success,NULL,&errmsg);
                }
	  else if(choice==2){
	  	printf("enter name| tel| addr:");
                char name[12]="";
                char tel[15]="";
                char addr[100]="";
                scanf("%s%s%s",name,tel,addr);
                printf("\n");
                getchar();
                char cmd2[64]="";
                sprintf(cmd2,"insert into \'%s\'values(\'%s\',\'%s\',\'%s\')",tablename,name,tel,addr);
                sqlite3_exec(db,cmd2,success,NULL,&errmsg);
	  }
	  else if(choice==3){
	        printf("Check all ?(y or n)>");
	        char get;
	        char cmd3[64]="";
	        getchar();
	        scanf("%c",&get);
	        if(get=='n'){
                printf("input the name who you want to look for:");
                char name[100]="";
                scanf("%s",name);
                printf("\n");
                
                sprintf(cmd3,"select * from \'%s\' where name=\'%s\';",tablename,name);
                sqlite3_exec(db,cmd3,select_callback,NULL,&errmsg);
                }
                else {
                  sprintf(cmd3,"select * from \'%s\';",tablename);
                  sqlite3_exec(db,cmd3,select_callback,NULL,&errmsg);
                }
	  }
	  else if(choice==4){
                printf("input the name who you want to delete:");
                char name[100]="";
                scanf("%s",name);
                printf("\n");
                char cmd4[64]="";
                sprintf(cmd4,"delete  from \'%s\' where name=\'%s\';",tablename,name);
                sqlite3_exec(db,cmd4,success,NULL,&errmsg);
	  }
	  else if(choice==5){
                printf("input the name who you want to change:");
                char name[100]="";
                scanf("%s",name);
                printf("\n input new name | new tel | new addr:");
                char tel[15]="";
                char addr[100]="";
                scanf("%s%s%s",name,tel,addr);
                printf("\n");
                char cmd5[64]="";
                sprintf(cmd5,"update \'%s\' set name=\'%s\',tel=\'%s\',addr=\'%s\' where name=\'%s\';",tablename,name,tel,addr,name);
	        sqlite3_exec(db,cmd5,success,NULL,&errmsg);
	  }
	  else break;
	  printf("input the cmd>");
	  scanf("%d",&choice);
	  printf("\n");
	}while(choice);
	 sqlite3_close(db);
	return 0;
}
//编译的时候需加:-lpthread -ldl
