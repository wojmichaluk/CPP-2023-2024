#ifndef MYLIST_H
#define MYLIST_H

#define IMPLEMENTED_constructorOfEmptyList
#define IMPLEMENTED_pushingAndPopingElementsFront
#define IMPLEMENTED_nodesStoredAsUniquePtrs
#define IMPLEMENTED_popFromWhenEmptyList
#define IMPLEMENTED_copyingDisabled
#define IMPLEMENTED_removingElements
#define IMPLEMENTED_iteratorOperations
#define IMPLEMENTED_iteratorWithRangedForLoop
//#define IMPLEMENTED_iteratorWithStlAlgorithm
#define IMPLEMENTED_ostreamOperator

#include <iostream>
#include <memory>

template<class T>
class MyList {
protected:
    size_t size_;

    struct Node {
        T data_;
        std::unique_ptr<Node> next_ {};
    };
    
    std::unique_ptr<Node> head_;

public:
    MyList() : size_{}, head_{} {}
    MyList(const MyList&) noexcept = delete;
    MyList& operator=(const MyList&) noexcept = delete;

    std::size_t size() const noexcept { return size_; }
    void push_front(T);
    T pop_front();
    const T& front() const;

    typedef T value_type; 

    struct Iterator {
    public:
        Iterator(Node* node = nullptr) noexcept : current_(node) {};

        Iterator &operator++() noexcept;
        Iterator operator++(int) noexcept;

        Iterator& operator=(Node *node) {
            current_ = node;
            return *this;
        }
        bool operator!=(const Iterator &other) const noexcept { return current_ != other.current_; }
        T& operator*() noexcept { return current_->data_; }

    private:
        Node *current_;
    };

    Iterator begin() const noexcept { return Iterator(head_.get()); }
    Iterator end() const noexcept { return Iterator(); }

    void remove(T);

    friend std::ostream &operator<<(std::ostream& os, const MyList& ml) {
        os << "Rozmiar listy: " << ml.size_ << std::endl;
        for (Iterator iter = ml.begin(); iter != Iterator(); iter++) {
            os << *iter << std::endl;
        }

        return os;
    }
};

template<class T>
void MyList<T>::push_front(T element) {
    if (size() == 0) {
        head_ = std::make_unique<Node>(element, nullptr);
    } else {
        std::unique_ptr<Node> new_head = std::make_unique<Node>(element, std::move(head_));
        head_ = std::move(new_head);
    }
    size_++;
}

template<class T>
T MyList<T>::pop_front() {
    if (size() == 0) {
        throw std::out_of_range("Próba usunięcia z pustej listy");
    }

    T removed_element = head_->data_;

    head_ = std::move(head_->next_);
    size_--;

    return removed_element;
}

template<class T>
const T& MyList<T>::front() const {
    if (size() == 0) {
        throw std::out_of_range("Próba pobrania z pustej listy");
    }

    return head_->data_;
}

template<class T>
MyList<T>::Iterator& MyList<T>::Iterator::operator++() noexcept {
    if (current_ != nullptr) {
        current_ = current_->next_.get();
    }
    return *this;
}

template<class T>
MyList<T>::Iterator MyList<T>::Iterator::operator++(int) noexcept {
    Iterator tempIter = *this;
    ++*this;                   
    return tempIter;           
}

template<class T>
void MyList<T>::remove(T element) {
    std::vector<T> values;
    std::vector<bool> checks;
    size_t old_size = size();

    for (size_t i = 0; i < old_size; i++) {
        T value = pop_front();
        values.push_back(value);
        checks.push_back(value == element);
    }

    std::reverse(values.begin(), values.end());
    std::reverse(checks.begin(), checks.end());

    for (size_t i = 0; i < old_size; i++) {
        if (!checks[i]) {
            push_front(values[i]);
        }
    }
}

#endif // MYLIST_H
