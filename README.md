<h3 align="center">TermMaze-Engine</h3>

<p align="center">
  Lekki, konsolowy silnik generatora i solvera labiryntów napisany w <b>C++17</b>. Wykorzystuje kody sterujące <b>ANSI</b> do płynnego renderowania bez migotania oraz klasyczne algorytmy grafowe (<b>DFS</b> i <b>BFS</b>) do tworzenia i rozwiązywania struktur w czasie rzeczywistym.
</p>

##  Główne funkcje

| Funkcja | Opis |
|---|---|
| **Generowanie Labiryntu (DFS)** | Silnik wykorzystuje zoptymalizowany algorytm Depth-First Search z stosem (`std::stack`) oraz generatorem Mersenne Twister (`std::mt19937`). |
| **Rozwiązywanie (BFS)** | Implementacja algorytmu Breadth-First Search na kolejce (`std::queue`) gwarantuje znalezienie matematycznie najkrótszej ścieżki do celu. |
| **Płynne UI w Terminalu** | Rysowanie siatki z użyciem bezpośredniego pozycjonowania kursora ANSI (`\033[H`) eliminuje migotanie (brak `cls` / `system("cls")`). |
| **Animacja w Czasie Rzeczywistym** | Wszystkie kroki generacji i poszukiwań ścieżki są animowane na żywo z precyzyjną kontrolą opóźnień (`std::this_thread::sleep_for`). |
| **Stylizowanie ANSI RGB** | Odpowiednie dobranie sekwencji ANSI pozwala renderować szare ściany w przestrzeni RGB (`\033[48;2;160;160;160m`), turkusową falę eksploracji oraz zieloną trasę końcową. |


##  Przepływ Działania

| Etap | Opis działania |
| :---: | :--- |
| **Inicjalizacja** | Ukrycie kursora terminala (`\033[?25l`) oraz przygotowanie pełnej siatki ścian o wymiarach $25 \times 25$. |
| **Generacja** | Dynamiczne drążenie korytarzy z punktu $(1,1)$ z podglądem animacji na żywo. |
| **Pauza** | 3-sekundowe wstrzymanie po ukończeniu generowania pełnej struktury. |
| **Rozwiązywanie** | Eksploracja przestrzeni algorytmem BFS, a następnie rekonstrukcja i podświetlenie najkrótszej drogi do mety $(23, 23)$. |

---

##  Architektura i Logika Projektu

Projekt prezentuje praktyczne zastosowanie teorii grafów w środowisku konsolowym bez użycia zewnętrznych bibliotek graficznych.

###  Algorytm Generowania (Recursive Backtracker / DFS)
Generowanie labiryntu polega na losowym przeszukiwaniu grafu w głąb za pomocą stosu. Użycie struktury `std::stack` zapobiega przepełnieniu stosu wywołań (stack overflow) właściwemu dla czystej rekurencji:
* **Przeskok o 2 komórki:** Generator szuka nieodwiedzonych sąsiadów odległych o $2$ punkty w kierunkach góra/dół/lewo/prawo ($dx \in \{2, -2, 0, 0\}$, $dy \in \{0, 0, 2, -2\}$).
* **Usuwanie ścian:** Po wylosowaniu kierunku z użyciem `std::uniform_int_distribution`, silnik zamienia w ścieżkę (`PATH`) zarówno komórkę docelową, jak i komórkę pośrednią:
  $$\text{punkt}_{\text{sciana}} = \left(x + \frac{dirX}{2}, y + \frac{dirY}{2}\right)$$
* **Cofanie (Backtracking):** Gdy brak poprawnych sąsiadów, silnik zdejmuje element ze stosu (`s.pop()`) i cofa się do wcześniejszego rozgałęzienia.

###  Algorytm Rozwiązywania (Breadth-First Search)
Poszukiwanie ścieżki wykorzystuje przeszukiwanie wszerz, co zapewnia optymalność znalezionej drogi w grafie nieważonym:
* **Fala BFS:** Kolejka `std::queue<punkt>` przetwarza kolejne węzły. Każde odwiedzone pole zostaje tymczasowo oznaczone znakiem `.` (renderowane jako błękitny blok ANSI) oraz zapisuje swojego poprzednika w tablicy `rodzic[y][x]`.
* **Rekonstrukcja ścieżki:** Po osiągnięciu punktu docelowego silnik pętlą `while` przechodzi od mety do startu po wskaźnikach z tablicy `rodzic`:
  $$\text{teraz} = \text{rodzic}[\text{teraz}.y][\text{teraz}.x]$$
  Podmienia przy tym komórki na znak `ROUTE` (`*`), co powoduje ich podświetlenie na kolor zielony.

###  Renderowanie i Sekwencje Sterujące ANSI
Wykorzystanie standardowych kodów sterujących terminala zapewnia szybkie i estetyczne odświeżanie:
* **Pozycjonowanie kursora:** `\033[H` przestawia kursor w lewy górny róg okna zamiast czyszczenia bufora, eliminując klatkowanie.
* **Formatowanie tła:** 
  * Ściana (`WALL`): `\033[48;2;160;160;160m  \033[0m` (szary kolor w trybie RGB 24-bit).
  * Odwiedzone (`.`): `\033[46m  \033[0m` (cyan tło).
  * Najkrótsza droga (`ROUTE`): `\033[42m  \033[0m` (zielone tło).
* **Ukrywanie kursora:** `\033[?25l` wyłącza widoczność migającego kursora na czas działania programu.

---

##  Struktura Klas

* **`plansza`**: Reprezentuje siatkę dwuwymiarową (`std::vector<std::vector<char>>`). Przechowuje stan komórek, odpowiada za bezpieczny dostęp (`isValid`, `getCell`, `setCell`) oraz za właściwy proces renderowania klastrów ANSI.
* **`generujLab`**: Moduł odpowiedzialny za budowanie labiryntu. Operuje na referencji do obiektu `plansza`, implementując generator losowy i pętlę nawrotów.
* **`RozwiazLab`**: Autonomiczny solver wykonujący algorytm BFS. Odpowiada za animację fali przeszukiwania, czyszczenie śladów oraz finalne wyznaczenie optymalnej trasy.
