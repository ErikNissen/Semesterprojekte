# Projekt-X - Passwortgenerator
Dieses Softwareprojekt wurde erstellt im Rahmen des Moduls "Mobile Systeme", welches im Wintersemester 2021 / 2022 angeboten wurde in der Fachhochschule Kiel. Autoren des Softwareprojekts: Nico Johnsen und Erik Nissen.

# Funktionsweise der App
Diese App generiert ein Passwort welches auf echte Zufallszahlen basiert. Diese Zufallszahlen werden über eine API abgerufen, welche mit einem Quantencomputer kommuniziert. Weitere Informationen sind weiter unten anzutreffen.

# Hinweis
```diff
- Aufgrund der Anforderung werden die Passwörter in der Firebase Datenbank von Google abgespeichert. 
- Daher ist diese App (aktuell) nicht sicher jedoch wird dies in näherer Zukunft sich ändern sobald dafür Zeit ist.
```

## Seite 1 - Login
– Email Login
- Registrieren
- Passwort zurücksetzen

## Seite 2 – Passwort Parameter Generator
- API PW Generator
    - https://qrng.anu.edu.au/contact/api-documentation/
- Slider für Parameter
- Button für Passwortgenerator
- Button zum speichern des Passwortes

## Seite 3 - ListView
- Liste der Passwörter
- Button zum kopieren eines Passwortes
- Button zum löschen eines Passwortes

## Meilensteine 

<details>
<summary><h3>✔M1</h3></summary>
AF1 und AF2 sind erfüllt. Die Routen und die ListView/GridView müssen noch keine 
sinnvollen Daten beinhalten.
<details>
<summary>✔AF1</summary>
Die App besteht aus mind. drei unterschiedlichen Routen (entspricht Screens innerhalb der
App), zwischen denen navigiert werden kann.
</details>
<details>
<summary>✔AF2</summary>
Die App enthält mind. eine scrollbare ListView oder GridView.
</details>
</details>

<details>
<summary><h3>✔M2</h3></summary>
AF3 und AF4 sind erfüllt. Die App kann also Daten von einem Gerätesensor oder aus einer 
öffentlichen API darstellen und den authentifizierten Anwender erkennen.
<details>
<summary>✔AF3</summary>
Die App bindet sinnvoll mind. einen Sensor des mobilen Geräts oder eine öffentliche API
ein. Siehe unten, um Anregungen diesbezügl. zu erhalten.
</details>
<details>
<summary>✔AF4</summary>
Die App unterstützt eine Authentifizierung der Anwender. Ob die Authentifizierung anonym,
mittels E-Mail und Passwort und/oder über andere Dienste erfolgt, ist freigestellt. Es wird die
Verwendung von Firebase empfohlen.
</details>
</details>

<details>
<summary><h3>✔M3</h3></summary>
Es wird die finale Version der App präsentiert, die alle oben genannten Anforderungen AF1-
5 erfüllt.
<details>
<summary>✔AF5</summary>
Die App speichert ausgewählte Daten auf einem Server in einer Datenbank und/oder einem
Objekt-Storage. Es wird die Verwendung von Firebase empfohlen
</details>
</details>


<details>
<summary><h3>Quickstart-Guide</h3></summary>
Zuerst muss man sich registrieren, wenn man registriert ist oder schon ein Account hat, meldet man sich in der APP an.
Man befindet sich dann schon im Passwort Generator, hier gibt man an wie lang das Password sein soll und welche Zeichen dieses beinhalten soll
und klickt dann auf „Generiere Passwort", wenn einem das Passwort gefällt kann man es speichern und bei Bedarf eine Notiz dazu schreiben.
Um die erstellten Passwörter sich anzuschauen, drückt man oben links in der Ecke (links neben dem Zahnrad) auf das Symbol und sieht dann alle Passwörter,
die man gespeichert hat samt Notizen. Die Passwörter kann man sich kopieren oder wenn man diese nicht mehr braucht löschen.
</details>

____
____

## main.dart
In dieser Datei befinden sich die Klassen, welche die Grundfunktionen der App beinhaltet.

<details>
<summary><h3>Klassen</h3></summary>
<details>
<summary>GeneratorEinstellungen</summary>
In der Klasse werden die Passwortparameter; die Länge des Passwortes sowie die Zeichengruppen; gesetzt 
sowie der Generator gestartet.
</details>
<details>
<summary>Settings</summary>
Diese Klasse beinhalten allgemeine Einstellungen, welche aktuell nur Platzhalter sind.
</details>
</details>

## firebase.dart
In dieser Datei befinden sich die Klassen, welche mit der Firebase kommunizieren.

<details>
<summary><h3>Übersicht</h3></summary>
<details>
<summary>Klassen</summary>
<details>
<summary>LoginPage</summary>
Hier kann sich der Nutzer einloggen sowie zu den Seiten "Regestrieren" oder "Passwort zurücksetzen" gelangen.
</details>
<details>
<summary>ForgotPassword</summary>
Hier kann der Nutzer sein Passwort zurücksetzen.
</details>
<details>
<summary>RegisterPage</summary>
In der Klasse wird ein neuer Benutzer angelegt.
</details>
<details>
<summary>DatenbankView</summary>
Auf dieser Seite werden die gespeicherten Passwörter abgerufen und angezeigt.
Der Nutzer kann von hier aus Passwörter kopieren sowie löschen.
</details>
</details>
<details>
<summary>Funktionen</summary>
<details>
<summary>_encpass</summary>
Diese Funktion wandelt das Klartext Passwort mithilfe des SHA512 Algorithmus um.
</details>
<details>
<summary>createcollection</summary>
Hier wird die Bezeichnung für eine Collection generiert, indem die Email sowie der SHA512-Hash des Passwortes konkatiniert wird und das Ergebnis mit dem MD5 Algorithmus verschlüsselt wird.
</details>
</details>
</details>

## crypto.dart
In dieser Datei wird das Passwort generiert.
<details>
<summary><h3>Funktionen</h3></summary>
<details>
<summary>Qrand</summary>
Diese Funktion gibt ein URL zurück, welcher die Länge des Passwortes enthält.
</details>
<details>
<summary>Gen_Password</summary>
In dieser Funktion werden zuerst die verbotenen Symbole definiert.
Im nächsten Schritt wird die Differenz dieser Menge und der Menge der erlaubten Symbole gebildet.
Damit es keine Zufallszahlen gibt, die größer als der größte Index in der Menge der erlaubten Symbole ist, wird die Menge der erlaubten Symbole so lange verdoppelt, bis diese größer/gleich 255 ist.
Danach werden die Zufallszahlen über eine API von einem Quantencomputer gezogen.
Falls die Passwortlänge größer als 255 ist, wird die Menge der erlaubten Symbole mit dem ganzzahligen Anteil des Quotienten aus der Passwortlänge und 255 multipliziert.
Am Ende setzt sich das Passwort aus den Zeichen zusammen, welche in der Menge der Zufallszahlen ist.
</details>
</details>
