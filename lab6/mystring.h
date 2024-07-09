#ifndef MYSTRING_H
#define MYSTRING_H

#include <iostream>
#include <cstring>
#include <algorithm>
#include <set>
#include <map>
#include <vector>
#include <functional>
#include <random>
#include <ctime>
#include <cctype>

#define STATIC_SIZE 20

class MyString {
private:
    char static_text[STATIC_SIZE + 1]; // place for '\0' at the end
    std::string dynamic_text;
    static std::string alphanum;
    static char randomAlphaChar() { return rand() % 26 + 65 + rand() % 2 * 32; }

public:
    MyString() : static_text{}, dynamic_text{} {}
    MyString(const char*);
    MyString(const MyString&);

    static size_t initialBufferSize_;

    struct iterator {
        typedef std::forward_iterator_tag iterator_category;
        typedef char value_type;
        typedef ptrdiff_t difference_type;
        typedef char* pointer;
        typedef char& reference;

        explicit iterator(MyString* myString, size_t position);
        auto getPosition() const { return position; }
        iterator& operator++();
        iterator& operator--();

        size_t operator-(iterator);
        iterator operator+(size_t);

        bool operator!=(iterator anotherIt) { return string != anotherIt.string; }
        bool operator==(iterator anotherIt) { return !this->operator!=(anotherIt); }
        char& operator*() { return string[position]; }

    private:
        MyString* origin;
        std::string string;
        size_t position;
    };

    struct const_iterator {
        typedef std::forward_iterator_tag iterator_category;
        typedef char value_type;
        typedef ptrdiff_t difference_type;
        typedef char* pointer;
        typedef char& reference;

        explicit const_iterator(const MyString*, size_t);
        auto getPosition() const { return position; }
        const_iterator& operator++();
        const_iterator& operator--();

        size_t operator-(const_iterator) const;
        const_iterator operator+(size_t) const;

        bool operator!=(const_iterator anotherIt) const { return string != anotherIt.string; }
        bool operator==(const_iterator anotherIt) const { return !this->operator!=(anotherIt); }
        char operator*() const { return string[position]; }

    private:
        const MyString* origin;
        std::string string;
        size_t position;
    };

    auto capacity() const { return STATIC_SIZE + dynamic_text.capacity(); }
    auto size() const { return strlen(static_text) + dynamic_text.length(); }
    bool empty() const { return size() == 0; }

    iterator begin() { return iterator(this, 0); }
    iterator end() { return iterator(nullptr, size()); }

    const_iterator begin() const { return const_iterator(this, 0); }
    const_iterator cbegin() const { return const_iterator(this, 0); }
    const_iterator cend() const { return const_iterator(nullptr, size()); }
    const_iterator end() const { return const_iterator(nullptr, size()); }

    bool operator!=(const MyString& rhs) const { return strcmp(static_text, rhs.static_text) || dynamic_text != rhs.dynamic_text; }
    bool operator<(const MyString& rhs) const { return strcmp(static_text, rhs.static_text) < 0 && dynamic_text < rhs.dynamic_text; }
    bool operator==(const MyString& rhs) const { return !this->operator!=(rhs); }
    char operator[](size_t) const;
    void operator+=(char);
    MyString& operator=(const MyString& rhs);
    explicit operator std::string() const { return std::string(static_text) + dynamic_text; }
    
    void push_back(char);
    void clear();
    friend std::ostream& operator<<(std::ostream&, const MyString&);
    friend std::istream& operator>>(std::istream&, MyString&);

    MyString& trim();
    MyString& toLower();
    MyString join(const std::vector<MyString>&) const;
    static MyString generateRandomWord(size_t);

    std::set<MyString> getUniqueWords() const;
    std::map<MyString, size_t> countWordsUsageIgnoringCases() const;
    
    bool startsWith(const char *text) const;
    bool endsWith(const char *text) const;
    bool all_of(std::function<bool(char)> predicate) const { return std::all_of(begin(), end(), predicate); }
};

#endif //MYSTRING_H
