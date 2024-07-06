# Huffman_coding

This project implements Huffman coding for text file compression and decompression. Huffman coding is a lossless data compression algorithm that uses variable-length codes to represent characters based on their frequencies.

## Features
- Compress text files using Huffman coding.
- Decompress compressed files to their original text format.
- Efficiently handles character frequency counting and binary code generation.

## Getting Started

### Prerequisites
- C++ compiler (e.g., g++, clang++)
- Standard Template Library (STL)

### Installation

1. Clone the repository:
    ```sh
    git clone https://github.com/shrushti0906/huffman_coding.git
    cd huffman_coding
    ```

2. Compile the Huffman coding program:
    ```sh
    g++ src/huffman.cpp -o huffman
    ```

3. Run the program:
    ```sh
    ./huffman
    ```

### Usage

1. Prepare a text file to compress (e.g., `data/sample.txt`).
2. Run the Huffman coding program and follow the prompts to compress and decompress the file.

### Example

```sh
Enter the name of file to compress:
data/sample.txt
