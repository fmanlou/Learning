#include <inttypes.h>   /* for uintptr_t */
#include <assert.h>
#include <stdbool.h>

typedef struct _avl_tree_node
{
    struct _avl_tree_node *left;
    struct _avl_tree_node *right;
    struct _avl_tree_node *parent;

    int value;
    int height;
} avl_tree_node;

static avl_tree_node *
avl_tree_make_node(int value)
{
    avl_tree_node *node = malloc(sizeof(avl_tree_node));
    assert(node != NULL);
    node->left = NULL;
    node->right = NULL;
    node->parent = NULL;
    node->value = value;
    node->height = 1;
}

static void 
avl_rotate(avl_tree_node * node)
{
    /* a b c */
    avl_tree_node *a, *b, *c;

    a = node;
    if(node->left->height > node->right->height)
    {
        if(node->left->left->height > node->left->right->height)
        {
            /*       a               b
             *      / \            /   \
             *     b   A?  =>     c     a
             *    / \            / \   / \
             *   c   B?         C?  D?B?  A?
             *  / \
             * C?  D?
             */
            b = a->left;
            c = b->left;

            b->parent = a->parent;
            a->parent = b;

            a->left = b->right;
            b->right->parent = a;
            b->right = a;
        }
        else
        {
            /*      a            c
             *     / \         /   \
             *    b   A? =>   b     a
             *   / \         / \   / \
             *  B?  c       B?  C?D?  A?
             *     / \
             *    C?  D?
             */
            b = a->left;
            c = b->right;

            c->parent = a->parent;

            b->right = c->left;
            c->left->parent = b;

            a->left = c->right;
            c->right->parent = a;

            c->left = b;
            c->right = a;
        }
    }
    else
    {
        if(node->right->right->height > node->right->left->height)
        {

            /*   a                  b
             *  / \               /   \
             * A?  b      =>     a     c
             *    / \           / \   / \
             *   B?  c         A?  B?C?  D?
             *      / \
             *     C?  D?   
             */
            b = a->right;
            c = b->right;

            b->parent = a->parent;
            a->right = b->left;
            a->right->parent = a;
            b->left = a;
            a->parent = b;
        }
        else
        {
            /*   a                c
             *  / \             /   \
             * A?  b    =>     a     b
             *    / \         / \   / \
             *   c   B?      A?  C?D?  B?
             *  / \
             * C?  D?  
             */
            b = a->right;
            c = b->left;

            c->parent = a->parent;
        }
    }

    return;
}

static inline bool
avl_balance_check(avl_tree_node *node)
{
    int diff = node->left->height - node->right->height;
    return (diff != 2 && diff != -2);
}

static inline int
avl_get_left_subtree_height(avl_tree_node *node)
{
    return (node->left != NULL) ? node->left->height : 0;
}

static inline int
avl_get_right_subtree_height(avl_tree_node *node)
{
    return (node->right != NULL) ? node->right->height : 0;
}

void 
avl_tree_rebalance_after_insert(avl_tree_node *root, avl_tree_node *inserted)
{
    avl_tree_node *node;
    bool done;

    node = inserted->parent;

    do
    {
        node = node->parent;
        /* This node is root node */
        if(node == NULL)
            return;
        /* Height has not been changed */
        if(avl_get_left_subtree_height(node) == avl_get_right_subtree_height(node))
            return;
        node->height++;

        /* If this node's height is unbalanced,
         * we rotate this node. That will make 
         * parent height minus 1 and tree is balanced.
         */
        if(avl_balance_check(node) == false)
        {
            avl_rotate(node);
            done = true;
        }
    } while(!done);
}

avl_tree_node *
avl_tree_insert(avl_tree_node *root, int value)
{
    avl_tree_node **next = &root, *cur_ptr = NULL;
    int res;

    if(root == NULL)
        return NULL;

    while(*next != NULL)
    {
        cur_ptr = *next;
        res = cur_ptr->value - value;
        if(res < 0)
            next = &cur_ptr->left;
        else if(res > 0)
            next = &cur_ptr->right;
        else
            return cur_ptr;
    }

    *next = avl_tree_make_node(value);
    avl_tree_rebalance_after_insert(root, *next);
    return NULL;
}

void 
avl_tree_rebalance_after_remove(avl_tree_node *root, avl_tree_node *node)
{

}

void
avl_tree_remove(avl_tree_node *root, avl_tree_node *node)
{
    avl_tree_node *successor;

	if(node->right == NULL)
	{
		successor = node->left;
	}
	else
	{
		successor = node->right;
		while(successor->left != NULL)
			successor = successor->left;
		if(successor->right != NULL)
		{
			if(successor == successor->parent->left)
				successor->parent->left = successor->right;
			else
				successor->parent->right = successor->right;

			successor->right->parent = successor->parent;
			successor->right->left = successor;
			successor->parent = successor->right;
			successor->right = NULL;
		}
	}

	if(successor == NULL)
	{
		free(node);
		return;
	}

	/* replace node with successor */
	if(node->parent != NULL)
	{
		if(node == node->parent->left)
			node->parent->left = successor;
		else
			node->parent->right = successor;
	}

	if(successor->parent != NULL)
	{
		if(successor == successor->parent->left)
			successor->parent->left = NULL;
		else
			successor->parent->right = NULL;
		
	}
	successor->parent = node->parent;
	successor->left = node->left;
	successor->right = node->right;
	successor->height = node->height;

	avl_tree_rebalance_after_remove(root, parent);
}
