ESIEACloud
==========

Projet de Web Development
Arthur CLOUET et Nicolas LOUIS

Pour l'installation : se connecter en root et lancer le script install.sh.

Le système contient de base 2 utilisateurs :
	login : Martin		password : pass
	login : user		password : salut

Le but de ce projet est de créer une plateforme de gestion de fichier façon cloud.

Chaque utilisateur peut se connecter via l'interface web en cliquant sur "Sign In".
"Sign Up" permet de s'enregistrer en tant que nouvel utilisateur.

Les deux utilisateurs contiennent par défaut 2 fichiers dans leurs dossier personnel, 1 image et 1 fichier texte, afin de servir d'exemple.

Il est possible sur la page de gestion d'upload un fichier et de se déconnecter.

Pour le programme nous avons décidé de coder avec le langage C qui est rapide et qui permet de tout contrôler.
Pour la base de données nous avons utilisé la base de données PostgreSQL, qui est libre et performante, elle comprend aussi une librairie de développement en C.

Nous avons décidé de ne pas stocker les mots de passe dans la base de données, car cela peut être dangereux. Nous avons choisi de ne stocker que des hash des mots de passe, pour ce faire nous avons utilisé l'algorithme Sha-256 qui est réputé sûr.
Pour les cookies on stocke un hash du login, cette fonction peut être améliorée en rajoutant facilement une graine dans la fonction de hash. Nous stockons la même valeur dans la base de données, et nous comparons les 2 valeurs.

Pour l'interface web nous avons utilisé les technologies HTML, CSS et JavaScript.
