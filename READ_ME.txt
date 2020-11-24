Bonjour,

Si vous voulez run les codes, il faut le faire dans le dosier "Tout", là où tout est en désordre mais où chaque fichier à accès aux autres.

En revanche, si vous voulez juste allez voir certaines parties du projet, certains codes, etc.. Tous nos fichiers sont triés dans des dossiers

- Codes C:
	- Fichiers source:
		Les différents codes.c
		- Attente active:
			Les 3 problèmes implémentés avec nos mutex/sémaphores par attente active
		- POSIX:
			Les 3 problèmes implémentés avec les mutex/sémaphores de la libraire POSIX
		- Verrous:
			Test-and-set, test-and-test-and-set et la sémaphore utilisant l'attente active
			Le bonus backoff-test-and-test-and-set ainsi que le code test_verrous qui permet de tester les différents verrous
	- Fichiers header:
		Les 2 headers du test-and-test-and-set et de la sémaphore
- Codes Python:
	Les 2 scripts python pour faire les graphes
		- 1 pour les 3 problèmes
		- 1 pour les 3 verrous
- Graphiques
	Les différents graphiques au format png et pdf
		- 1 graphique par format et par problème (donc 6 fichiers)
		- 1 graphique par format et par verrou (donc 4 fichiers)
- Mesures
	Les différents fichiers csv produits par le bash, contenant les données des graphiques
- Scripts Bash + Makefile
	- Les 2 scripts bash (1 pour les 3 problèmes, 1 pour les 2 verrous)
	- Le makefile général du projet
	
Chaque fichier de code (C, bash, python Makefile) est commenté afin d'avoir toutes les informations nécessaires.