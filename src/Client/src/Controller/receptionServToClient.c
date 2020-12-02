/* 
 * Fichier de traitement du packet recu de la part du serveur
 * 
 * @author noeline
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <gtk/gtk.h>

#include "../packetmanager.h"
#include "receptionServToClient.h"

GtkBuilder *builder = NULL;

/**
 * Affichage de la page pour savoir si le client est pret
 * 
 * @author noeline
 */
void serverIsPlayerReady() {
    GtkWidget *win = NULL;
    gtk_init(0, NULL);
    builder = gtk_builder_new_from_file("View/PageJeSuisPret.glade");
    win = GTK_WIDGET(gtk_builder_get_object(builder, "app_pret"));
    gtk_builder_connect_signals(builder, NULL);
    gtk_widget_show(win);
    gtk_main();
}

/**
 * Affichage de la page d'attente
 * 
 * @author noeline
 */
void serverWaitingEnd() {
    gtk_main_quit();
    GtkWidget *win;
    gtk_init(0, NULL);
    builder = gtk_builder_new_from_file("View/PageAttente.glade");
    win = GTK_WIDGET(gtk_builder_get_object(builder, "app_attente"));
    gtk_builder_connect_signals(builder, NULL);
    gtk_widget_show(win);
}

/**
 * Affichage de la page pour faire le choix
 * 
 * @author noeline
 */
void serverMakeChoice() {
    gtk_main_quit();
    GtkWidget *win = NULL;
    gtk_init(0, NULL);
    builder = gtk_builder_new_from_file("View/PageChoix.glade");
    win = GTK_WIDGET(gtk_builder_get_object(builder, "app_choix"));
    gtk_builder_connect_signals(builder, NULL);
    gtk_widget_show(win);
}

/**
 * reception du résultat
 * 
 * @author noeline
 * @param packet
 */
void serverScore(packetServerScore packet) {
    gtk_main_quit();
    GtkWidget *win = NULL;
    gtk_init(0, NULL);
    builder = gtk_builder_new_from_file("View/PageResultat.glade");
    win = GTK_WIDGET(gtk_builder_get_object(builder, "app_resultat"));
    
    char txt[100];
    switch (packet.score) {
        case 0:
        {
            //il a dénoncer et l'autre n'a rien dit
            GtkLabel *lblResultat = GTK_LABEL(gtk_builder_get_object(builder, "lblResultat"));
            snprintf(txt, 100, "Vous n'avez été trahis \n Aucune comdamnation");
            gtk_label_set_text(GTK_LABEL(lblResultat), txt);
            break;
        }
        case 6:
        {
            //les 2 n'ont rien dit
            GtkLabel *lblResultat = GTK_LABEL(gtk_builder_get_object(builder, "lblResultat"));
            snprintf(txt,100, "Vous n'avez été trahis \n Comdamnation : 6 mois");
            gtk_label_set_text(GTK_LABEL(lblResultat), txt);
            break;
        }
        case 5:
        {
            //les 2 ont dénoncer
            GtkLabel *lblResultat = GTK_LABEL(gtk_builder_get_object(builder, "lblResultat"));
            snprintf(txt,100, "Vous avez été trahis \n Comdamnation : 5 ans");
            gtk_label_set_text(GTK_LABEL(lblResultat), txt);
            break;
        }
        case 10:
        {
            //l'autre à dénnoncé et lui n'a rien dit 
            GtkLabel *lblResultat = GTK_LABEL(gtk_builder_get_object(builder, "lblResultat"));
            snprintf(txt, 100,"Vous avez été trahis \n Comdamnation : 10 ans");
            gtk_label_set_text(GTK_LABEL(lblResultat), txt);
            break;
        }
    }

    gtk_builder_connect_signals(builder, NULL);
    gtk_widget_show(win);
    gtk_main();
}

/**
 * Envoi de la fin de la partie ou non
 * 
 * @author noeline
 * @param packet
 */
void serverIsThisTheEnd(packetServerIsThisTheEnd packet) {
    switch (packet.gameEnd) {
        case 1:
        {
            gtk_main_quit();
            break;
        }
        case 0:
        {
            gtk_main_quit();
            break;
        }
    }

}
