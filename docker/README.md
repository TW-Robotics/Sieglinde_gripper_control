# Dockerdateien für ROS Ansteuerung des Taurob Greifers

Docker Client verbindet einen PC/Raspberry Pi mit Arduino für die Ansteuerung des Greifers.
Docker Images bauen mit:

```console
$ docker build -t client .
```
```console
$ docker build -t master .
```
```console
$ docker build -t test .
```
Alle Docker Container starten mit:

```console
$ docker-compose up
```



