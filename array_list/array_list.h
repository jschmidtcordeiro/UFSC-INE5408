// Copyright [2018] <COLOQUE SEU NOME AQUI...>
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
    static const auto DEFAULT_MAX = 10u;
};

}  // namespace structures

#endif

template<typename T>
structures::ArrayList<T>::ArrayList() {
    max_size_ = DEFAULT_MAX;
    contents = new T[max_size_];
    size_ = 0;
}

template<typename T>
structures::ArrayList<T>::ArrayList(std::size_t max) {
    max_size_ = max;
    contents = new T[max_size_];
    size_ = 0;
}

template<typename T>
structures::ArrayList<T>::~ArrayList() {
    size_ = 0;
    delete [] contents;
}

template<typename T>
void structures::ArrayList<T>::clear() {
    size_ = 0;
}

template<typename T>
void structures::ArrayList<T>::push_back(const T& data) {
    if (full()) {
        throw std::out_of_range("lista cheia");
    } else {
        contents[size_] = data;
        size_++;
    }
}

template<typename T>
void structures::ArrayList<T>::push_front(const T& data) {
    if (full()) {
        throw std::out_of_range("lista cheia");
    } else {
        for (std::size_t i = size_; i > 0; i--) {
            contents[i] = contents[i - 1];
        }
        size_++;
        contents[0] = data;
    }
}

template<typename T>
void structures::ArrayList<T>::insert(const T& data, std::size_t index) {
    if (full()) {
        throw std::out_of_range("lista cheia");
    }
    if (index > size_ || index < 0) {
        throw std::out_of_range("posicao invalida");
    }
    size_++;

    for (size_t i = size_ - 1; i > index; i--) {
        contents[i] = contents[i - 1];
    }
    contents[index] = data;
}

template<typename T>
void structures::ArrayList<T>::insert_sorted(const T& data) {
    if (full()) {
        throw std::out_of_range("fila cheia");
    }
    size_t pos = 0;

    while (pos < size_ && data > contents[pos]) {
        // comparison_function
        pos++;
    }
    return(insert(data, pos));
}

template<typename T>
T structures::ArrayList<T>::pop(std::size_t index) {
    if (index > (size_ - 1) || index < 0) {
        throw std::out_of_range("index invalido");
    }
    size_--;
    T out = contents[index];
    for (size_t i = index; i <= (size_ - 1); i++) {
        contents[i] = contents[i + 1];
    }

    return(out);
}



template<typename T>
T structures::ArrayList<T>::pop_back() {
    // Teste se a fila esta vazia
    if (empty()) {
        throw std::out_of_range("fila vazia");
    }
    size_--;
    return size_;
}

template<typename T>
T structures::ArrayList<T>::pop_front() {
    // Teste se a fila esta vazia
    if (empty()) {
        throw std::out_of_range("fila vazia");
    }
    T out = contents[0];
    for (size_t i = 0; i < (size_ - 1); i++) {
        contents[i] = contents[i + 1];
    }
    size_--;
    return out;
}

template<typename T>
void structures::ArrayList<T>::remove(const T& data) {
    if (!contains(data)) {
        throw std::out_of_range("dado invalido");
    }
    size_t addr = find(data);
    pop(addr);
}

template<typename T>
bool structures::ArrayList<T>::full()const  {
    return size_ == max_size_;
}
template<typename T>
bool structures::ArrayList<T>::empty()const {
    return (size_ == 0);
}

template<typename T>
bool structures::ArrayList<T>::contains(const T& data) const {
    std::size_t pos = 0;
    while (pos <= size_ - 1  && !(contents[pos] == data)) {
        pos++;
    }
    if (pos > size_ - 1) {
        return false;
    } else {
        return true;
    }
}


template<typename T>
std::size_t structures::ArrayList<T>::find(const T& data) const {
    std::size_t pos = 0;
    while (pos <= size_ - 1 && !(contents[pos] == data)) {
        pos++;
    }
    return(pos);
    
}

template<typename T>
std::size_t structures::ArrayList<T>::size() const {
    return(size_);
}

template<typename T>
std::size_t structures::ArrayList<T>::max_size() const {
    return(max_size_);
}

template<typename T>
T& structures::ArrayList<T>::at(std::size_t index) {
    if (empty()) {
        throw std::out_of_range("lista vazia");
    } else if (index < 0 || index > size_) {
        throw std::out_of_range("posicao invalida");
    } else {
        return contents[index];
    }
}

template<typename T>
T& structures::ArrayList<T>::operator[](std::size_t index) {
    if (empty()) {
        throw std::out_of_range("lista vazia");
    } else if (index < 0 || index > size_) {
        throw std::out_of_range("posicao invalida");
    } else {
        return contents[index];
    }
}

template<typename T>
const T& structures::ArrayList<T>::at(std::size_t index) const {
    if (empty()) {
        throw std::out_of_range("lista vazia");
    } else if (index < 0 || index > size_) {
        throw std::out_of_range("posicao invalida");
    } else {
        return contents[index];
    }
}

template<typename T>
const T& structures::ArrayList<T>::operator[](std::size_t index) const {
    if (empty()) {
        throw std::out_of_range("lista vazia");
    } else if (index < 0 || index > size_) {
        throw std::out_of_range("posicao invalida");
    } else {
        return contents[index];
    }
}
