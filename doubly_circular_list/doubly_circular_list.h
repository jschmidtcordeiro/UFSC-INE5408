//! Copyright [year] <Copyright Owner>
namespace structures {

template <typename T>
class DoublyCircularList {
 public:
    DoublyCircularList();
    ~DoublyCircularList();

    void clear();

    void push_back(const T &data);                 // insere no fim
    void push_front(const T &data);                // insere no início
    void insert(const T &data, std::size_t index);  // insere na posição
    void insert_sorted(const T &data);             // insere em ordem

    T pop(std::size_t index);   // retira da posição
    T pop_back();               // retira do fim
    T pop_front();              // retira do início
    void remove(const T &data);  // retira específico

    bool empty() const;                 // lista vazia
    bool contains(const T &data) const;  // contém

    T &at(std::size_t index);   // acesso a um elemento (checando limites)
    const T &at(std::size_t index) const;  // getter constante a um elemento

    std::size_t find(const T &data) const;  // posição de um dado
    std::size_t size() const;              // tamanho

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

/**
 * @brief Constructor
 */
template <typename T>
structures::DoublyCircularList<T>::DoublyCircularList() {
    head = nullptr;
    tail = nullptr;
    size_ = 0;
}
/**
 * @brief Destructor
 */
template <typename T>
structures::DoublyCircularList<T>::~DoublyCircularList() {
    clear();
}

/**
 * @brief Clear the double circular list
 */
template <typename T>
void structures::DoublyCircularList<T>::clear() {
    for (size_t i = size_; i > 0; i--) {
        pop_back();
    }
}

/**
 * @brief Insert a elemnt in the end of the list
 *
 * @param data The data of the element that is going to be inserted
 */
template <typename T>
void structures::DoublyCircularList<T>::push_back(const T &data) {
    insert(data, size_);
}

/**
 * @brief Insert a element in the beggining of the list
 *
 * @param data The data of the element that is going to be inserted
 */
template <typename T>
void structures::DoublyCircularList<T>::push_front(const T &data) {
    Node *new_node = new Node(data, head);
    if (new_node == nullptr) {
        throw std::out_of_range("lista cheia");
    }
    if (size_ > 0) {
        new_node->next(head);
        new_node->prev(head->prev());
        head->prev()->next(new_node);
        head->prev(new_node);
    } else {
        new_node->next(new_node);
        new_node->prev(new_node);
    }
    head = new_node;
    size_++;
}

/**
 * @brief Insert a element in a specific position in the list
 *
 * @param data The data of the element that is going to be inserted
 * @param index The index of the element that is going to be inserted
 */
template <typename T>
void structures::DoublyCircularList<T>::insert(const T &data,
                                            std::size_t index) {
    if (index < 0 || index > size_) {
        throw std::out_of_range("index invalido");
    }
    if (index == 0) {
        push_front(data);
    } else {
        Node *new_node = new Node(data, head);
        if (new_node == nullptr) {
            throw std::out_of_range("lista cheia");
        }
        Node *previous = head;
        for (std::size_t i = 0; i < index - 1; i++) {
            previous = previous->next();
        }

        new_node->next(previous->next());
        new_node->prev(previous);
        previous->next()->prev(new_node);
        previous->next(new_node);

        size_++;
    }
}

/**
 * @brief Insert a element acordingly to the sorting in the list
 *
 * @param data The data of the element that is going to be inserted
 */
template <typename T>
void structures::DoublyCircularList<T>::insert_sorted(const T &data) {
    Node *curr = head;
    std::size_t index = 0;
    while (index < size_ && data > curr->data()) {
        curr = curr->next();
        index++;
    }
    insert(data, index);
}

/**
 * @brief Remove a element acordingly to an index and return the data
 *
 * @param index The index of the element that is going to be inserted
 *
 * @return The data of the eliminated element
 */
template <typename T>
T structures::DoublyCircularList<T>::pop(std::size_t index) {
    if (size_ == 0) {
        throw std::out_of_range("lista vazia");
    }

    if (index < 0 || index >= size_) {
        throw std::out_of_range("index invalido");
    }

    Node *eliminate = head;

    for (std::size_t i = 0; i < index; i++) {
        eliminate = eliminate->next();
    }

    eliminate->next()->prev(eliminate->prev());
    eliminate->prev()->next(eliminate->next());
    T output = eliminate->data();
    if (eliminate == head) {
        head = eliminate->next();
    }

    delete eliminate;
    size_--;
    return output;
}

/**
 * @brief Remove the last element and return the data
 *
 * @return The data of the eliminated element
 */
template <typename T>
T structures::DoublyCircularList<T>::pop_back() {
    return pop(size_ - 1);
}

/**
 * @brief Remove the first element and return the data
 *
 * @return The data of the eliminated element
 */
template <typename T>
T structures::DoublyCircularList<T>::pop_front() {
    return pop(0);
}

/**
 * @brief Remove a element acordingly to the data provided
 *
 * @param data The data of the element that is going to be removed
 */
template <typename T>
void structures::DoublyCircularList<T>::remove(const T &data) {
    Node *curr = head;
    std::size_t index = 0;
    while (index < size_ && data != curr->data()) {
        curr = curr->next();
        index++;
    }
    pop(index);
}

/**
 * @brief Check if the list is empty
 *
 * @return true for empty list and false for not empty
 */
template <typename T>
bool structures::DoublyCircularList<T>::empty() const {
    return (size_ == 0);
}

/**
 * @brief Check if an element of the list contains the input data
 *
 * @param data The data to be check in the list
 *
 * @return True if it has an element with the same data and False if not
 */
template <typename T>
bool structures::DoublyCircularList<T>::contains(const T &data) const {
    return (find(data) != size_);
}

/**
 * @brief Get the element data in an index
 *
 * @param index The index of an element
 *
 * @return The data of the element
 */
template <typename T>
T& structures::DoublyCircularList<T>::at(std::size_t index) {
    if (index < 0 || index >= size_) {
        throw std::out_of_range("index invalido");
    }
    Node *curr = head;
    std::size_t i = 0;
    while (i < size_ && i < index) {
        curr = curr->next();
        i++;
    }
    return curr->data();
}

/**
 * @brief Get the constant element data in an index
 *
 * @param index The index of an element
 *
 * @return The data of the element
 */
template <typename T>
const T &structures::DoublyCircularList<T>::at(std::size_t index) const {
    if (index < 0 || index >= size_) {
        throw std::out_of_range("index invalido");
    }
    Node *curr = head;
    std::size_t i = 0;
    while (i < size_ && i < index) {
        curr = curr->next();
        i++;
    }
    return curr->data();
}

/**
 * @brief Get the element index based on the data input
 *
 * @param data The data of an element
 *
 * @return The index of the element
 */
template <typename T>
std::size_t structures::DoublyCircularList<T>::find(const T &data) const {
    Node *curr = head;
    std::size_t index = 0;
    while (index < size_ && data != curr->data()) {
        curr = curr->next();
        index++;
    }
    return index;
}

/**
 * @brief Get the size of the list
 *
 * @return The size of the list
 */
template <typename T>
std::size_t structures::DoublyCircularList<T>::size() const {
    return size_;
}
