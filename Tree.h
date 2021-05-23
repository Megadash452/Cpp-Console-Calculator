#pragma once
#include "Lib.h"

namespace lib {
    struct Node {
        Node();
        //Node(int _id);
        Node(Node* _parent);
        //Node(Node* _parent, int _id);
        ~Node();

        Node* append_child(Node* _child); // return Node*
        Node* get_child_by_id(unsigned int _id);

        Node* get_parent();
        Node* set_parent(Node* _parent);

        std::vector<unsigned int> get_used_ids();
        void set_used_ids(Tree* _key, std::vector<unsigned int>*);
        void set_used_ids(Node* _key, std::vector<unsigned int>*);
        std::vector<unsigned int>* access_used_ids_ptr(Node* _key);
        std::vector<unsigned int>* access_used_ids_ptr(Tree* _key);

        unsigned int id;
        std::vector<Node*> children;
    private:
        Node* parent;
        std::vector<unsigned int>* used_ids;
    };

    struct Tree {
        Tree(string _name);
        Tree(Tree&);
        ~Tree();

        Node* get_node_by_id(unsigned int _id);

        string name;
        Node* first_node;
        std::vector<unsigned int>* used_node_ids;
    };
}