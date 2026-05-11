#include <iostream>
#include <fstream>
#include <queue>
#include <unordered_map>
#include <vector>
#include <bitset>
#include <string>

using namespace std;

struct Node {
    char ch;
    int freq;
    Node *left, *right;
    Node(char c, int f) : ch(c), freq(f), left(nullptr), right(nullptr) {}
};

struct Compare {
    bool operator()(Node* l, Node* r) {
        return l->freq > r->freq;
    }
};

void generateCodes(Node* root, string str, unordered_map<char, string> &huffmanCode) {
    if (!root) return;
    if (!root->left && !root->right) huffmanCode[root->ch] = str;
    generateCodes(root->left, str + "0", huffmanCode);
    generateCodes(root->right, str + "1", huffmanCode);
}

Node* globalRoot = nullptr;

void decompressFile(string inputFile, string outputFile) {
    ifstream in(inputFile, ios::binary);
    ofstream out(outputFile);
    if (!in.is_open()) {
        cout << "Error: Binary file not found." << endl;
        return;
    }
    if (globalRoot == nullptr) {
        cout << "Error: Huffman Tree not found in memory. Compress a file first in this session." << endl;
        return;
    }

    Node* curr = globalRoot;
    char byte;
    while (in.get(byte)) {
        bitset<8> bits(byte);
        for (int i = 7; i >= 0; --i) {
            if (bits[i] == 0) curr = curr->left;
            else curr = curr->right;

            if (!curr->left && !curr->right) {
                out.put(curr->ch);
                curr = globalRoot;
            }
        }
    }
    in.close();
    out.close();
    cout << "Decompression finished: " << outputFile << endl;
}

void compressFile(string inputFile, string outputFile) {
    ifstream in(inputFile, ios::binary);
    if (!in.is_open()) {
        cout << "Error: Cannot open input file." << endl;
        return;
    }

    unordered_map<char, int> freq;
    string content = "";
    char ch;
    while (in.get(ch)) {
        content += ch;
        freq[ch]++;
    }
    in.close();

    priority_queue<Node*, vector<Node*>, Compare> pq;
    for (auto it = freq.begin(); it != freq.end(); ++it) {
        pq.push(new Node(it->first, it->second));
    }

    while (pq.size() > 1) {
        Node *left = pq.top(); pq.pop();
        Node *right = pq.top(); pq.pop();
        Node *parent = new Node('\0', left->freq + right->freq);
        parent->left = left;
        parent->right = right;
        pq.push(parent);
    }

    globalRoot = pq.top();
    unordered_map<char, string> huffmanCode;
    generateCodes(globalRoot, "", huffmanCode);

    ofstream out(outputFile, ios::binary);
    string encodedStr = "";
    for (char c : content) encodedStr += huffmanCode[c];

    for (size_t i = 0; i < encodedStr.length(); i += 8) {
        string byteStr = encodedStr.substr(i, 8);
        while (byteStr.length() < 8) byteStr += '0'; 
        char byte = (char)bitset<8>(byteStr).to_ulong();
        out.put(byte);
    }
    out.close();
    cout << "Compression finished: " << outputFile << endl;
}

int main() {
    int choice;
    string filename;

    while (true) {
        cout << "\n--- Huffman Compression Tool ---" << endl;
        cout << "1. Compress a file\n2. Decompress a file\n3. Exit\nChoice: ";
        cin >> choice;

        if (choice == 3) break;

        cout << "Enter filename: ";
        cin >> filename;

        if (choice == 1) {
            compressFile(filename, "compressed.bin");
        } else if (choice == 2) {
            decompressFile("compressed.bin", "decompressed_output.txt");
        } else {
            cout << "Invalid choice." << endl;
        }
    }

    return 0;
}
