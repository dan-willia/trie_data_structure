# trie_data_structure
This project implements a trie structure.

The basic idea of a trie, when used with words, is that you store all the first letters of the words as children of the parent node; all the strings stored in level one have a length of one, and there will be as many children as there are unique first letters in your list of words. For level two, store the first two letters of each word as children of the node of the appropriate first letter. Continue until all words are stored. The number of levels should be equal to the length of the longest word. Here is an example:

Say we have the following words: "cat, cart, i, a, an, and, ant". The associated trie would look like this:

            (Root)
          /    |   \  
        "c"   "i"  "a"
         |          |
        "ca"       "an"
       /   \       /   \
     "car" "cat" "and" "ant"
     /
  "cart"

When actually implementing my trie, I discovered that the keys are stored "implicitly" in the trie, meaning the words are not directly stored as shown in the trie above. Words are stored implicitly by storing pointers to other nodes at different indices in an array. The index will encode the character information (I use the ASCII encoding).

Let's assume we have a simple 26 letter encoding, where 'a' = 0, 'b' = 1, ..., 'z' = 25. Then, taking the example from above, Root will be a node that has an array of 26 pointers. Since 2 = 'c', 8 = 'i', and 0 = 'a', indices 2, 8, and 0 in this array will point to other nodes. The rest of the pointers will be null. In this way, words are stored implicitly in the trie.

The basic operations on a trie include search, insert, and delete. I've implemented these as well as some auxiliary functions, such as printing all the words in the trie, finding the height (and therefore the length of the longest word) of a trie, and removing a trie without memory leaks. 

One of the applications of tries is autocomplete. I implemented a rudimentary version of this. In my implementation, given a string and a trie, all the words in the trie that include the string as a prefix are printed.

I've included a test file that I hope is nearly comprehensive. Run it to see that all tests pass and a brief demo of the "autocomplete" feature. To play around with "autocomplete", use load_words_trie("words_alpha.txt") to create a large trie, and use print_words_from_prefix(trie_name, "...") to see the words that contain "..." as prefix. 

Words_alpha.txt is a freely available dictionary of words that contain only alphanumeric characters. It was obtained from https://github.com/dwyl/english-words). 
