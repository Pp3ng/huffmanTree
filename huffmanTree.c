#include <stdio.h>
#include <stdlib.h>

#define MAX_WEIGHT 10000

typedef struct TreeNode
{
    int weight;
    int parent;
    int left;
    int right;
} Node;

typedef struct HuffmanTree
{
    Node *data;
    int length;
} HuffmanTree;

// Function to initialize the Huffman tree
HuffmanTree *initTree(const int *weight, int length)
{
    HuffmanTree *T = (HuffmanTree *)malloc(sizeof(HuffmanTree));
    if (T == NULL)
    {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }

    T->data = (Node *)malloc(sizeof(Node) * (2 * length - 1));
    if (T->data == NULL)
    {
        perror("Memory allocation failed");
        free(T);
        exit(EXIT_FAILURE);
    }

    T->length = length;

    // Initialize nodes with weights and default values
    for (int i = 0; i < length; i++)
    {
        T->data[i].weight = weight[i];
        T->data[i].parent = 0;
        T->data[i].left = T->data[i].right = -1;
    }

    return T;
}

// Function to select two nodes with the minimum weights
int *selectMin(HuffmanTree *T, int *result)
{
    int min = MAX_WEIGHT;
    int secondMin = MAX_WEIGHT;
    int minIndex = -1;
    int secondIndex = -1;

    for (int i = 0; i < T->length; i++)
    {
        if (T->data[i].parent == 0)
        {
            if (T->data[i].weight < min)
            {
                min = T->data[i].weight;
                minIndex = i;
            }
        }
    }

    for (int i = 0; i < T->length; i++)
    {
        if (T->data[i].parent == 0 && i != minIndex)
        {
            if (T->data[i].weight < secondMin)
            {
                secondMin = T->data[i].weight;
                secondIndex = i;
            }
        }
    }

    result[0] = minIndex;
    result[1] = secondIndex;
    return result;
}

// Function to create the Huffman tree
void createTree(HuffmanTree *T)
{
    int min, secondMin;
    int length = T->length * 2 - 1;

    for (int i = T->length; i < length; i++)
    {
        int result[2];
        int *res = selectMin(T, result);
        min = res[0];
        secondMin = res[1];

        T->data[i].weight = T->data[min].weight + T->data[secondMin].weight;
        T->data[i].left = min;
        T->data[i].right = secondMin;
        T->data[min].parent = T->data[secondMin].parent = i;
        T->length++;
    }
}

// Function to print the Huffman tree structure
void printHuffmanTree(HuffmanTree *T, int index, int level)
{
    if (index != -1)
    {
        printHuffmanTree(T, T->data[index].right, level + 1);
        for (int i = 0; i < level; i++)
        {
            printf("    "); // Print spaces for indentation
        }
        printf("%d\n", T->data[index].weight);
        printHuffmanTree(T, T->data[index].left, level + 1);
    }
}

// Main function
int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Usage: %s <Element> <Element> ... <Element>\n", argv[0]);
        return 1;
    }

    int numElements = argc - 1;
    int weight[numElements];

    for (int i = 1; i < argc; i++)
    {
        weight[i - 1] = atoi(argv[i]);
    }

    HuffmanTree *T = initTree(weight, numElements);
    createTree(T);
    printHuffmanTree(T, T->length - 1, 0);

    // Free dynamically allocated memory
    free(T->data);
    free(T);

    return 0;
}
