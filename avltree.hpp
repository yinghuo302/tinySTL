/*
 * @Author: zanilia
 * @Date: 2021-11-23 10:48:07
 * @LastEditTime: 2022-08-26 10:24:39
 * @Descripttion: 
 */
template<class ValueType>
class AVLTreeNode{
public:
    ValueType val;
    AVLTreeNode<ValueType>* left;
    AVLTreeNode<ValueType>* right;
    int height;
    AVLTreeNode(const ValueType& _val):val(_val),left(NULL),right(NULL),height(0){}
    AVLTreeNode():left(NULL),right(NULL),height(0){}
    AVLTreeNode(const ValueType& _val,int _height):left(NULL),right(NULL),height(_height),val(_val){}
};
static inline int max(int a,int b){
	return (a>b)? a:b;
}
template<class ValueType>
class AVLTree{
    typedef AVLTreeNode<ValueType> TreeNode;
private:
    TreeNode* root;
    static inline int getHeight(TreeNode* node){
        if(node)
            return node->height;
        return 0;
    }
    static TreeNode* minNode(TreeNode* node){

    }
    static TreeNode* maxNode(TreeNode* node){
        
    }
    static TreeNode* RRotate(TreeNode* node){
        TreeNode* tem = node->left;
        node->left = tem->right;
        tem->right = node;
        node->height = max(getHeight(node->left),getHeight(node->right))+1;
        tem->height = max(getHeight(tem->left),getHeight(tem->right)) + 1;
        return tem;
    }
    static TreeNode* LRotate(TreeNode* node){
        TreeNode* tem = node->right;
        node->right = tem->left;
        tem->left = node;
        node->height = max(getHeight(node->left),getHeight(node->right))+1;
        tem->height = max(getHeight(tem->left),getHeight(tem->right)) + 1;
        return tem;
    }
    static TreeNode* LRRotate(TreeNode* node){
        node->left = LRotate(node->left);
        return RRotate(node);
    }
    static TreeNode* RLRotate(TreeNode* node){
        node->right = RRotate(node->right);
        return LRotate(node);
    }
    static TreeNode* insert(TreeNode* node,const ValueType& value){
        if(!node)
            node = new TreeNode(value);
        else if(value<node->val){
            node->left = insert(node->left,value);
            if(getHeight(node->left)-getHeight(node->right)==2)
                if(value<node->left->val)
                    node = RRotate(node);
                else
                    node = LRRotate(node);
        }
        else{
            node->right = insert(node->right,value);
            if(getHeight(node->right)-getHeight(node->left)==2)
                if(value<node->right->val)
                    node = RLRotate(node);
                else
                    node = LRotate(node);
        }
        node->height = max(getHeight(node->left),getHeight(node->right));
        return node;    
    }
    static TreeNode* pop(TreeNode* node,const ValueType& value){
        if(!root)
            return NULL;
        if(value<node->val){
            node->left = pop(node->left,value);
            if(getHeight(node->right)-getHeight(node->left)==2)
                if(value<node->left->val)
                    node = LRRotate(node);
                else
                    node = LLRotate(node);
        }
        else if(value>node->val){
            node->right = pop(node->right,value);
            if(getHeight(node->left)-getHeight(node->right)==2)
                if(value<node->right->val)
                    node = RRRatate(node);
                else
                    node = RLRotate(node);
        }
        else{
            if (root->left && root->right){
                if (getHeight(root->left) > getHeight(tree->right)){
                    TreeNode *m = maxNode(tree->left);
                    tree->key = m->key;
                    tree->left = pop(tree->left, m->val);
                }
            } else{
                Node *min = avltree_maximum(tree->right);
                tree->key = min->key;
                tree->right = delete_node(tree->right, min);
            }
        }else{
            Node *tmp = tree;
            tree = tree->left ? tree->left : tree->right;
            free(tmp);
        }
        node->height = max(getHeight(node->left),getHeight(node->right));
        return node;
    }
public:
    void push(const ValueType& value){
        root = insert(root,value);
    }
    void pop(const ValueType& value){
        root = pop(root,value);
    }
    bool find(const ValueType& value){
        if(!root)
            return false;
        TreeNode* node = root;
        while(node){
            if(value<node->val)
                node = node->left
            else if(value>node->val)
                node = node->right;
            else
                return true;
        }
        return false;
    }
    const ValueType& minElement(){
        if(!root)
            throw 0;
        TreeNode *tem = root;
        while(tem->left)
            tem = tem->left;
        return tem->val;
    }
    const ValueType& maxElement(){
        if(!root)
            throw 0;
        TreeNode *tem = root;
        while(tem->right)
            tem = tem->right;
        return tem->val;
    }
    bool empty(){
        return root;
    }
};