# Budowanie i Uruchamianie
Do budowania użyłem CMake. Pozwolił na podzielenie kodu na czytelne moduły.
### Budowanie
Aby zbudować projekt:<br />
```mkdir build && cd build```<br />
```cmake .. && cmake --build .```
### Uruchamianie
Aby uruchomić zbudowany projekt:<br />
```./pwr_racing```

# Zastosowane technologie
- Język programowania: C++ 17
- Kompilator: g++ 11.4.0
- Build system: CMake

# Algorytm
### Problem
Spośród zbioru punktów na płaszczyźnie 2D, znaleźć taki podzbiór, który otacza wszystkie pozostałe punkty.
### Rozwiązanie - Graham Scan
[Opis algorytmu Graham Scan na stronie geeks for geeks](https://www.geeksforgeeks.org/convex-hull-using-graham-scan/) <br />
Do znalezienia otoczki wypukłej, czyli takiej, która pomiędzy swoimi wierzchołkami nie
ma kątów wklęsłych użyłem algorytmu Graham Scan. Polega on na znalezieniu punktu najbliższego do osi X jako punkt 0, a następnie
posortowaniu pozostałych punktów według kąta pomiędzy wektorem, który tworzą razem z punktem 0, a osią X.
Iterując po tych punktach następnie "zawijamy się" wokół grupy punktów, a jeśli znajdziemy punkt, który
otacza punkty już znajdujące się w otoczce, to "odwijamy" tak długo, aż je otoczymy.
# Organizacja kodu
W celu poprawienia organizacji i modularności kodu, podzieliłem go na 3 katalogi:
- convex_hull - tam znajduje się kod oraz nagłówki związane z obliczaniem otoczki wypukłej
- utils - proste funkcje pomocnicze
- point - tutaj zdefiniowany jest ```struct Point``` oraz logika odczytywania punktów z pliku. 

W moim kodzie nie tworzyłem klas ani namespaców, żeby zbytnio nie komplikować.
