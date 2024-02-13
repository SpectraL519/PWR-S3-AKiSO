<script type="text/javascript"
  src="https://cdnjs.cloudflare.com/ajax/libs/mathjax/2.7.0/MathJax.js?config=TeX-AMS_CHTML">
</script>
<script type="text/x-mathjax-config">
  MathJax.Hub.Config({
    tex2jax: {
      inlineMath: [['$','$'], ['\\(','\\)']],
      processEscapes: true},
      jax: ["input/TeX","input/MathML","input/AsciiMath","output/CommonHTML"],
      extensions: ["tex2jax.js","mml2jax.js","asciimath2jax.js","MathMenu.js","MathZoom.js","AssistiveMML.js", "[Contrib]/a11y/accessibility-menu.js"],
      TeX: {
      extensions: ["AMSmath.js","AMSsymbols.js","noErrors.js","noUndefined.js"],
      equationNumbers: {
      autoNumber: "AMS"
      }
    }
  });
</script>

# Semestr 3 - Architektura Komputerów i Systemy Operacyjne

<br />

### Lista 1 (Lab) Termin oddania do 14.10.2022 21.10.2022 24.10.2022

Uwaga: To jest ostatni termin oddania listy na laboratorium, te zadania proszę nie wysyłać na SVN!

1. (2pt) Zainstaluj program do wirtualizacji VirtualBox. Zapoznaj się z programem.

2. (5pt) Zainstaluj w środowisku wirtualnym (VirtualBox) dystrybucję Linuksa Ubuntu. Pobierz obraz systemu tutaj. Naucz się podstawowych komend obsługi systemu z konsoli np. cd, ls, cat, less, apt-get itp.

3. (8pt) Zainstaluj w środowisku wirtualnym (VirtualBox) dystrybucję Linuksa Arch Linux. Pobierz obraz systemu tutaj. Naucz się podstawowych informacji o systemie oraz umiej wytłumaczyć w kilku zdaniach co najmniej
    * Co to jest BIOS oraz UEFI?
    * Co to jest GPT, MBR?
    * Co to jest i jak obsługiwać program do robienia partycji dysku np. fdisk? Wykonaj podstawowe polecenia programu samodzielnie w maszynie wirtualnej
    * Co to jest system plików i jakie systemy plików wykorzystuje Linux?
Ogólne pytania z procesu instalacji
Przykładowe instalacje Arch Linuksa i instrukcja oraz instalacja w VirtualBox

1. (10pt)* Zainstaluj w środowisku wirtualnym system operacyjny z rodziny BSD np. FreeBSD. Jako podstawowy system plików wybierz ZFS oraz wytłumaczyć co to są jails oraz pokaż przykład zastosowania. Umiej zastosować wirtualizację z wykorzystaniem bhyve.
Uwaga: Można wykorzystać też dowolny inny program do wirtualizacji zamiast programu VirtualBox np. QEMU, VMWare Player, ...

<br />
<br />
<br />

### Lista 2 (Lab) Termin wysłania na SVN do 31.10.2022

Na SVN proszę wysłać tylko zadania 3, 4. Resztę zadań należy oddać na pierwszych (lub drugich) zajęciach po terminie wysłania.

1. (5pt) Uruchom poniższy program w symulatorze MARIE (przełącz 'Output mode' na 'UNICODE'). Wytłumacz przy oddawaniu jak on działa.

```

                    LOAD        str_ptr
                    STORE       tolower_ptr
                    JNS         tolower
                    HALT

tolower_itr,        DEC     0
tolower_ptr,        HEX     0
tolower_idx,        HEX     0
tolower_offset,     HEX     20
tolower,            HEX     0

tolower_while,      LOAD        tolower_ptr
                    ADD         tolower_itr
                    STORE       tolower_idx
                    CLEAR
                    ADDI        tolower_idx
                    SKIPCOND    400
                    JUMP        tolower_do
                    JUMPI       tolower

tolower_do,         ADD         tolower_offset
                    OUTPUT
                    LOAD        tolower_itr
                    ADD         ONE
                    STORE       tolower_itr
                    JUMP        tolower_while

str_ptr,            HEX     18          / memory location of str
str,                HEX     48          / H
                    HEX     45          / E
                    HEX     4C          / L
                    HEX     4C          / L
                    HEX     4F          / O
                    HEX     D           / carriage return
                    HEX     57          / W
                    HEX     4F          / O
                    HEX     52          / R
                    HEX     4C          / L
                    HEX     44          / D
                    HEX     0           / NULL char

/ constants
ONE,                DEC     1
```

2. (5pt) Uruchom poniższy program w symulatorze MARIE (przełącz 'Output mode' na 'DEC'). Wytłumacz przy oddawaniu jak on działa (źródła tego i innych przykładowych programów można znaleźć na stronie https://github.com/mathewmariani/MARIE-Examples).

```
Cond,       LOAD        COUNT       / Load count into AC
            SUBT        TEN         / Remove 10 from count
            SKIPCOND    000         / Skipcond 000 if AC < 0
            JUMP        End         / End Loop

Loop,       LOAD        COUNT       / Load count into AC
            ADD         ONE         / Increment Count by 1
            STORE       COUNT       / Store AC in count
            JNS         Fibb
            JUMP        Cond        / Check loop conditions

Fibb,       HEX         000         / Store value for JNS
            CLEAR                   / AC = 0

            / Fi = F1 + F2
            ADD         F1          / AC + F1
            ADD         F2          / AC + F2
            STORE       Fi          / Fi = AC

            / F1 = F2
            LOAD        F2          / AC = F2
            STORE       F1          / F1 = AC

            / F2 = Fi
            LOAD        Fi          / AC = Fi
            STORE       F2          / F2 = AC 

            / Quick Output
            LOAD        Fi          / AC = FI
            OUTPUT                  / Output AC

            JUMPI       Fibb

End,        HALT                    / Halt process

/ variables
COUNT,      DEC         0           / count for loop
Fi,         DEC         0
F1,         DEC         0
F2,         DEC         1

/ constant values
ZERO,       DEC         0
ONE,        DEC         1
TWO,        DEC         2
THREE,      DEC         3
FOUR,       DEC         4
FIVE,       DEC         5
SIX,        DEC         6
SEVEN,      DEC         7
EIGHT,      DEC         8
NINE,       DEC         9
TEN,        DEC         10
```

3. (10pt) Wytłumacz jak wykonane jest mnożenie dla MARIE (patrz przykład z symulatora). Korzystając z tego przykładu napisz dzielenie z resztą.

4. (15pt)* Napisz program dla MARIE, który wypisuje liczbę zapisaną w rejestrze AC w postaci szesnastkowej (np. w języku C ten program działałby podobnie jak printf("%x",123);).

```
                    LOAD        number
                    JNS         tohex
                    HALT
number,             DEC         123

tohex,              ...
                    ...
                    ...
```

<br />
<br />
<br />

### Lista 3 (Lab) Termin wysłania na SVN do 13.11.2022

Na SVN proszę wysłać tylko zadania 6, 7 i 8. Resztę zadań należy oddać najpóźniej na pierwszych (lub drugich) zajęciach po terminie 13.11.2022.

1. (5pt) Wytłumacz jakie pliki zawierają katalogi /dev, /proc oraz sys. Wykorzystując polecenie dd odczytaj pierwszy sektor z dysku głównego (uwaga na prawa dostępu) lub podpiętego pendrive'a i wyświetl przez hexdump -C. Z katalogu proc wyświetl informacje o pamięci, procesorze i partycjach.

2. (5pt) Zapoznaj się z programem ps (man ps). Naucz się posługiwać tym programem, aby umieć sprawdzać co najmniej istnienie i parametry wybranych procesów (PID procesu i rodzica, stan procesu, priorytet, nice, ilość pamięci, zużycie czasu procesora). Uruchom też kilka terminali pokaż jakie urządzenie tty wykorzystują. Wykonując komendę ps axjf pokaż wszystkie procesy które podpięte są do tych terminali (kolumna TTY).

3. (5pt) Zapoznaj się z kompilatorem języka C (polecenie gcc) oraz języka C++ (polecenie g++). Uruchom poniższy program w języku C.

```
$ cat > test.c
#include <stdio.h>

int main(int argc, char *argv[])
{
    printf("Hello, World!\n");
    return 0;
}
^D
$ gcc -Wall -pedantic test.c
$ ./a.out
```

Wytłumacz każdy z powyższych kroków. Co oznaczają opcje -Wall oraz -pedantic? Zobacz man gcc.

4. (5pt) Pokaż na przykładzie (np. sleep 1000, sleep 1001, ...) zarządzanie zadaniami wykorzystując <polecenie> & - uruchamianie w tle (background) oraz jobs, fg, bg, kill oraz ^Z. Uruchom kilka zadań w tle i pokaż jak można nimi zarządzać, czyli zatrzymywać, wznawiać oraz kończyć ich działanie. Pokaż jak uruchomione zadanie (nie w tle), można w czasie działania uruchomić w tle np. wykonując komendę sleep 100 (bez &) w czasie działanie przełącz je do działania w tle.

5. (5pt) Poleceniem mkfifo (man mkfifo) utwórz potok nazwany (ang. named FIFO). Wywołując polecenie cat w różnych terminalach spowoduj wpisywanie danych do potoku przez jeden(ne) proces(y), i odczytywanie i wyświetlanie ich przez inne. Zaobserwuj, kiedy polecenie cat czytające z potoku czeka na więcej danych, a kiedy kończy pracę. Analogicznie, kiedy czeka na więcej danych (z klawiatury) polecenie cat piszące do potoku?

6. (8pt) Napisz program w języku C, który wykorzystując sekwencje Esc (ang. escape sequences) standardu ANSI wyświetli na ekranie napis "Hello, World!", po kolei we wszystkich dostępnych przez terminal kolorach. Czy terminal może wyświetlić 256 lub więcej kolorów?\

7. (10pt) Napisz potok poleceń (może być w skrypcie), który zamienia wszystkie nazwy plików w danym katalogu (bez podkatalogów) na małe litery, czyli wszystkie duże litery występujące w nazwach plików zostaną zamienione na małe, a małe litery pozostają oczywiście dalej małe. Skrypt powinien działać poprawnie na takich nazwach plików jak " ABC DEF", "-AbC aBc" i "--ABC DEF". Przy oddawaniu, proszę podane nazwy plików zakładać w konsoli korzystając z polecenia touch.

8. (10pt)* W shellu można przekierować standardowe wejście, wyjście i wyjście błędu przez wykorzystanie przekierowań <, > oraz 2>. Załóżmy jednak że już wykonaliśmy komendę i dopiero w czasie działającego już procesu chcemy zmienić wejście, wyjście lub wyjście błędu. Na przykład

```
$ sleep 1000 &
[1] 4096
$ ls -l /proc/4096/fd
lrwx------ 1 user users 64 10-30 12:32 0 -> /dev/pts/4
lrwx------ 1 user users 64 10-30 12:32 1 -> /dev/pts/4
lrwx------ 1 user users 64 10-30 12:32 2 -> /dev/pts/4
$ # tutaj zmieniamy wyjście działającego procesu 4096 na plik /tmp/foo
$ # oczywiście nie kończymy działa procesu np. przez kill 4096 w trakcie
$ # zmiany wyjścia ...
$ ...
$
$ ls -l /proc/4096/fd
lrwx------ 1 user users 64 10-30 12:32 0 -> /dev/pts/4
lrwx------ 1 user users 64 10-30 12:32 1 -> /tmp/foo
lrwx------ 1 user users 64 10-30 12:32 2 -> /dev/pts/4
```

Napisz krótką instrukcje w pliku txt jak można wykonać takie przekierowanie i wyślij na SVN. Czy można przenieść działający już program w terminalu do drugiego terminala? Jeśli tak, to pokaż jak to zrobić, jeśli nie, to wytłumacz dlaczego?
Przykład konwersji stron podręcznika man do formatu PDF:

```
$ man -t ps | ps2pdf - ps.pdf
$ man -t gcc | ps2pdf - gcc.pdf
$ # Dla czcionek 'Courier'
$ zcat $(man -w gcc) | groff -Tps -fC -mandoc | ps2pdf - "gcc.pdf"
```

W przypadku braku programu ps2pdf, należy zainstalować pakiet ghostscript np. pod archlinuksem:

```
# pacman -S ghostscript
```

<br />
<br />
<br />

### Lista 4 (Lab) Termin wysłania na SVN do 27.11.2022 4.12.2022

1. (10pt) Napisz skrypt w Bashu, który pokazuje informacje o wszystkich procesach (podobne jak program ps aux). W zadaniu wykorzystaj system plików proc (standardowo w systemie Linux montowanym w katalogu /proc, man 5 proc) do pobrania informacji o procesach np. cat /proc/PID/status (i/lub /proc/PID/stat) wyświetla informacje o procesie PID. Wyświetl ppid, pid, comm, state, tty, rss, pgid, sid i poznaj dokładnie wszystkie wymienione oznaczenia! Dodatkowo wyświetl informację ile proces ma otwartych plików. Wszystkie te informacje o jednym procesie mają być "ładnie" (patrz np. man column) wyświetlone w jednym wierszu podobnie jak w programie ps.

2. (15pt) Napisz skrypt w Bashu, który co sekundę prezentuje informacje o systemie operacyjnym. Dane pobierz wykorzystując pseudo system plików proc w Linuksie domyślnie zamontowanym w katalogu /proc (patrz man 5 proc) oraz sysfs. Skrypt powinien prezentować następujące informacje:
    * Aktualną oraz średnią prędkość wysyłania i odbierania danych z sieci (odczytaj i zinterpretuj /proc/dev/net oraz wyświetl w B, KB lub MB w zależność od aktualnej prędkości) i
    * Aktualne wykorzystanie rdzeni procesora dla każdego rdzenia osobno w procentach wraz z aktualną częstotliwością pracy rdzenia procesora (podobnie jak htop) i
    * Jak długo system jest uruchomiony w dniach, godzinach, minutach i sekundach (/proc/uptime) i/lub
    * Aktualny stan baterii w procentach (/sys/class/power_supply/BAT0/uevent) i
    * Obciążenie systemu /proc/loadavg oraz
    * Aktualne wykorzystanie pamięci /proc/meminfo (przeanalizuj co oznaczają 3 początkowe wiersze).
W przypadku prędkości przesyłania danych skrypt powinien prezentować "graficznie" historię poprzednich pomiarów np. prosty wykres słupkowy. Przykładowe programy z wykresami na których można się wzorować to: s-tui lub bmon lub bpytop. Można wykorzystać inne znaki w UTF-8. Zobacz też informacje o komendzie tput np. link i/lub link. Układ oraz kolejność wyświetlanych informacji jest dowolna.

3. (10pt) Napisz skrypt w Bashu wykorzystujący REST API do pobierania danych z dwóch przykładowych źródeł np. Chuck Norris API i The Cat API lub dowolne inne które pobiera tekst i obrazki. Do zapytań RESTowych wykorzystaj curl lub wget do parsowania JSONa wystarczy program jq (pacman -S jq), dla osób korzystających z formatu XML dostępny jest program xmllint (pacman -S libxml2). Po uruchomieniu skryptu na ekranie pokaż obraz z bazy 'The Cat API' wykorzystując np. program img2txt (pacman -S libcaca) lub catimg oraz poniżej wyświetl losowy cytat z bazy Chucka Norrisa.

4. (15pt) Napisz skrypt w Bashu, który znajduje takie same pliki w podanym katalogu oraz podkatalogach i wyświetla je w terminalu posortowane w kolejności malejącej po wielkościach plików (z pełną ścieżką), czyli na początku zostaną wyświetlone duplikaty plików które zajmują najwięcej miejsca na dysku. Pliki są takie same jeśli mają taką samą zawartość nie jeśli mają takie same nazwy i/lub wielkość. Przykładowe wywołanie programu

```
$ ./searchduplicate /bin
```

gdzie pierwszym parametrem jest katalog w którym, mają zostać znalezione duplikaty plików.
Wskazówka: Na początku najlepiej jest obliczyć hash wszystkich plików np. sha256sum (man sha256sum), później można efektywnie ( O(nlogn) ) znaleźć pliki które są takie same.

5. (15pt)* Celem tego zadania jest dokładniejsze poznanie ANSI escape sequences i obsługi terminali. Bazując np. na grze arkanoid napisz prostą wersję gry Pac-Man lub dowolny prosty wariant gry Boulder Dash. Zrób tak aby gra dostosowywała się do wielkości terminala. Przetestuj program na różnych emulatorach terminali np. xterm, urxvt, st, gnome-terminal, linux console itp., czy są jakieś różnice?

<br />
<br />
<br />

### Lista 5 (Lab) Termin wysłania na SVN do 18.12.2022

1. (5pt) Napisz program w języku C, który uruchomi powłokę (Bash) z prawami roota. Po kompilacji programu można ustawić (z poziomu roota) dowolne atrybuty (np. patrz SUID). Następnie już z poziomu dowolnego użytkownika uruchamiając program uruchamia się konsola administratora, podobnie jak sudo /bin/bash (bez wprowadzania hasła). Oczywiście proszę nie wykorzystywać programu 'sudo' we własnym programie!

2. (5pt) Napisz w języku C programy testujące, które odpowiedzą na następujące pytania:
    * Czy można napisać program do obsługi wszystkich sygnałów (patrz kill -l)? Napisz program prezentujący odpowiedź.
    * Czy jest możliwe wysłać sygnał SIGKILL, lub inny do procesu init (PID 1) czyli np. kill -9 1 (nawet będąc rootem)?
    * Czy sygnały są kolejkowane? Np. napisz program testowy wysyłający wiele razy do danego procesu sygnał (np. SIGUSR1) i zobacz czy wszystkie dotarły.

3. (10pt) Zaimplementuj w języku C prostą wersję powłoki o nazwie lsh. Jak prawdziwa powłoka, lsh odczytuje linię ze standardowego wejścia i przeszukuje ścieżki ze zmiennej PATH (inaczej mówiąc zamiast execve wykonuje execvp) i wykonuje podany program. Proszę pamiętać o ustawieniu argumentów wykonywanej komendy. Jeśli linia kończy się znakiem (&), wtedy lsh powinien nie czekać aż komenda zostanie skończona i od razu wrócić. W innym przypadku lsh powinien zaczekać, aż program wykona się. lsh powinien skończyć swoje działanie naciskając klawisze Control+D lub pisząc exit. Zmieniamy katalogi przez wpisanie komendy cd. Komendy cd oraz exit to komendy wbudowane. Uwaga: Procesy uruchomione w tle, które się zakończyły mogą stać się procesami 'zombi', rozwiąż ten problem w lsh.

4. (10pt) Zaimplementuj w programie lsh z poprzedniego zadania potoki | (ang. pipe) oraz przekierowanie standardowego wejścia (<), wyjścia (>) oraz wyjścia błędu (2>). Wskazówka: Zobacz program lssort.c. Ponadto Ctrl-C przerywa wykonywanie programu w powłoce (nie samej powłoki oraz zadań wykonywanych w tle).

5. (15pt)* Zaimplementuj w programie lsh zarządzanie zadaniami (job-control), czyli co najmniej komendy wbudowane fg, bg, jobs oraz ^Z. Patrz książka Michael Kerrisk, "Linux Programming Interface".

6. (15pt)* Napisz moduł dla Linuksa w języku C, który dodaje nowe wywołanie systemowe i działa na aktualnej wersji Ubuntu i/lub Arch Linux. Nowe wywołanie systemowe wyświetla tylko napis "Hello World!" (wykorzystując printk). Napisz program w języku C, który testuje nowe wywołanie systemowe. Uwaga: Pamiętaj, że dodanie nowego wywołania, aby rozszerzyć funkcjonalność jądra nie powinno być stosowane jako pierwszy wybór! Potraktuj to zadanie tylko jako ćwiczenie.

<br />
<br />
<br />

### Lista 6 (Lab) Termin wysłania na SVN do 8.01.2023 15.01.2023

Uwaga: Wszystkie zadanie wykonujemy na symulatorze. Na SVN proszę wysłać tylko zadania 2, 3 i 4 w postaci linków do symulatora. Po prostu proszę założyć np. plik lista_5_zadanie_2.txt i tam wpisać tylko link oraz podobnie lista_5_zadanie_3.txt.

1. (10pt) Przeanalizuj dokładnie działanie procesora 4-Bit CPU. Przy oddawaniu zadania odpowiedzieć należy na jedno z pytań:
    * która instrukcja potrzebuje więcej niż 1 cykl zegara na wykonanie (execute). Zobacz sygnały 'Exec Clock' i 'Exec Done'
    * wskaż układ w którym realizowane jest dodawanie i odejmowanie oraz wytłumacz jak on działa (zobacz sygnały ADD i SUB, które wchodzą na wejście bramki OR)
    * wytłumacz jak przebiega cykl fetch instr, fetch param, execute, write back (control unit)
    * wytłumacz jak działa zwiększanie instruction pointera oraz skąd wiadomo w których momentach należy go zwiększyć tzn. jedne instrukcje posiadają parametry inne nie, skąd wiadomo kiedy można przejść do następnej komórki pamięci (które bramki tym sterują?)
    * wytłumacz na przykładzie jak działa instrukcja JMP, prześledź sygnały i wytłumacz jak działają bramki (Set Address) w instruction pointer
    * wytłumacz jak działa mechanizm flagi zero, jakie instrukcje mogą zmienić flage?
    * wytłumacz działanie instrukcji SWP i prześledź cały cykl (fetch, ...) jego działania
    * wytłumacz działanie instrukcji MOV i prześledź cały cykl (fetch, ...) jego działania
    * wytłumacz działanie instrukcji OUT i prześledź cały cykl (fetch, ...) jego działania
    * wytłumacz działanie instrukcji JZ i prześledź cały cykl (fetch, ...) jego działania
    * wytłumacz działanie instrukcji ADD i prześledź cały cykl (fetch, ...) jego działania
    * wytłumacz działanie instrukcji SUB i prześledź cały cykl (fetch, ...) jego działania
    * wytłumacz działanie instrukcji AND i prześledź cały cykl (fetch, ...) jego działania
    * wytłumacz działanie instrukcji OR i prześledź cały cykl (fetch, ...) jego działania
    * wytłumacz działanie instrukcji XOR i prześledź cały cykl (fetch, ...) jego działania
    * wytłumacz działanie instrukcji IN i prześledź cały cykl (fetch, ...) jego działania
    * wytłumacz co się dzieje jak wprowadzimy "nielegalną" instrukcję np. do pamięci wpiszemy 0x0e. Czego brakuje? Co należało by zrobić aby procesor po prostu ominął instrukcję

Prowadzący wybiera numer pytania na które należy odpowiedzieć, więc należy znać odpowiedzi na wszystkie, czyli po prostu rozumieć jak działa przedstawiony procesor. Prowadzący wybierając pytanie może dopytywać się różnych innych szczegółów procesora.

2. (15pt) Do 4-Bit CPU dodaj nową instrukcje nazwijmy ją TAB (TRANSFER A TO B) o kodzie 0x0C, która przesyła zawartość rejestru A do B.

3. (15pt) W 4-Bit CPU pamięć jest realizowana za pomocą 16x4 'diode matrix' + dekoder (16 komórek pamięci 4 bitowych), czyli szyna adresowa jest 4-bitowa (maks 2^4 komórek pamięci). Zmodyfikuj ten CPU tak aby szyna adresowa była 5-bitowa, przy czym instrukcje skoków JZ, JMP mogą być 4-bitowe i tylko na adresy parzyste, czyli pierwszy bit w skoku ustawiamy na zero, więc możemy skakać tylko na adresy 0, 2, 4, 6, ... lub można to rozwiązać w inny sposób np. skoki tylko do pierwszych 16 komórek (lub drugich 16-32) itp.

4. (10pt)* Zrób zadanie poprzednie tak, aby możliwe były jednak skoki w dowolne 5-bitowe adresy pamięci z wykorzystaniem dalej 4-bitowych komórek pamięci ROM (bez zmian mamy też rejestry 'instruction register' i 'parameter register').

<br />
<br />
<br />

### Lista 7 (Lab) Termin wysłania na SVN do 22.01.2023 oraz oddania do 2.02.2023

1. (10pt) Napisz program w asemblerze nasm (lub innym) dla procesora x86, który wyświetla na standardowym wyjściu liczbę 32-bitową w kodzie szesnastkowym, czyli np. takie printf("%x\n",123456). Do wyświetlania wykorzystaj wywołanie systemowe write. Pokaż jak program wykonuje się w gdb (debugger).

2. (10pt) Napisz program w asemblerze x86 (32-bit), który wysyła na standardowe wyjście liczby pierwsze z zakresu od 1 do 100 000.

3. (10pt) Wykorzystując konwersje BCD (TYLKO BCD), napisz program w asemblerze nasm (lub innym) dla procesora x86, który wyświetla na ekranie liczbę 16-bitową w kodzie dziesiętnym. Wytłumacz dokładnie zasadę jego działania.

4. (10pt) Napisz program w asemblerze nasm (lub innym) dla procesora x86 z rozkazami SIMD (SSE2, SSE4, AVX, ...), który liczy silnię n! na liczbach 512 bitowych. Zauważ, że np. 128-bitowe rejestry XMM0,...,XMM7 od wersji SSE2, mogą być traktowane jako dwa 64-bitowe liczby całkowite lub cztery 32-bitowe itd. Liczba n pobierana jest z argumentów argc, argv (lub ze standardowego wejścia) oraz wynik wysyłany jest na standardowe wyjście.

5. (10pt) Wzorując się na szybkim mnożeniu dla procesora 6502 przedstawionym na wykładzie i/lub artykule Multiplying and Dividing on the 6502, napisz program w nasm (lub innym) dla procesora x86, który wykonuje mnożenie i dzielenie z resztą liczby 32-bit przez 32-bit (czyli wraca wynik mnożenia i dzielenia oraz resztę). Staraj się zrobić dzielenie o najmniejszej złożoności obliczeniowej. Nie wolno wykorzystywać wbudowanych rozkazów mnożenia i dzielenia, tylko dodawanie, odejmowanie i przesunięcia bitowe z ALU, czyli nie robimy prostego mnożenia i dzielenia tylko przez dodawanie i odejmowanie.

6. (10pt) Napisz program w asemblerze nasm (lub innym) dla procesora x86 z wykorzystaniem koprocesora matematycznego x87, który potrafi obliczać bardzo proste wyrażenia arytmetyczne. Program pobiera ze standardowego wejścia łańcuch znaków postaci "liczba operacja liczba" np. 2 * 2.5 lub 3.14 / 5 itd. Wykorzystując koprocesor matematyczny oblicza wynik (na liczbach zmiennoprzecinkowych) i wysyła na standardowe wyjście. Do konwersji na liczby zmiennoprzecinkowe należy samemu napisać odpowiednie procedury tzn. bez wykorzystania funkcji bibliotecznych np. scanf, atof, printf, ftoa itp. (ale można wzorować się na kodach z linków!). Nie muszą to być pełne konwersje tzn. np. 1e12 itp. wystarczy format cyfry kropka cyfry!

7. (10pt) Napisz w asemblerze x86 program rysujący zbiór Mandelbrota (patrz wykład 2022.12.21). Inicjalizację trybu graficznego można przeprowadzić wykorzystując kod boot.
(10pt) 

8. Napisz funkcje w asemblerze nasm (lub innym) dla procesora x86 z wykorzystaniem koprocesora matematycznego x87, które obliczają:

    * $\ln{x}$
    * $e^x$
    * $\sinh{x} = \frac{e^x - e^{-x}}{2}$
    * $(\sinh{x})^{-1} = \ln{(x + \sqrt{x^2 + 1})}$

<br />
<br />
<br />

### Lista 8 (Lab) Termin wysłania na SVN oraz oddania do 2.02.2023

1. (5pt) Napisz program w języku C, który dokonuje konwersji liczby zmiennoprzecinkowej zapisanej w postaci dziesiętnej do postaci binarnej z DOWOLNĄ DOKŁADNOŚCIĄ.

```
$ ./f2b
Składnia: <liczba> <liczba cyfr po przecinku>
$ ./f2b 0.3 500
0.010011001100110011001100110011001100110011001100110011
00110011001100110011001100110011001100110011001100110011
00110011001100110011001100110011001100110011001100110011
00110011001100110011001100110011001100110011001100110011
00110011001100110011001100110011001100110011001100110011
00110011001100110011001100110011001100110011001100110011
00110011001100110011001100110011001100110011001100110011
00110011001100110011001100110011001100110011001100110011
001100110011001100110011001100110011001100110011001100
```

2. (5pt) Napisz program (nazwijmy go np. sasm) w języku C, który asembluje (zamienia na kod maszynowy) program napisany dla prostego procesora MARIE (patrz np. ćwiczenia lista 9). W tym zadaniu można zrobić, program który wykorzystuje tylko adresy bezpośrednie (bez etykiet).

3. (5pt) Napisz program (nazwijmy go np. sasm) w języku C, który asembluje program napisany dla prostego procesora (patrz np. ćwiczenia lista 9). W tym zadaniu program, powinien pozwalać na używanie etykiet w kodzie asemblera.

4. (5pt) Napisz w języku C własną implementacje funkcji printf i scanf (nazwijmy je myprintf i myscanf). Funkcje nie mogą wykorzystywać, żadnych funkcji bibliotecznych (atoi, fprintf, fscanf itp.) oraz makr va_start, va_arg i va_end (np. możesz skorzystać z wyjaśnienia tutaj oraz patrz X86 calling conventions i dokładniej cdecl) oraz można wykorzystać wywołania systemowe read i write z odpowiednim standardowym deskryptorem. Program należy skompilować na maszynę 32-bitową tzn. gcc -m32 np. dla 64-bitowego systemu ArchLinux trzeba zainstalować pakiet gcc-multilib z repozytorium multilib. W funkcjach wystarczy zaimplementować "%s", "%d", "%x" i "%b", gdzie w naszej implementacji "%s" wyświetla ciąg znaków, "%d" liczbę w systemie dziesiętnym, "%x" liczbę w systemie szesnastkowych oraz "%b" liczbę w systemie binarnym.

5. (5pt) Napisz w języku C wielowątkową wersję mnożenia macierzy boolowskich. Program powinien pobierać z linii komend wielkość macierzy (wypełniać ją losowymi wartościami 0 lub 1, patrz man 3 random) oraz liczbę wątków, która powinna zostać uruchomiona do mnożenia. Zaimplementuj program tak, że każdy wątek pracuje na osobnym wierszu, jeśli jeden skończy pracę to dalej pracuje na następnym wolnym wierszu oraz pamiętaj, że pojedynczy iloczyn skalarny (wiersz razy kolumna) może zostać ustalony wcześniej nawet po pierwszej koniunkcji. Pamiętaj, że przy dostępie do zmiennych współdzielonych mogą wystąpić wyścigi!

6. (5pt) Wykorzystując rozkazy MMX, bibliotekę SDL oraz wzorując się na przykładzie z wykładu fade, napisz program wykonujący płynne przenikanie jednego obrazu graficznego w drugi. Postaraj się jak najbardziej zoptymalizować program (czyli uzyskać jak największe FPS).

7. (5pt) Napisz program w języku C podobny do minitalk bez wykorzystywania dodatkowych procesów (fork) lub wątków. Wykorzystaj wywołanie systemowe select oraz gniazda. Program ma być w tym zadaniu prostym komunikatorem internetowym. Na początku następuje proste logowanie (bez haseł) do serwera, wtedy wyświetlone są loginy wszystkich zalogowanych użytkowników. Następnie możemy wysłać wiadomość do dowolnego użytkownika i tylko do niego.

8. (5pt) Do poprzedniego zadania dodaj proste szyfrowane połączenie. Do szyfrowania można wykorzystać dowolną bibliotekę np. OpenSSL.

9. (5pt) Zrób zadanie 1 tak, aby działało na maszynie 64-bitowej (x86-64, AMD64). Patrz x86 calling conventions, a dokładniej x86-64 calling conventions oraz System V AMD64 ABI.

10. (10pt) Napisz program w języku C, który mnoży (wystarczy losowe) dwie macierze o dowolnym rozmiarze n (wartość pobierana z linii komend) przez siebie i wraca czas wykonywania tej operacji (man gettimeofday). Zrób tą samą operacją najpierw wykonując transpozycję drugiej macierzy. Jaki teraz otrzymamy czas działania? Dlaczego? Następnie postaraj się bardziej zoptymalizować program pod pamięć podręczną (ang. cache) procesora.

11. (10pt) Załóż system plików FAT i VFAT (podobnie jak na wykładzie). Utwórz na nim kilka plików (co najmniej jeden większy od wielkości pojedynczego klastra) i pokaż jak są przechowywane w systemie plików (hexdump -C) np. jak zmieniła się tablica alokacji (FAT), tablica katalogów (root directory entry) oraz gdzie znajduje się zawartość plików. Usuń wybrany plik i pokaż jak zmienił się system plików. Co należy zrobić aby odzyskać skasowany plik? Wprowadź długą nazwę pliku i pokaż jak jest reprezentowana w systemie FAT i VFAT.

12. (10pt) Napisz w języku C program, wykorzystujący FUSE, który pozwala szyfrować dane na dysku. Dokładnie uproszczoną wersję programu gocryptfs. Podobnie jak program gocryptfs tworzymy dwa katalogi np. /tmp/crypt-raw, który przechowywuje szyfrowane dane oraz /tmp/crypt który przedstawia dane z katalogu /tmp/crypt-raw w postaci odkodowanej. Do kodowania można wykorzystać np. algorytm AES lub inny aktualnie uważany za bezpieczny.