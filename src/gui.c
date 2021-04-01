#include <gtk/gtk.h>
#include <stdio.h>
#include "memory.h"


int main(int argc, char *argv[])
{
    GtkBuilder      *builder; 
    GtkWidget       *window;
    GtkWidget       *memory;
        
    gtk_init(&argc, &argv);

    builder = gtk_builder_new();
    gtk_builder_add_from_file (builder, "OS_gui.glade", NULL);

    window = GTK_WIDGET(gtk_builder_get_object(builder, "window_main"));
    gtk_builder_connect_signals(builder, NULL);

    memory = GTK_WIDGET(gtk_builder_get_object(builder,"memory"));

    g_object_unref(builder);

    gtk_widget_show(window);                
    gtk_main();

    return 0;
}

void on_add_clicked(){
	printf("Add block...");
}

void on_window_main_destroy() {
    gtk_main_quit();
}


gboolean on_memory_draw(GtkWidget *widget, cairo_t *cr, gpointer data) {
	
	guint width, height;

    //int totalOfBlocks = getMemorySize();
    //BlockList bl = getBlockList();

    int totalOfBlocks = 100;
	int size = 10;
    int positionX = 0;
    int positionY = 0;

	width = gtk_widget_get_allocated_width(widget);
	height = gtk_widget_get_allocated_height(widget);

    for(int i = 0; i < totalOfBlocks; i++) {
        if(positionX == height) {
            positionY += size + 1;
            positionX = 0;
        }
        if(i % 2 == 0){
            cairo_rectangle (cr, positionX, positionY, size, size);
            cairo_set_source_rgba (cr, 1, 0, 0, 1);
            cairo_fill (cr);

        } else {
            cairo_rectangle (cr, positionX, positionY, size, size);
            cairo_set_source_rgba (cr, 1, 1, 1, 1);
            cairo_fill (cr);

        }
        positionX += size + 1;
    }
	return FALSE;	
}


