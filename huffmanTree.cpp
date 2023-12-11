#include <iostream>
#include <vector>
#include <limits>

// Class representing a node in the Huffman tree
class TreeNode
{
public:
    int weight;
    int parent;
    int left;
    int right;

    // Constructor with default values
    TreeNode(int w = 0, int p = 0, int l = -1, int r = -1) : weight(w), parent(p), left(l), right(r) {}
};

// Class representing the Huffman tree
class HuffmanTree
{
public:
    std::vector<TreeNode> data;
    int length;

    // Constructor to initialize the tree with given weights
    HuffmanTree(const std::vector<int> &weights) : length(weights.size())
    {
        data.resize(2 * length - 1);

        // Initialize leaf nodes with weights
        for (size_t i = 0; i < length; i++)
        {
            data[i] = TreeNode(weights[i], 0, -1, -1);
        }
    }

    // Function to select two nodes with the minimum weights
    std::pair<int, int> selectMin() const
    {
        int min = std::numeric_limits<int>::max();
        int secondMin = std::numeric_limits<int>::max();
        int minIndex = -1;
        int secondIndex = -1;

        // Find the node with the minimum weight
        for (size_t i = 0; i < length; i++)
        {
            if (data[i].parent == 0)
            {
                if (data[i].weight < min)
                {
                    min = data[i].weight;
                    minIndex = static_cast<int>(i);
                }
            }
        }

        // Find the node with the second minimum weight
        for (size_t i = 0; i < length; i++)
        {
            if (data[i].parent == 0 && static_cast<int>(i) != minIndex)
            {
                if (data[i].weight < secondMin)
                {
                    secondMin = data[i].weight;
                    secondIndex = static_cast<int>(i);
                }
            }
        }

        return std::make_pair(minIndex, secondIndex);
    }

    // Function to create the Huffman tree
    void createTree()
    {
        int min, secondMin;
        int treeLength = length * 2 - 1;

        // Build the Huffman tree by merging nodes
        for (size_t i = length; i < static_cast<size_t>(treeLength); i++)
        {
            auto [minIndex, secondIndex] = selectMin();

            min = minIndex;
            secondMin = secondIndex;

            // Create a new node with the sum of weights of the selected nodes
            data[i] = TreeNode(data[min].weight + data[secondMin].weight, 0, min, secondMin);
            data[min].parent = data[secondMin].parent = static_cast<int>(i);
            length++;
        }
    }

    // Function to print the Huffman tree structure recursively
    void printHuffmanTree(int index, int level) const
    {
        if (index != -1)
        {
            printHuffmanTree(data[index].right, level + 1);
            for (int i = 0; i < level; i++)
            {
                std::cout << "    ";
            }
            std::cout << data[index].weight << "\n";
            printHuffmanTree(data[index].left, level + 1);
        }
    }
};

// Main function
int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        std::cerr << "Usage: " << argv[0] << " <Element> <Element> ... <Element>\n";
        return 1;
    }

    std::vector<int> weights;
    for (int i = 1; i < argc; i++)
    {
        weights.push_back(std::atoi(argv[i]));
    }

    // Create Huffman tree on the heap
    HuffmanTree *huffmanTree = new HuffmanTree(weights);
    huffmanTree->createTree();

    // Print the Huffman tree structure
    huffmanTree->printHuffmanTree(huffmanTree->length - 1, 0);

    // Deallocate memory
    delete huffmanTree;

    return 0;
}
