#include <bits/stdc++.h>
#define MAX_TREE_HT 256
using namespace std;

// Se mapira sekoj karakter so negovata hufmanova vrednost
map<char, string> codes;

// Se zacuvuva frekvencijata na karakterite od vneseniot tekst
map<char, int> freq;

// Generiranje na steblata vo Hufmanovoto drvo
struct MinHeapNode
{
    char data;			 // Eden od karakterite od vneseniot tekst
    int freq;			 // Frekvencija na karakterot
    MinHeapNode *left, *right; // Levo i desno steblo

    MinHeapNode(char data, int freq)
    {
        left = right = NULL;
        this->data = data;
        this->freq = freq;
    }
};

// Funkcija za prioritet
struct compare
{
    bool operator()(MinHeapNode* l, MinHeapNode* r)
    {
        return (l->freq > r->freq);
    }
};

// Funkcija za printanje na karakterite zaedno so nivnata hufmanova vrednost
void printCodes(struct MinHeapNode* root, string str)
{
    if (!root)
        return;
    if (root->data != '$')
        cout << root->data << ": " << str << "\n";
    printCodes(root->left, str + "0");
    printCodes(root->right, str + "1");
}

// Funkcija za skladiranje na karakterite zaedno so nivnata hufmanova vrednost vo tabela, se koristi C++ STL mapiranje
void storeCodes(struct MinHeapNode* root, string str)
{
    if (root==NULL)
        return;
    if (root->data != '$')
        codes[root->data]=str;
    storeCodes(root->left, str + "0");
    storeCodes(root->right, str + "1");
}

// STL prioritet na zapisuvanje na drvoto
priority_queue<MinHeapNode*, vector<MinHeapNode*>, compare> minHeap;

// Funkcija za generiranje ne Hufmanovo drvo
void HuffmanCodes(int size)
{
    struct MinHeapNode *left, *right, *top;
    for (map<char, int>::iterator v=freq.begin(); v!=freq.end(); v++)
        minHeap.push(new MinHeapNode(v->first, v->second));
    while (minHeap.size() != 1)
    {
        left = minHeap.top();
        minHeap.pop();
        right = minHeap.top();
        minHeap.pop();
        top = new MinHeapNode('$', left->freq + right->freq);
        top->left = left;
        top->right = right;
        minHeap.push(top);
    }
    storeCodes(minHeap.top(), "");
}

void calcFreq(string str, int n)
{
    for (int i=0; i<str.size(); i++)
        freq[str[i]]++;
}

//Funkcija koja izminuva niz site karakteri vo stringot
//Ako s[i]=='1' togash se generira desno steblo
//Ako s[i]=='0' togash se generira levo steblo
string decode_file(struct MinHeapNode* root, string s)
{
    string ans = "";
    struct MinHeapNode* curr = root;
    for (int i=0;i<s.size();i++)
    {
        if (s[i] == '0')
            curr = curr->left;
        else
            curr = curr->right;

        //generiranje na list (vrednost)
        if (curr->left==NULL and curr->right==NULL)
        {
            ans += curr->data;
            curr = root;
        }
    }

    return ans+'\0';
}

int main()
{
    string str;
    cout << "Vnesete zbor:\n";
    cin >> str;
    string encodedString, decodedString;
    calcFreq(str, str.length());
    HuffmanCodes(str.length());
    cout << "\nTabela na karakterite i nivnite frekvencii:\n";
    for (auto v=codes.begin(); v!=codes.end(); v++)
        cout << v->first <<' ' << v->second << endl;

    for (auto i: str)
        encodedString+=codes[i];

    cout << "\nEnkodiran Hufmanov kod:\n" << encodedString << endl;
    decodedString = decode_file(minHeap.top(), encodedString);
    cout << "Negovata dolzina e:\n"<<  encodedString.length() << endl;
    cout << "\nDekodiran Hufmanov kod:\n" << decodedString << endl;
    cout << "Negovata dolzina e:\n"<<  (decodedString.length() - 1) << endl;
    return 0;
}
