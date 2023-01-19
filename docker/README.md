# Dockerdateien für ROS Ansteuerung des Taurob Greifers

Docker Client verbindet einen PC/Raspberry Pi mit Arduino für die Ansteuerung des Greifers.
Docker Images in den jeweiligen Ordnern bauen mit:

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

Danach kann mit:

```console
$ docker exec -it "ContainerNummer" bash
```
auf den Test Container zugegriffen werden.

Mit den folgenden Befehlen kann der Greifer sowie die 5-Achse betrieben werden. Der Greifer subscribt das Topic **greifen** und die 5-Achse das Topic **drehen**.

Grundstellung des Greifers (geschlossen)
```console
$ rostopic pub greifen std_msgs/Int16 -- 0 
```
Gänzlich geöffneter Greifer
```console
$ rostopic pub greifen std_msgs/Int16 -- -360
```
zweite Grundstellung des Greifers (geschlossen)
```console
$ rostopic pub greifen std_msgs/Int16 -- -720
```


