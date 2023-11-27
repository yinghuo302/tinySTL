/*
 * @Author: zanilia
 * @Date: 2022-03-29 15:50:20
 * @LastEditTime: 2022-03-29 23:12:56
 * @Descripttion: 
 */
#define RB_SET_RED 1
#define RB_SET_BLACK 0
template<class Key>
class Set{
    struct Node{
		Key key;
		bool color;
		Node* left;
		Node* right;
		Node* parent;
		RBTreeNode(const Key& _key,const Value& _val):key(_key),color(RB_SET_RED),left(NULL),right(NULL),parent(NULL){}
	};
	class Iterator;
	friend class Iterator;
    Node* root;
    static Node* search(Node* root,const Key& _key){
        while(root) {
            if(_key>root->key)
                root = root->right;
            else if( _key < root->key )
                root = root->left; 
            else 
                return root;
        }
        return NULL;
    }
    void insert(Node* node){
        if(!root){
            root = node;
            node->color = RB_SET_BLACK;
            return ;
        }
        Node *prev = NULL;
        Node *curr = root;
        while (curr){
            prev = curr;
            if (node->key < curr->key)
                curr = curr->left;
            else
                curr = curr->right;
        }
        node->parent = prev;
        if (node->key < prev->key)
            prev->left = node;
        else
            prev->right = node;      
        rbtree_insert_fixup(root, node);
    }
    static Node* minNode(Node* node){
        if(!node)
            return NULL;
        while(node->left)
            node = node->left;
        return node;
    }
    static Node* maxNode(Node* node){
        if(!node)
            return NULL;
        while(node->right)
            node = node->right;
        return node;
    }
    static void rbtree_insert_fixup(Node*& root,Node* node){
        Node *parent, *gparent;
        while ((parent=node->parent) &&parent->color==RB_SET_RED){
            gparent = parent->parent;
            if (parent == gparent->left){    
                Node *uncle = gparent->right;
                if(uncle&&uncle->color==RB_SET_RED){
                    uncle->color = RB_SET_BLACK;
                    parent->color = RB_SET_BLACK;
                    gparent->color = RB_SET_RED;
                    node = gparent;
                }
                else{ 
                    if(node==parent->right){
                        rbtree_left_rotate(root,parent);
                        Node* tem = parent;
                        parent = node;
                        node = tem;
                    }
                    parent->color = RB_SET_BLACK;
                    gparent->color = RB_SET_RED;
                    rbtree_right_rotate(root,gparent);
                }
            }
            else{
                Node *uncle = gparent->left;
                if (uncle && uncle->color==RB_SET_RED){
                    uncle->color = RB_SET_BLACK;
                    parent->color = RB_SET_BLACK;
                    gparent->color = RB_SET_RED;
                    node = gparent;
                }
                else{
                    if(node==parent->left){
                        rbtree_right_rotate(root,parent);
                        Node* tem = parent;
                        parent = node;
                        node = tem;
                    }
                    parent->color = RB_SET_BLACK;
                    gparent->color = RB_SET_RED;
                    rbtree_left_rotate(root,gparent);
                }
            }
        }
        root->color = RB_SET_BLACK;
    }
    static void rbtree_delete_fixup(Node* &root, Node *node, Node *parent){
        Node *other;
        while ((!node || node->color==RB_SET_BLACK) && node != root){
            if (parent->left == node){
                other = parent->right;
                if (other->color==RB_SET_RED){
                    other->color = RB_SET_BLACK;
                    parent->color = RB_SET_RED;
                    rbtree_left_rotate(root, parent);
                    other = parent->right;
                }
                if ((!other->left || other->left->color==RB_SET_BLACK) &&
                    (!other->right || other->right->color==RB_SET_BLACK)){
                    other->color=RB_SET_RED;
                    node = parent;
                    parent = node->parent;
                }
                else{
                    if (!other->right || other->right->color==RB_SET_BLACK){
                        other->left->color=RB_SET_BLACK;
                        other->color=RB_SET_RED;
                        rbtree_right_rotate(root, other);
                        other = parent->right;
                    }
                    other->color =  parent->color;
                    parent->color=RB_SET_BLACK;
                    other->right->color=RB_SET_BLACK;
                    rbtree_left_rotate(root, parent);
                    node = root;
                    break;
                }
            }
            else{
                other = parent->left;
                if (other->color==RB_SET_RED){
                    other->color=RB_SET_BLACK;
                    parent->color=RB_SET_RED;
                    rbtree_right_rotate(root, parent);
                    other = parent->left;
                }
                if ((!other->left || other->left->color==RB_SET_BLACK) &&
                    (!other->right || other->right->color==RB_SET_BLACK)){
                    other->color=RB_SET_RED;
                    node = parent;
                    parent = node->parent;
                }
                else{
                    if (!other->left || other->left->color==RB_SET_BLACK){
                        other->right->color=RB_SET_BLACK;
                        other->color=RB_SET_RED;
                        rbtree_left_rotate(root, other);
                        other = parent->left;
                    }
                    other->color = parent->color;
                    parent->color=RB_SET_BLACK;
                    other->left->color=RB_SET_BLACK;
                    rbtree_right_rotate(root, parent);
                    node = root;
                    break;
                }
            }
        }
        if (node)
            node->color = RB_SET_BLACK;
    }
    void rbtree_delete(Node *node){
        Node *child, *parent;
        int color;
        if (node->left&&node->right) {
            Node *replace = node;
            replace = replace->right;
            while (replace->left != NULL)
                replace = replace->left;
            if (node->parent){
                if (node->parent->left == node)
                    node->parent->left = replace;
                else
                    node->parent->right = replace;
            } 
            else 
                root = replace;
            child = replace->right;
            parent = replace->parent;
            color = replace->color;
            if (parent == node)
                parent = replace;
            else{
                if (child)
                    child->parent = parent;
                parent->left = child;
                replace->right = node->right;
                node->right->parent = replace;
            }
            replace->parent = node->parent;
            replace->color = node->color;
            replace->left = node->left;
            node->left->parent = replace;
            if (color == RB_SET_BLACK)
                rbtree_delete_fixup(root, child, parent);
            delete(node);
            return ;
        }
        if (node->left !=NULL)
            child = node->left;
        else 
            child = node->right;
        parent = node->parent;
        color = node->color;
        if (child)
            child->parent = parent;
        if (parent){
            if (parent->left == node)
                parent->left = child;
            else
                parent->right = child;
        }
        else
            root = child;
        if (color == RB_SET_BLACK)
            rbtree_delete_fixup(root, child, parent);
        delete(node);
    }
    static void rbtree_left_rotate(Node*& root, Node *node){
        Node *tem = node->right;
        node->right = tem->left;
        if (tem->left)
            tem->left->parent = node;
        tem->parent = node->parent;
        if (node->parent){
            if (node->parent->left == node)
                node->parent->left = tem; 
            else
                node->parent->right = tem;
        }
        else
            root = tem;
        tem->left = node;
        node->parent = tem;
    }
    static void rbtree_right_rotate(Node*& root, Node *node){
        Node *tem = node->left;
        node->left = tem->right;
        if (tem->right != NULL)
            tem->right->parent = node;
        tem->parent = node->parent;
        if (node->parent){
            if (node == node->parent->right)
                node->parent->right = tem;
            else
                node->parent->left = tem;
        }
        else
            root = tem; 
        tem->right = node;
        node->parent = tem;
    }
public:
    void insert(const Key& _key){
        Node* node = new Node(_key);
        insert(node);
    }
    bool find(const Key& _key,Value & _val){
        Node* node = search(root,_key);
        if(node){
            _val = node->val;
            return true;
        }
        return false;
    }
    void erase(const Key& _key){
        Node* node = search(root,_key);
        if(node)
            rbtree_delete(node);
    }
	class Iterator{
        Node* ptr;
    public:
        friend class Set<Key>;
        typedef Key value_type;
        Iterator() = delete;
        Iterator(Node* p):ptr(p){}
        Iterator(const Iterator&) = default;
        Iterator& operator++(){
            if(ptr->right){
                ptr = ptr->right;
                while(ptr->left)
                    ptr = ptr->left;
                return *this;
            }
            Node* p = ptr->parent;
            while(ptr==p->right){
                ptr = p;
                p =  p->parent;
            }
            if(ptr->right==p)
                ptr = p;
            return *this;
        }
        Iterator& operator--(){

        }
        bool operator==(const Iterator& i){
            return ptr==i.ptr;
        }
        bool operator!=(const Iterator& i){
            return ptr!=i.ptr;
        }
        value_type& operator*(){
            return ptr->key;
        }
        value_type* operator->(){
            return &(ptr->key);
        }
	};
};