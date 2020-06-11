/* 
 * Author: Savvas Theofilou
 */

#ifndef CLASSINVERTEDINDEX_H
#define CLASSINVERTEDINDEX_H
#include <fstream>

struct node
{
    unsigned int id,height,neighbors_size;
    node *left,*right;
    class ClassInvertedIndex *neighbor;
};

class ClassInvertedIndex
{
    public:
        ClassInvertedIndex();
        ~ClassInvertedIndex();
        void INSERT(unsigned int,node*&,unsigned int,bool&);
        node* SEARCH(node*,unsigned int);
        node*& get_root() {return root;}
        void Print_InOrder(node*,std::ofstream&);
        void delete_link(unsigned int,node*&,unsigned int);
    private:
        node *root;
        bool added; //I XRISI TOU EINAI GIA NA APOFEGVETAI I KLISI GIA BALANCE ENW DEN EXEI EISAXTHEI KAINOURGIOS KOMVOS->E3IKONOMISI XRONOU
        unsigned int height(node*);
        void balance(node*&);
        int getBalance(node*);
        void SingleLeftRotate(node*&);
        void RightLeftRotate(node*&);
        void SingleRightRotate(node*&);
        void LeftRightRotate(node*&);
        unsigned int MAX(unsigned int,unsigned int);
        void add_neighbor(unsigned int,node*&,bool&,node*&);
        void Print_InOrder_SUBTREE(node*,std::ofstream&);
        node* getMinValueNode(node*);
        void DELETE(unsigned int,node*&,bool&);
        void deleteTree(node*&);
};
//(node*&) -> CALL BY REFERENCE (DEXETAI TIN DIEFTHINSI MNIMIS TOU DIXTI
//            SE NODE GIA NA MENOUN OI ALLAGES POU GINONTAI)

#endif // CLASSINVERTEDINDEX_H


