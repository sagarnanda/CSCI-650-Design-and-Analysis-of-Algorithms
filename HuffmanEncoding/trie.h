#ifndef TRIE_H
#define TRIE_H

#include"node.h"
#include <map>

/*
 *@DESC : Trie class which has some private and some public  member function and constructor and destructor.
 */
class Trie
{
    public:
    Trie();
    Trie(Node<char> * rt);
    void setprev(Trie *t1);
    void setnext(Trie *t2);
    void setpriority(Trie *t1, Trie *t2);
    //Operator overloader to copy tries.
    Trie& operator=(const Trie& rhs);
    Node<char>* getRoot() const { return root; }
    Node<char>* copyTrie(Node<char> *original);
    int getpriority();
    map<char, string> printOrder(Node<char>* node);
    //Check variable checking if memory is in use by any other trie or not.If it is set to 1 then call destructor and delete the whole tree.
    int check;
    ~Trie();
    private:
    Node<char>* root;
    void deleteTree(Node<char>* node);
    std::map<char, string> result;
    void traverseOrder(Node<char>* node, string &temp); 
};
#endif
