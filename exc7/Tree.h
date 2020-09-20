#ifndef H_TREE
#define H_TREE
#define SIZESTR 10
#define SIZE 20
typedef char* KeyType;
typedef char* ValueType;
typedef struct _TreeNode {
    KeyType key;
    ValueType value;
    struct _TreeNode* left;
    struct _TreeNode* right;
    struct _TreeNode* parent;
} TreeNode;
typedef struct _Tree {
    TreeNode* root;
} Tree;
void InsertInTreeNode(Tree* tree, TreeNode* newNode);
TreeNode* InitTreeNode(KeyType key, ValueType value);
TreeNode* SearchValueByKey(Tree* tree, KeyType key);
ValueType GetValueByKey(Tree* tree, KeyType key);
void InsertTreeValueByKey(Tree* tree, KeyType key, ValueType value);
char* GenerateString(int size);
void FreeTreeNode(TreeNode* node);
void DeleteTreeNodeByKey(Tree* tree, KeyType key);
void PrintTree(TreeNode* root, int level);
void TreeDelete(Tree* tree);
#endif

