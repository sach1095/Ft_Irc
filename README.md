# Ft_Irc

Création d'un serveur IRC (Internet Relay Chat)

Intro :

IRC (Internet Relay Chat) est un protocole de communication textuel sur Internet. Il sert
à la communication instantanée principalement sous la forme de discussions en groupe
par l’intermédiaire de canaux de discussion, mais peut aussi être utilisé pour de la communication directe entre deux personnes.
Les clients IRC se connectent à des serveurs IRC afin d’accéder à des canaux. Les
serveurs IRC sont connectés entre eux afin de créer des réseaux.

Les sources utiles pendant le déroulement du projet :

- <a href="http://abcdrfc.free.fr/rfc-vf/rfc1459.html#411"> La doc rfc1459 vf </a>

- <a href="https://www.alien.net.au/irc/irc2numerics.html"> alien.net </a>

- <a href="https://www.bogotobogo.com/cplusplus/sockets_server_client.php"> Bogotobogo </a>

- <a href="https://datatracker.ietf.org/doc/html/rfc1459#section-1.1"> datatracker </a>

- <a href="https://web.maths.unsw.edu.au/~lafaye/CCM/sockets/sockfonc.htm"> CommentCaMarche.net - Les fonctions de l'API Socket</a>

- <a href="https://www.geeksforgeeks.org/socket-programming-cc/?ref=lbp"> geeksforgeeks </a>

Pour bien comprendre comment fonctionne le fonctionnement de la communication entre serveur et client, voici une représentation  visuelle :

<img  height="400" width="300" src="https://github.com/sach1095/Ft_Irc/blob/master/img/Socket_server.png" alt="serve/clien_communication" />

Pour cloner le project :

- git clone https://github.com/sach1095/Ft_Irc.git

--------------------------------------------------------------------------------

Pour lancer le project :

- make

Cette commande compile le projet.

--------------------------------------------------------------------------------

- make start

Cette commande compile et lance le serveur. (en localhost 127.0.0.1)

--------------------------------------------------------------------------------

- make bot

Lancer cette commande dans un autre terminal pour démarrer le bot.

--------------------------------------------------------------------------------

Vous pouvez vous connecter de n'importe quelle client Irc en entrant dans le paramètre de server (du client) :

- Server : 127.0.0.1
- Port : 9999
- Server password : 123

Puis vos identifiants (Nickname, Login, ...).

--------------------------------------------------------------------------------

Dans votre terminal vous pourrez voir s'afficher :

- Les connection et deconnection détailler des utilisateurs.

- Comment les message sont reçu par le serveur.

--------------------------------------------------------------------------------

Une fois connecter, je vous invite a rejoindre la channel : bot_chan pour echanger avec le Bot avec la commande suivante :

- JOIN bot_chan

Celui-ci peut tenir un echange (bonjour, comment va tu , etc),

Il trie les gros mots et kick l'utilisateur du canal (connard, etc).

Il peut donner l'heure et la dates (quelle heure est-il, quelle est la date).

Aussi il peut completer des replique de film et pub. (pas de bra, quand c'est trop, wazaa, etc)

Tester le et amusez-vous ;)

P.S : il est supportaire du PSG, dit lui dites pas "allez l'OM".
