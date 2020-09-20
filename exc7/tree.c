#include"Tree.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
void PrintTree(TreeNode* root, int level) {//классический рекурсивный вывод дерева
    if (root)
    {
        PrintTree(root->left, level + 1); //сначала левые части
        for (int i = 0; i < level; i++) {
            printf("\t");
        }
        puts(root->key);
        PrintTree(root->right, level + 1); //потом правые
    }
}
TreeNode* InitTreeNode(KeyType key, ValueType value) {//инициализация Tree
    TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
    node->key = key;
    node->value = value;
    return node;
}
TreeNode* SearchValueByKey(Tree* tree, KeyType key) {
    TreeNode* currentNode = tree->root;
    if (tree->root == NULL) {
        return NULL;
    }
    short flag = strcmp(tree->root->key, key);
    while (flag) {
        if (flag > 0) {//currentNode->key > key
            currentNode = currentNode->left;
        }
        else if (flag < 0) {
            currentNode = currentNode->right;
        }
        else {
            break;
        }
        if (currentNode == NULL || currentNode->key == NULL) {
            break;
        }
        flag = strcmp(currentNode->key, key);
    }
    return currentNode;
}
ValueType GetValueByKey(Tree* tree, KeyType key) {

    TreeNode* node = SearchValueByKey(tree, key);
    if (node) {
        return node->value;
    }
    else {
        return NULL;
    }

}
void InsertInTreeNode(Tree* tree, TreeNode* newNode) {//вставка подчасти дерева с информацией в дерево
    TreeNode* currentNode = tree->root;
    if (currentNode == 0) {
        tree->root = newNode;
        newNode->left = 0;
        newNode->right = 0;
        newNode->parent = 0;
        return 0;
    }
    while (1) {
        if (strcmp(currentNode->key, newNode->key) > 0) {//сравнение двух строк: Левая больше Правой строки?
            if (currentNode->left != 0) {
                currentNode = currentNode->left;
            }
            else {
                currentNode->left = newNode;
                newNode->left = 0;
                newNode->right = 0;
                newNode->parent = currentNode;
                return 0;
            }


        }
        else {
            if (currentNode->right != 0) {
                currentNode = currentNode->right;
            }
            else {
                currentNode->right = newNode;
                newNode->left = 0;
                newNode->right = 0;
                newNode->parent = currentNode;
                return 0;
            }
        }
    }
}
void InsertTreeValueByKey(Tree* tree, KeyType key, ValueType value) {//вставка ассоциативного элемента в дерево по ключу
    TreeNode* node = InitTreeNode(key, value);
    InsertInTreeNode(tree, node);
}
char* GenerateString(int size) {//моя обычная генерация строки из алфавита строчных букв
    char Arr[26] = "abcdefghijklmnopqrstuvwxyz";
    char* someKey = (char*)malloc((size + 1) * sizeof(char));
    for (int i = 0; i < size; i++) {
        someKey[i] = Arr[rand() % 26];
    }
    someKey[size] = 0;
    return someKey;
}
void FreeTreeNode(TreeNode* node){ //высвобождение памяти подчасти дерева
    free(node->key);
    free(node->value);
    free(node);
}
void DeleteTreeNodeByKey(Tree* tree, KeyType key) {   
 //используем поиск по ключу, выполняем условия:  если left и right указывают на NULL, то это крайний и его надо стереть, если всего лишь один 
 //из указателей равен 0, то кидаем родителю ссылку на следующий элемент, а следующий на родителя если не крайний узел - заходим по ссылке в
 //правое поддерево и ищем минимальный элемент и его ставим на место удаляемого
    TreeNode* trash = SearchValueByKey(tree, key);
    if (trash == NULL) {
        return 0;
    }
    if (trash->left == NULL && trash->right == NULL) {
        if (trash->parent != NULL) {
            if (trash->parent->left == trash) {
                trash->parent->left = NULL;
            }
            else {
                trash->parent->right = NULL;
            }
        }
        else {
            tree->root = NULL;
        }
    }
    else if (trash->left == NULL || trash->right == NULL) {
        if (trash->parent == NULL) {
            if (trash->left == NULL) {//есть элемент справа
                tree->root = trash->right;
                trash->right->parent = 0;
            }
            else {//есть элемент слева
                tree->root = trash->left;
                trash->left->parent = 0;
            }
        }
        else {
            if (trash->left == NULL) {//есть элемент справа
                if (trash->parent->left == trash) {
                    trash->parent->left = trash->right;
                    trash->right->parent = trash->parent;
                }
                else {
                    trash->parent->right = trash->right;
                    trash->right->parent = trash->parent;
                }
            }
            else {//åñòü ýëåìåíò ñëåâà
                if (trash->parent->left == trash) {
                    trash->parent->left = trash->left;
                    trash->left->parent = trash->parent;
                }
                else {
                    trash->parent->right = trash->left;
                    trash->left->parent = trash->parent;
                }
            }
        }
    }
    else {
        TreeNode* currentNode = trash->right;
        while (currentNode->left != NULL) {
            currentNode = currentNode->left;
        }
        if (currentNode != trash->right) {
            currentNode->parent->left = NULL;
            currentNode->left = trash->left;
            currentNode->right = trash->right;
        }
        else {
            currentNode->left = trash->left;
        }


        if (trash->parent != NULL) {
            currentNode->parent = trash->parent;
            if (trash->parent->left == trash) {
                trash->parent->left = currentNode;
            }
            else {
                trash->parent->right = currentNode;
            }
        }
        else {
            currentNode->parent = 0;
            tree->root = currentNode;
        }
    }
    FreeTreeNode(trash);
}
void TreeDelete(Tree* tree) {//деструктор Tree
    while (tree->root) {//удалим всё используя поиск по ключу, подставка текущего ключа означает удлаение текущей подчасти дерева
        DeleteTreeNodeByKey(tree, tree->root->key);
    }
}
