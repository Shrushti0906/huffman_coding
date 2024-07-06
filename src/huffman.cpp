#include<bits/stdc++.h>
using namespace std;

//Node of huffman tree
class huffman_node
{
    public:
        char data;
        int freq;
        huffman_node* left;
        huffman_node* right;
        huffman_node(char data, int freq) : data(data), freq(freq), left(nullptr), right(nullptr) {}
};

//Comparator to comparatoreach element by their frequency
class mycomparator
{
    public:
        bool operator()(huffman_node* x1, huffman_node* x2)
        {
            return x1->freq > x2->freq;
        }
};

//Function to build huffman tree
huffman_node* buildHuffmantree(unordered_map<char,int> &frequencies)
{
    priority_queue<huffman_node*,vector<huffman_node*>,mycomparator> q;

    for(auto it:frequencies)
    {
        q.push(new huffman_node(it.first,it.second));
    }

    while(q.size()>1)
    {
        huffman_node* left = q.top();
        q.pop();
        huffman_node* right = q.top();
        q.pop();

        huffman_node* temp = new huffman_node('$',left->freq+right->freq);
        temp->left = left;
        temp->right = right;
        q.push(temp);
    }
    return q.top();
}

//Function to generate binary code for each character
void generateCodes(huffman_node* root, string s, unordered_map<char,string> &codes)
{
    if(root==NULL)
        return;

    if(root->left==NULL && root->right==NULL)
    {
        codes[root->data] = s;
    }

    generateCodes(root->left, s+'0',codes);
    generateCodes(root->right, s+'1',codes);
}

//Function to compress the data file
long long int compress(string text, huffman_node* root, string compressedFile)
{
    unordered_map<char,string> codes;
    generateCodes(root,"",codes);

    int n = text.size();
    
    string s;
    for(int i=0;i<n;i++)
    {
        s += codes[text[i]];
    }
    
    fstream comp_outfile;
    comp_outfile.open(compressedFile,ios::binary | ios::trunc | ios::out);
    if (!comp_outfile)
    {
        cout << "Error opening the file "<< compressedFile << endl;
        return 0;
    }

    //Compress the data into bits
    for(int i=0;i<size(s);)
    {
        int curr = 0;
    
        for(int j=6;j>=0&&i<size(s);i++,j--)
        {
            curr += (1 << (j))*(s[i]=='1');
        }
        comp_outfile << (char)curr;
    }
    comp_outfile.close();
    return s.size();
}


//Function to decompress the file
void decompress(string compressedFile, string decompressedFile,huffman_node* root, long long int n)
{
    fstream comp_infile;
    comp_infile.open(compressedFile, ios::in | ios::binary);

    if (!comp_infile)
    {
        cout << "Error opening the file "<< compressedFile << endl;
        return;
    }

    string compressedData;
    stringstream buffer;
    buffer << comp_infile.rdbuf();
    compressedData = buffer.str();
    comp_infile.close();

    string currentCode;
    for (char c : compressedData)
    {
        for (int i = 6; i >= 0; --i)
        {
            currentCode += ((c >> i) & 1) ? '1' : '0';
            if(currentCode.size()==n)
                break;
        }
    }

    fstream outfile;
    outfile.open(decompressedFile,ios::out | ios::trunc);

    if (!outfile)
    {
        cout << "Error opening the file " << decompressedFile << endl;
        return;
    }

    huffman_node* current = root;
    for (char bit : currentCode) 
    {
        if (bit == '0') 
        {
            current = current->left;
        }
        else 
        {
            current = current->right;
        }

        if (current->left == NULL && current->right == NULL) 
        {
            outfile << current->data;
            current = root;
        }
    }
    outfile.close();
}


int main()
{
    //To get input file
    string inputFile;
    cout<<"Enter the name of file to compress:"<<endl;
    cin>>inputFile;

    int size = inputFile.size();
    string s = inputFile.substr(0,size-4);
    string compressedFile = s + "-compressed.bin";
    string decompressedFile = s + "-decompressed.txt";

    //Open the input file
    fstream infile;
    infile.open(inputFile,ios::in);
    if(!infile)
    {
        cout<<"Error opening the file "<<inputFile<<endl;
        exit(1);
    }

    //Read input file
    stringstream buffer;
    buffer << infile.rdbuf();
    string text;
    text = buffer.str();

    //Count frequencies of each character
    unordered_map<char,int> frequencies;
    for(int i=0;i<text.size() && text[i];i++)
    {
        frequencies[text[i]]++;
    }

    //Root of the huffman tree
    huffman_node* root = buildHuffmantree(frequencies);

    //Compress the input file
    long long int n = compress(text,root,compressedFile);

    //Decompress the input file
    decompress(compressedFile,decompressedFile,root,n);

    //Close the input file
    infile.close();
    return 0;
}
