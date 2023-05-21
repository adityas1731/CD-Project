#include <iostream>
#include <string>
#include <vector>

class TrieNode {
public:
    char value;
    bool is_end_of_word;
    std::vector<TrieNode*> children;

    TrieNode(char value) {
        this->value = value;
        this->is_end_of_word = false;
        for (int i = 0; i < 26; i++) {
            this->children.push_back(nullptr);
        }
    }

    ~TrieNode() {
        for (int i = 0; i < 26; i++) {
            if (this->children[i] != nullptr) {
                delete this->children[i];
            }
        }
    }
};

class Trie {
public:
    TrieNode* root;

    Trie() {
        this->root = new TrieNode('\0');
    }

    ~Trie() {
        delete this->root;
    }

    void insert(const std::string& word) {
        TrieNode* current = this->root;
        for (char c : word) {
            int index = c - 'a';
            if (current->children[index] == nullptr) {
                current->children[index] = new TrieNode(c);
            }
            current = current->children[index];
        }
        current->is_end_of_word = true;
    }

    bool search(const std::string& word) {
        TrieNode* current = this->root;
        for (char c : word) {
            int index = c - 'a';
            if (current->children[index] == nullptr) {
                return false;
            }
            current = current->children[index];
        }
        return current->is_end_of_word;
    }

    void autocomplete(const std::string& prefix) {
        TrieNode* current = this->root;
        for (char c : prefix) {
            int index = c - 'a';
            if (current->children[index] == nullptr) {
                return;
            }
            current = current->children[index];
        }
        std::vector<std::string> words;
        std::string word = prefix;
        autocomplete_helper(current, words, word);
        for (const std::string& w : words) {
            std::cout << w << std::endl;
        }
    }

private:
    void autocomplete_helper(TrieNode* node, std::vector<std::string>& words, std::string& word) {
        if (node->is_end_of_word) {
            words.push_back(word);
        }
        for (int i = 0; i < 26; i++) {
            if (node->children[i] != nullptr) {
                word += node->children[i]->value;
                autocomplete_helper(node->children[i], words, word);
                word.pop_back();
            }
        }
    }
};

int main() {
    Trie trie;
    trie.insert("apple");
    trie.insert("banana");
    trie.insert("cherry");
    trie.insert("dog");
    trie.insert("cat");

    std::string input;
    std::cout << "Enter text: ";
    std::getline(std::cin, input);

    int pos = input.length() - 1;
    while (pos >= 0 && input[pos] != ' ') {
        pos--;
    }
    std::string prefix = input.substr(pos + 1);
    trie.autocomplete(prefix);

    return 0;
}