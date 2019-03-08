/* ************************************************************************
 *       Filename:  Graph.c
 *    Description:  
 *        Version:  1.0
 *        Created:  2019年03月07日 10时14分08秒
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/
#include<gtk/gtk.h>
#include<string.h>
#include<unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <pthread.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include"sqlite3.h"
  struct entry_list{
   GtkWidget *entry1;
   GtkWidget *entry2;
   GtkWidget *entry3;
   GtkWidget *entry4;
  };
  struct show{
     int count;
    char name[10][10];
    char tel[10][10];
    char addr[10][10];
   
  };
 sqlite3 *db;
 char *errmsg;
 void get_enter(GtkWidget *widget, gpointer entry){
	const gchar *name;
	name=gtk_entry_get_text(GTK_ENTRY(entry));
	char cmd[64]="";
   sprintf(cmd,"create table \'%s\' (name text, tel text ,addr text);",name);
	        //发包(给数据库发包，)
	sqlite3_exec(db,cmd,NULL,NULL,&errmsg);
}
void create(){
    	GtkWidget *window=gtk_window_new(GTK_WINDOW_TOPLEVEL);
    	gtk_window_set_title(GTK_WINDOW(window), "添加表");
        gtk_container_set_border_width(GTK_CONTAINER(window), 60); // 设置窗口边框的宽度
        gtk_widget_set_size_request(window,400,240);
        g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
        GtkWidget *table=gtk_table_new(2,1,TRUE);
        gtk_container_add(GTK_CONTAINER(window),table);
        GtkWidget *button=gtk_button_new_with_label("提交");
        GtkWidget *label=gtk_label_new("请输入要创建的表名");
        GtkWidget *entry=gtk_entry_new();
        gtk_table_attach_defaults(GTK_TABLE(table),entry,1,2,0,1);
        gtk_table_attach_defaults(GTK_TABLE(table),label,0,1,0,1);
        gtk_table_attach_defaults(GTK_TABLE(table),button,0,2,1,2);
        g_signal_connect(button,"pressed",G_CALLBACK(get_enter),entry);
        gtk_widget_show_all(window);
        gtk_main();
}
void get_entry_add(GtkWidget *widget, gpointer entry1){
       struct entry_list* entry=(struct entry_list*)entry1;
       const gchar *name;
       const gchar *tel;
       const gchar *addr;
       const gchar *tablename;
       tablename=gtk_entry_get_text(GTK_ENTRY(entry->entry1));
       name=gtk_entry_get_text(GTK_ENTRY(entry->entry2));
       tel=gtk_entry_get_text(GTK_ENTRY( entry->entry3));
       addr=gtk_entry_get_text(GTK_ENTRY(entry->entry4));
       char cmd2[64]="";
       sprintf(cmd2,"insert into \'%s\'values(\'%s\',\'%s\',\'%s\')",tablename,name,tel,addr);
       sqlite3_exec(db,cmd2,NULL,NULL,&errmsg);
       
}
void add(GtkButton *p, gpointer data){
     GtkWidget *window=gtk_window_new(GTK_WINDOW_TOPLEVEL);
    	gtk_window_set_title(GTK_WINDOW(window), "添加联系人");
        gtk_container_set_border_width(GTK_CONTAINER(window), 60); // 设置窗口边框的宽度
        gtk_widget_set_size_request(window,400,360);
        g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
        GtkWidget *table=gtk_table_new(5,2,TRUE);
        gtk_container_add(GTK_CONTAINER(window),table);
        GtkWidget *label0=gtk_label_new("数据库名:");
        GtkWidget *label1=gtk_label_new("新建联系人");
        GtkWidget *label2=gtk_label_new("姓名：");
        GtkWidget *label3=gtk_label_new("电话号码：");
        GtkWidget *label4=gtk_label_new("住址：");
        GtkWidget *button=gtk_button_new_with_label("确定");
        struct entry_list *entry;
        entry=(struct entry_list*)malloc(sizeof(struct entry_list));
        entry->entry1=(GtkWidget *)malloc(sizeof(GtkWidget));
        entry->entry2=(GtkWidget *)malloc(sizeof(GtkWidget));
        entry->entry3=(GtkWidget *)malloc(sizeof(GtkWidget));
        entry->entry4=(GtkWidget *)malloc(sizeof(GtkWidget));
        entry->entry1=gtk_entry_new();
        entry->entry2=gtk_entry_new();
        entry->entry3=gtk_entry_new();
        entry->entry4=gtk_entry_new();
        gtk_table_attach_defaults(GTK_TABLE(table),label1,0,2,0,1);
        gtk_table_attach_defaults(GTK_TABLE(table),label0,0,1,1,2);
        gtk_table_attach_defaults(GTK_TABLE(table),label2,0,1,2,3);
        gtk_table_attach_defaults(GTK_TABLE(table),label3,0,1,3,4);
        gtk_table_attach_defaults(GTK_TABLE(table),label4,0,1,4,5);
        gtk_table_attach_defaults(GTK_TABLE(table),entry->entry1,1,2,1,2);
        gtk_table_attach_defaults(GTK_TABLE(table),entry->entry2,1,2,2,3);
        gtk_table_attach_defaults(GTK_TABLE(table),entry->entry3,1,2,3,4); 
        gtk_table_attach_defaults(GTK_TABLE(table),entry->entry4,1,2,4,5);
        gtk_table_attach_defaults(GTK_TABLE(table),button,0,2,5,6);
        g_signal_connect(button,"pressed",G_CALLBACK(get_entry_add),entry);
        gtk_widget_show_all(window);
        gtk_main();
}
int select_callback(void * data, int col_count, char ** col_values, char ** col_Name){
    struct show *result=(struct show *)data;
    char get[col_count][10];
    memset(get,0,sizeof(get));
    for(int i=0;i<col_count;i++){
      strcpy(get[i],col_values[i]) ;
    }
    strcpy(result->name[result->count],get[0]) ;
    strcpy(result->tel[result->count],get[1]) ;
    strcpy(result->addr[result->count],get[2]) ;
    result->count++;
    return 0;
}
 
void checkone(GtkWidget *widget, gpointer entry1){
     GtkWidget *window=gtk_window_new(GTK_WINDOW_TOPLEVEL);
     gtk_window_set_title(GTK_WINDOW(window), "查询结果");
     gtk_container_set_border_width(GTK_CONTAINER(window), 60); // 设置窗口边框的宽度
     gtk_widget_set_size_request(window,600,400);
     g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
     struct entry_list *entry=(struct entry_list *)entry1;
     const gchar *tablename;
     const gchar *name;
     struct show *result;
     result=(struct show *)malloc(sizeof(struct show));
     //result->name=(char *)malloc(100*sizeof(char));
    // result->tel=(char *)malloc(100*sizeof(char));
     //result->addr=(char *)malloc(100*sizeof(char));
     result->count=0;
     tablename=gtk_entry_get_text(GTK_ENTRY(entry->entry1));
     name=gtk_entry_get_text(GTK_ENTRY(entry->entry2));
     char cmd2[64]="";
     sprintf(cmd2," select * from  \'%s\' where name=\'%s\'",tablename,name);
     sqlite3_exec(db,cmd2,select_callback,result,&errmsg);
     
     
     GtkWidget *table=gtk_table_new(result->count+1,3,TRUE);
     gtk_container_add(GTK_CONTAINER(window),table);
       GtkWidget *label_1=gtk_label_new("姓名");
       GtkWidget *label_2=gtk_label_new("电话号码");
       GtkWidget *label_3=gtk_label_new("住址");
       gtk_table_attach_defaults(GTK_TABLE(table),label_1,0,1,0,1);
       gtk_table_attach_defaults(GTK_TABLE(table),label_2,1,2,0,1);
       gtk_table_attach_defaults(GTK_TABLE(table),label_3,2,3,0,1);
     for(int i=0;i<result->count;i++){
       GtkWidget *label1=gtk_label_new(result->name[i]);
       GtkWidget *label2=gtk_label_new(result->tel[i]);
       GtkWidget *label3=gtk_label_new(result->addr[i]);
       gtk_table_attach_defaults(GTK_TABLE(table),label1,0,1,1+i,2+i);
       gtk_table_attach_defaults(GTK_TABLE(table),label2,1,2,1+i,2+i);
       gtk_table_attach_defaults(GTK_TABLE(table),label3,2,3,1+i,2+i);
     }
     gtk_widget_show_all(window);
     gtk_main();
}
void checktwo(GtkWidget *widget, gpointer entry1){
       GtkWidget *window=gtk_window_new(GTK_WINDOW_TOPLEVEL);
       gtk_window_set_title(GTK_WINDOW(window), "查询结果");
       gtk_container_set_border_width(GTK_CONTAINER(window), 60); // 设置窗口边框的宽度
       gtk_widget_set_size_request(window,600,400);
       g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
      struct entry_list *entry=(struct entry_list *)entry1;
      const gchar *tablename;
      struct show *result;
      result=(struct show *)malloc(sizeof(struct show));
     //result->name=(char *)malloc(100*sizeof(char));
    // result->tel=(char *)malloc(100*sizeof(char));
     //result->addr=(char *)malloc(100*sizeof(char));
      result->count=0;
      tablename=gtk_entry_get_text(GTK_ENTRY(entry->entry1));
      char cmd2[64]="";
      sprintf(cmd2," select * from  \'%s\' ",tablename);
      sqlite3_exec(db,cmd2,select_callback,result,&errmsg);
      
       GtkWidget *table=gtk_table_new(result->count+1,3,TRUE);
      gtk_container_add(GTK_CONTAINER(window),table);
       GtkWidget *label_1=gtk_label_new("姓名");
       GtkWidget *label_2=gtk_label_new("电话号码");
       GtkWidget *label_3=gtk_label_new("住址");
       gtk_table_attach_defaults(GTK_TABLE(table),label_1,0,1,0,1);
       gtk_table_attach_defaults(GTK_TABLE(table),label_2,1,2,0,1);
       gtk_table_attach_defaults(GTK_TABLE(table),label_3,2,3,0,1);
     for(int i=0;i<result->count;i++){
       GtkWidget *label1=gtk_label_new(result->name[i]);
       GtkWidget *label2=gtk_label_new(result->tel[i]);
       GtkWidget *label3=gtk_label_new(result->addr[i]);
       gtk_table_attach_defaults(GTK_TABLE(table),label1,0,1,1+i,2+i);
       gtk_table_attach_defaults(GTK_TABLE(table),label2,1,2,1+i,2+i);
       gtk_table_attach_defaults(GTK_TABLE(table),label3,2,3,1+i,2+i);
     }
     gtk_widget_show_all(window);
     gtk_main();
}
void check(GtkButton *p, gpointer data){
        GtkWidget *window=gtk_window_new(GTK_WINDOW_TOPLEVEL);
    	gtk_window_set_title(GTK_WINDOW(window), "查询联系人");
        gtk_container_set_border_width(GTK_CONTAINER(window), 60); // 设置窗口边框的宽度
        gtk_widget_set_size_request(window,600,400);
        g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
        GtkWidget *table=gtk_table_new(4,2,TRUE);
        gtk_container_add(GTK_CONTAINER(window),table);
	GtkWidget *label0=gtk_label_new("数据库名:");
        GtkWidget *label1=gtk_label_new("姓名:");
	GtkWidget *button1=gtk_button_new_with_label("目标查询");
	GtkWidget *button2=gtk_button_new_with_label("查询所有");
	struct entry_list *entry;
        entry=(struct entry_list*)malloc(sizeof(struct entry_list));
        entry->entry1=(GtkWidget *)malloc(sizeof(GtkWidget));
        entry->entry2=(GtkWidget *)malloc(sizeof(GtkWidget));
        entry->entry3=(GtkWidget *)malloc(sizeof(GtkWidget));
        entry->entry4=(GtkWidget *)malloc(sizeof(GtkWidget));
        entry->entry1=gtk_entry_new();
        entry->entry2=gtk_entry_new();
        entry->entry3=gtk_entry_new();
        entry->entry4=gtk_entry_new();
        gtk_table_attach_defaults(GTK_TABLE(table),label0,0,1,0,1);
        gtk_table_attach_defaults(GTK_TABLE(table),entry->entry1,1,2,0,1);
        gtk_table_attach_defaults(GTK_TABLE(table),label1,0,1,1,2);
        gtk_table_attach_defaults(GTK_TABLE(table),entry->entry2,1,2,1,2);
        gtk_table_attach_defaults(GTK_TABLE(table),button1,0,2,2,3);
        gtk_table_attach_defaults(GTK_TABLE(table),button2,0,2,3,4);
        g_signal_connect(button1,"pressed",G_CALLBACK(checkone),entry);
        g_signal_connect(button2,"pressed",G_CALLBACK(checktwo),entry);
        gtk_widget_show_all(window);
        gtk_main();
}
void delete_cmd(GtkWidget *widget, gpointer entry1){
     struct entry_list *entry=(struct entry_list *)entry1;
     const gchar *tablename;
     const gchar *name;
     tablename=gtk_entry_get_text(GTK_ENTRY(entry->entry1));
     name=gtk_entry_get_text(GTK_ENTRY(entry->entry2));
       char cmd2[64]="";
       sprintf(cmd2," delete from  \'%s\' where name=\'%s\'",tablename,name);
       sqlite3_exec(db,cmd2,NULL,NULL,&errmsg);
}
void delete(GtkButton *p, gpointer data){
        GtkWidget *window=gtk_window_new(GTK_WINDOW_TOPLEVEL);
    	gtk_window_set_title(GTK_WINDOW(window), "删除联系人");
        gtk_container_set_border_width(GTK_CONTAINER(window), 60); // 设置窗口边框的宽度
        gtk_widget_set_size_request(window,400,270);
        g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
        GtkWidget *table=gtk_table_new(3,2,TRUE);
        gtk_container_add(GTK_CONTAINER(window),table);
        GtkWidget *button=gtk_button_new_with_label("提交");
        GtkWidget *label1=gtk_label_new("姓名：");
        GtkWidget *label2=gtk_label_new("输入操作数据库：");
        struct entry_list *entry;
        entry=(struct entry_list*)malloc(sizeof(struct entry_list));
        entry->entry1=(GtkWidget *)malloc(sizeof(GtkWidget));
        entry->entry2=(GtkWidget *)malloc(sizeof(GtkWidget));
        entry->entry3=(GtkWidget *)malloc(sizeof(GtkWidget));
        entry->entry4=(GtkWidget *)malloc(sizeof(GtkWidget));
        entry->entry1=gtk_entry_new();
        entry->entry2=gtk_entry_new();
        entry->entry3=gtk_entry_new();
        entry->entry4=gtk_entry_new();
        gtk_table_attach_defaults(GTK_TABLE(table),label1,0,1,1,2);
        gtk_table_attach_defaults(GTK_TABLE(table),entry->entry1,1,2,0,1);
        gtk_table_attach_defaults(GTK_TABLE(table),label2,0,1,0,1);
        gtk_table_attach_defaults(GTK_TABLE(table),entry->entry2,1,2,1,2);
        gtk_table_attach_defaults(GTK_TABLE(table),button,0,2,2,3);
        g_signal_connect(button,"pressed",G_CALLBACK(delete_cmd),entry);
        gtk_widget_show_all(window);
        gtk_main();
        gtk_widget_show_all(window);
        gtk_main();
}
//void change_ok(GtkButton *p, gpointer data){
     
//}
void change_cmd(GtkButton *p, gpointer data){
     GtkWidget *window=gtk_window_new(GTK_WINDOW_TOPLEVEL);
     gtk_window_set_title(GTK_WINDOW(window), "编辑联系人");
     gtk_container_set_border_width(GTK_CONTAINER(window), 60); // 设置窗口边框的宽度
     gtk_widget_set_size_request(window,400,270);
     g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
     GtkWidget *table=gtk_table_new(4,2,TRUE);
     gtk_container_add(GTK_CONTAINER(window),table);
     struct entry_list *entry_1=(struct entry_list *)data;
     const gchar *tablename;
     const gchar *name;
     struct show *result;
     result=(struct show *)malloc(sizeof(struct show));
     //result->name[0]=(char *)malloc(100*sizeof(char));
    // result->tel[0]=(char *)malloc(100*sizeof(char));
    // result->addr[0]=(char *)malloc(100*sizeof(char));
     result->count=0;
     tablename=gtk_entry_get_text(GTK_ENTRY(entry_1->entry1));
     name=gtk_entry_get_text(GTK_ENTRY(entry_1->entry2));
     char cmd2[64]="";
     sprintf(cmd2," select * from  \'%s\' where name=\'%s\'",tablename,name);
     sqlite3_exec(db,cmd2,select_callback,result,&errmsg);
     GtkWidget *button=gtk_button_new_with_label("确定");
     GtkWidget *label1=gtk_label_new("姓名：");
     GtkWidget *label2=gtk_label_new("联系方式：");
     GtkWidget *label3=gtk_label_new("地址：");
        struct entry_list *entry;
        
        entry=(struct entry_list*)malloc(sizeof(struct entry_list));
        entry->entry1=(GtkWidget *)malloc(sizeof(GtkWidget));
        entry->entry2=(GtkWidget *)malloc(sizeof(GtkWidget));
        entry->entry3=(GtkWidget *)malloc(sizeof(GtkWidget));
        entry->entry4=(GtkWidget *)malloc(sizeof(GtkWidget));
        entry->entry1=gtk_entry_new();
        entry->entry2=gtk_entry_new();
        entry->entry3=gtk_entry_new();
        entry->entry4=gtk_entry_new();
       // gtk_editable_set_editable(GTK_EDITABLE(entry->entry1),TRUE);
        //gtk_editable_set_editable(GTK_EDITABLE(entry->entry2),TRUE);
        //gtk_editable_set_editable(GTK_EDITABLE(entry->entry3),TRUE);
     gtk_entry_set_text(GTK_ENTRY(entry->entry1),tablename);
     gtk_entry_set_text(GTK_ENTRY(entry->entry2), result->name[result->count-1]);  // 设置内容
     gtk_entry_set_text(GTK_ENTRY(entry->entry3), result->tel[result->count-1]);   
     gtk_entry_set_text(GTK_ENTRY(entry->entry4), result->addr[result->count-1]); 
    
     gtk_table_attach_defaults(GTK_TABLE(table),label1,0,1,0,1);
     gtk_table_attach_defaults(GTK_TABLE(table),label2,0,1,1,2);
     gtk_table_attach_defaults(GTK_TABLE(table),label3,0,1,2,3); 
     gtk_table_attach_defaults(GTK_TABLE(table),button,0,2,3,4); 
     
     gtk_table_attach_defaults(GTK_TABLE(table),entry->entry2,1,2,0,1);
     gtk_table_attach_defaults(GTK_TABLE(table),entry->entry3,1,2,1,2);
     gtk_table_attach_defaults(GTK_TABLE(table),entry->entry4,1,2,2,3); 
     
     
     g_signal_connect(button,"pressed",G_CALLBACK(get_entry_add),entry);
      char cmd3[64]="";
     sprintf(cmd3," delete  from  \'%s\' where name=\'%s\'",tablename,name);
     sqlite3_exec(db,cmd3,NULL,NULL,&errmsg);
     gtk_widget_show_all(window);
        gtk_main();
}
void change(GtkButton *p, gpointer data){
        GtkWidget *window=gtk_window_new(GTK_WINDOW_TOPLEVEL);
    	gtk_window_set_title(GTK_WINDOW(window), "编辑联系人");
        gtk_container_set_border_width(GTK_CONTAINER(window), 60); // 设置窗口边框的宽度
        gtk_widget_set_size_request(window,400,270);
        g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
        GtkWidget *table=gtk_table_new(3,2,TRUE);
        gtk_container_add(GTK_CONTAINER(window),table);
        GtkWidget *button=gtk_button_new_with_label("确认");
        GtkWidget *label1=gtk_label_new("姓名：");
        GtkWidget *label2=gtk_label_new("输入操作数据库：");
        struct entry_list *entry;
        entry=(struct entry_list*)malloc(sizeof(struct entry_list));
        entry->entry1=(GtkWidget *)malloc(sizeof(GtkWidget));
        entry->entry2=(GtkWidget *)malloc(sizeof(GtkWidget));
        //entry->entry3=(GtkWidget *)malloc(sizeof(GtkWidget));
        //entry->entry4=(GtkWidget *)malloc(sizeof(GtkWidget));
        entry->entry1=gtk_entry_new();
        entry->entry2=gtk_entry_new();
        //entry->entry3=gtk_entry_new();
       // entry->entry4=gtk_entry_new();
        gtk_table_attach_defaults(GTK_TABLE(table),label1,0,1,1,2);
        gtk_table_attach_defaults(GTK_TABLE(table),entry->entry1,1,2,0,1);
        gtk_table_attach_defaults(GTK_TABLE(table),label2,0,1,0,1);
        gtk_table_attach_defaults(GTK_TABLE(table),entry->entry2,1,2,1,2);
        gtk_table_attach_defaults(GTK_TABLE(table),button,0,2,2,3);
        g_signal_connect(button,"pressed",G_CALLBACK(change_cmd),entry);
        
        gtk_widget_show_all(window);
        gtk_main();
}
void exits(GtkButton *p, gpointer data){
      GtkWidget *window=(GtkWidget *)data;
        g_signal_connect(p, "pressed", G_CALLBACK(gtk_main_quit), NULL);
}
void ui(){
	GtkWidget *window=gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window), "通讯录系统");
    gtk_container_set_border_width(GTK_CONTAINER(window), 60); // 设置窗口边框的宽度
     g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
	GtkWidget *vbox=gtk_vbox_new(TRUE,10);
	gtk_container_add(GTK_CONTAINER(window),vbox);
	GtkWidget *button1=gtk_button_new_with_label("创建新表");
	GtkWidget *button2=gtk_button_new_with_label("添加联系人");
	GtkWidget *button3=gtk_button_new_with_label("查询联系人");
	GtkWidget *button4=gtk_button_new_with_label("删除联系人");
	GtkWidget *button5=gtk_button_new_with_label("修改联系人");
	GtkWidget *button6=gtk_button_new_with_label("退出系统");
	gtk_container_add(GTK_CONTAINER(vbox),button1);
	gtk_container_add(GTK_CONTAINER(vbox),button2);
	gtk_container_add(GTK_CONTAINER(vbox),button3);
	gtk_container_add(GTK_CONTAINER(vbox),button4);
	gtk_container_add(GTK_CONTAINER(vbox),button5);
	gtk_container_add(GTK_CONTAINER(vbox),button6);
	g_signal_connect(button1,"pressed",G_CALLBACK(create),NULL);
	g_signal_connect(button2,"pressed",G_CALLBACK(add),NULL);
	g_signal_connect(button3,"pressed",G_CALLBACK(check),NULL);
	g_signal_connect(button4,"pressed",G_CALLBACK(delete),NULL);
	g_signal_connect(button5,"pressed",G_CALLBACK(change),NULL);
	g_signal_connect(button6,"pressed",G_CALLBACK(exits),window);

    gtk_widget_show_all(window);
    gtk_main();
}
int main(int argc, char    *argv[])
{
	  gtk_init(&argc,&argv);
	 int ret=sqlite3_open("a.db",&db);
	 if(ret!=SQLITE_OK){
	 	perror("sqlite_open error\n");
	 	return 0;
	 }
	ui();
	return 0;
}

