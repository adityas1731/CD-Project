CD-Project

DATA STRUCTURE SERIALIZER in C++

Run the C++ file in any IDE. 

Give the input for the binary tree nodes.

The code allows you to convert a binary tree into a serialized form represented as a vector of characters and then deserialize the serialized data back into the original binary tree.

Here's how the code works:

1. The `Node` struct represents a node in the binary tree. It contains an integer value (`val`) and pointers to its left and right child nodes (`left` and `right`).

2. The `serialize` function takes a pointer to the root node of a binary tree and returns a vector of characters representing the serialized data. The serialization process follows a pre-order traversal of the tree.

3. Inside the `serialize` function:
   - If the node is null (represented by a null pointer), it pushes a null character (`'\0'`) onto the `data` vector.
   - If the node is not null, it pushes a character (`'\x01'`) onto the `data` vector to indicate a valid node.
   - The value of the node (`val`) is then converted to a series of characters using a `reinterpret_cast` to treat the `int` value as an array of `char` values. These characters are then pushed onto the `data` vector.
   - The function recursively serializes the left and right subtrees and appends their serialized data to the `data` vector.

4. The `deserialize` function takes a reference to the serialized data vector (`data`) and a reference to an index variable (`index`) to keep track of the current position in the vector. It returns a pointer to the root node of the deserialized binary tree.

5. Inside the `deserialize` function:
   - The function reads the header character from the `data` vector at the current index.
   - If the header is a null character (`'\0'`), indicating a null node, it returns a null pointer.
   - If the header is a valid node character (`'\x01'`), it reads the value of the node from the `data` vector as a series of characters and reconstructs the `int` value.
   - The function recursively deserializes the left and right subtrees and creates a new node with the deserialized values.
   - Finally, it returns a pointer to the newly created node.

6. In the `main` function:
   - The user is prompted to enter values for the binary tree nodes. The input values are stored in a vector of `Node*` called `nodes`.
   - The nodes are linked together to form a binary tree.
   - The root of the binary tree is obtained from the `nodes` vector.
   - The binary tree is then serialized using the `serialize` function, and the serialized data is printed to the console.
   - The serialized data is deserialized using the `deserialize` function, and the deserialized node's value, along with the values of its left and right child nodes, are printed to the console.
   - Finally, memory allocated for the nodes is freed to avoid memory leaks.

Note: The code assumes that the user enters the values for the binary tree nodes in the order of a level-order traversal.
