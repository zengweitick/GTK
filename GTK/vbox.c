#include<gtk/gtk.h>

void fun1(GtkButton *button,gpointer userdata){

	 gtk_label_set_text(GTK_LABEL(userdata),"macos");
	 return ;
	}

int main(int argc, char  *argv[])
{
	gtk_init(&argc,&argv);
	char string[]="linux";
	gchar *title=string;
	 GtkWidget *vbox=gtk_new_vbox();
     GtkWidget *window=gtk_window_new(GTK_WINDOW_TOPLEVEL);
     gtk_window_set_title(GTK_WINDOW(window),title);
     gtk_widget_set_size_request(window,320,220);
     g_signal_connect(window,"destroy",G_CALLBACK(gtk_main_quit),NULL);
     GtkWidget *button=gtk_button_new_with_label("button");
     GtkWidget *label1=gtk_label_new("Linux");
     GtkWidget *label2=gtk_label_new("windows");
     gtk_container_add(GTK_CONTAINER(window),vbox);
     gtk_container_add(GTK_CONTAINER(vbox),label1);
     gtk_container_add(GTK_CONTAINER(vbox),label2);
    // GtkWidget *button2=gtk_button_new_with_label("button2");
 
	//gtk_container_add(GTK_CONTAINER(window),button);
	g_signal_connect(button,"pressed",G_CALLBACK(fun1),label1);
	gtk_widget_show_all(window);
	gtk_main(); 
	return 0;
}
