#include "mystring.h"

MyString::MyString(const char *text) {
    strncpy(static_text, text, STATIC_SIZE);
    if (strlen(text) >= STATIC_SIZE) {
        static_text[STATIC_SIZE] = '\0';
        dynamic_text = text + STATIC_SIZE;
    } else {
        static_text[strlen(text)] = '\0';
    }
}

MyString::MyString(const MyString &text) {
    strcpy(static_text, text.static_text);
    dynamic_text = text.dynamic_text;
}

size_t MyString::initialBufferSize_ = STATIC_SIZE;

char MyString::operator[](size_t i) const {
    if (i >= size()) {
        throw std::out_of_range("Przekroczono zakres tablicy znaków");
    } else if (i < STATIC_SIZE) {
        return static_text[i];
    }
    return dynamic_text[i - STATIC_SIZE];
}

void MyString::operator+=(char c) {
    int current_len = strlen(static_text);

    if (current_len < STATIC_SIZE) {
        static_text[current_len] = c;
        static_text[current_len + 1] = '\0';
    } else {
        dynamic_text += c;
    }
}

MyString& MyString::operator=(const MyString& rhs) {
    strcpy(static_text, rhs.static_text);
    dynamic_text = rhs.dynamic_text;
    return *this;
}

void MyString::push_back(char c) {
    int current_len = strlen(static_text);

    if (current_len < STATIC_SIZE) {
        static_text[current_len] = c;
        static_text[current_len + 1] = '\0';
    } else {
        dynamic_text.push_back(c);
    }
}

void MyString::clear() {
    strcpy(static_text, "\0");
    dynamic_text.clear();
}

std::ostream& operator<<(std::ostream& os, const MyString& ms) {
    if (ms.size() <= STATIC_SIZE) {
        return os << ms.static_text;
    }
    return os << ms.static_text << ms.dynamic_text;
}

std::istream& operator>>(std::istream& is, MyString& ms) {
    std::string whole;
    std::string temp;
    while (is >> temp) {
        temp.push_back(' ');
        whole.append(temp);
    }

    const char *text = whole.c_str();
    strncpy(ms.static_text, text, STATIC_SIZE);

    if (strlen(text) >= STATIC_SIZE) {
        ms.static_text[STATIC_SIZE] = '\0';
        ms.dynamic_text = text + STATIC_SIZE;
    } else {
        ms.static_text[strlen(text)] = '\0';
    }

    return is;
}

MyString& MyString::trim() { 
    std::string string = std::string(*this);
    auto first = std::find_if_not(string.begin(), string.end(), ::isspace);
    auto last = std::find_if_not(string.rbegin(), string.rend(), ::isspace).base();

    std::string trimmedText = std::string(first, last);
    MyString trimmedString = MyString(trimmedText.c_str());
    *this = trimmedString;
    return *this;
}

MyString& MyString::toLower() {
    std::string string = std::string(*this);
    std::transform(string.begin(), string.end(), string.begin(), ::tolower);
    *this = MyString(string.c_str());
    return *this;
}

MyString MyString::join(const std::vector<MyString> &texts) const {
    std::string joinedText;
    std::string currentElement;

    if (texts.size() == 0) {
        return MyString();
    } else if (texts.size() == 1) {
        return MyString(*this);
    }

    joinedText += std::string(texts.at(0));
    for (auto iter = texts.begin() + 1; iter != texts.end(); iter++) {
        joinedText += std::string(*this);
        currentElement = std::string(*iter);
        joinedText += currentElement;
    }

    MyString joinedString = MyString(joinedText.c_str());
    return joinedString;
}

MyString MyString::generateRandomWord(size_t length) {
    std::string randomText(length, ' ');
    std::generate_n(randomText.begin(), length, randomAlphaChar);
    return MyString(randomText.c_str());
}

std::set<MyString> MyString::getUniqueWords() const {
    std::set<MyString> uniqueWords;
    MyString string = *this; 
    string.toLower();

    std::string text = std::string(string);
    auto prev = text.begin();
    auto curr = text.begin();
    
    while (prev != text.end()) {
        prev = std::find_if_not(prev, text.end(), ::isspace);
        curr = std::find_if(prev, text.end(), ::isspace);
        auto left = prev - text.begin();
        auto right = curr - text.begin();
        std::string current = text.substr(left, right - left);
        uniqueWords.insert(MyString(current.c_str()));
        prev = curr;
    }

    return uniqueWords;
}

std::map<MyString, size_t> MyString::countWordsUsageIgnoringCases() const {
    std::map<MyString, size_t> countWords;
    /*MyString string = *this;
    string.toLower();

    std::string text = std::string(string);
    auto prev = text.begin();
    auto curr = text.begin();
    
    while (prev != text.end()) {
        prev = std::find_if_not(prev, text.end(), ::isspace);
        curr = std::find_if(prev, text.end(), ::isspace);

        auto left = prev - text.begin();
        auto right = curr - text.begin();
        std::string current = text.substr(left, right - left);

        current.erase(std::remove_if(current.begin(), current.end(), [](char c){ return !std::isalpha(c); }));
        MyString word = MyString(current.c_str());

        if (countWords.find(word) == countWords.end()) {
            countWords.insert(std::pair<MyString, size_t>(word, 1));
        } else {
            countWords.find(word)->second += 1;
        }
        
        prev = curr;
    }*/

    return countWords;
}

bool MyString::startsWith(const char *text) const { 
    std::string temp = text;
    const_iterator it = std::search(begin(), end(), temp.begin(), temp.end()); 
    return it == begin();
}

bool MyString::endsWith(const char *text) const { 
    std::string temp = text;
    const_iterator it = std::search(begin(), end(), temp.begin(), temp.end()); 
    return (long unsigned)(end() - it) == temp.length();
}

MyString::iterator::iterator(MyString* myString, size_t position) {
    origin = myString;
    if (myString != nullptr) {
        string = std::string(*myString);
    }
    this->position = position;
}

MyString::iterator& MyString::iterator::operator++() {
    if (position < string.size() - 1) {
        position++;
    } else {
        *this = origin->end();
    }
    return *this;
}

MyString::iterator& MyString::iterator::operator--() {
    if (position > 0) {
        position--;
    }
    return *this;
}

size_t MyString::iterator::operator-(MyString::iterator anotherIt) {
    if (position - anotherIt.position > 0) {
        return position - anotherIt.position;
    }
    return (size_t)0;
}

MyString::iterator MyString::iterator::operator+(size_t pos) {
    for (size_t i = 0; i < pos; i++) {
        this->operator++();
    }
    return *this;
}

MyString::const_iterator::const_iterator(const MyString* myString, size_t position) {
    origin = myString;
    if (myString != nullptr) {
        string = std::string(*myString);
    }
    this->position = position;
}

MyString::const_iterator& MyString::const_iterator::operator++() {
    if (position < string.size() - 1) {
        position++;
    } else {
        *this = origin->end();
    }
    return *this;
}

MyString::const_iterator& MyString::const_iterator::operator--() {
    if (position > 0) {
        position--;
    }
    return *this;
}

size_t MyString::const_iterator::operator-(MyString::const_iterator anotherIt) const {
    if (position - anotherIt.position > 0) {
        return position - anotherIt.position;
    }
    return (size_t)0;
}

MyString::const_iterator MyString::const_iterator::operator+(size_t pos) const {
    const_iterator ret = const_iterator(origin, position);
    for (size_t i = 0; i < pos; i++) {
        ret.operator++();
    }
    return ret;
}
