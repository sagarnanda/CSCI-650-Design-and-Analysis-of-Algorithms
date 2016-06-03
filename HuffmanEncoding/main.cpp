/* 
 *@Name - Sagar Nanda
 *@Turnin Id - snanda
 *
 *@DESC -  Huffman Coding - Building Huffman encoding trie, using classes Node and Trie. The class Node have public data members: Node *prev (left), Node *next (right), int priority, and character value. 
 *
 *
 */

#include<iostream>
#include<string>
#include<fstream>
#include<map>

#include "priority_queue.h"
#include "trie.h"

using namespace std;

int main(int argc, char* argv[])
{
    ifstream infile(argv[1]);
    char ch;
    map <char,int> mymap;
    while (infile.get(ch))
    {
        ch = toupper(ch);
        if(ch != 10 && ch != 13)//Ignoring ASCII cvalue for Line Feed and Carriage Return
        {
            if (mymap.count(ch)>0)
            {
                //update priority 
                mymap[ch]+=1; 
            }
            else
            {
                //add to the map
                mymap[ch]=1; 
            }
        }
    }
    PriorityQueue <Trie *> pqueue;

    for (map<char,int>::iterator it=mymap.begin(); it!=mymap.end(); ++it)
    {
        Node<char>* node = new Node<char> (it->first, NULL, NULL, it->second);
        Trie *t= new Trie(node);
        pqueue.enqueue(t,it->second);
    }
    while(pqueue.size()>1)
    {
        Node<char> *pnode = new Node<char>(0,NULL,NULL,0);
        Trie trie1;
        trie1 = pqueue.front();
        pqueue.dequeue();
        Trie trie2; 
        trie2 = pqueue.front();
        pqueue.dequeue();
        //Merging trie1 and trie2
        Trie *trie3;
        trie3 = new Trie(pnode);
        trie3->setprev(&trie1);
        trie3->setnext(&trie2);
        trie3->setpriority(&trie1,&trie2);
        //Enqueueing back into list.
        pqueue.enqueue(trie3,trie3->getpriority());
    }
    Trie trie4;
    trie4 = pqueue.front();

    map<char, string> result = trie4.printOrder(trie4.getRoot());
    //Setting check to 1, so destructor deep deletes.
    trie4.check = 1;
    int sum = 0;
    int freq = 0;

    /*The first integer is the total number of bits required to encode the given input calculated by the formula given.
     *  where f(c) is a frequency of character c in the input file and d(c) is the length of the encoding for c (number of bits in the c’s encoding).
     */
    for(map<char, int>::iterator it = mymap.begin(); it != mymap.end(); it++)
    {
        sum = sum + (it->second*8);
    }
     
    /*  The second integer in the last line of the output file represents the total number of bits in the original file (each character is represented by 8 bits).
     *  This number is calculated by the same formula as given, except d(c) is the same for all characters and equal to 8.
     */

    for(map<char, string>::iterator it1 = result.begin(); it1 != result.end(); it1++)
    {
        string temp = it1->second;
        freq = freq + (temp.size() * mymap[it1->first]);
    }

    cout << freq << endl;
    cout << sum << endl;
    pqueue.dequeue();
}
