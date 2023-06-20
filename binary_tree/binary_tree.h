// Copyright [year] <Copyright Owner>
#include "array_list.h"

namespace structures {

template<typename T>
class BinaryTree {
public:
    ~BinaryTree();

    void insert(const T& data);

    void remove(const T& data);

    bool contains(const T& data) const;

    bool empty() const;

    std::size_t size() const;

    ArrayList<T> pre_order() const;

    ArrayList<T> in_order() const;

    ArrayList<T> post_order() const;

private:
    struct Node {
        explicit Node(const T& data) : data{data},
        left{nullptr}, right{nullptr} {}

        void insert(const T& data_) {
            if (data_ < data) {
                // Insert Left
                if (left == nullptr) {
                    left = new Node(data_);
                } else {
                    left->insert(data_);
                }
            } else {
                // Insert Right
                if (right == nullptr) {
                    right = new Node(data_);
                } else {
                    right->insert(data_);
                }
            }
        }

        Node* remove(const T& data_) {
            if (data_ < data) {
                // Vai à esquerda.
                if (left != nullptr) {
                    left = left->remove(data_);
                    return this;
                } else {
                    return nullptr;
                }
            } else if (data_ > data) {
                // Vai à direita.
                if (right != nullptr) {
                    right = right->remove(data_);
                    return this;
                } else {
                    return nullptr;
                }
            } else {
                if (right != nullptr && left != nullptr) {
                    // 2 filhos.
                    Node* temp = right->minimum();
                    data = temp->data;
                    right = right->remove(data);
                    return this;
                } else if (right != nullptr) {
                    // 1 filho à direita.
                    Node* temp = right;
                    delete this;
                    return temp;
                } else if (left != nullptr) {
                    // 1 filho à esquerda.
                    Node* temp = left;
                    delete this;
                    return temp;
                } else {
                    // Folha.
                    delete this;
                    return nullptr;
                }
            }
        }

        bool contains(const T& data_) const {
            bool out = false;

            // Equal
            if (data_ == data) {
                out = true;
            } else {
                // Left
                if (left != nullptr && data_ < data) {
                    out = left->contains(data_);
                }
                // Right
                if (right != nullptr && data_ > data) {
                    out = right->contains(data_);
                }
            }

            return out;
        }

        void pre_order(ArrayList<T>& v) const {
            v.push_back(data);

            if (left != nullptr) {
                left->pre_order(v);
            }

            if (right != nullptr) {
                right->pre_order(v);
            }
        }

        void in_order(ArrayList<T>& v) const {
            if (left != nullptr) {
                left->in_order(v);
            }

            v.push_back(data);

            if (right != nullptr) {
                right->in_order(v);
            }
        }

        void post_order(ArrayList<T>& v) const {
            if (left != nullptr) {
                left->post_order(v);
            }

            if (right != nullptr) {
                right->post_order(v);
            }

            v.push_back(data);
        }

        Node* minimum() {
            if (left == nullptr) {
                return this;
            } else {
                return left->minimum();
            }
        }
                
        T data;
        Node* left;
        Node* right;
    };

    Node* root;
    std::size_t size_;
};

template<typename T>
structures::BinaryTree<T>::~BinaryTree() {
    if (root != nullptr) {
        structures::ArrayList<T> list_nodes = pre_order();
        while (!list_nodes.empty()) {
            remove(list_nodes.pop_back());
        }
    }
}

template<typename T>
void structures::BinaryTree<T>::insert(const T& data) {
    if (empty()) {
        root = new Node(data);
    } else {
        if (contains(data)) {
            throw std::out_of_range("dado ja esta na arvore");
        } else {
            root->insert(data);
        }
    }

    size_++;
}

template<typename T>
void structures::BinaryTree<T>::remove(const T& data) {
    if (empty()) {
        throw std::out_of_range("arvore vazia");
    }
    if (contains(data)) {
        root -> remove(data);
        size_--;
    } else {
        throw std::out_of_range("dado invalido");
    }
}

template<typename T>
bool structures::BinaryTree<T>::contains(const T& data) const {
    if (empty()) {
        throw std::out_of_range("arvore vazia");
    }

    return root->contains(data);
}

template<typename T>
bool structures::BinaryTree<T>::empty() const {
    return size_ == 0;
}

template<typename T>
std::size_t structures::BinaryTree<T>::size() const {
    return size_;
}

template<typename T>
ArrayList<T> structures::BinaryTree<T>::pre_order() const {
    structures::ArrayList<T> v{};

    if (!empty()) {
        root->pre_order(v);
    }

    return v;
}

template<typename T>
ArrayList<T> structures::BinaryTree<T>::in_order() const {
    structures::ArrayList<T> v{};

    if (!empty()) {
        root->in_order(v);
    }

    return v;
}

template<typename T>
ArrayList<T> structures::BinaryTree<T>::post_order() const {
    structures::ArrayList<T> v{};

    if (!empty()) {
        root->post_order(v);
    }

    return v;
}

}  // namespace structures
