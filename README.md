# Dilemme du prisonnier

Le but du projet est d'implementer le dilemme du prisonnier à la demande d'un laboratoire. Le fonctionnement doit être simple car les laborantins ne sont pas des experts en informatique. Le projet doit être sous forme d'un jeu entre deux personnes. Chaque personne aura le choix entre trahir ou collaborer. Les deux personnes ne sauront pas avec qui elle joue pour éviter que des facteurs extérieurs interviennent dans le choix des actions.

# Reglementation

Dans cette expérience, il y a 3 issues possibles :

- Les deux clients collaborent : 6 mois de prison chacun.
- Le client 1 trahit et le client 2 collabore : client 1 sera relâché et le client 2 aura 10 ans de prison. Inversement dans le meme cas.
- Les deux clients trahissent : 5 ans de prison chacun.


## Pour commencer

Le projet est décomposé en deux parties : un serveur et un nombre défini de client qui jouent ensemble.

### Pré-requis

Ce qu'il est requis pour commencer avec notre projet :

- Gestion des parties par le serveur
- Utilisation d'une View pour l'affichage pour le client 
- Configuration du serveur (ip, port)
- Configuration des clients (id)

### Installation

Les étapes pour installer le programme : 

1. Accéder au dossier dans lequel se trouve le fichier main, via la commande `cd /chemin/`.
2. Démarrer au minimum 3 postes pour les roles de serveur et 2 clients.

## Démarrage

*Compilation du client :*

`cd /implementationdilemmeduprisonnier/src/Client`
Puis éxécuter la commande : `make clean, make all`.

*Compilation du serveur :*

`cd /implementationdilemmeduprisonnier/src/Serveur`
Puis éxécuter la commande : `make clean, make all` 

*Afin de générer la documentation :*

Pour le client : 
`cd /implementationdilemmeduprisonnier/src/Client`
Puis éxécuter la commande : `make documentation`

Pour le serveur : 
`cd /implementationdilemmeduprisonnier/src/Serveur`
Puis éxécuter la commande : `make documentation`

###Configurer la connectivité

Allez dans le fichier conf.ini qui se trouve dans 
`cd /implementationdilemmeduprisonnier/src/Client/output`
et modifier l'ardresse ip de par la votre si le client est sur un poste differents du serveur.

## Auteurs

- Noëline Miet 
- Thomas Risi
- Anthony Chomette
- Paul Meunier

