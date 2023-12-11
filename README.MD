# Huffman Coding Implementation

This repository contains implementations of Huffman coding, a widely used algorithm for lossless data compression.

## C Implementation


The C implementation is provided in the `huffman_c.c` file. It includes the following functionalities:

- `initTree`: Initializes a Huffman tree with the given weights.
- `selectMin`: Selects two nodes with the minimum weights from the Huffman tree.
- `createTree`: Constructs the Huffman tree by repeatedly selecting and merging nodes.
- `printHuffmanTree`: Prints the structure of the Huffman tree.

#### Usage

To run the C implementation, compile the code using a C compiler and provide a list of integer weights as command-line arguments. For example:

```bash
./huffman_c 3 1 4 1 5 9
```

## C++ Implementation


The C++ implementation is provided in the huffman_cpp.cpp file. It encapsulates the Huffman coding functionality in classes:

- `treeNode`: Represents a node in the Huffman tree.
- `HuffmanTree`:  Represents the Huffman tree and includes functions for tree creation and printing.
