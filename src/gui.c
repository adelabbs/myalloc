#include <gtk/gtk.h>
#include <stdio.h>
#include "batch.h"
#include "util.h"
#include "memory_internal.h"

GtkBuilder      *builder; 
GtkWidget       *window;
GtkWidget       *memoryRep;
GtkFileChooser     *filechooser;

int log_fd;

char *filepath;

/**
 * @brief GUI launcher
 * 
 * @param argc 
 * @param argv 
 * @return int 
 */
int main(int argc, char *argv[])
{
    initLog(&log_fd, "gui.log");
    
    gtk_init(&argc, &argv);

    builder = gtk_builder_new();
    gtk_builder_add_from_file (builder, "OS_gui.glade", NULL);

    window = GTK_WIDGET(gtk_builder_get_object(builder, "window_main"));

    memoryRep = GTK_WIDGET(gtk_builder_get_object(builder,"memory"));
    filechooser = GTK_FILE_CHOOSER(gtk_builder_get_object(builder,"file_choser"));
    gtk_file_chooser_set_local_only(filechooser, TRUE);

    gtk_builder_connect_signals(builder, NULL);


    g_object_unref(builder);

    gtk_widget_show(window);                
    gtk_main();

    return 0;
}

/**
 * @brief 
 * 
 */
void on_window_main_destroy() {
    gtk_main_quit();
}

/**
 * @brief Function for button clicker
 * 
 */
void on_read_button_clicked() {
    if(filepath != NULL) {
        printf("%s\n",filepath);
        batch(filepath);
        gtk_widget_queue_draw(memoryRep);
    }
}

void on_file_choser_file_set() {
    filepath = gtk_file_chooser_get_filename(filechooser);
    printf("Input file %s\n",filepath);
}

gboolean on_memory_draw(GtkWidget *widget, cairo_t *cr, gpointer data) {
	guint width, height;

    if(memory != NULL) {
        int totalOfBlocks = getMemorySize(memory);
        BlockListPtr bl = getMemoryBlockList(memory);
        

        int size = 10;
        int positionX = 0;
        int positionY = 0;
        int currentBlockSize = 0;
        int blockIndice = 0;

        width = gtk_widget_get_allocated_width(widget);
        height = gtk_widget_get_allocated_height(widget);

        for(int i = 0; i < totalOfBlocks; i++) {
            if(positionX >= height) {
                positionY += size + 1;
                positionX = 0;
            }
            if(bl != NULL){
                cairo_rectangle (cr, positionX, positionY, size, size);
                cairo_set_source_rgba (cr, 1, 0, 0, 1);
                cairo_fill (cr);
                blockIndice ++;
                currentBlockSize = getBlockSize(bl);
            } else {
                cairo_rectangle (cr, positionX, positionY, size, size);
                cairo_set_source_rgba (cr, 1, 1, 1, 1);
                cairo_fill (cr);
            }

            if(blockIndice == currentBlockSize && bl != NULL)  {
            blockIndice = 0;
            bl = getNextBlock(bl);
            }

            positionX += size + 1;
        }
    }
	return FALSE;	
}


