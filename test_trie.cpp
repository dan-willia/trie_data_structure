#include "trie.cpp"

trie* hand_build_small_trie() {
    /*
                a
              /   \
             n     r
            /     / \
           t     e   t 
    */

    trie* test_trie = new trie;

    // add "ant" to trie
    test_trie->root->children[int('a')] = new node;
    test_trie->root->children[int('a')]->children[int('n')] = new node;
    test_trie->root->children[int('a')]->children[int('n')]->children[int('t')] = new node;
    test_trie->root->children[int('a')]->children[int('n')]->children[int('t')]->isTerminal = true;
    test_trie->root->children[int('a')]->children[int('n')]->children[int('t')]->isWord = true;
    test_trie->size++;

    // add "are" to trie
    test_trie->root->children[int('a')]->children[int('r')] = new node;
    test_trie->root->children[int('a')]->children[int('r')]->children[int('e')] = new node;
    test_trie->root->children[int('a')]->children[int('r')]->children[int('e')]->isTerminal = true;
    test_trie->root->children[int('a')]->children[int('r')]->children[int('e')]->isWord = true;
    test_trie->size++;

    // add "art" to trie
    test_trie->root->children[int('a')]->children[int('r')]->children[int('t')] = new node;
    test_trie->root->children[int('a')]->children[int('r')]->children[int('t')]->isTerminal = true;
    test_trie->root->children[int('a')]->children[int('r')]->children[int('t')]->isWord = true;
    test_trie->size++;

    // add "an" to trie
    test_trie->root->children[int('a')]->children[int('n')]->isWord = true;
    test_trie->size++;
    
    return test_trie;
}

void test_trie_find_hand() {
    trie* tr = hand_build_small_trie();

    // Test 1: check all words
    if (trie_find(tr, "an") && trie_find(tr, "ant") && trie_find(tr, "are") && trie_find(tr, "art")) {
        cout << "passed trie_find_hand test 1" << endl; 
    }
    else {
        cout << "passed trie_find_hand test 1" << endl;
    }

    // Test 2: searching for partially matching entry
    if (!trie_find(tr, "ar")) {
        cout << "passed trie_find_hand test 2" << endl;
    }
    else {
        cout << "failed trie_find_hand test 2" << endl;
    }

    // Test 3: searching for words not in trie
    if (!trie_find(tr, "and")) {
        cout << "passed trie_find_hand test 3" << endl;
    }
    else {
        cout << "failed trie_find_hand test 3" << endl;
    }
}

void test_trie_insert() {
    trie* tr = new trie;

    // Test 1: inserting a single word
    trie_insert(tr, "test");
    if (trie_find(tr, "test")) {
        cout << "passed trie_insert test 1" << endl;
    }
    else {
        cout << "failed trie_insert test 1" << endl;
    }

    // Test 2: inserting different prefixes
    trie_insert(tr, "cat");
    trie_insert(tr, "dog");
    if (trie_find(tr, "cat") && trie_find(tr, "dog")) {
        cout << "passed trie_insert test 2" << endl;
    }
    else {
        cout << "failed trie_insert test 2" << endl;
    }

    // Test 3: inserting common prefixes
    trie_insert(tr, "cater");
    trie_insert(tr, "cattle");
    if (trie_find(tr, "cater") && trie_find(tr, "cattle")) {
        cout << "passed trie_insert test 3" << endl;
    }
    else {
        cout << "failed trie_insert test 3" << endl;
    }

    // Test 4: inserting empty string does nothing
    trie_insert(tr, "");
    if (!trie_find(tr, "")) {
        cout << "passed trie_insert test 4" << endl;
    }
    else {
        cout << "failed trie_insert test 4" << endl;
    }
}

void test_trie_find() {
    trie* tr = new trie;
    
    // Test 1: searching empty trie
    if (!trie_find(tr, "word")) {
        cout << "passed trie_find test 1" << endl;
    }
    else {
        cout << "failed trie_find test 1" << endl;
    }

    // Test 2: searching for partially matching entry
    trie_insert(tr, "cattle");
    if (!trie_find(tr, "cat")) {
        cout << "passed trie_find test 2" << endl;
    }
    else {
        cout << "failed trie_find test 2" << endl;
    }

    // Test 3: searching for words not in trie
    trie_insert(tr, "cat");
    trie_insert(tr, "dog");
    if (!trie_find(tr, "lizard")) {
        cout << "passed trie_find test 3" << endl;
    }
    else {
        cout << "failed trie_find test 3" << endl;
    }
}

void test_trie_delete() {
    trie* tr = new trie;

    // Test 0: deleting word from empty trie
    trie_delete(tr, "and");
    if (!has_children(tr->root)) {
        cout << "passed trie_delete test 0" << endl;
    }
    else {
        cout << "failed trie_delete test 0" << endl;
    }

    trie_insert(tr, "cat");
    trie_insert(tr, "cater");
    trie_insert(tr, "cattle");

    // Test 1: deleting key not in trie
    trie_delete(tr, "cats");
    if (trie_find(tr, "cat") && trie_find(tr, "cater") && trie_find(tr, "cattle")) {
        cout << "passed trie_delete test 1" << endl;
    }
    else {
        cout << "failed trie_delete test 1" << endl;
    }

    // Test 2: deleting prefix not in trie
    trie_delete(tr, "cate");
    if (trie_find(tr, "cat") && trie_find(tr, "cater") && trie_find(tr, "cattle")) {
        cout << "passed trie_delete test 2" << endl;
    }
    else {
        cout << "failed trie_delete test 2" << endl;
    }

    trie_insert(tr, "a");
    trie_insert(tr, "an");
    trie_insert(tr, "ant");
    trie_insert(tr, "ante");

    // Test 3: deleting terminal node
    trie_delete(tr, "cattle");
    if (!trie_find(tr, "cattle")) {
        cout << "passed trie_delete test 3" << endl;
    }
    else {
        cout << "failed trie_delete test 3" << endl;
    }

    // Test 4: deleting node with children
    trie_delete(tr, "a");
    if (!trie_find(tr, "a") && trie_find(tr, "an") && trie_find(tr, "ant") && trie_find(tr, "ante")) {
        cout << "passed trie_delete test 4" << endl;
    }
    else {
        cout << "failed trie_delete test 4" << endl;
    }

    // Test 5: deleting word that shares prefix
    trie_delete(tr, "ante");
    if (!trie_find(tr, "ante") && trie_find(tr, "ant")) {
        cout << "passed trie_delete test 5" << endl;
    }
    else {
        cout << "failed trie_delete test 5" << endl;
    }
}

void test_trie_structure() {
    // make sure data members isTerminal / is Word are correct
    trie* tr = new trie;

    trie_insert(tr, "an");
    trie_insert(tr, "ant");
    trie_insert(tr, "are");
    trie_insert(tr, "art");

    // Test 1: test non-terminal word
    if (!tr->root->children[int('a')]->children[int('n')]->isTerminal && tr->root->children[int('a')]->children[int('n')]->isWord) {
        cout << "passed trie_structure test 1" << endl;
    }
    else {
        cout << "failed trie_structure test 1" << endl;
    }
}

void test_print_words_from_prefix() {
    // test with hand-built trie
    trie* tr = hand_build_small_trie();

    cout << "*** Testing print_words_from_prefix: expected output: are, art" << endl;
    print_words_from_prefix(tr, "ar");
    cout << "***" << endl;
}

// demo with large dictionary
void demo_print_words_from_prefix() {
    cout << "*** Running demo of print_words_from_prefix using large dictionary:" << endl;
    vector<string> words = load_words_vec("words_alpha.txt");
    cout << "loaded " << words.size() << " words into vector" << endl;

    trie* tr = load_words_trie("words_alpha.txt");
    cout << "trie has size " << tr->size << endl;
    
    cout << "Printing words with prefix 'nume'" << endl;
    print_words_from_prefix(tr, "nume");
    cout << "***" << endl;
}

int main() 
{
    test_trie_find_hand();
    test_trie_insert();
    test_trie_find();
    test_trie_delete();
    test_trie_structure();
    test_print_words_from_prefix();

    demo_print_words_from_prefix();
}