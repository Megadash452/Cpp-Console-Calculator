#include "Tree.h"
using lib::Tree;
using lib::Node;

Tree::Tree(string _name)
    : name(_name), first_node(new Node), used_node_ids(new std::vector<unsigned int>)
{
    this->first_node->set_used_ids(this, this->used_node_ids);
}

Tree::Tree(Tree& t)
    : name(t.name), first_node(new Node{ t.first_node }), used_node_ids(new std::vector<unsigned int>{ *t.used_node_ids })
{
}

Tree::~Tree()
{
    delete this->first_node;
    delete this->used_node_ids;
}

Node* lib::Tree::get_node_by_id(unsigned int _id)
{
    return this->first_node->get_child_by_id(_id);
}

/// --- Node ---

Node::Node()
    : id(0), parent(nullptr), used_ids(nullptr)
{

}

//Node::Node(Node* _parent)
//    : id(0), parent(_parent), used_ids(parent->access_used_ids_ptr(this))
//{
//    // increment id until
//    for (unsigned int id : *(this->used_ids))
//        this->id++;
//    this->id++;
//    this->used_ids->push_back(this->id);
//    /*for (this->id = 0; this->id < this->parent->children.size(); this->id++)
//        if (this->parent->children[this->id]->id != this->id)
//        {
//            break;
//        }*/
//}

//Node::Node(Node* _parent, int _id)
//    : id(-1), parent(_parent), used_ids(parent->access_used_ids_ptr(this))
//{
//    for (Node* child : this->parent->children)
//        if (child->id != _id)
//        {
//            this->id = _id;
//            return;
//        }
//}

Node::Node(Node& other)
    : id(other.id), parent(other.parent), used_ids(other.used_ids)
{
    // make a copy of each child (Node*)
    for (auto i = other.children.begin(); i != other.children.end(); i++)
    {
        this->children.push_back(new Node(**i));
    }
}

lib::Node::Node(Node* other)
    : id(other->id), parent(other->parent), used_ids(other->used_ids)
{
    // make a copy of each child (Node*)
    for (auto i = other->children.begin(); i != other->children.end(); i++)
    {
        this->children.push_back(new Node(*i));
    }
}

Node::~Node()
{
    for (Node* child : this->children)
        delete child;
}


Node* Node::append_child(Node* _child) // return Node*
{
    /*for (Node* child : this->parent->children)
        if (child->id == _child->id)
        {
            std::cout << "Cannot append Child Node id= <" << _child->id << "> because there already exists a child with that id" << std::endl;
        }*/

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

Node* lib::Node::get_child_by_id(unsigned int _id)
{ // Get child node if node->id matches the wanted id
    if (this->id == _id)
        return this;
    
    Node* target_node = nullptr;
    if (this->children.size() > 0)
        for (Node* child : this->children)
        {
            target_node = child->get_child_by_id(_id);
            if (target_node)
                return target_node;
        }
            
    return nullptr;
}

Node* lib::Node::get_parent()
{
    return this->parent;
}

Node* lib::Node::set_parent(Node* _parent)
{
    this->parent = _parent;
    for (this->id = 0; this->id < this->parent->children.size(); this->id++)
        if (this->parent->children[this->id]->id != this->id)
        {
            break;
        }
    return this;
}

std::vector<unsigned int> lib::Node::get_used_ids()
{
    return *(this->used_ids);
}

void lib::Node::set_used_ids(Tree* _key, std::vector<unsigned int>* vect)
{
    // find out if this node belongs to the _key
    this->used_ids = _key->used_node_ids;
}

void lib::Node::set_used_ids(Node* _key, std::vector<unsigned int>* vect)
{
    // find out if this node belongs to the _key
    if (this->parent == _key)
        this->used_ids = vect;
}

std::vector<unsigned int>* lib::Node::access_used_ids_ptr(Node* _key)
{
    // find out if this node belongs to the _key
    if (this->parent == _key)
        return this->used_ids;
    return nullptr;
}

std::vector<unsigned int>* lib::Node::access_used_ids_ptr(Tree* _key)
{
    // find out if this node belongs to the _key
    return nullptr;
}
