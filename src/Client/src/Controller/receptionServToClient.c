/**
 * @file receptionServToClient.c
 * @author noeline
 * @brief Fichier de traitement des paquets reçu de la part du serveur
 * @version 0.1
 * @date 2020-12-17
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <gtk/gtk.h>
#include "../packetmanager.h"
#include "receptionServToClient.h"
#include "envoiClientToServ.h"

GtkBuilder *builder = NULL;

/**
 * @brief Affichage de la premiere page de la page de l'experience
 * 
 */
void initView() {
    GtkWidget *win;
    gtk_init(0, NULL);
    builder = gtk_builder_new_from_file("output/View/PageAttente.glade");
    printf("###%p : \n", builder);
    win = GTK_WIDGET(gtk_builder_get_object(builder, "PageAttente "));
    gtk_builder_connect_signals(builder, NULL);
    gtk_widget_show(win);
    gtk_main();
}


/**
 * @brief Affichage de la page pour savoir si le client est pret
 * 
 */
void serverIsPlayerReady() {
/*     gtk_main_quit();
    GtkWidget *win = NULL;
    gtk_init(0, NULL);
    builder = gtk_builder_new_from_file("View/PageJeSuisPret.glade");
    win = GTK_WIDGET(gtk_builder_get_object(builder, "app_pret"));
    gtk_builder_connect_signals(builder, NULL);
    gtk_widget_show(win);
    gtk_main(); */

    
    char confirmation = 'N';
    do {
        printf("Entrez O pour confirmer que vous etes prêt à lancer la partie : \n");
        scanf("%c", &confirmation);
    }while(confirmation != 'O');


}

/**
 * @brief Affichage de la page d'attente
 * 
 */
void serverWaitingEnd() {
/*     gtk_main_quit();
    GtkWidget *win;
    gtk_init(0, NULL);
    builder = gtk_builder_new_from_file("View/PageAttente.glade");
    win = GTK_WIDGET(gtk_builder_get_object(builder, "app_attente"));
    gtk_builder_connect_signals(builder, NULL);
    gtk_widget_show(win); */
}

/**
 * @brief Affichage de la page pour faire le choix
 * 
 * @param sockfd Socket de la connexion, pour envoyer la réponse
 */
void serverMakeChoice(int sockfd) {
/*     gtk_main_quit();
    GtkWidget *win = NULL;
    gtk_init(0, NULL);
    builder = gtk_builder_new_from_file("View/PageChoix.glade");
    win = GTK_WIDGET(gtk_builder_get_object(builder, "app_choix"));
    gtk_builder_connect_signals(builder, NULL);
    gtk_widget_show(win); */

    char choix = 'N';

    do {
        printf("Faites votre choix : \n Soit de trahir votre allié, Entrez 'T',\n Ou au contraire de collaborer, Entrez 'C'\n");
        scanf("%c", &choix);
    }while(choix != 'T' && choix != 'C');

    printf("Choix bon\n");

    if (choix == 'T') {
        printf("Vous avez choisis de trahir !!!!!!!!!\n");
        clientChoiceBetray(sockfd);
    }
    else if (choix == 'C') {
        printf("Vous avez choisis de Collaborer !!!!!!!!!\n");
        clientChoiceCollabore(sockfd);
    }
    else {
        perror("invalid choice");
    }

}

/**
 * @brief reception du résultat
 * 
 * @param packet Paquet de résultat reçu
 * @param socket Socket de la connexion
 */
void serverScore(packetServerScore *packet, int socket) {
/*     gtk_main_quit();
    GtkWidget *win = NULL;
    gtk_init(0, NULL);
    builder = gtk_builder_new_from_file("View/PageResultat.glade");
    win = GTK_WIDGET(gtk_builder_get_object(builder, "app_resultat")); */
    
    char txt[100];
    switch (packet->score) {
        case 0:
        {
            //il a dénoncer et l'autre n'a rien dit
/*             GtkLabel *lblResultat = GTK_LABEL(gtk_builder_get_object(builder, "lblResultat"));
            snprintf(txt, 100, "Vous n'avez pas été trahis \n Aucune comdamnation");
            gtk_label_set_text(GTK_LABEL(lblResultat), txt); */
            printf("Vous n'avez pas été trahis\n Aucune comdamnation\n");
            break;
        }
        case 6:
        {
            //les 2 n'ont rien dit
/*             GtkLabel *lblResultat = GTK_LABEL(gtk_builder_get_object(builder, "lblResultat"));
            snprintf(txt,100, "Vous n'avez pas été trahis \n Comdamnation : 6 mois");
            gtk_label_set_text(GTK_LABEL(lblResultat), txt); */
            printf("Vous n'avez pas été trahis\n Comdamnation : 6 mois\n");
            break;
        }
        case 5:
        {
            //les 2 ont dénoncer
/*             GtkLabel *lblResultat = GTK_LABEL(gtk_builder_get_object(builder, "lblResultat"));
            snprintf(txt,100, "Vous avez été trahis \n Comdamnation : 5 ans");
            gtk_label_set_text(GTK_LABEL(lblResultat), txt); */
            printf("Vous avez été trahis\nComdamnation : 5 ans\n");
            break;
        }
        case 10:
        {
            //l'autre à dénnoncé et lui n'a rien dit 
/*             GtkLabel *lblResultat = GTK_LABEL(gtk_builder_get_object(builder, "lblResultat"));
            snprintf(txt, 100,"Vous avez été trahis \n Comdamnation : 10 ans");
            gtk_label_set_text(GTK_LABEL(lblResultat), txt); */
            printf("Vous avez été trahis\nComdamnation : 10 ans\n");
            break;
        }
    }
    ClientWaitingGame(socket);

/*     gtk_builder_connect_signals(builder, NULL);
    gtk_widget_show(win);
    gtk_main(); */
}

/**
 * @brief Reception de la fin de la partie ou non
 * 
 * @param packet Paquet reçu de type : packetServerIsThisTheEnd
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
