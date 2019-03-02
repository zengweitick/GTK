#include<gtk/gtk.h>
#include<string.h>
#include<unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <pthread.h>
#include <fcntl.h>
#include <stdio.h>

#include <stdlib.h>
int fd;
void fun1(GtkButton *button,gpointer userdata){
	int a=0;
    printf("暂停或播放播放\n");
    a=write(fd,"pause\n",strlen("pause\n"));
    printf("a=%d\n",a);
	}

int main(int argc, char  *argv[])
{
	  gtk_init(&argc,&argv);
	  GtkWidget *button=gtk_button_new_with_label("暂停或播放");
      GtkWidget *window=gtk_window_new(GTK_WINDOW_TOPLEVEL);
      gtk_container_add(GTK_CONTAINER(window),button);
      g_signal_connect(button,"pressed",G_CALLBACK(fun1),NULL);
      mkfifo("fifo_cmd",0777);
      gtk_widget_show_all(window);
	  pid_t pid;
      pid=fork();
	  if(pid<0){
	  	perror("fork error");
        exit(0);
	  }
	  else if(pid==0){
           execlp("mplayer","mplayer","-slave","-quiet","-input","file=./fifo_cmd","coffee.mp3",NULL);
           exit(0);
	  }
	  else {
	  	  fd=open("./fifo_cmd",O_WRONLY);
	  	  printf("this is parent\n");
          if(fd<0)exit(1);
	      gtk_main(); 
	  }

	return 0;
}
