ESIEACloud
==========

Projet de Web Development

Pour l'installation se connecter en root et lancer le script install.sh.

Le système contient de base 2 utilisateurs :
	login : Martin		password : pass
	login : user		password : salut

Le but de ce projet est de créer un mini-cloud.

Chaque utilisateur peut se connecter via l'interface web en cliquant sur "Sign in"

Les deux utilisateurs contiennent par défault 2 fichiers dans leurs dossier personnel, 1 image et 1 fichier text.

La deconnexion ne marche pas encore, pour se déconnecter, il suffit de supprimer le cookie.


Pour le programme nous avons décider de coder avec le langage C qui est rapide et qui permet de tout controller.
Pour la base de données nous avons utiliser la base de données Postgres, qui est libre et performante, elle comprend aussi une librairie de developpement en C.
Nous avons décider de ne pas stocker les mot de passe dans la base de donnée, car cela peut être dansgeureux. Nous avons choisi de ne stocker que des hash des mots de passes, pour ce faire nous avons utiliser l'algorythme Sha-256 qui est réputé sûre.
Pour les cookie on stocke un hash du login, cette fonction peut être amélioré en rajoutant facilement une graine dans la fonction de hash. Nous stockons la même valeur dans la base de donnée, et nous comparons les 2 valeurs.
Pour l'interface web nous avons utiliser les technologie html et javascript.
