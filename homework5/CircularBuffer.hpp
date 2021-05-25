#pragma once

template<class T>
class CircularBuffer {
private:
    int size = 0;
    int capacity = 0;
    T *elements = nullptr;
public:
    class Iterator {
    private:
        T *elements = nullptr;
    public:
        using iterator_category = std::random_access_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = T*;
        using reference = T&;

        explicit Iterator(T *start) {
            elements = start;
        }

        Iterator(const Iterator &other) {
            elements = other.elements;
        }

        ~Iterator() = default;

        Iterator operator+(value_type tempNum) {
            elements += tempNum;
            return *this;
        }

        Iterator operator++() {
            elements++;
            return *this;
        }

        Iterator operator-(value_type tempNum) {
            elements -= tempNum;
            return *this;
        }

        value_type operator-(const Iterator &other) const {
            return elements - other.elements;
        }

        Iterator operator--() {
            elements--;
            return *this;
        }

        reference operator*() const {
            return *(elements);
        }

        pointer operator->() {
            return elements;
        }

        bool operator==(const Iterator &other) const {
            return elements == other.elements;
        }

        bool operator!=(const Iterator &other) const {
            return elements != other.elements;
        }

        bool operator<(const Iterator &other) const {
            return elements < other.elements;
        }

        bool operator>(const Iterator &other) const {
            return elements > other.elements;
        }

        bool operator<=(const Iterator &other) const {
            return elements <= other.elements;
        }

        bool operator>=(const Iterator &other) const {
            return elements >= other.elements;
        }
    };

    explicit CircularBuffer(int tempCapacity) {
        capacity = tempCapacity + 1;
        elements = new T[capacity];
    }

    CircularBuffer(const CircularBuffer &other) {
        size = other.size;
        capacity = other.capacity;
        elements = other.elements;
    }
    //todo delete
    ~CircularBuffer() = default;
    //todo more information in exceptions
    T &operator[](int index) const {
        if (size == 0)
            throw std::out_of_range("Error: empty container");
        if (index >= size)
            throw std::out_of_range("Error: index is out of range");
        return elements[index % capacity];
    }
    //todo O(1)
    void addFirst(T first) {
        if (size < capacity - 1) {
            for (int i = size; i >= 1; i--)
                elements[i] = elements[i - 1];
            elements[0] = first;
            size++;
        } else {
            for (int i = capacity - 2; i >= 1; i--)
                elements[i] = elements[i - 1];
            elements[0] = first;
        }
    }

    void addLast(T last) {
        if (size < capacity - 1) {
            elements[size] = last;
            size++;
        } else {
            for (int i = 1; i < capacity - 1; i++)
                elements[i - 1] = elements[i];
            elements[capacity - 2] = last;
        }
    }

    void delFirst() {
        for (int i = 0; i < size - 1; i++)
            elements[i] = elements[i + 1];
        size--;
    }

    void delLast() {
        if (size > 0)
            size--;
    }

    void changeCapacity(int tempCapacity) {
        if (tempCapacity < size) {
            throw std::logic_error("Error: not enough capacity");
        } else {
            T *tempElements = new T[tempCapacity + 1];
            for (int i = 0; i < size; i++)
                tempElements[i] = elements[i];
            //todo delete[]
            delete elements;
            elements = tempElements;
            capacity = tempCapacity + 1;
        }
    }

    Iterator begin() const {
        return Iterator(elements);
    }

    Iterator end() const {
        return Iterator(elements + size);
    }

    T first() const {
        return elements[0];
    }

    T last() const {
        return elements[size - 1];
    }
};