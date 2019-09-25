#include <gtk/gtk.h>

#define EVENTS_MASK ( GDK_ENTER_NOTIFY_MASK | GDK_LEAVE_NOTIFY_MASK )

void load_css ( void );
GtkWidget *createWindow ( const gint width, const gint height );
GtkWidget *createChild (
    const gchar *const name,
    const guint border,
    const gint width,
    const gint height,
    const gchar *const label_text );

gboolean enter_event_callback ( GtkWidget *widget, GdkEvent *event );
gboolean leave_event_callback ( GtkWidget *widget, GdkEvent *event );

int main ( int argc, char *argv[] )
{
    GtkWidget *window;
    GtkWidget *grid;
    GtkWidget *child1;
    GtkWidget *child2;
    GtkWidget *child3;
    GtkWidget *child4;
    GtkWidget *child5;
    GtkWidget *child6;
    GtkWidget *child7;
    GtkWidget *child8;
    GtkWidget *child9;
    /// ***
    GtkWidget *new_child1;
    GtkWidget *new_child2;
    GtkWidget *new_child3;
    GtkWidget *new_child4;
    /// ***
    gtk_init ( &argc, &argv );
    load_css();
    window = createWindow ( 400, 400 );
    /// ***
    grid = gtk_grid_new();
    gtk_grid_set_column_homogeneous ( GTK_GRID ( grid ), TRUE );
    gtk_grid_set_row_homogeneous    ( GTK_GRID ( grid ), TRUE );
    gtk_container_add ( GTK_CONTAINER ( window ), grid );
    /// ***
    child1 = createChild ( "catch_hover",   3, 100, 100, "1" );
    child2 = createChild ( "myChild",       3, 100, 100, "2" );
    child3 = createChild ( "myChild",       3, 100, 100, "3" );
    child4 = createChild ( "myChild",       3, 100, 100, "4" );
    child5 = createChild ( "catch_hover",   3, 100, 100, "5" );
    child6 = createChild ( "myChild",       3, 100, 100, "6" );
    child7 = createChild ( "myChild",       3, 100, 100, "7" );
    child8 = createChild ( "myChild",       3, 100, 100, "8" );
    child9 = createChild ( "catch_hover",   3, 100, 100, "9" );
    /// ***
    new_child1 = createChild ( "myChild",   3, 100, 100, "10" );
    new_child2 = createChild ( "myChild",   3, 100, 100, "11" );
    new_child3 = createChild ( "myChild",   3, 100, 100, "12" );
    new_child4 = createChild ( "myChild",   3, 100, 100, "13" );
    /// ***
    gtk_grid_attach ( GTK_GRID ( grid ), child1, 0, 0, 1, 1 );
    gtk_grid_attach ( GTK_GRID ( grid ), child2, 1, 0, 1, 1 );
    gtk_grid_attach ( GTK_GRID ( grid ), child3, 2, 0, 1, 1 );
    gtk_grid_attach ( GTK_GRID ( grid ), child4, 0, 1, 1, 1 );
    gtk_grid_attach ( GTK_GRID ( grid ), child5, 1, 1, 1, 1 );
    gtk_grid_attach ( GTK_GRID ( grid ), child6, 2, 1, 1, 1 );
    gtk_grid_attach ( GTK_GRID ( grid ), child7, 0, 2, 1, 1 );
    gtk_grid_attach ( GTK_GRID ( grid ), child8, 1, 2, 1, 1 );
    gtk_grid_attach ( GTK_GRID ( grid ), child9, 2, 2, 1, 1 );
    /// ***
    gtk_grid_attach ( GTK_GRID ( grid ), new_child1, 1, 0, 2, 1 );
    gtk_grid_attach ( GTK_GRID ( grid ), new_child2, 2, 0, 1, 2 );
    gtk_grid_attach ( GTK_GRID ( grid ), new_child3, 0, 1, 1, 2 );
    gtk_grid_attach ( GTK_GRID ( grid ), new_child4, 0, 2, 2, 1 );
    /// ***

    /// ***
    gtk_widget_show_all ( window );
    gtk_main();
}

void load_css ( void )
{
    GtkCssProvider *provider;
    GdkDisplay     *display;
    GdkScreen      *screen;
    /// ***
    const gchar *css_style_file = "style.css";
    GFile *css_fp               = g_file_new_for_path ( css_style_file );
    GError *error               = 0;
    /// ***
    provider = gtk_css_provider_new ();
    display  = gdk_display_get_default ();
    screen   = gdk_display_get_default_screen ( display );
    /// ***
    gtk_style_context_add_provider_for_screen   ( screen, GTK_STYLE_PROVIDER ( provider ), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION );
    gtk_css_provider_load_from_file             ( provider, css_fp, &error );
    /// ***
    g_object_unref ( provider );
}

GtkWidget *createWindow ( const gint width, const gint height )
{
    GtkWidget *window = gtk_window_new  ( GTK_WINDOW_TOPLEVEL );
    g_signal_connect        ( window, "destroy", gtk_main_quit, window );
    gtk_widget_set_events   ( window, GDK_KEY_PRESS_MASK );
    /// ***
    gtk_window_set_default_size     ( GTK_WINDOW ( window ), width, height );
    gtk_container_set_border_width  ( GTK_CONTAINER ( window ), 50 );
    return window;
}

GtkWidget *createChild (
    const gchar *const name,
    const guint border,
    const gint width,
    const gint height,
    const gchar *const label_text )
{
    GtkWidget *eventBox = gtk_event_box_new();
    GtkWidget *child    = gtk_grid_new();
    /// ***
    GtkWidget *label    = gtk_label_new ( NULL );
    /// *** Set Events and to catch the Enter and Leave Signals
    gtk_widget_set_events    ( eventBox, EVENTS_MASK );

    /// *** Add to Container
    gtk_container_add ( GTK_CONTAINER ( child ), eventBox );
    gtk_container_add ( GTK_CONTAINER ( eventBox ), label );
    /// *** SET Child
    gtk_widget_set_name ( child, name );
    gtk_container_set_border_width ( GTK_CONTAINER ( child ), border );
    gtk_widget_set_size_request    ( child, width, height );
    /// *** SET Label
    g_object_set ( label,
                   "label", label_text,
                   "name", "myLabel",
                   "margin", 40,
                   "tooltip-text", label_text,
                   NULL );

    /// *** Catch the Enter and Leave Signals
    const gchar *const ret = gtk_widget_get_name( child );

    /// ***
    if ( strcmp( ret, "catch_hover" ) == 0 )
    {
        g_signal_connect_swapped ( eventBox, "enter-notify-event", G_CALLBACK ( enter_event_callback ), child );
        g_signal_connect_swapped ( eventBox, "leave-notify-event", G_CALLBACK ( leave_event_callback ), child );
    }

    return child;
}

gboolean enter_event_callback ( GtkWidget *widget, GdkEvent *event )
{
    if ( event->type == GDK_ENTER_NOTIFY )
    {
        ///g_print( "Enter\n" );
        gtk_widget_set_name ( widget, "HOVER" );
        return TRUE;
    }

    return FALSE;
}

gboolean leave_event_callback ( GtkWidget *widget, GdkEvent *event )
{
    if ( event->type == GDK_LEAVE_NOTIFY )
    {
        ///g_print( "Leave\n" );
        gtk_widget_set_name ( widget, "catch_hover" );
        return TRUE;
    }

    return FALSE;
}
