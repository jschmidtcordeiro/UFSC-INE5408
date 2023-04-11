#ifndef STRUCTURES_ARRAY_LIST_H
#define STRUCTURES_ARRAY_LIST_H

#include <cstdint>
#include <stdexcept>  // C++ Exceptions

namespace structures {

template<typename T>
class ArrayList {
public:
    ArrayList();
    explicit ArrayList(std::size_t max_size);
    ~ArrayList();

    void clear();
    void push_back(const T& data);
    void push_front(const T& data);
    void insert(const T& data, std::size_t index);
    void insert_sorted(const T& data);
    T pop(std::size_t index);
    T pop_back();
    T pop_front();
    void remove(const T& data);
    bool full() const;
    bool empty() const;
    bool contains(const T& data) const;
    std::size_t find(const T& data) const;
    std::size_t size() const;
    std::size_t max_size() const;
    T& at(std::size_t index);
    T& operator[](std::size_t index);
    const T& at(std::size_t index) const;
    const T& operator[](std::size_t index) const;
    // descricao do 'operator []' na FAQ da disciplina

private:
    T* contents;
    std::size_t size_;
    std::size_t max_size_;
    int end_;

    static const auto DEFAULT_MAX = 10u;
};

}

#endif

template<typename T>
structures::ArrayList<T>::ArrayList() {
    max_size_ = DEFAULT_MAX;
    contents = new T[max_size_];
    end_ = -1;
} 

template<typename T>
structures::ArrayList<T>::ArrayList(std::size_t max) {
    max_size_ = max;
    contents = new T[max_size_];
    end_ = -1;
} 

template<typename T>
structures::ArrayList<T>::~ArrayList() {
    end_ = -1;
    delete [] contents;
}

template<typename T>
void structures::ArrayList<T>::clear() {
    end_ = -1;
}

template<typename T>
void structures::ArrayList<T>::push_back(const T& data) {
    if (full()) {
        throw std::out_of_range("fila cheia");
    } else {
        end_++;
        contents[end_] = data;
    }
}

template<typename T>
void structures::ArrayList<T>::push_front(const T& data) {
    if (full()) {
        throw std::out_of_range("fila cheia");
    } else {
        end_++;
        for (int i = end_; i > 0; i--) {
            contents[i] = contents[i - 1];
        }
        contents[0] = data;
    }
}

template<typename T>
void structures::ArrayList<T>::insert(const T& data, std::size_t index) {
    if (full()) {
        throw std::out_of_range("fila cheia");
    }
    end_++;

    for (int i = end_; i <= index; i--) {
        contents[i] = contents[i - 1];
    }
    contents[index] = data;
}

template<typename T>
void structures::ArrayList<T>::insert_sorted(const T& data) {
    if (full()) {
        throw std::out_of_range("fila cheia");
    }
    int pos = 0;

    while(pos <= end_) {
        // comparison_function
        pos++;
    }
    return(insert(data, pos));
}

template<typename T>
T structures::ArrayList<T>::pop(std::size_t index) {
    if (index > end_ || index < 0) {
        throw std::out_of_range("index invalido");
    }
    end_--;
    T out = contents[index];
    for (int i = index; i <= end_; i++) {
        contents[i] = contents[i + 1]
    }

    return(out);
}



template<typename T>
T structures::ArrayList<T>::pop_back() {
    // Teste se a fila esta vazia
    if (empty()) {
        throw std::out_of_range("fila vazia");
    }
    end_--;
    return end_ + 1;
}

template<typename T>
T structures::ArrayList<T>::pop_front() {
    // Teste se a fila esta vazia
    if (empty()) {
        throw std::out_of_range("fila vazia");
    }
    T out = contains[0];
    for (int i = 0; i < end_; i++) {
        contents[i] = contents[i + 1];
    }
    end_--;
    return out;
}

template<typename T>
bool structures::ArrayList<T>::full()const  {
    return end_ + 1 == static_cast<int>(max_size());
}
template<typename T>
bool structures::ArrayList<T>::empty()const {
    return (end_ == -1);
}

template<typename T>
bool structures::ArrayList<T>::contains(const T& data) const {
    int pos = 0;
    while (pos <= end_ && !(contents[pos] == data)) {
        pos++;
    }
    if (pos > end_) {
        return false;
    } else {
        return true;
    }
}


template<typename T>
std::size_t structures::ArrayList<T>::find(const T& data) const {
    int pos = 0;
    while (pos <= end_ && !(contents[pos] == data)) {
        pos++;
    }
    if (pos > end_) {
        throw std::out_of_range("dado nao encontrado");
    } else {
        return(pos);
    }
}
