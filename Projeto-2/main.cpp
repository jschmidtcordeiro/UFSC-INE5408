#define MOODLE

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

// TrieNode represents a node in the trie data structure
class TrieNode {
public:
    explicit TrieNode(char c) : nodeChar(c), valid(false), position(0), length(0), prefix(0) {}

    char nodeChar;
    bool valid;
    std::vector<TrieNode*> children;
    unsigned long position;
    unsigned long length;
    unsigned long prefix;
};

// Trie represents the trie data structure
class Trie {
public:
    Trie() {
        root = new TrieNode('\0');
    }

    ~Trie() {
        deleteRoot(root);
    }

    // Insert a word into the trie
    void insert(TrieNode* node, const std::string& word, unsigned long position, unsigned long length) {
        for (char c : word) {
            bool foundInChild = false;
            node->prefix++;

            for (TrieNode* child : node->children) {
                if (child->nodeChar == c) {
                    node = child;
                    foundInChild = true;
                    break;
                }
            }

            if (!foundInChild) {
                TrieNode* newNode = new TrieNode(c);
                node->children.push_back(newNode);
                newNode->prefix++;
                node = newNode;
            }
        }

        node->valid = true;
        node->position = position;
        node->length = length;
    }

    // Find a prefix in the trie
    TrieNode* findPrefix(const std::string& word) {
        TrieNode* node = root;

        for (char c : word) {
            bool foundInChild = false;

            for (TrieNode* child : node->children) {
                if (child->nodeChar == c) {
                    node = child;
                    foundInChild = true;
                    break;
                }
            }

            if (!foundInChild) {
                return nullptr;
            }
        }

        return node;
    }

    // Get the root node of the trie
    TrieNode* get_root() {
        return root;
    }

private:
    TrieNode* root;

    // Recursively delete the trie nodes
    void deleteRoot(TrieNode* node) {
        if (node == nullptr) {
            return;
        }

        for (TrieNode* child : node->children) {
            deleteRoot(child);
        }

        delete node;
    }
};

int main(int argc, char* argv[]) {
    std::string filename;
    std::string line;
    std::string dict;
    std::ifstream file;
    Trie tree;

    #ifndef MOODLE
    // Receive the input argument
    if (argc < 2) {
        std::cout << "Error: No input filename provided.\n";
        std::cout << "Usage: ./program [name_of_file.dic]\n";
        return 1;  // Return an error code
    }
    filename = argv[1];
    #endif

    #ifdef MOODLE
    std::cin >> filename;
    #endif

    // Read file
    file.open(filename);

    if (!file.is_open()) {
        std::cout << "Error: Unable to open the file.\n";
        return 1;  // Return an error code
    }

    // Read dictionary words from the file
    while (getline(file, line)) {
        dict += line + "\n";
    }

    file.close();   // Close file

    // Extract dictionary words, positions, and lengths
    size_t offset = 0;
    std::vector<std::string> dictWords;
    std::vector<unsigned long> positions;
    std::vector<unsigned long> lengths;

    while (true) {
        size_t begin = dict.find('[', offset);
        size_t end = dict.find(']', offset);

        if (begin == std::string::npos) {
            break;
        }

        std::string word = dict.substr(begin + 1, end - begin - 1);

        if (dict.find('\n', offset) == std::string::npos) {
            offset = dict.length() + 1;
        } else {
            offset = dict.find('\n', offset) + 1;
        }

        dictWords.push_back(word);
        positions.push_back(begin);
        lengths.push_back(offset - begin - 1);
    }

    // Insert dictionary words into the trie
    for (size_t i = 0; i < dictWords.size(); i++) {
        tree.insert(tree.get_root(), dictWords[i], positions[i], lengths[i]);
    }

    std::vector<std::string> inputWords;
    // Read input words
    while (true) {
        std::string inputWord;
        std::cin >> inputWord;

        if (inputWord == "0") {
            break;
        }

        inputWords.push_back(inputWord);
    }

    // Process input words and find prefixes in the trie
    for (const std::string& word : inputWords) {
        TrieNode* tmp = tree.findPrefix(word);

        if (tmp) {
            int tmp_prefix = tmp->valid ? tmp->prefix : tmp->prefix - 1;
            std::cout << word << " is prefix of " << tmp_prefix << " words" << std::endl;

            if (tmp->length > 1) {
                std::cout << word << " is at (" << tmp->position << "," << tmp->length << ")" << std::endl;
            }
        } else {
            std::cout << word << " is not prefix" << std::endl;
        }
    }

    return 0;
}
