# Aufgabe: Verschlüsselung in C

Ihre Aufgabe besteht darin, ein C-Programm zu schreiben, dass Daten mit einem einfachen XOR-Algorithmus verschlüsseln kann.

﻿Die Verschlüsselungsfunktionen sind bereits deklariert worden. Sie finden es in der Datei [crypto.h](crypto.h). Lesen aufmerksam die Kommentare in dieser Datei.

Implementieren Sie die Funktionen in einer Datei `crypto.c`. Verändern Sie nicht den Inhalt von `crypto.h`. Der Schlüssel, repräsentiert durch die Struktur `KEY` besteht aus einer Zeichenkette und einer Zahl, die das Verschlüsselungsverfahren anzeiht `type`. `type` ist für die XOR-Verschlüsseung mit `1` festgelegt.

*Tipp*: Denken Sie daran, keinen Code zu duplizieren und führen Sie gegebenenfalls weitere Funktionen ein, um dies zu vermeiden.


## XOR-Verschlüsselung

Implementieren Sie ein Verschlüsselung, die auf der Verknüpfung von Text und Schlüssel per XOR basiert.

Bei der XOR-Verschlüsselung werden Klartext und Schlüssel per XOR miteinander verknüpft. Der Schlüssel kann ein beliebig langer Text sein. Wenn der Klartext länger als der Schlüssel ist, wird der Schlüssel einfach wiederholt. Die Zahlenwerte von Schlüssel und Klartext werden dann per XOR miteinander verknüpft. Die Entschlüsselung funktioniert genauso, indem wieder der verschlüsselte Text und der Schlüssel per XOR miteinander verknüpft werden.

Beispielsweise würde beim Schlüssel `TPERULES` (damit ist jetzt auch klar, woher diese Aufgabe ursprünglich stammt) folgendes passieren:

```console
Klartext:
    A  B  C  D  E  F  G  H  I  J  K  L  M  N  O  P  Q  R  S  T  U  V  W  X  Y  Z
    1  2  3  4  5  6  7  8  9  10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26
Schlüssel:
    T  P  E  R  U  L  E  S  T  P  E  R  U  L  E  S  T  P  E  R  U  L  E  S  T  P
    20 16 5  18 21 12 5  19 20 16 5  18 21 12 5  19 20 16 5  18 21 12 5  19 20 16
Ergebnis:
    U  R  F  V  P  J  B  [  ]  Z  N  ^  X  B  J  C  E  B  V  F  @  Z  R  K  M  J
    21 18 6  22 16 10 2  27 29 26 14 30 24 2  10 3  5  2  22 6  0  26 18 11 13 10
Schlüssel:
    T  P  E  R  U  L  E  S  T  P  E  R  U  L  E  S  T  P  E  R  U  L  E  S  T  P
    20 16 5  18 21 12 5  19 20 16 5  18 21 12 5  19 20 16 5  18 21 12 5  19 20 16
Ergebnis:
    A  B  C  D  E  F  G  H  I  J  K  L  M  N  O  P  Q  R  S  T  U  V  W  X  Y  Z
    1  2  3  4  5  6  7  8  9  10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26
```

Das Ergebnis entsteht durch das XOR-Verknüpfen der Zahlenwerte, z.B. wird `A` mit `T` verschlüsselt, indem man `1 ^ 20 = 21` rechnet. Die Entschlüsselung erfolgt dann umgekehrt, d.h. `21 ^ 20 = 1`, womit sich wieder ein `A` ergibt.
Beachten Sie, dass bei der XOR-Verschlüsselung der Schlüssel `KEY.chars` beliebig lang werden kann. Außerdem brauchen Sie zur Darstellung des verschlüsselten Textes mehr als 26 Buchstaben, nämlich 32. Nehmen Sie daher einfach noch die Zeichen `@=0, [=27, \=28, ]=29, ^=30 und _=31` mit auf.


## Makefile

Schreiben Sie ein Makefile, dass das Bauen und Testen des Programms automatisiert. Folgende Targets sollten mindestens vorhanden sein:

  * `all`
  * `clean`
  * `runtest`

Weitere Targets werden für das Erstellen der Objektdateien und das Linken benötigt. Fügen Sie diese ebenfalls ein.


## Test

Schreiben Sie automatisierte Unit-Tests mit denen Sie die korrekte Funktionsweise der Implementierungen und der Factory-Klasse überprüfen. Legen Sie die Tests in eine andere Datei als die Verschlüsselung. Denken Sie daran, auch die Fehler zu testen.

Da die Unit-Test-Frameworks für C relativ schwergewichtig sind, verwenden Sie am besten zwei einfache Makros nach dem folgenden Vorbild. So ersparen Sie sich das Einbinden eines Frameworks.

```c
#define mu_assert(message, test) do { if (!(test)) return message; } while (0)
#define mu_run_test(test) do { char *message = test(); tests_run++; \
                                if (message) return message; } while (0)
```

Die Test können dann wie folgt geschrieben werden:

```c
static char* test1() {
    mu_assert("Meldung", 1 == 1);
}

static char* allTests() {
    mu_run_test(test1);
    /* weitere Tests */
    return 0;
}

int main() {
    char *result = allTests();

    if (result != 0) printf("%s\n", result);
    else             printf("ALL TESTS PASSED\n");

    printf("Tests run: %d\n", tests_run);

    return result != 0;
}
```

## Programm

Schreiben Sie *ein* Programm, dass sowohl ver- auch entschlüsseln kann. Wie es genutzt wird, bestimmt es selbst aus dem Namen, unter dem es aufgerufen wurde (siehe Wert von `argv[0]`):

  * unter dem Namen `encrypt` verschlüsselt es
  * unter dem Namen `decrypt` entschlüsselt es

Das Programm bekommt als ersten Kommandozeilen-Parameter den Schlüssel übergeben. Wenn ein zweiter Parameter gegeben ist, wird dies als Dateiname interpretiert. Andernfalls liest das Programm die Eingaben von `stdin`.

Der verschlüsselte Text wird in jedem Fall auf der Console (`stdout`) wieder ausgegeben.

Beachten Sie, dass das Programm auch prüfen muss, ob die Parameter korrekt angegeben wurden und nicht läuft, wenn z.B. der Schlüssel fehlt. Auch müssen falsche Zeichen im Text oder Schlüssel gemeldet werden.

```console
$ ./encrypt MYKEY
HALLO
EXGIV
$ ./decrypt MYKEY
EXGIV
HALLO
$ ./encrypt MYKEY ../test.txt
IPNVADJ_]\DWSQ\UMS_L@A_@JY\E
I\Y]OHKXFQALNVJHR^K^
@P_]THQY@KHWS_\DUNK
$ ./encrypt
Usage: KEY [file name]
./encrypt aaa ../test.txt
Error: Key contains illegal characters
```

Fehlermeldungen geben Sie bitte grundsätzlich auf `stderr` aus.
