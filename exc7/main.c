#include"Tree.h"
#include<time.h>
int main() {
    srand(time(NULL));
    Tree tree;
    (&tree)->root = 0;

    for (int i = 0; i < SIZE; i++) {
        KeyType some_key = GenerateString(SIZESTR);
        ValueType some_value = GenerateString(SIZESTR);

        InsertTreeValueByKey(&tree, some_key, some_value);
    }
    TreeNode* ptr = (&tree)->root->left;
    PrintTree((&tree)->root, 0);

    TreeDelete(&tree);
    return 0;
}