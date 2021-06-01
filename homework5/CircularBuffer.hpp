#pragma once

using namespace std;

template<class T>
class CircularBuffer {
private:
    size_t bufSize = 0;
    size_t capacity = 0;
    size_t bufStart = 0;
    size_t finish = 0;
    T *bufElements = nullptr;
public:
    class Iterator {
    private:
        T *elements = nullptr;
        size_t size;
        size_t index;
        size_t start;
    public:
        using iterator_category = std::random_access_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = T*;
        using reference = T&;

        explicit Iterator(T *tempElements, size_t tempSize, size_t tempIndex, size_t tempStart) {
            elements = tempElements;
            size = tempSize;
            index = tempIndex;
            start = tempStart;
        }

        Iterator(const Iterator &other) {
            elements = other.elements;
            size = other.size;
            index = other.index;
            start = other.start;
        }

        Iterator &operator+=(difference_type tempNum) {
            index += tempNum;
            return *this;
        }

        Iterator operator+(difference_type tempNum) const {
            Iterator temp = *this;
            temp += tempNum;
            return temp;
        }

        Iterator &operator++() {
            index++;
            return *this;
        }

        Iterator &operator-=(difference_type tempNum) {
            index -= tempNum;
            return *this;
        }

        Iterator operator-(difference_type tempNum) const {
            Iterator temp = *this;
            temp -= tempNum;
            return temp;
        }

        difference_type operator-(const Iterator &tempNum) const {
            return index - tempNum.index;
        }

        Iterator &operator--() {
            index--;
            return *this;
        }

        reference operator*() {
            return elements[(start + index) % size];
        }

        pointer operator->() {
            return elements + (start + index) % size;
        }

        bool operator==(const Iterator &other) const {
            return index == other.index;
        }

        bool operator!=(const Iterator &other) const {
            return index != other.index;
        }

        bool operator<(const Iterator &other) const {
            return index < other.index;
        }

        bool operator>(const Iterator &other) const {
            return index > other.index;
        }

        bool operator<=(const Iterator &other) const {
            return index <= other.index;
        }

        bool operator>=(const Iterator &other) const {
            return index >= other.index;
        }
    };

    explicit CircularBuffer(size_t tempCapacity) {
        capacity = tempCapacity + 1;
        bufElements = new T[tempCapacity + 1];
        bufSize = 0;
        bufStart = 0;
        finish = 0;
    }

    CircularBuffer(const CircularBuffer &other) {
        capacity = other.capacity;
        bufElements = new T[bufSize];
        size = other.size;
        bufStart = other.start;
        finish = 0;

        for (size_t i = 0; i < bufSize; i++) {
            *bufElements[i] = other.elements[i];
        }
    }

    //fixed delete
    ~CircularBuffer() {
        delete[] bufElements;
    }

    //fixed more information in exceptions
    T &operator[](size_t index) const {
        if (bufSize == 0)
            throw std::out_of_range("Error: empty container");
        if (index >= bufSize)
            throw std::out_of_range(
                    "Error: index is out of range ; index must be in range 0 - " + std::to_string(bufSize - 1) +
                    " ; your index: " + std::to_string(index));
        return bufElements[((index % bufSize) + bufStart) % capacity];
    }

    //fixed O(1)
    void addFirst(T first) {
        bufStart = (capacity + bufStart - 1) % capacity;
        bufElements[bufStart] = first;

        if (bufSize == capacity - 1)
            finish = (capacity + finish - 1) % capacity;
        else
            bufSize++;
    }

    void addLast(T last) {
        bufElements[finish] = last;
        finish = (finish + 1) % capacity;

        if (bufSize == capacity - 1)
            bufStart = (bufStart + 1) % capacity;
        else
            bufSize++;
    }

    void delFirst() {
        if (bufSize > 0) {
            bufSize--;
            bufStart = (bufStart + 1) % capacity;
        }
    }

    void delLast() {
        if (bufSize > 0) {
            bufSize--;
            finish = (capacity + finish - 1) % capacity;
        }
    }

    void changeCapacity(size_t tempCapacity) {
        if (tempCapacity < bufSize)
            throw std::logic_error("Error: not enough capacity");

        T *tempElements = new T[tempCapacity + 1];
        for (size_t i = 0; i < bufSize; i++)
            tempElements[i] = bufElements[i];
        //fixed delete[]
        delete[] bufElements;
        bufElements = tempElements;
        capacity = tempCapacity + 1;
        bufStart = 0;
        finish = bufSize % capacity;
    }

    Iterator begin() const {
        return Iterator(bufElements, capacity, 0, bufStart);
    }

    Iterator end() const {
        return Iterator(bufElements, capacity, bufSize, bufStart);
    }

    T first() const {
        return bufElements[bufStart];
    }

    T last() const {
        return bufElements[(bufSize + bufStart - 1) % capacity];
    }
};