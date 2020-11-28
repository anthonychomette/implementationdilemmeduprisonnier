/* 
 * Fichier de traitement du packet recu de la part du serveur
 * 
 * @autor noeline
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <gtk/gtk.h>

#include "../packetmanager.h"
//#include "receptionServToClient.h"

GtkBuilder *builder = NULL;

/**
 * Affichage de la page pour savoir si le client est pret
 * 
 * @autor noeline
 */
void serverIsPlayerReady(){
    GtkWidget *win;
    gtk_init(0, NULL);
    builder = gtk_builder_new_from_file("glade/PageJeSuisPret.glade");
    win = GTK_WIDGET(gtk_builder_get_object(builder, "app_pret"));
    gtk_builder_connect_signals(builder, NULL);
    gtk_widget_show(win);
    gtk_main();
}

/**
 * Affichage de la page d'attente
 * 
 * @autor noeline
 */
void serverWaitingEnd(){
    gtk_main();
    GtkWidget *win;
    gtk_init(0, NULL);
    builder = gtk_builder_new_from_file("glade/PageAttente.glade");
    win = GTK_WIDGET(gtk_builder_get_object(builder, "app_attente"));
    gtk_builder_connect_signals(builder, NULL);
    gtk_widget_show(win);
}

/**
 * Affichage de la page pour faire le choix
 * 
 * @autor noeline
 */
void serverMakeChoice(){
    gtk_main();
    GtkWidget *win;
    gtk_init(0, NULL);
    builder = gtk_builder_new_from_file("glade/PageChoix.glade");
    win = GTK_WIDGET(gtk_builder_get_object(builder, "app_choix"));
    gtk_builder_connect_signals(builder, NULL);
    gtk_widget_show(win);
}

/**
 * reception du résultat
 * 
 * @autor noeline
 * @param packet
 */
void serverScore(packetServerScore packet){
    gtk_main();
    GtkWidget *win;
    gtk_init(0, NULL);
    builder = gtk_builder_new_from_file("glade/PageResultat.glade");
    win = GTK_WIDGET(gtk_builder_get_object(builder, "app_resultat"));
    
    
    switch(packet.score){
        case 0: {
            //il a dénoncer et l'autre n'a rien dit
            gtk_label_set_label(GTK_LABEL(win->lblResultat), "Vous n'avez été trahis \n Aucune comdamnation");
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
}

/**
 * Envoi de la fin de la partie ou non
 * 
 * @autor noeline
 * @param packet
 */
void serverIsThisTheEnd(packetServerIsThisTheEnd packet){
    switch(packet.gameEnd){
        case true : {
            gtk_main_quit();
        }
        case false : {
            gtk_main_quit();
        }
    }
    
}
