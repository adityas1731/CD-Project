#include <iostream>
#include <vector>

// Define a struct for a binary tree node
struct Node {
    int val;
    Node* left;
    Node* right;

    Node(int v, Node* l = nullptr, Node* r = nullptr) : val(v), left(l), right(r) {}
};

// Function to serialize a binary tree
// Takes a pointer to the root node as input and returns a vector of chars
std::vector<char> serialize(Node* node) {
    std::vector<char> data;

    // If the node is null, push a null character onto the data vector and return
    if (!node) {
        data.push_back('\0');
        return data;
    }

    // If the node is not null, push a character indicating a valid node onto the data vector
    data.push_back('\x01');

    // Push the value of the node onto the data vector as a series of characters
    int val = node->val;
    char* val_ptr = reinterpret_cast<char*>(&val);
    for (int i = 0; i < sizeof(int); ++i) {
        data.push_back(val_ptr[i]);
    }

    // Recursively serialize the left and right subtrees and append the serialized data to the data vector
    auto left_data = serialize(node->left);
    auto right_data = serialize(node->right);
    data.insert(data.end(), left_data.begin(), left_data.end());
    data.insert(data.end(), right_data.begin(), right_data.end());

    return data;
}

// Function to deserialize a binary tree
// Takes a reference to the data vector and a reference to an index variable as input
// The index variable is used to keep track of the current position in the data vector
// Returns a pointer to the root node of the deserialized tree
Node* deserialize(std::vector<char>& data, int& index) {
    // Read the header character from the data vector
    char header = data[index++];

    // If the header is null, return null
    if (header == '\0') {
        return nullptr;
    }

    // If the header is valid, read the value of the node from the data vector as a series of characters
    int val;
    for (int i = 0; i < sizeof(int); ++i) {
        reinterpret_cast<char*>(&val)[i] = data[index++];
    }

    // Recursively deserialize the left and right subtrees and create a new node with the deserialized values
    auto left = deserialize(data, index);
    auto right = deserialize(data, index);
    return new Node(val, left, right);
}

// Main function
int main() {
    std::cout << "Enter values for binary tree nodes (0 to end input):" << std::endl;

    // Read values for binary tree nodes from user input
    std::vector<Node*> nodes;
    while (true) {
        int val;
        std::cin >> val;
        if (val == 0) {
            break;
        }

        auto node = new Node(val);
        nodes.push_back(node);
    }

    // Link nodes to form binary tree
    int n = nodes.size();
    for (int i = 0; i < n; ++i) {
        int left_idx = 2 * i + 1;
        int right_idx = 2 * i + 2;
        if (left_idx < n) {
            nodes[i]->left = nodes[left_idx];
        }
        if (right_idx < n) {
            nodes[i]->right = nodes[right_idx];
        }
    }

    // Serialize and deserialize binary tree
    auto root = nodes.empty() ? nullptr : nodes[0];
    auto serialized_data = serialize(root);
    std::cout << "Serialized data: ";
    for (char c : serialized_data) {
        std::cout << static_cast<int>(static_cast<unsigned char>(c)) << " ";
    }
    std::cout << std::endl;

    int index = 0;
    auto deserialized_node = deserialize(serialized_data, index);
    std::cout << "Deserialized node: " << deserialized_node->val << " " << deserialized_node->left->val << " " << deserialized_node->right->val << std::endl;

    // Free memory allocated for nodes
    for (auto node : nodes) {
        delete node;
    }

    return 0;
}