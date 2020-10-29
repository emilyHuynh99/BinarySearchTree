
#include <iostream>
#include <string>
#include <fstream>

using namespace std;
//!! right side is greater than, left side if less than OR EQUAL TO

/*
Algorithm:
    1. read in the initial villains values from the input
        properly place them into a tree
    2. generate combinations of attributes with read in max value of attributes
        look through tree
            if one of attribute of the combination is greater than a villain's it is a hero
            else it's a villain (if its greater than the highest villain combo, then it is a hero)
*/

template <class type>
struct binTreeNode
{
    type item;
    binTreeNode<type> *left, *right;
};

struct candidateType
{
    int strength;
    int awareness;
    int gadgetSkill;
    bool operator > (candidateType node1);
};

//insert function
//desc:this function must first compare the values passed in to the current values
    //to see where the newNode will be placed, if one value is greater than the other 
    //it should be placed to the right
//return: nothing
//parameter: pointer to root node, node to be insertted
// ? binTreeNode<candidateType>* do we need to retyrn type pointer to binTreeNode? and for what??
void insert(binTreeNode<candidateType> *mainNode, binTreeNode<candidateType> *newNode)// binary search tree
{
    //insertion is recursive? since we only call insert when we know a node needs to be insertted
    //we want to build a binary search tree, not just insert in the last placed node
    //therefore we need to traverse the nodes and compare to see where the values belong
    //right side, if one value is greater than the other, 
    //left side, if all values is less than those values

    //to insert we start at the root, look for an empty spot in the right place to 
    //add a new node

    //we can still utilize the preorderTraversal, if it returns true
    //then it belongs on the right side, else it belongs on the left side

    //this is an empty spot we've found and its where we'll place the 
    //new node

    //cout << "insert function" << endl;
    // ! still a huge work in progress, cases are not all considered for in recursive function
    if(mainNode != nullptr)
    {

        bool greaterThan = ((newNode -> item) > (mainNode -> item));
        //first you want to compare and see which side the new node belongs to
        if(greaterThan && (mainNode -> right == nullptr))
        {
            //if true then newNode belongs on right side so we check if right side of 
            //node is available
            /*cout << newNode -> item. strength << " " << newNode -> item.awareness << " " << newNode -> item.gadgetSkill;
            cout << " Inserted on the right side of node: " ;
            cout << mainNode->item.strength << " " << mainNode->item.awareness << " " << mainNode->item.gadgetSkill << endl;*/
            //if(rootNode -> right != nullptr)
             mainNode -> right = newNode;
             return; //only after insertion may you return 
            
        }
        else if(greaterThan && (mainNode -> right != nullptr))
        {
            return insert(mainNode -> right, newNode);
        }
        else if(!greaterThan && (mainNode -> left == nullptr))
        {
            /*cout << newNode -> item. strength << " " << newNode -> item.awareness << " " << newNode -> item.gadgetSkill;
            cout << " Inserted on the left side of node: " ;
            cout << mainNode->item.strength << " " << mainNode->item.awareness << " " << mainNode->item.gadgetSkill << endl;*/
            mainNode -> left = newNode;
            return;
        }
        else
        {
            return insert(mainNode -> left, newNode);
        }
    }
    else// if the mainNode passed in is null, which it shouldn't be because we should always have a root
    {
        cout << "insert function, node empty" << endl;
        cout << "bad returning...." << endl;
        return;
    }
}

//traversal function: attempting to compare all the values in the nodes to value of node passed, 
    // using flag instead of return
//parameters: pointer pointing to the root of the tree, node to be compared with, flag 
    //to determine whether node to be compared with is a villain or hero
//return: void
void traversal (binTreeNode<candidateType> *root, binTreeNode<candidateType> * pNode, bool &isVillain)
{
    //isVillain
    if(root != nullptr)
    {
        traversal(root -> left, pNode, isVillain);
        traversal(root -> right, pNode, isVillain);
        if(!((pNode->item) > (root->item)))
        {
            isVillain = true; 
            return;
        }
    }
    return;
}

//operator overloader: overloads the greater than operator to compare the values of two 
    //candidatesTypes
//parameter: object of candidateType(this) 'calling' the overloader(this function) and 
    //a passed in object of the same type to be compared with 
//return type: returns true if the obj that called the function is greater in the strength, 
    //awareness, or gadgetSkill aspect, anything that is less than or equal to returns a false
bool candidateType::operator > (candidateType node1) //invalid declaration, candidateType *node2
{
    /*cout << "operator overloader" << endl;
    //values that are completely equal will get insertted into the tree twice based on this algorithm
    cout << "caller strength: " << strength << " passed in strength: " << node1.strength << endl;
    cout << "caller awareness: " << awareness << " passed in awareness: " << node1.awareness << endl;
    cout << "caller gadgetSkill: " << gadgetSkill << " passed in gadgetSkill: " << node1.gadgetSkill << endl;*/
    if((this -> strength) > (node1.strength))
    {
        //cout << "returning true" << endl;
        return true;
    }
    
    else if((awareness) > (node1.awareness))
    {
        //cout << "returning true" << endl;
        return true;
    }
    else if((gadgetSkill) > (node1.gadgetSkill))
    {
        //cout << "returning true" << endl;
        return true; //these characteristics are indeed  of a hero's
    }
    else
    {
        //cout << "return false \n";
        return false; //and this candidate it a villain and belongs in the villain tree
    }
        
}

//deleteTree function: deallocates memory allocated to hold the binary tree through post order
    //traversal, thereby starting at the leaves and deallocating up 
//parameters: root pointing to the root of the binary tree
//return type: n/a
void deleteTree(binTreeNode<candidateType> *root)
{
    //cout << "tree deletion" << endl;
    if(root == nullptr) ///nothing to delete here
    {
        return;
    }
    else
    {
        //deleting root from the bottom up
        //in postorder way
        deleteTree(root -> left);
        deleteTree(root -> right);

        delete root; //this should delete the memory allocated to the root node as well
    }
}

int main()
{
    ifstream infile;
    string filename;
    int initialVillains, maxValue = 0;
    int heroes = 0;

    do
    {
        //prompting for input file name:
        cout << "Enter input file name: ";
        cin >> filename;

        infile.open(filename);
    }
    while(!infile.is_open());

    while(!infile.eof())
    {
        bool villain = true;
        infile >> initialVillains >> maxValue;

        //adding the initial(read in nodes)
        binTreeNode<candidateType> *root;
        binTreeNode<candidateType> *newNode;

        root = new binTreeNode<candidateType>;
        
        infile >> (root -> item).strength >> (root -> item).awareness >> (root -> item).gadgetSkill;   //very first node, read in 
        if(infile.eof())
        {
            delete root; //!important to delete bc ends up not being used but we declared using 'new'
            break; //and deallocate
        }
        root -> left = nullptr;
        root -> right = nullptr;
        //root = newNode; //root node

        //cout << "root " << (root -> item).strength << " " << (root -> item).awareness << " " << (root->item).gadgetSkill << endl;
        //current = newNode; //current now points to whatever newNode was pointing to
        //binTreeNode<candidateType> *tempRoot = root;

        for(int i = 0; i < initialVillains-1; i++) //this loops will read in the first villains
        {
            newNode = new binTreeNode<candidateType>;

            infile >> (newNode -> item).strength >> (newNode -> item).awareness >> (newNode -> item).gadgetSkill;   //reading in values for another node
            
            //then you want to compare, see if one value is bigger it belongs to the right, 
            newNode -> left = nullptr;
            newNode -> right = nullptr;
            
            insert(root, newNode);
            //we don't need to worry about deallocating any allocated memory(nodes) here 
            //bc all these nodes are the initial nodes and will be used(insertted)
        }
        
        //newNodes have a different pointer pointing to it so we can use newNode and current?
        //now we need to generate our combinations of values with maxValue
        for(int i = 1; i <= maxValue; i++)  //strength  ****THESE LOOPS WORK PROPERLY***
        {
            for(int j = 1; j <= maxValue; j++)  //awareness
            {
                for(int e = 1; e <= maxValue; e++) //gadgetSkil
                {
                    newNode = new binTreeNode<candidateType>;

                    (newNode -> item).strength = i;
                    (newNode -> item).awareness = j;
                    (newNode -> item).gadgetSkill = e;
                    newNode -> left = nullptr;
                    newNode -> right = nullptr;
                    
                    //compare the generated node values to all the values in the tree currently
                    traversal(root, newNode, villain);  
                    if(villain) //if this returns false
                    {
                        //false return means that we have found a villain
                        //we will need to insert it into the binary search tree
                        insert(root, newNode);
                    }
                    else
                    {
                        heroes++;
                        //!important to delete bc ends up not being used but we declared using 'new'
                        delete newNode; 
                    }
                    villain = false;    //resetting the villain flag
                }
            }
        }
        
        // ! dont forget to properly deallocate the binary tree
        deleteTree(root);
        //delete newNode;
        //delete root;

        cout << heroes << " heroes" << endl;
        heroes = 0;
    //end of loop reading in values from the input file here
    }


}
