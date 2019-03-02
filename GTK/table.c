#include<gtk/gtk.h>
// void fun(GtkButton *button,gpointer userdata){
// 	char *a=(char *)userdata;
// 	printf("%s\n",a);
// }
int main(int argc, char  *argv[])
{
	gtk_init(&argc,&argv);
	char string[]="linux";
	gchar *title=string;
    GtkWidget *button1=gtk_button_new_with_label("button1");
    GtkWidget *button2=gtk_button_new_with_label("button2");
    GtkWidget *button3=gtk_button_new_with_label("button3");
    GtkWidget *window=gtk_window_new(GTK_WINDOW_TOPLEVEL);
    GtkWidget *table=gtk_table_new(2,2,TRUE);
    gtk_container_add(GTK_CONTAINER(window),table);
    gtk_table_attach_defaults(GTK_TABLE(table),button1,0,1,0,1);
    gtk_table_attach_defaults(GTK_TABLE(table),button2,1,2,0,1);
    gtk_table_attach_defaults(GTK_TABLE(table),button3,0,2,1,2);
	 
	gtk_window_set_title(GTK_WINDOW(window),title);
    gtk_widget_set_size_request(window,320,220);
    g_signal_connect(window,"destroy",G_CALLBACK(gtk_main_quit),NULL);
 
	 
	gtk_widget_show_all(window);
	gtk_main(); 
	return 0;
}