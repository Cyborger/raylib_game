# Raylib Game
**Projet L1 ISTN défi, binôme Bouchaud Lucas et Seznec Romain.**

## Exercices réalisés

Voici la liste des exercices réalisés :
La mention "V" signifie que l'exercice correspondant a été réalisé et la mention "F" qu'il n'a pas été réalisé. 

**Exercice 1 :** V

**Exercice 2 :** V

**Exercice 3 :** V

**Exercice 4 :** V

**Exercice 5 :** V

**Exercice 6 :** V

**Exercice 7 :** V

**Exercice 8 :** V

**Exercice 9 :** V

**Exercice 10 :** V

**Exercice 11 :** V

**Exercice 12 :** V

**Exercice 13 :** V

**Exercice 14 :** V

**Exercice 15 :** V

**Exercice 16 :** V

**Exercice 17 :** V

**Exercice 18 :** V

**Exercice 19 :** V

**Exercice 20 :** V

**Exercice 21 :** V

**Exercice 22 :** F (Frein)

**Exercice 23 :** F (Compteur de vitesse)

**Exercice 24 :** V

**Exercice 25 :** V

**Exercice 26 :** F (Piece et point)

**Exercice 27 :** F (Piège et vie)

**Exercice 28 :** V

**Exercice 29 :** V

**Exercice 30 :** V

**Exercice 31 :** V

**Exercice 32 :** V

**Exercice 33 :** V

**Exercice 34 :** V

**Exercice 35 :** V

**Exercice 36 :** V

**Exercice 37 :** V

**Exercice 38 :** V

**Exercice 39 :** V

**Exercice 40 :** V

**Exercice 41 :** V

**Exercice 42 :** V

**Exercice 43 :** V

**Exercice 44 :** V

**Exercice 45 :** V

**Exercice 46 :** F (Communication plus compacte)

**Exercice 47 :** F (Protocole de communication)

### Notions complémentaires

Afin de garder un code consistant et organisé, nous découpons la structure de projet sous plusieurs modules :

- raylib_car;
- raylib_car_input;
- raylib_edge;
- raylib_game;
- raylib_obstacle;
- raylib_rectangles;
- raylib_ui.

L'ensemble des définitions comprises dans ces modules sont prédéclarées dans le fichier d'en-tête 'raylib_game.h' et tire avantage de cette fonctionnalité du C.

Nous utilisons également des structures non donnée en consignes afin de structurer au mieux notre projet (exemple du *GameTransform* qui regroupe position et taille).

# Touches du clavier

Voici les touches du clavier ainsi que leurs actions assignées utiles au fonctionnement du programme :

- Flèche haut -> Aller vers le haut
- Flèche gauche -> Aller vers la gauche
- Flèche bas -> Aller vers le bas
- Flèche droite -> Aller vers la droite
- Maj gauche -> Nitro

Il est possible d'utiliser le joystick pour contrôler la voiture.

# Communication avec la carte

Vous trouverez le code Arduino dans le dossier `arduino_code`.

**De la carte à l'ordinateur**, nous utilisons le joystick qui permet de déplacer la voiture.

**De l'ordinateur vers la carte**, nous utilisons la LED d'affichage intégré sur la carte Arduino Uno (indicatif : L). Cette LED s'active lorsque le joueur recule ou freine à l'aide de la touche flèche du bas.