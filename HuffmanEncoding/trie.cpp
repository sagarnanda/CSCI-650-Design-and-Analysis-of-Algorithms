#include"trie.h"


/*
 * 
 *@DESC : Trie constructor, Initializing variables. Check varibale sets to 0.
 * 
 *@Input : N/A
 * 
 *@Output: N/A
 * 
 */
Trie::Trie()
{
    this->root = NULL;
    check = 0;
} 
//////////////////////////////////////////////////////////////////////////////////////

/*
 * 
 *@DESC : Trie  paramaterized Constructor. Initializing nodes and check variable.
 * 
 *@Input : Root
 * 
 *@Output: N/A
 * 
 */
Trie::Trie(Node <char>* root)
{
    this->root = root;
    this->root->prev = root->prev;
    this->root->next = root->next;
    check = 0;
}
//////////////////////////////////////////////////////////////////////////////////////


/*
 * 
 *@DESC : Trie Destructor, calling deleteTree function, only if check is 1.
 * 
 *@Input : N/A
 * 
 *@Output: N/A
 * 
 */
Trie::~Trie()
{

    if (check == 1)
        deleteTree( this->root);
}
//////////////////////////////////////////////////////////////////////////////////////


/*
 * 
 *@DESC :  Delete tree is a recursive function to every prev node and the next node.
 * 
 *@Input :Node(Current Node) 
 * 
 *@Output: N/A
 *
 */
void Trie::deleteTree(Node<char> *node)
{

    if(node->prev)
        deleteTree(node->prev);
    if(node->next)
        deleteTree(node->next);
    if(node)
        delete node;
}
//////////////////////////////////////////////////////////////////////////////////////


/*
 * 
 *@DESC : Operator Overloading, overloads = operator, It calls copyTrie.
 * 
 *@Input : cnode
 * 
 *@Output: returning trie pointer.
 * 
 */
Trie& Trie::operator=(const Trie& cnode)
{
    if (this != &cnode)
    {
        Node<char> *temp = copyTrie(cnode.getRoot());
        delete cnode.root;
        this->root = temp;
    }
    return *this;
}
//////////////////////////////////////////////////////////////////////////////////////


/*
 * 
 *@DESC : Copying trie is a recursive function, checking if it is NULL do nothing, 
 *        if not create a new node and assign it to original (priority and value) and then recursive call to all the prev node and next node in the trie.
 * 
 *@Input : Original Node.
 * 
 *@Output: Returning new node.
 * 
 */
Node<char>* Trie::copyTrie(Node<char> *original)
{
    if(original == NULL)
        return NULL;

    Node<char> *node = new Node<char>();
    node->value = original->value;
    node->priority = original->priority;

    node->prev = copyTrie(original->prev);
    delete original->prev;
    node->next = copyTrie(original->next);
    delete original->next;
    return node;
}
//////////////////////////////////////////////////////////////////////////////////////


/*
 * 
 *@DESC : Setter function to set previous.
 * 
 *@Input : trie1 
 * 
 *@Output: N/A
 * 
 */
void Trie::setprev(Trie *t1)
{
    this->root->prev = t1->root;
}
//////////////////////////////////////////////////////////////////////////////////////


/*
 * 
 *@DESC : Setter function to set next.
 * 
 *@Input :  trie2
 * 
 *@Output: N/A
 * 
 */
void Trie::setnext(Trie *t2)
{
    this->root->next = t2->root;
}
//////////////////////////////////////////////////////////////////////////////////////


/*
 * 
 *@DESC : Setter function to add priorities of trie1 and trie2.
 * 
 *@Input : trie1 and trie2
 * 
 *@Output: N/A
 * 
 */
void Trie::setpriority(Trie *t1, Trie *t2)
{
    this->root->priority=t1->root->priority + t2->root->priority;
}
//////////////////////////////////////////////////////////////////////////////////////


/*
 * 
 *@DESC : Getter function to get priority.
 * 
 *@Input : N/A
 * 
 *@Output: Returning Priority.
 * 
 */
int Trie::getpriority()
{
    return this->root->priority;
}
//////////////////////////////////////////////////////////////////////////////////////


/*
 * 
 *@DESC : printOrder function calls traverse order then prints it out using iterator. 
 * 
 *@Input : Node
 * 
 *@Output: Prints out the result map, character and their encoding.
 * 
 */
map<char, string> Trie::printOrder(Node<char>* node)
{
    string temp = "";
    result.clear();
    traverseOrder(node, temp);
  
    for(map<char, string>::iterator it = result.begin(); it != result.end(); it++)
    {
        if(it->first != 0)
        {
            cout << it->first << " " << it->second << endl;
        }
    }
    return result;
}
//////////////////////////////////////////////////////////////////////////////////////


/*
 * 
 *@DESC : traverseOrder function is a recursive function to assign '0' to all the prev and '1' to all the next  to  return encoding to printOrder function.
 * 
 *@Input : Node and temp string
 * 
 *@Output: N/A
 * 
 */
void Trie::traverseOrder(Node<char> *node, string &temp)
{
    if(node)
    {
        string prev = temp + "0";
        traverseOrder(node->prev, prev); 
        result.insert(make_pair(node->value, temp));
        string next = temp + "1";
        traverseOrder(node->next, next); 
    }
}
//////////////////////////////////////////////////////////////////////////////////////
