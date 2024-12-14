#include "trie.h"

void create_alphabet() {
    for (int i=0; i<ALPHABET_SIZE; i++) {
        ALPHABET[i] = i;
    }
}

vector<int> convert_string(const string& s) {
    vector<int> v;
    for (char ch : s) {
        v.push_back(int(ch));
    } 
    return v;
}

void print_vec(const vector<int>& v) {
    for (int i : v) {
        cout << i << " ";
    }
}

void print_trie(node*& root) {
    create_alphabet();
    for (int i = 0; i < ALPHABET_SIZE; ++i) {
        if (root->children[i] != nullptr) {
            cout << char(ALPHABET[i]) << endl;
            print_trie(root->children[i]);
        }
    }
}

void print_words_helper(node*& root, string word) {
    create_alphabet();
    for (int i=0; i<ALPHABET_SIZE; ++i) {
        if (root->children[i] != nullptr) {
            string cur_word = word + char(ALPHABET[i]);
            if (root->children[i]->isWord) {
                cout << cur_word << endl;
            }
            if (!root->children[i]->isTerminal) {
                print_words_helper(root->children[i], cur_word);
            }
        }
    }
}

void print_words(trie*& tr) {
    print_words_helper(tr->root, "");
}

int find_height_helper(node*& root, int height) {
    int cur_max_height = height;
    for (int i=0; i<ALPHABET_SIZE; ++i) {
        if (root->children[i] != nullptr) {
            int height2 = find_height_helper(root->children[i], height + 1);
            cur_max_height = max(cur_max_height, height2); 
        }
    }
    return cur_max_height;
}

int find_height(trie*& tr) {
    return find_height_helper(tr->root, 0);
}

bool has_children(node*& n) {
    for (int i=0; i<ALPHABET_SIZE; i++) {
        if (n->children[i] != nullptr) {
            return true;
        }
    }
    return false;
}

bool trie_find(trie*& tr, string key) {
    node* root = tr->root;
    vector<int> v = convert_string(key);

    for (int i=0; i<v.size(); ++i) {
        if (root->children[v[i]] == nullptr) {
            return false;
        }
        root = root->children[v[i]];
    }
    return root->isWord;
}

void trie_insert(trie*& tr, string key) {   
    if (!tr || !tr->root) {
        cerr << "Error: Trie is not initialized" << endl;
        return;
    }

    // do nothing if key is empty string
    if (key == "") {
        return;
    }

    node* root = tr->root;
    vector<int> v = convert_string(key);

    if (v.empty()) {
        cerr << "Error: Key is empty or conversion failed" << endl;
        return;
    }

    for (int i=0; i<v.size(); ++i) {
        if (v[i] < 0 || v[i] >= ALPHABET_SIZE) {
            cerr << "Error: Invalid character index " << v[i] << endl;
            return;
        }

        if (root->children[v[i]] == nullptr) {
            root->children[v[i]] = new node;
            root->isTerminal = false;
        }
        root = root->children[v[i]];
    }

    if (root->isWord) { // key already in trie; do nothing
        return;
    }
    else { 
        root->isWord = true;
        tr->size++;
        if (!has_children(root)) {
            root->isTerminal = true;
        }
    }
}

void delete_node(node*& root) {
    if (!root) {    // do nothing if root already nullptr;
        return;
    }

    // recurisvely delete children
    for (int i=0; i<ALPHABET_SIZE; ++i) {
        if (root->children[i]) {
            delete_node(root->children[i]);
            root->children[i] = nullptr;
        }
    }
    delete root;
    root = nullptr;
}

void remove_trie(trie*& tr) {
    if (tr->root) {
        delete_node(tr->root);
    }
    delete tr;
    tr = nullptr;
}

node* trie_delete_recursive(trie*& tr, node*& root, vector<int> v) {
    // reached end of key, reset node values
    if (!root) {    // if key not in trie, root may be null
        return root;
    }

    if (v.size() == 0) {
        if (root->isWord) { // does nothing if key not in trie
            root->isWord = false;
            tr->size--;
        }

        // do not delete node if it has children
        if (has_children(root)) {
            return root;
        }
        else {
            delete_node(root);
            return nullptr;
        }
    }

    vector<int> v2;
    for (int i=1; i<v.size(); i++) { // copy all but first element of v to v2
        v2.push_back(v.at(i));
    }

    root->children[v[0]] = trie_delete_recursive(tr, root->children[v[0]], v2);

    if (has_children(root) || root->isWord) {
        return root;
    }
    else {
        delete_node(root);
        return nullptr;
    }
}

void trie_delete(trie*& tr, string key) {
    // do nothing if tr is empty
    if (tr->size == 0) {
        return;
    }

    vector<int> v = convert_string(key);
    trie_delete_recursive(tr, tr->root, v);

    // delete trie if no remaining words
    if (!tr->root) {
        remove_trie(tr);
    }
}

node* find_node(trie*& tr, string s) {
    node* root = tr->root;
    vector<int> v = convert_string(s);

    for (int i=0; i<v.size(); ++i) {
        if (root->children[v[i]] == nullptr) {
            return nullptr;
        }
        root = root->children[v[i]];
    }
    return root;
}

void print_words_node(node*& root, string prfx) {
    print_words_helper(root, prfx);
}

void print_words_from_prefix(trie*& tr, string prfx) {
    node* n = find_node(tr, prfx);
    print_words_node(n, prfx);
}

vector<string> load_words_vec(string filename) {
    vector<string> words;
    ifstream file(filename);
    string word;
    while (file >> word) {
        words.push_back(word);
    }
    return words;
}

trie* load_words_trie(string filename) {
    trie* tr = new trie;
    ifstream file(filename);
    string word;
    while (file >> word) {
        trie_insert(tr, word);
    }
    return tr;
}