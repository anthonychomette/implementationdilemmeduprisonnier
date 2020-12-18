# Dilemme du prisonnier

Le but du projet est d'implementer le dilemme du prisonnier à la demande d'un laboratoire. Le fonctionnement doit etre simple car les laborantins ne sont pas des experts en informatique. Le projet doit etre sous forme d'un jeu entre deux personnes. Chaque personne aura le choix entre trahir ou collaborer. Les deux personnes ne sauront pas avec qui elle joue pour éviter que des facteurs exterieurs interviennent dans le choix des actions.

## Pour commencer

Le projet est décomposé en deux parties : un serveur et n client qui jouent ensemble.

### Pré-requis

Ce qu'il est requis pour commencer avec notre projet :

- Gestion des parties par le serveur
- Utilisation d'une View par le client 
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
`cd /implementationdilemmeduprisonnier/src/Client/make documentation`

Pour le serveur : 
`cd /implementationdilemmeduprisonnier/src/Serveur/make documentation`

## Auteurs

Noëline Miet 
Thomas Risi
Anthony Chomette
Paul Meunier

