#include "binary_trees.h"

static int _is_perfect(const binary_tree_t *tree)
{
    int left, right;

    if (!tree)
        return (0);
    left = _is_perfect(tree->left);
    right = _is_perfect(tree->right);
    if (left == -1 || right == -1 || left != right)
        return (-1);
    return (left + 1);
}

static heap_t *_first_parent(heap_t *tree)
{
    int left, right;

    if (!tree)
        return (NULL);
    left = _is_perfect(tree->left);
    right = _is_perfect(tree->right);
    if (!tree->left || !tree->right || left != right)
        return (tree);
    return (_first_parent(tree->left));
}

heap_t *_heapify(heap_t *node)
{
    heap_t *tmp;

    while (node->parent && node->n > node->parent->n)
    {
        tmp = node->parent;
        node->parent = tmp->parent;
        tmp->parent = node;
        if (node->left)
            node->left->parent = tmp;
        if (node->right)
            node->right->parent = tmp;
        if (tmp->left && tmp->left != node)
            tmp->left->parent = node;
        if (tmp->right && tmp->right != node)
            tmp->right->parent = node;
        if (node->parent)
        {
            if (node->parent->left == tmp)
                node->parent->left = node;
            else
                node->parent->right = node;
        }
        tmp->left = (tmp->left == node) ? tmp->left->left : tmp->left;
        tmp->right = (tmp->right == node) ? tmp->right->right : tmp->right;
        node->left = (node->left == tmp) ? node->left : tmp;
        node->right = (node->right == tmp) ? node->right : tmp;
    }
    return (node);
}

heap_t *heap_insert(heap_t **root, int value)
{
    heap_t *node, *parent;

    if (!root)
        return (NULL);
    node = binary_tree_node(NULL, value);
    if (!*root)
        return (*root = node);
    parent = _first_parent(*root);
    if (!parent->left)
        parent->left = node;
    else
        parent->right = node;
    node->parent = parent;
    return (_heapify(node));
}
