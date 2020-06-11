/* 
 * Author: Savvas Theofilou
 */

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string>
#include "ClassInvertedIndex.h"

int main()
{
    std::ifstream c,i;
    std::ofstream w;
    bool link_check=false;
    unsigned int ID,link_to,line=1;
    std::string command,input,output;
    ClassInvertedIndex tree;
    c.open("commands.txt",std::ios::in);
    if (!c)
        {
            std::cout<<"Error while opening commands file!\nPress Enter to exit program..";
            getchar();
            exit(0);
        }
    c>>command;
    if (command!="READ_DATA")
        {
            std::cout<<"No 'READ_DATA' command was found!Check your commands file!\nPress Enter to exit program..";
            getchar();
            exit(0);
        }
    c>>input;
    std::cout<<"Reading "<<input<<".."<<std::endl;
    i.open(input.c_str(),std::ios::in);
    if (!i)
        {
            std::cout<<"Error while opening input file!\nPress Enter to exit program..";
            getchar();
            exit(0);
        }
    while (1)   // INPUT FILE READING AND CREATION OF AVL TREE
        {
            unsigned int n1,n2; // 2 while etsi wste na min dimiourgei se ka8e perasma n1 kai n2 kai
            while (!i.eof())    // otan teleiwsei na diagrafoun oi metavlites n1,n2.
            {
                i>>n1>>n2;
                tree.INSERT(n1,tree.get_root(),n2,link_check);
            }
            break;
        }       // END OF INPUT READING
    i.close();
    std::cout<<"Processing.."<<std::endl;
    while (1) //READING OF COMMANDS FILE INSERT-DELETE-WRITE TO OUTPUT
        {
            c>>command;
            line++;
            if (command=="WRITE_INDEX")
                {
                    c>>output;
                    w.open(output.c_str(),std::ios::out);
                    if (!w)
                        {
                            std::cout<<"Error while creating output file!\nPress Enter to exit program..";
                            getchar();
                            exit(0);
                        }
                    std::cout<<"Printing to "<<output<<".."<<std::endl;
                    tree.Print_InOrder(tree.get_root(),w);
                    w.close();
                    exit(0);
                }
            else if (command=="INSERT_LINK")
                {
                    c>>ID>>link_to;
                    if ((ID<0) || (link_to<0))
                        {
                            std::cout<<"A negative number was found in an 'INSERT_LINK' command in line "<<line<<"!Check your commands file!\nPress Enter to exit program..";
                            getchar();
                            exit(0);
                        }
                    tree.INSERT(ID,tree.get_root(),link_to,link_check);
                    if (!link_check)
                        std::cout<<"There was an error in line "<<line<<", the link already exists! Ignoring.."<<std::endl;

                }
            else if (command=="DELETE_LINK")
                {
                    c>>ID>>link_to;
                    if ((ID<0) || (link_to<0))
                        {
                            std::cout<<"A negative number was found in a 'DELETE_LINK' command in line "<<line<<"!Check your commands file!\nPress Enter to exit program..";
                            getchar();
                            exit(0);
                        }
                    tree.delete_link(ID,tree.get_root(),link_to);
                }
            else
                {
                    std::cout<<"There was an error with the command in line "<<line<<"!Check your commands file!\nPress Enter to exit program..";
                    getchar();
                    exit(0);
                }
        }
    return 0;
}


