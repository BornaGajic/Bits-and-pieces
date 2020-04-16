#ifndef B_TREE_HPP
#define B_TREE_HPP

class Node;

class B_Tree
{
    Node* root;
    int min_degree;

    public:
        B_Tree (Node* root_node, int degree);

        void InsertElement (int element);
        void Search (int element);
        void DeleteElement (int element);

        Node* get_root () const;
    
    private:
        void split_();
};

#endif