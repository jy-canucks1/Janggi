# Janggi
Korean Chess "Janggi" game available online and offline

## Language, Framework, Idea

* C++ and X11 for the game part
* C for the socket programming part(TCP/IP, echo server and client) 
* MVC model
* Work done in Linux environment

## Traditional Game setting

![280px-Janggi](https://github.com/jy-canucks1/Janggi/assets/84373345/c13f7590-6f0b-4c59-9868-7ba8ccad6614)

## Starting UI

Game

* default game

![K-030](https://github.com/jy-canucks1/Janggi/assets/84373345/7b4fc790-d693-4035-adcf-a2a66c25c5cd)

* game after setup

![K-004](https://github.com/jy-canucks1/Janggi/assets/84373345/9e2efd26-acb6-4edd-90d5-9daac0d7a1f3)

Set up

![K-003](https://github.com/jy-canucks1/Janggi/assets/84373345/f91e78a7-09d0-4f6b-8b58-9ee30be5e93a)

## Pieces
General(King in chess) is G(green/blue) or g(red).

![K-022](https://github.com/jy-canucks1/Janggi/assets/84373345/d62c558d-f3e7-407a-adab-6d3572bf472c)


Guard is U(green/blue) or u(red).

![K-023](https://github.com/jy-canucks1/Janggi/assets/84373345/4e3b3411-3e71-44ed-84c2-15184554884d)


Horse(Knight in chess) is H(green/blue) or h(red).

![K-024](https://github.com/jy-canucks1/Janggi/assets/84373345/16f21921-8201-41fc-9141-306701a8411b)


Elephant is E(green/blue) or e(red).

![K-025](https://github.com/jy-canucks1/Janggi/assets/84373345/2c53a76d-ec26-4075-89db-fee4b96dfa5a)


Chariot(Rook in chess) is C(green/blue) or c(red).

![K-026](https://github.com/jy-canucks1/Janggi/assets/84373345/f9da2826-d380-4e23-80f6-8db0758db48f)


Cannon is A(green/blue) or a(red).

![K-027](https://github.com/jy-canucks1/Janggi/assets/84373345/88b7e0a0-bcd6-4506-814f-72ed21f5a9c0)

Soldier(Pawn in chess) is S(green/blue) or s(red).

![K-028](https://github.com/jy-canucks1/Janggi/assets/84373345/72f46381-e008-4030-9fbf-b9c0a27dc605)

Horse and Elephant settings

There are 4 settings available. Each players can choose one of them.
(In this game, OFFLINE Only. For online mode, Inner Elephant setting is available)

![K-029](https://github.com/jy-canucks1/Janggi/assets/84373345/c62b549e-cae1-46e2-8302-3ee12d2af595)


## Rules

Basic Rules link: https://en.wikipedia.org/wiki/Janggi

Check

![K-005](https://github.com/jy-canucks1/Janggi/assets/84373345/1265699a-7e09-43c2-bd38-9fa9e40244fd)

Checkmate

Ends the game. The winner gets 1pt.

![K-009](https://github.com/jy-canucks1/Janggi/assets/84373345/d35a2977-ab96-4022-b6ad-d11769509064)

Bikjang

You must call Bikjang to confirm Bikjang. Then 0.5pt is given to each side.

![K-006](https://github.com/jy-canucks1/Janggi/assets/84373345/23fe374b-2c1a-4ae8-89f1-3a5463203ac0)

![K-007](https://github.com/jy-canucks1/Janggi/assets/84373345/0eaa36b3-7b4c-4021-a4c9-86bfda6f040d)

* Bikjang

The Generals(Kings) may face each other on the same file in Janggi. This creates a situation called bikjang ("laughing generals"). The next player to move has two choices: make a move to break bikjang (for example by moving the king or moving a piece in between), or pass the turn, causing the game to end in a draw.

link: https://www.pychess.org/variants/janggi

## commend lines

* setup

\+ piece position

Places the piece at the position.

![K-003](https://github.com/jy-canucks1/Janggi/assets/84373345/71cc300f-a19c-4f18-a20e-08a49ee097a1)

\- position

Removes the piece from the position.

done

![K-004](https://github.com/jy-canucks1/Janggi/assets/84373345/b098ee59-bac5-49c4-a9fb-98e3a020ed31)

* game

game human human

Two human players attend. (Adding the option for game with computer like "game human computer" is under consideration.)

![K-030](https://github.com/jy-canucks1/Janggi/assets/84373345/000c4061-7923-47d1-b6cd-0d9a9650ff81)

move start_position end_position

Moves the piece from the start_position to the end_position.

![K-006](https://github.com/jy-canucks1/Janggi/assets/84373345/263ae642-1328-46fc-a04d-c5137d8ac1d3)

pass

Skips the turn.

![K-005](https://github.com/jy-canucks1/Janggi/assets/84373345/cbd984b6-fb9e-41f1-850e-9849a6cc397b)

![K-017](https://github.com/jy-canucks1/Janggi/assets/84373345/f76fe53f-7eac-4762-bf54-490f961d8079)

resign

Gives up the game. The winner gets 1pt.

![K-016](https://github.com/jy-canucks1/Janggi/assets/84373345/fc1ac278-201f-45f9-8e1b-58a3db485bcd)

![K-018](https://github.com/jy-canucks1/Janggi/assets/84373345/144118c7-2320-439d-82e1-58d460856934)

![K-019](https://github.com/jy-canucks1/Janggi/assets/84373345/2664a026-37fe-4295-9f05-2b16479e5c1a)

Ctrl + D (EOF)

Shows the final score.

![K-007](https://github.com/jy-canucks1/Janggi/assets/84373345/77319268-ad44-448b-9a30-eaf12fe64f20)


## Online mode

1. Select Online mode.
2. Create the Session(server side) and Wait for the user joining the session(client side).

![K-012](https://github.com/jy-canucks1/Janggi/assets/84373345/f3a516db-4d76-4ece-9d90-b76d7a41be32)

3. You can chat with the user joining the session and once gl is typed twice, from both sides then game starts.

![K-013](https://github.com/jy-canucks1/Janggi/assets/84373345/d3f2e506-aee9-4d73-8e43-f57075d7f219)

![K-020](https://github.com/jy-canucks1/Janggi/assets/84373345/7c2089d4-b0e6-43b2-ab9b-9c0fbb8e5576)

4. While one side is typing the commend line, the other side looking at the waiting message.

![K-015](https://github.com/jy-canucks1/Janggi/assets/84373345/7bbda528-8b3b-42e0-ae19-398c069c832b)

