/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <gtk/gtk.h>

#include "src/packetmanager.h"
#include "receptionServToClient.h"

GtkBuilder *builder = NULL;

//Reception de la partie a faire êtes vous prets ?
void serverIsPlayerReady(){
    GtkWidget *win;
    //TODO à quoi servent argc et argv
    //gtk_init(&argc, &argv);
    builder = gtk_builder_new_from_file("glade/PageJeSuisPret.glade");
    //TODO GTKWidget ?
    win = GTK_WIDGET(gtk_builder_get_object(builder, "app_pret"));
    gtk_builder_connect_signals(builder, NULL);
    gtk_widget_show(win);
    gtk_main();
}

//Reception attend l'autre joueur
void serverWaitingEnd(){
    GtkWidget *win;
    //gtk_init(&argc, &argv);
    builder = gtk_builder_new_from_file("glade/PageAttente.glade");
    win = GTK_WIDGET(gtk_builder_get_object(builder, "app_attente"));
    gtk_builder_connect_signals(builder, NULL);
    gtk_widget_show(win);
    gtk_main();
}

//Reception début partie
void serverMakeChoice(){
    GtkWidget *win;
    //gtk_init(&argc, &argv);
    builder = gtk_builder_new_from_file("glade/PageChoix.glade");
    win = GTK_WIDGET(gtk_builder_get_object(builder, "app_choix"));
    gtk_builder_connect_signals(builder, NULL);
    gtk_widget_show(win);
    gtk_main();
}

//Reception résultats
void serverScore(packetServerScore packet){
    
    GtkWidget *win;
    //gtk_init(&argc, &argv);
    builder = gtk_builder_new_from_file("glade/PageResultat.glade");
    win = GTK_WIDGET(gtk_builder_get_object(builder, "app_resultat"));
    
    
    switch(packet.score){
        case 0: {
            //il a dénoncer et l'autre n'a rien dit
            gtk_label_set_label(GTK_LABEL(win->lblResultat), "Vous n'avez été trahis \n Comdamnation : 0");
        }
        case 6: {
            //les 2 n'ont rien dit
            gtk_label_set_label(GTK_LABEL(win->lblResultat), "Vous n'avez été trahis \n Comdamnation : 6 mois");
        }
        case 5: {
            //les 2 ont dénoncer
            gtk_label_set_label(GTK_LABEL(win->lblResultat), "Vous avez été trahis \n Comdamnation : 5 ans");
        }
        case 10: {
          //l'autre à dénnoncé et lui n'a rien dit 
            gtk_label_set_label(GTK_LABEL(win->lblResultat), "Vous avez été trahis \n Comdamnation : 10 ans");
        }
    }
    
    gtk_builder_connect_signals(builder, NULL);
    gtk_widget_show(win);
    gtk_main();
}

//Reception fin du round ou continuer
void serverIsThisTheEnd(packetServerIsThisTheEnd packet){
    switch(packet.gameEnd){
        case true : {
            gtk_main_quit ();
        }
        case false : {
            gtk_main_quit ();
            serverWaitingEnd();
        }
    }
    
}
