#ifndef MYSORTING_H
#define MYSORTING_H

#include "myList.h"
#include <algorithm>
#include <cstring>
#include <cmath>

template<class T>
void mySort(T& array) {
    int size = std::size(array);

    for (int i = 0; i < size - 1; i++) {
        for (int j = i + 1; j < size; j++) {
            if (array[i] > array[j]) {
                std::swap(array[i], array[j]);
            }
        }
    }
}

template<class T>
void mySort(std::vector<T>& vector) {
    std::sort(vector.begin(), vector.end());
}

template<class T> 
void mySort(MyList<T>& ml) {
    std::vector<T> values;
    size_t old_size = ml.size();

    for (size_t i = 0; i < old_size; i++) {
        T value = ml.pop_front();
        values.push_back(value);
    }

    std::sort(values.begin(), values.end());
    std::reverse(values.begin(), values.end());

    for (size_t i = 0; i < old_size; i++) {
        ml.push_front(values[i]);
    }
}

int cmp_case_insensitive(const char *first, const char *second) {
    size_t first_len = strlen(first);
    size_t second_len = strlen(second);

    for (std::size_t i = 0; i < std::min(first_len, second_len); i++) {
        char fc = tolower(first[i]);
        char sc = tolower(second[i]);

        if (fc < sc) return -1;
        else if (fc > sc) return 1;
    }

    return first_len - second_len;
}

template<int dim1, int dim2> 
void mySort(char (&char_array)[dim1][dim2]) {
    for (int i = 0; i < dim1 - 1; i++) {
        for (int j = i + 1; j < dim1; j++) {
            int compared = cmp_case_insensitive(char_array[i], char_array[j]);
            
            if (compared > 0) {
                std::swap(char_array[i], char_array[j]);
            }
        }
    }
}

#endif // MYSORTING_H
