/* 
 * Author: Savvas Theofilou
 */

#include "ClassInvertedIndex.h"

ClassInvertedIndex::ClassInvertedIndex()
{
    root=NULL;
    added=false;
}

ClassInvertedIndex::~ClassInvertedIndex()
{
    deleteTree(root); //KALESMA ANADROMIKIS SINARTISIS..
}

void ClassInvertedIndex::INSERT(unsigned int ID,node *&p,unsigned int link,bool &linkcheck) // TA BALANCE GINONTAI ANADROMIKA ARA DEN XREIAZETAI ARRAY GIA
{                                                                                           // NA KANW TA BALANCE GIA OLA TA NODES POY PERASE TO NEO STIXIO
    if (p==NULL)
        {
            p=new node;
            p->id=ID;
            p->height=0;
            p->left=NULL;
            p->right=NULL;
            p->neighbor=new ClassInvertedIndex;  //EDW GINETAI I DIMIOURGIA TOU KOMVOU ARA KAI O PRWTOS TOU GITONAS..
            p->neighbors_size=0;
            add_neighbor(link,p->neighbor->get_root(),linkcheck,p);
            added=true;
        }
    else
        {
            if (ID<p->id)
                {
                    INSERT(ID,p->left,link,linkcheck);
                    if (added)
                        balance(p);
                }
            else if (ID>p->id)
                {
                    INSERT(ID,p->right,link,linkcheck);
                    if (added)
                        balance(p);
                }
            else
                {
                    add_neighbor(link,p->neighbor->get_root(),linkcheck,p);
                    added=false;
                }
        }
    p->height=MAX(height(p->left),height(p->right))+1;
}

node* ClassInvertedIndex::SEARCH(node *p,unsigned int x)
{
    if (p==NULL)
        return NULL;
    if (x<p->id)
        SEARCH(p->left,x);
    else if (x>p->id)
        SEARCH(p->right,x);
    else
        return p;
}

void ClassInvertedIndex::Print_InOrder(node *p,std::ofstream &outputfile)
{
    if (p!=NULL)
        {
            Print_InOrder(p->left,outputfile);
            outputfile<<p->id<<", "<<p->neighbors_size;
            Print_InOrder_SUBTREE(p->neighbor->get_root(),outputfile); //PAROMIA SINARTISI INORDER GIA TO DENTRO TWN GITWNWN TOU..
            outputfile<<std::endl;
            Print_InOrder(p->right,outputfile);
        }
}

void ClassInvertedIndex::delete_link(unsigned int ID,node *&p,unsigned int link)
{
    node *found=SEARCH(p,ID);
    bool deleted=false;
    if (found==NULL)
        return;
    else
        {
            DELETE(link,found->neighbor->get_root(),deleted);
            if (deleted)
                found->neighbors_size--;
        }
}

unsigned int ClassInvertedIndex::height(node *p)
{
    if (p==NULL)
        return 0;
    return p->height;
}

int ClassInvertedIndex::getBalance(node *p)
{
    if (p==NULL)
        return 0;
    return height(p->left)-height(p->right);
}

void ClassInvertedIndex::balance(node *&p)
{
    int balance=getBalance(p);
    if (balance>1) //height(p->left)-height(p->right)
        {
            if (getBalance(p->left)>=0)
                SingleRightRotate(p);
            else
                LeftRightRotate(p);
        }
    else if (balance<-1) //height(p->left)-height(p->right)
        {
            if (getBalance(p->right)<=0)
                SingleLeftRotate(p);
            else
                RightLeftRotate(p);
        }
}

void ClassInvertedIndex::SingleLeftRotate(node *&p)
{
    node *temp;
    temp=p->right;
    p->right=temp->left;
    temp->left=p;
    p->height=MAX(height(p->left),height(p->right))+1;
    temp->height=MAX(p->height,height(temp->right))+1;
    p=temp;
}

void ClassInvertedIndex::RightLeftRotate(node *&p)
{
    SingleRightRotate(p->right);
    SingleLeftRotate(p);
}

void ClassInvertedIndex::SingleRightRotate(node *&p)
{
    node *temp;
    temp=p->left;
    p->left=temp->right;
    temp->right=p;
    p->height=MAX(height(p->left),height(p->right))+1;
    temp->height=MAX(p->height,height(temp->left))+1;
    p=temp;
}

void ClassInvertedIndex::LeftRightRotate(node *&p)
{
    SingleLeftRotate(p->left);
    SingleRightRotate(p);
}

unsigned int ClassInvertedIndex::MAX(unsigned int n1,unsigned int n2)
{
    if (n1>n2)
        return n1;
    else
        return n2;
}

void ClassInvertedIndex::add_neighbor(unsigned int ID,node *&p,bool &linkcheck,node *&SUBTREE)
{
    if (p==NULL)
        {
            p=new node;
            p->id=ID;
            p->height=0;
            p->left=NULL;
            p->right=NULL;
            linkcheck=true;
            SUBTREE->neighbors_size++;
        }
    else
        {
            if (ID<p->id)
                {
                    add_neighbor(ID,p->left,linkcheck,SUBTREE);
                    if (linkcheck)
                        balance(p);
                }
            else if (ID>p->id)
                {
                    add_neighbor(ID,p->right,linkcheck,SUBTREE);
                    if (linkcheck)
                        balance(p);
                }
            else
                linkcheck=false; // Link already exists.
        }
    p->height=MAX(height(p->left),height(p->right))+1;
}

void ClassInvertedIndex::Print_InOrder_SUBTREE(node *p,std::ofstream &outputfile) //InOrder gia tous gitones tou komvou
{
    if (p!=NULL)
        {
            Print_InOrder_SUBTREE(p->left,outputfile);
            outputfile<<", "<<p->id;
            Print_InOrder_SUBTREE(p->right,outputfile);
        }
}

node* ClassInvertedIndex::getMinValueNode(node *p) //Epistrofi tis diefthinsis mnimis tou elaxistou
{
    if (p==NULL)
        return p;
    if (p->left==NULL)
        return p;
    return getMinValueNode(p->left);
}

void ClassInvertedIndex::DELETE(unsigned int ID,node *&p,bool &deleted)
{
    if (p==NULL)
        return ;
    else
        {
            if (ID<p->id)
                DELETE(ID,p->left,deleted);
            else if (ID>p->id)
                DELETE(ID,p->right,deleted);
            else
                {
                    if ((p->left==NULL) && (p->right!=NULL)) //EXEI DEKSI PAIDI->REPLACE TON KOMVO ME DEKSI PAIDI
                        {
                            node *temp;
                            temp=p->right;
                            *p=*temp;
                            delete temp;
                            deleted=true;
                        }
                    else if ((p->right==NULL)  && (p->left!=NULL)) //EXEI ARISTERO PAIDI->REPLACE TON KOMVO ME ARISTERO PAIDI
                        {
                            node *temp;
                            temp=p->left;
                            *p=*temp;
                            delete temp;
                            deleted=true;
                        }
                    else if ((p->right==NULL)  && (p->left==NULL)) //DEN EXEI PAIDIA->APLA DELETE TON KOMVO
                        {
                            delete p;
                            p=NULL;
                            deleted=true;
                        }
                    else //EXEI DIO PAIDIA->REPLACE TON KOMVO I ME TO MIN TOU DEKSIA PAIDIOU I ME TO MAX TOU ARISTEROU PAIDIOU
                        {
                            node *temp=getMinValueNode(p->right); //
                            p->id=temp->id;                       //  REPLACE TON KOMVO ME TO MIN TOU DEKSIOU PAIDIOU
                            DELETE(temp->id,p->right,deleted);    //
                            deleted=true;
                        }
                }
        }
    if (p==NULL)
        return ;
    p->height=MAX(height(p->left),height(p->right))+1;
    balance(p);
}

void ClassInvertedIndex::deleteTree(node *&p) //DESTRUCTOR STIN OUSIA..
{
    if (p!=NULL)
        {
            deleteTree(p->left);
            deleteTree(p->right);
            delete p;
        }
    p=NULL;
}


