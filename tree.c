#include <stdio.h>
#include <stdlib.h>
#include "tree.h"

// A useful helper function for contains/find/insert.
// This returns the pointer to the node that matches the
// key or NULL if nothing matches.
tree_node *find_node(tree_node *t, const void *key, int (*comparison_fn)(const void *, const void *))
{
    if (t == NULL)
    {
        return NULL;
    }

    if (comparison_fn(t->key, key) > 0)
    {
        return find_node(t->left, key, comparison_fn);
    }
    if (comparison_fn(t->key, key) < 0)
    {
        return find_node(t->right, key, comparison_fn);
    }
    else
    {
        return t;
    }
}

// Allocates a new tree with the specified comparison function.
tree *new_tree(int (*comparison_fn)(const void *, const void *))
{
    (void)comparison_fn;
    tree *newtree = (tree*)malloc(sizeof(tree));
    if (newtree == NULL)
    {
        return NULL;
    }
    newtree->root = NULL; //Make sure to initalize data
    newtree->comparison_fn = comparison_fn;
    return newtree;
}

// Frees the the nodes, but does not free the keys
// or data (deliberately so).
void free_node(tree_node *t)
{
    (void)t;

    if (t == NULL)
    {
        return;
    }

    free_node(t->left);
    free_node(t->right);
    free(t);
}

// And frees the entire tree and the nodes
// but again, not the data or keys.
void free_tree(tree *t)
{
    (void)t;

    if (t == NULL)
    {
        return;
    }

    free_node(t->root);
    free(t);
}

// Returns true if the key (comparison == 0) is in the tree
bool contains(tree *t, const void *key)
{
    (void)t;
    (void)key;
     
    if (t == NULL)
    {
        return false;
    }

    tree_node *current = t->root;
    if (find_node(current, key, t->comparison_fn))
    {
        return true;
    }
    else
    {
        return false;
    } 
    
}

// Returns the data or NULL if the data is not in the tree.
void *find(tree *t, const void *key)
{
    (void)t;
    (void)key;
    if (t == NULL)
    {
        return NULL;
    }

    tree_node  *node = find_node(t->root, key, t->comparison_fn);
    if (node != NULL)
    {
        return node->data;
    }
    else
    {
        return NULL;
    }
}

// Inserts the element into the tree
void insert(tree *t, void *key, void *data)
{
    (void)t;
    (void)key;
    (void)data;


    tree_node *parent = NULL;
    tree_node *current = t->root;
    int cmp;

    while (current != NULL)
    {
        cmp = t->comparison_fn(current->key, key);

        if (cmp == 0)
        {
            current->data = data;
            return;
        }

        parent = current;
        if (cmp > 0)
        {
            current = current->left;
        }
        else
        {
            current = current->right;
        }

    }
 
    tree_node *node = (tree_node*)malloc(sizeof(tree_node));
    node->key = key;
    node->data = data;
    node->left = NULL;
    node->right = NULL;

    if (parent == NULL)
    {
        t->root = node;
    }
    else if (cmp > 0)
    {
        parent->left = node;
    }
    else
    {
        parent->right = node;
    }
}

// This visits every node in an in-order traversal,
// calling f on key, data, context.  Context is
// so that f has an ability to maintain its own state
// between calls.  This is a useful helper function for implemneting
// traverse
void traverse_node(tree_node *t, void (*f)(void *, void *, void *), void *context)
{
    (void)t;
    (void)f;
    (void)context;
    tree_node *current = t;

    if (current == NULL)
    {
        return;
    }

    traverse_node(current->left, f, context);
    f(current->key, current->data, context);
    traverse_node(current->right, f, context);

    return;

}

void traverse(tree *t, void (*f)(void *, void *, void *), void *context)
{
    (void)t;
    (void)f;
    (void)context;
    
    traverse_node(t->root, f, context);

    return;
}


 
