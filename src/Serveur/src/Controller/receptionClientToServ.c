/* 
 * Fichier de traitement du packet recu de la part du client
 * 
 * @autor noeline
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "src/packetmanager.h"
#include "receptionClientToServ.h"

void servInitClient(packetClientInit packet) {

}

void servIsPlayerReady(packetClientPlayerReady packet) {
    //envoi du packet de début jeu
}

void servChoice(packetClientPlayerChoice packet) {
    switch (packet.choice) {
        case true:
        {
            //trahison 1
            //TODO entrer dans le csv 1 pour ce joueur et ce round
        }
        case false:
        { 
            //collaboration 0
            //TODO entrer dans le csv 0 pour ce joueur et ce round
        }
    }
    //envoi du message de mise en attente si il est le premier à repondre avec l'appel de la fonction serverWaitingEnd(int sockfd)
    //Sinon calcul du resultat enregistrement de celui ci dans le csv et envoi de la page de résultat aux 2 joueurs
}