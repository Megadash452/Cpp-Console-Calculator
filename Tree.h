#pragma once
#include <string>
#include <vector>
#include <exception>
using std::string;

namespace lib {
    struct Tree;
    struct Node {
        Node();
        //Node(int _id);
        //Node(Node* _parent);
        //Node(Node* _parent, int _id);
        Node(Node&);
        Node(Node*);
        ~Node();

        template<typename N_type>
        N_type* append_child(N_type* _child)
        {
            _child->set_parent(this);
            _child->set_used_ids(this, this->used_ids);
            if (!_child->id)
            {
                for (unsigned int id : *(this->used_ids))
                    _child->id++;
                _child->id++;
                this->used_ids->push_back(_child->id);
            }
            this->children.push_back(_child);
            return _child;
        }
        //template<typename N_type>
        Node* get_child_by_id(unsigned int _id);

        Node* get_parent();
        std::vector<Node*> get_siblings();
        Node* set_parent(Node* _parent);

        std::vector<unsigned int> get_used_ids();
        void set_used_ids(Tree* _key, std::vector<unsigned int>*);
        void set_used_ids(Node* _key, std::vector<unsigned int>*);
        std::vector<unsigned int>* access_used_ids_ptr(Node* _key);
        std::vector<unsigned int>* access_used_ids_ptr(Tree* _key);

        unsigned int id;
        std::vector<Node*> children;
    protected:
        Node* parent;
        std::vector<unsigned int>* used_ids;
    };

    struct Tree {
        Tree();
        Tree(string _name);
        Tree(Tree&);
        ~Tree();

        Node* get_node_by_id(unsigned int _id);

        string name;
        Node* first_node;
        std::vector<unsigned int>* used_node_ids;
    };

    
}