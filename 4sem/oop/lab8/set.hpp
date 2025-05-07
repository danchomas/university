#ifndef SET_H
#define SET_H

#include <stdexcept>
#include <algorithm>

template<typename T, size_t N = 100>
class Set {
private:
    T data[N];
    size_t count;

public:
    Set() : count(0) {}

    void add(const T& value) {
        if (count >= N) {
            throw std::invalid_argument("Set is full");
        }
        if (contains(value)) {
            return;
        }
        data[count++] = value;
        // Keep sorted for binary search
        for (size_t i = count - 1; i > 0 && data[i] < data[i-1]; --i) {
            std::swap(data[i], data[i-1]);
        }
    }

    void remove(const T& value) {
        for (size_t i = 0; i < count; ++i) {
            if (data[i] == value) {
                for (size_t j = i; j < count - 1; ++j) {
                    data[j] = data[j+1];
                }
                --count;
                return;
            }
        }
    }

    bool contains(const T& value) const {
        size_t left = 0;
        size_t right = count;
        while (left < right) {
            size_t mid = left + (right - left) / 2;
            if (data[mid] == value) {
                return true;
            }
            if (data[mid] < value) {
                left = mid + 1;
            } else {
                right = mid;
            }
        }
        return false;
    }

    size_t size() const { return count; }
    bool empty() const { return count == 0; }

    T& operator[](size_t index) {
        if (index >= count){
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }

    const T& operator[](size_t index) const {
        if (index >= count)
        {
             throw std::out_of_range("Index out of range");
        }
        return data[index];
    }

    // Iterators for range-based for loops
    T* begin() { return &data[0]; }
    const T* begin() const { return &data[0]; }
    T* end() { return &data[count]; }
    const T* end() const { return &data[count]; }
};

#endif // SET_H
