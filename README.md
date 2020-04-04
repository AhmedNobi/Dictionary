# Dictionary
Simple dictionary project can search and listen to a word.
We can search, listen and show the exiting trees in the dictionary.
Trie is an efficient information retrieval data structure. Using Trie, search complexities can be brought to optimal limit (key length).
If we store keys in binary search tree, a well balanced BST will need time proportional to M * log N,
where M is maximum string length and N is number of keys in tree. Using Trie, we can search the key in O(M) time.
However the penalty is on Trie storage requirements.
