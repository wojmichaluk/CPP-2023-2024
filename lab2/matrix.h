#ifndef MATRIX_H
#define MATRIX_H

/** @file matrix.h
@brief Przeciążanie operatorów na przykładzie Macierzy (bardziej szczegolowa tresc w README.md):
1. Zaimplementuj klasę TwoDimensionMatrix odzwierciedlajaca macierz 2*2, zawierającą:
    - tablice typu MatrixElement (tzn. int), oraz `size_` (=2)
    - konstruktory:
        - bezargumentowy - zerujący wszystkie elementy
        - kopiujący
        - przyjmujący jako argument tablicę (const MatrixElement matrix[size_][size_]) i kopiujący z niej wartości
    - funkcja składowa do dostępu do elementów (get() zwracająca odpowiedni element
    - funkcja zwracająca `size_` o nazwie `size()`, proponuję aby była `static constexpr`
    - po zaimplementowaniu usun makro `UNIMPLEMENTED_CONSTRUCTORS`
2. Uzupełnij klasy o następujące operacje zdefiniowane poprzez przeciążenie operatorów:
    - operator przypisania kopiujący (głęboko): `operator=()`
       - po zaimplementowaniu usun makro `UNIMPLEMENTED_ASIGNMENT_OPERATOR`
    - operatory wypisywania do strumienia (funkcja zewn.) - forma dowolna, byleby wszystkie elementy były w strumieniu
       - po zaimplementowaniu usun makro `UNIMPLEMENTED_OSTREAM_OPERATOR`
    - operatory wczytywania z strumienia (funkcja zewn.) - format dla macierzy:
      { a, b }
      { c, d }
      powinno się odbyć:
      ```
        a b
        c d
      ```
       - po zaimplementowaniu usun makro `UNIMPLEMENTED_ISTREAM_OPERATOR`
    - operatory arytmetyczne (stosujące odpowiednie operacje na macierzach):
        - `TwoDimensionMatrix operator+(const TwoDimensionMatrix& matrix1, const TwoDimensionMatrix& matrix2); // jako funkcja globalna`
        - `TwoDimensionMatrix& operator*=(MatrixElement number); // metoda klasy`
        - Zadany operator logiczny (metoda klasy):
          `TwoDimensionMatrix operator&&(const TwoDimensionMatrix& matrix) const;`
           - po zaimplementowaniu usun makro `UNIMPLEMENTED_ARITHMETIC_OPERATORS`
    - operator tablicowy dostający się po indeksie do pierwszego z wymiarów tablicy (metoda klasy), **proszę pamiętać o wersji const**
          `MatrixElement* operator[](size_t i);`
       - po zaimplementowaniu usun makro `UNIMPLEMENTED_SUBSCRIPT_OPERATOR`
    - operator konwersji do size_t, zwracający to co `size()` (metoda klasy)
       - po zaimplementowaniu usun makro `UNIMPLEMENTED_CONVERSION_OPERATOR`
Deklaracja klasy i funkcji globalnych powinna się znaleźć w pliku "matrix.h", natomiast definicje funkcji zewnętrznych i metod klas w pliku źródłowym "matrix.cpp"
____________________________________________________________________________________
## Uwaga (bardziej wiazaca tresc jest w pliku `README.md`):
Wszystkie atrybuty powinny być prywatne, konstruktory i metody - publiczne,
metody większe niż 1-linijkowe powinny być zadeklarowane w klasie, zdefiniowane
poza klasą, obiekty typów klasowych powinny być w miarę możliwości przekazywane
w argumentach funkcji przez referencję, proszę też stosować słówko "const" w
odpowiednich miejscach.

Mozna tworzyc dowolna ilosc metod pomocniczych, jednakze aby byly one prywatne.
____________________________________________________________________________________
## Punktacja:
Na maksa przejście wszystkich testów i niepoprawnych operacji na pamieci (m.in. wyciekow pamieci)
____________________________________________________________________________________
## Najczestrze pytania:
1. Jak ma działać && dla macierzy?
    Wykonująca na każdym z elementów &&, czyli:
    ```
    { 0, 0 }      { 0, 6 }      { 0, 0 }
    {-3, 9 }  &&  { 0, -9 }  =  { 0, 1 }
    ```
2. Jak ma działać operator tablicowy []?
    Operator ten przyjmuje tylko jeden argument (poza this), a chcemy odnieść się w następujący sposób:
    `matrix[row][column]`, dlatego ten operator musi zwrócić matrix[row] typu `MatrixElement*`.
3. Mam operator indeksowania [], a kompilator jakby go nie widzi.
    To najczęstrzy błąd w tym zadaniu - muszą być dwie wersje - jedna zwykła, a druga stała (przydomek `const`)
____________________________________________________________________________________
# Pytania po implementacji ćwiczenia:
@note A. Jaka jest różnica między przeciążaniem operatorów jako metoda klasy vs jako funkcja?
@note B. Których operatorów nie da się przeciążać?
@note C. Wymień operatory mające różną ilość argumentów?
@note D. Jakie konsekwencje będzie miało przeciążanie operatorów logicznych? (chodzi o lazy-evaluation)
**/

#include <iosfwd>

#include "matrixElement.h"

class TwoDimensionMatrix
{
    constexpr static size_t size_ = 2;

public:
    TwoDimensionMatrix();
    TwoDimensionMatrix(const TwoDimensionMatrix&);
    explicit TwoDimensionMatrix(const MatrixElement matrix[size_][size_]);
    MatrixElement get(int, int) const;
    static constexpr size_t size() {
        return size_;
    }

    void operator=(const TwoDimensionMatrix to_copy);
    friend std::ostream& operator<<(std::ostream& os, const TwoDimensionMatrix& to_write);
    friend std::istream& operator>>(std::istream& is, TwoDimensionMatrix& to_save);
    friend TwoDimensionMatrix operator+(const TwoDimensionMatrix& matrix1, const TwoDimensionMatrix& matrix2);
    TwoDimensionMatrix& operator*=(MatrixElement number); // metoda klasy 
    TwoDimensionMatrix operator&&(const TwoDimensionMatrix& matrix) const;
    MatrixElement* operator[](size_t i);
    const MatrixElement* operator[](size_t i) const;
    explicit operator size_t() const; 

private: // methods:

private: // fields:
    MatrixElement matrix_[size_][size_];
};

// jako funkcja globalna
inline TwoDimensionMatrix operator+(const TwoDimensionMatrix& matrix1, const TwoDimensionMatrix& matrix2) {
    int msize = (int)matrix1.size_;
    MatrixElement new_matrix[matrix1.size_][matrix1.size_];

    for (int i = 0; i < msize; i++) {
        for (int j = 0; j < msize; j++) {
            new_matrix[i][j] = matrix1.matrix_[i][j] + matrix2.matrix_[i][j];
        }
    }

    return TwoDimensionMatrix(new_matrix);
}

#endif // MATRIX_H
