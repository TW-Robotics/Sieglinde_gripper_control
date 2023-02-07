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
Der Master-Container stellt den ROSCore zur Verfügung. Der Client Container ist für die ROS-Serial Verbindung zum einem Arduino MEGA zuständig. Der Test Container wird ausschließlich für Testzwecke verwendet.

***
Zum Testen des Greifers kann mit:

```console
$ docker exec -it "ContainerNummer" bash
```
auf den Test Container zugegriffen werden. Im Test Container muss zuerst der ROS Workspace mit ``` $ source /opt/ros/noetic/setup.bash ``` gesourced werden. Danach muss die ROS_MASTER_URI auf den Master Container mit ```$ export ROS_MASTER_URI=http://master:11311``` gesetzt werden (Bei anderem ROSCore bitte dementsprechend anpassen).

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
***
5.Achse nach rechts drehen:
```console
$ rostopic pub drehen std_msgs/Int8 -- 1 
```
5.Achse anhalten:
```console
$ rostopic pub drehen std_msgs/Int8 -- 0 
```
5.Achse nach links drehen:
```console
$ rostopic pub drehen std_msgs/Int8 -- -1 
```

