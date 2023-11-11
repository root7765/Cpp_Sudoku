# Sudoku Lösen

Sudokus sind eine populäre Art von Zahlenpuzzels. Gespielt wird auf einen 9x9 Felder Spielfeld. Jeder Zelle wird 
dabei eine Ziffer von 1-9 zugordnet. Die Zahlen müssen so gewählt werden, dass in einer Zeile und einer Spalte
jede Ziffer nur einmal vorkommt. Darüher hinaus darf eine Ziffer in einem 3x3 Feld nur einmal vorkommen. Da eine 
gewissen Menge von Feldern bereits belegt sind ist dies bei den selbst eingetragenen Ziffern zu berücksichtigen.

## Aufgabe:

* Der Algorithmus zum Lösen eines Sudokos in `SudokuSolver.cpp` enthält **sieben** Fehler. Finden und beheben sie diese!

## Hinweise:

* Die Fehler orientieren sich an typischen Fehlern wie sie von Studierenden im Rahmen dieser Vorlesung gemacht werden.
* Es sind sowohl synktische als auch logische Fehler enthalten.
* Der Algorithmus wird erst vollständig funktionieren wenn sie **alle** Fehler gefunden haben!
* Ob ihre Lösung richtig ist können sie mir dem Moodle-Test überprüfen nachdem das lokale Sudoku gelösst ist.
* Sie dürften den Algorithmus ausführen und auch Debugging Funktionen hinzufügen (z.B. `cout`-Anweisungen)
* Nutzen sie auch den Debugger, um durch die Einzelschritte zu laufen.
* **Wechseln sie in das richtige Projektverzeichnis!**

## Hinweise zur Moodle Einreichung:
Sie können die Ergebnisse der Aufgaben in Moodle selbstständig überprüfen. Öffnen Sie dazu den Moodle Kurs und begeben sich zur Kachel Übungen.
Dort finden sie den entsprechenden Test. 
Sie müssen nun ihre Ergebnisse zusammenstellen. Dazu führen sie im Terminal das Script `./zipUpload.sh` aus (z.B. `./zipUpload.sh`).
Die nun entstandende Datei können sie im entsprechenden Moodle Test hochladen und überprüfen. Die Dateien folgen dem Schema
`upload_<Aufgabenverzeichnis>_<Zeitstempel>.zip`. Es können also mehrere ZIP-Dateien entstehen wenn sie mehrere Versuche benötigen.
Das Herunterladen der ZIP-Dateien geschieht über einen rechten Mausklick auf die Datei und das anschließende Auswählen von `Download` im Kontextmenü.

## Links

* Moodle <https://moodle.ostfalia.de/>
* C++ Referenz <https://de.cppreference.com/w/Hauptseite>
* Mehr Informationen zu Sudokus <https://de.wikipedia.org/wiki/Sudoku>
