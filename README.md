# Einleitung
In diesem Bericht wird das Thema maschinelles Lernen mit Fokus auf Lernen mit Belohnung eingegangen. Um genauer auf dieses Thema einzugehen, wurde eine Python-Software entwickelt, die einen Roboter simuliert, welcher mittels KI eigenständig von Punkt A zu Punkt B gelangen soll.

# Software
Die Software beinhaltet eine GUI sowie die KI (Roboter). Die GUI bietet verschiedene Funktionen wie Start, Automatic, Random Start/End Punkt, Exit, Iteration/Explore/Find Way und Row/Columns/Resize. Es gibt auch einen Logger, der Echtzeit-Informationen des Roboters anzeigt.

Hindernisse können erstellt werden, indem man Zellen mit der Maus markiert. Beim Start der Software werden zwei zufällige Punkte als Start- und Endpunkt auf einer Tabelle generiert und farblich hervorgehoben. Der Roboter startet an der gleichen Position wie der Startpunkt.

# KI (Roboter)
Um eine KI zu realisieren, wurde diese in einer separaten Klasse implementiert. Die Klasse beinhaltet das Überprüfen nach Hindernissen sowie die Bewegung des Roboters. Der Roboter speichert jedes Feld in einem Array und berechnet für jede besuchte Zelle die Punkte mit einer Formel. Im zweiten Durchgang kann man nun entscheiden, ob der Roboter weiter erkunden soll oder ob dieser den bestmöglichen Weg finden soll.

Der zweite Modus des Roboters sammelt Informationen über die Nachbarfelder, bewegt sich zum Feld mit der höchsten Punktzahl und wiederholt dies, bis das Ziel erreicht ist. Am Ende werden die Punkte anhand einer Formel berechnet und mit jedem Durchgang wird der Roboter einen besseren Weg finden, bis er den kürzesten Weg gefunden hat.
