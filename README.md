# Plazza
Le but de ce projet de Epitech était de nous faire réaliser une simulation d'une pizzeria, qui se compose de la réception qui accepte les nouvelles commandes, de plusieurs cuisines, elles-mêmes avec plusieurs cuisiniers, qui eux-mêmes cuisine plusieurs pizzas.
Le projet nous a apprit à traiter différents problèmes, notamment l'équilibrage de charge, la synchronisation des processus et des threads
et la communication.
Voici ce que nous avons utilisé dans ce projet :
- Fork, wait...
- Communication inter-processus (IPC)
- Les threads STL
- Les threads POSIX

## Comment le lancer ?
Tout d'abord il faut à la racine :
```bash
make
```
Ensuite il faut lancer le programme avec 3 arguments:  
- le premier s'agit du multiplieur de temps, une pizza prends X temps à être cuite * multiplieur.
- Le second est comme son nom l'indique le nombre de cuisiniers par cuisine, cela déterminera combien de cuisine ouvre le programme,
- Le dernier s'agit du temps de recharge des ingrédients dans les cuisines, les cuisines ont un nombre d'ingrédients qui se regénère selon ce temps, si elle n'a plus d'ingrédients une autre cuisine sera ouverte.

```bash
./plazza [multiplieur] [cuisiniers_par_cuisine] [recharge_ingrédients]
```

## Comment l'utiliser ?
    Les commandes de pizza doivent suivre le format suivant:
        S := TYPE TAILLE NOMBRE [; TYPE TAILLE NOMBRE ]*
        TYPE := [ a .. zA .. Z ]+
        TAILLE := S | M | L | XL | XXL
        NOMBRE := x [1..9][0..9]*
    Example de commande valide:
        regina XXL x2; fantasia M x3; margarita S x1

### Versions
```bash
gcc version 12.1.1 2022050
```


### Collaborateurs
[Thibault Bernuz](https://github.com/Haaycee)   
[Romain Very](https://github.com/RomaiinVery)
