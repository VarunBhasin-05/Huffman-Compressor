# Huffman Compression & Decompression Utility

A command-line tool built in C++ to demonstrate lossless data compression using Huffman Coding. This project was developed to explore the practical applications of Greedy Algorithms, Min-Heaps, and Bitwise operations.

## Features
* **Custom Input**: Compresses any user-specified text file.
* **Bit-Level Optimization**: Uses bit-packing to ensure the `.bin` file is physically smaller than the original.
* **Interactive Menu**: User-friendly CLI to switch between compression and decompression.

## How to Run

### 1. Prerequisites
You need a C++ compiler installed (like `g++`). Ensure your terminal/command prompt is open in the folder containing `main.cpp`.

### 2. Compilation
Compile the code using the following command:
g++ main.cpp -o huffman

### 3. Execution
Run the generated executable:
./huffman (for Linux/Mac)
huffman.exe (for Windows)

## Step-by-Step Instructions
1. **Prepare Input**: Create a file named `input.txt` (or any name you like) and add some text.
2. **Compress**: Choose **Option 1** and type the filename. This creates `compressed.bin`.
3. **Decompress**: Choose **Option 2**.
   * *Note: Decompression must be done in the same session as compression because the decoding tree is stored in RAM.*
4. **Verify**: Check `decompressed_output.txt` to see your original text recovered.

## Technical Details
* **Algorithm**: Huffman Coding (Greedy).
* **Time Complexity**: O(N log K), where N is the number of characters and K is the number of unique characters.
* **Space Complexity**: O(K) for storing the frequency map and the generated Huffman Tree.
* **Data Structures**: `std::unordered_map`, `std::priority_queue` (Min-Heap), and `Binary Tree`.
