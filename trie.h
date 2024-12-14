#include <string>
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

// use ASCII encoding for alphabet
const int ALPHABET_SIZE = 128;
int ALPHABET[ALPHABET_SIZE];

struct node
{
    node* children[ALPHABET_SIZE] = { nullptr }; 
    bool isTerminal = false;
    bool isWord = false;
};

struct trie {
    node* root;
    int size;
    trie() : root(new node), size(0) {}
};

// populates ALPHABET with ints 
void create_alphabet();

// converts string to vector using ASCII encoding
vector<int> convert_string(const string& s);

// prints the contents of a vector
void print_vec(const vector<int>& v);

// prints all characters stored (implicitly) in the trie
// recommend using print_words instead
void print_trie(const node*& root);

void print_words_helper(node*& root, string word);

// prints all words in tr
void print_words(trie*& tr);

int find_height_helper(node*& root, int height);

int find_height(trie*& tr);

// returns true if node has children, false otherwise
bool has_children(node*& n);

// returns true if key is in tr, false otherwise
bool trie_find(trie*& tr, string key);

// inserts key into tr; does nothing if key already in tr
void trie_insert(trie*& tr, string key);

// safely deletes node and all children
void delete_node(node*& root);

// safely deletes tr
void remove_trie(trie*& tr);

node* trie_delete_recursive(trie*& tr, node*& root, vector<int> v);

// deletes key if present in tr; otherwise does nothing
// when deleting final key, entire tr is removed
void trie_delete(trie*& tr, string key);

// returns node in tr that is terminal node of s; nullptr if s not in tr
node* find_node(trie*& tr, string s);

// given a node, prints all words in children
void print_words_from_node(node*& root, string prfx);

// prints all words in tr containing prfx
void print_words_from_prefix(trie*& tr, string prfx);

// reads words from fstream into vector<string>
vector<string> load_words_vec(string filename);

// reads words from fstream into trie*
trie* load_words_trie(string filename);