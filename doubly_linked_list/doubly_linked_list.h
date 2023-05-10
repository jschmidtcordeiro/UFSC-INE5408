//! Copyright [year] <Copyright Owner>
#include <cstdint>

namespace structures {

template<typename T>
class DoublyLinkedList {
 public:
    DoublyLinkedList();
    ~DoublyLinkedList();
    void clear();

    void push_back(const T& data);  // insere no fim
    void push_front(const T& data);  // insere no início
    void insert(const T& data, std::size_t index);  // insere na posição
    void insert_sorted(const T& data);  // insere em ordem

    T pop(std::size_t index);  // retira da posição
    T pop_back();  // retira do fim
    T pop_front();  // retira do início
    void remove(const T& data);  // retira específico

    bool empty() const;  // lista vazia
    bool contains(const T& data) const;  // contém

    T& at(std::size_t index);  // acesso a um elemento (checando limites)
    const T& at(std::size_t index) const;  // getter constante a um elemento

    std::size_t find(const T& data) const;  // posição de um dado
    std::size_t size() const;  // tamanho

 private:
    class Node {  // implementar cada um dos métodos de Node
     public:
        explicit Node(const T& data):
            data_{data}
        {}

        Node(const T& data, Node* next):
            data_{data},
            next_{next}
        {}

        Node(const T& data, Node* prev, Node* next):
            data_{data},
            prev_{prev},
            next_{next}
        {}

        T& data() {  // getter: dado
            return data_;
        }

        const T& data() const {  // getter const: dado
            return data_;
        }

        Node* prev() {  // getter: próximo
            return prev_;
        }

        const Node* prev() const {  // getter const: próximo
            return prev_;
        }

        void prev(Node* node) {  // setter: próximo
            prev_ = node;
        }

        Node* next() {  // getter: próximo
            return next_;
        }

        const Node* next() const {  // getter const: próximo
            return next_;
        }

        void next(Node* node) {  // setter: próximo
            next_ = node;
        }

     private:
        T data_;
        Node* prev_;
        Node* next_;
    };

    Node* head;  // primeiro da lista
    Node* tail;  // ultimo da lista
    std::size_t size_;
};

}  // namespace structures

template<typename T>
structures::DoublyLinkedList<T>::DoublyLinkedList() {
    // Inicializa as variaveis
    head = nullptr;
    tail = nullptr;
    size_ = 0;
}

template<typename T>
structures::DoublyLinkedList<T>::~DoublyLinkedList() {
    clear();
}

template<typename T>
void structures::DoublyLinkedList<T>::clear() {
    while (size_ > 0) {
        pop_front();
    }
}

template<typename T>
void structures::DoublyLinkedList<T>::push_back(const T& data) {
    insert(data, size_);
}

template<typename T>
void structures::DoublyLinkedList<T>::push_front(const T& data) {
    Node *new_node = new Node(data, head);
    if (new_node == nullptr) {
        throw std::out_of_range("lista cheia");
    }
    new_node->prev(nullptr);
    head = new_node;
    if (new_node->next() != nullptr) {
        new_node->next()->prev(new_node);
    }
    size_++;
}

template<typename T>
void structures::DoublyLinkedList<T>::insert(const T& data, std::size_t index) {
    if (index > size_ || index < 0) {
        throw std::out_of_range("index invalido");
    } else {
        if (index == 0) {
            push_front(data);
        } else {
            Node *new_node = new Node(data, head);
            if (new_node == nullptr) {
                throw std::out_of_range("lista cheia");
            }
            Node *previous = head;
            std::size_t pos = 0;
            while (pos < index - 1) {
                if (previous->next() != nullptr) {
                    previous = previous->next();
                }
                pos++;
            }
            new_node->next(previous->next());
            new_node->prev(previous);
            previous->next(new_node);
            if (new_node->next() != nullptr) {
                new_node->next()->prev(new_node);
            }
            size_++;
        }
    }
}

template<typename T>
void structures::DoublyLinkedList<T>::insert_sorted(const T& data) {
    Node *current = head;
    std::size_t index = 0;
    while (index < size_ && data > current->data()) {
        if (current != nullptr) {
            current = current->next();
        }
        index++;
    }
    insert(data, index);
}

template<typename T>
T& structures::DoublyLinkedList<T>::at(std::size_t index) {
    if (empty()) {
        throw std::out_of_range("lista vazia");
    } else if (index > size_ || index < 0) {
        throw std::out_of_range("posicao invalida");
    } else {
        Node *current = head;
        for (std::size_t i = 0; i < index; i++) {
            current = current->next();
        }
        return current->data();
    }
}

template<typename T>
T structures::DoublyLinkedList<T>::pop(std::size_t index) {
    if (index < 0 || index >= size_) {
        throw std::out_of_range("index invalido");
    }
    T output;
    if (index == 0) {
        output = pop_front();
    } else {
        Node *current = head;
        for (std::size_t i = 0; i < index; i++) {
            current = current->next();
        }
        output = current->data();
        if (current->next() != nullptr) {
            current->prev()->next(current->next());
            current->next()->prev(current->prev());
        } else {
            current->prev()->next(nullptr);
        }
        size_--;
        delete current;
    }
    return output;
}

template<typename T>
T structures::DoublyLinkedList<T>::pop_back() {
    return pop(size_ - 1);
}

template<typename T>
T structures::DoublyLinkedList<T>::pop_front() {
    if (empty()) {
      throw std::out_of_range("lista vazia");
    } else {
      Node *eliminate = head;
      head = eliminate->next();
      if (eliminate->next() != nullptr) {
            eliminate->next()->prev(nullptr);
      }
      T output = eliminate->data();
      delete eliminate;
      size_--;
      return output;
    }
}

template<typename T>
void structures::DoublyLinkedList<T>::remove(const T& data) {
    std::size_t index = find(data);
    pop(index);
}

template<typename T>
bool structures::DoublyLinkedList<T>::empty()const {
    return (size_ == 0);
}

template<typename T>
bool structures::DoublyLinkedList<T>::contains(const T& data) const {
    return (find(data) != size_);
}


template<typename T>
std::size_t structures::DoublyLinkedList<T>::find(const T& data) const {
    Node *current = head;
    std::size_t pos = 0;
    while (current->data() != data && pos < size_) {
        if (current->next() != nullptr) {
            current = current->next();
        }
        pos++;
    }
    if (pos >= size_) {
        return size_;
    } else {
        return(pos);
    }
}

template<typename T>
std::size_t structures::DoublyLinkedList<T>::size() const {
    return(size_);
}
