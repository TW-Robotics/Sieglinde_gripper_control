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
***
## Greifer
Grundstellung des Greifers (geschlossen)
```console
$ rostopic pub greifen std_msgs/Int16 -- 360
```
Gänzlich geöffneter Greifer
```console
$ rostopic pub greifen std_msgs/Int16 -- 0
```
zweite Grundstellung des Greifers (geschlossen)
```console
$ rostopic pub greifen std_msgs/Int16 -- -360
```
***
## Drehachse
Drehachse nach rechts drehen:
```console
$ rostopic pub drehen std_msgs/Int8 -- 1 
```
Drehachse anhalten:
```console
$ rostopic pub drehen std_msgs/Int8 -- 0 
```
Drehachse nach links drehen:
```console
$ rostopic pub drehen std_msgs/Int8 -- -1 
```
***
## Geschwindigkeit
Geschwindigkeit der Drehachse setzen (zwischen 0 und 50, default: 25):
```console
$ rostopic pub setpeed1 std_msgs/UInt8 -- *speed*
```
Geschwindigkeit des Greifers setzen (zwischen 0 und 50, default: 25):
```console
$ rostopic pub setpeed2 std_msgs/UInt8 -- *speed*
```
***
## Initialisieren
Initialisieren der Drehachse auf 0 Grad:
```console
$ rostopic pub init std_msgs/UInt8 -- 1
```
Initialisieren des Greifers auf 0 Grad:
```console
$ rostopic pub init std_msgs/UInt8 -- 2
```
