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

## Configurer le Client

Pour configurer le Client :
Allez dans le fichier conf.ini qui se trouve dans :
`/implementationdilemmeduprisonnier/src/Client/output`
Modifier l'ardresse ip par celle du serveur dans le champ : "ip"
Le port par celui du serveur dans le champ : "port".
Et enfin l'identifiant client dans le champ : "IdClient"

## Ex de fichier de config Client
`
[owner]
name=anthony
organization=cpe

[database]
ip=127.0.0.1
port=7799
IdClient=8
`

## Configurer le Serveur


Pour configurer le Serveur :
Allez dans le fichier Fichier_conf.ini qui se trouve dans :
`/implementationdilemmeduprisonnier/src/Serveur/output`
Modifier l'ardresse ip par celle souhaitée dans le champ : "ip"
Le port par celui souhaité dans le champ : "port".


## Ex de fichier de config Serveur
`
[Information]
ip=0.0.0.0
port=7799
`

## Lancer le Client et le Serveur

**Attention vous devez lancer le serveur dans le dossier où il se trouve !!!**
Ex :
Le serveur se trouve dans : `/implementationdilemmeduprisonnier/src/Serveur/output`
`cd /implementationdilemmeduprisonnier/src/Serveur/output`
Pour l'éxécuter : `./Server.out`

Pour le client de la même manière :
Le Client se trouve dans : `/implementationdilemmeduprisonnier/src/Client/output`
`cd /implementationdilemmeduprisonnier/src/Client/output`
Pour l'éxécuter : `./Client.out`

**Attention pour tester le Serveur Utiliser le client 4 et le client 8 !!!**
Pour cela utiliser deux client avec comme identifiant : 4 et 8.

## Auteurs

- Noëline Miet 
- Thomas Risi
- Anthony Chomette
- Paul Meunier

