#include <inttypes.h>   /* for uintptr_t */
#include <assert.h>
#include <stdbool.h>

typedef struct _avl_tree_node
{
    struct _avl_tree_node *left;
    struct _avl_tree_node *right;
    uintptr_t parent_balance;

    int value;
    int height;
} avl_tree_node;

static inline avl_tree_node *
avl_get_parent(avl_tree_node *node)
{
    return (avl_tree_node *)(node->parent_balance & ~3);
}

static inline void
avl_adjust_balance_factor(avl_tree_node *node, int amount)
{
    node->parent_balance += amount;
}

static inline int
avl_get_balance_factor(avl_tree_node *node)
{
    return (int)(node->parent_balance & 3) - 1; 
}

static inline int
avl_cmp(avl_tree_node *node1, avl_tree_node *node2)
{
   return (node1->value - node2->value);
}

static inline avl_tree_node *
avl_get_min(avl_tree_node *node1, avl_tree_node *node2)
{
   return (node1->value - node2->value > 0) ? node2 : node1;
}

static avl_tree_node *
avl_tree_make_node(int value)
{
    avl_tree_node *node = malloc(sizeof(avl_tree_node));
    assert(node != NULL);
    node->left = NULL;
    node->right = NULL;
    node->parent_factor = 0;
    node->value = value;
    node->height = 1;
}

/*
 * 1.
 *               p                     p
 *               |                     |
 *               a                     b
 *              / \                  /   \
 *             b   A?        =>     c     a
 *            / \                  / \   / \
 *           c   B?               C?  D?B?  A?
 *          / \
 *         C?  D?
 *
 * 2.
 *               p                     p
 *               |                     |
 *               a                     b
 *              / \                  /   \
 *             A?  b         =>     a     c
 *                / \              / \   / \
 *               B?  c            A?  B?C?  D?
 *                  / \
 *                 C?  D?   
 *
 * 3.
 *               p                     p
 *               |                     |
 *               a                     c
 *              / \                  /   \
 *             b   A?        =>     b     a
 *            / \                  / \   / \
 *           B?  c                B?  C?D?  A?
 *              / \
 *             C?  D?       
 *
 * 4.
 *               p                     p
 *               |                     |
 *               a                     c
 *              / \                  /   \
 *             A?  b         =>     a     b
 *                / \              / \   / \
 *               c   B?           A?  C?D?  B?
 *              / \
 *             C?  D?       
 *
 */
static avl_rotate(avl_tree_node * root, int type)
{
    /* a b c */
    avl_tree_node *min, *mid, *max;
    /* A B C D */
    avl_tree_node *one, *two, *three, *four;

    avl_tree_node *p = avl_get_parent(root); 
    switch(type)
    {
        case 0x11:
            min = root->left->left;
            mid = root->left;
            max = root;
            one = root->left->left->left;
            two = root->left->left->right;
            three = root->left->right;
            four = root->right;
            break;
        case 0x01:
            min = root;
            mid = root->right;
            max = root->right->right;
            one = root->left;
            two = root->right->left;
            three = root->right->right->left;
            four = root->right->right->right;
            break;
        case 0x00:
            min = root->left;
            mid = root->left->right;
            max = root;
            one = root->left->left;
            two = root->left->right->left;
            three = root->left->right->right;
            four = root->right;
            break;
        case 0x10:
            min = root;
            mid = root->right->left;
            max = root->right;
            one = root->left;
            two = root->right->left->left;
            three = root->right->left->right;
            four = root->right->right;
            break;
    }

    mid->parent_factor = p;
    if(c == p->left)
        p->left = mid;
    else
        p->right = mid;
    mid->left = min;
    mid->right = max;
    min->parent_factor = mid;
    max->parent_factor = mid;
    
    min->left = one;
    one->parent_factor = min;
    min->right = two;
    two->parent_factor = min;

    max->left = three;
    three->parent_factor = max;
    max->right = four;
    four->parent_factor = max;

    return;
}

void
avl_tree_handle_subtree_growth(avl_tree_node *node, avl_tree_node *parent, const int sign)
{
    int old_balance_factor, new_balance_factor;

    old_balance_factor = avl_get_balance_factor(parent);

    if(old_balance_factor == 0)
    {
        avl_adjust_balance_factor(parent, sign);
        return false;
    }

    new_balance_factor = old_balance_factor + sign;
    if(new_balance_factor == 0)
    {
        avl_adjust_balance_factor(parent, sign);
        return true;
    }

    if(sign * avl_get_balance_factor(node) > 0)
    {
        avl_rorate(node);
    }
}

void 
avl_tree_rebalance_after_insert(avl_tree_node *root, avl_tree_node *inserted)
{
    avl_tree_node *node, *parent;
    bool done;

    node = inserted;
    parent = avl_get_parent(node);
    if(parent == NULL)
        return;

    if(node == parent->left)
        avl_adjust_balance_factor(parent, -1); 
    else
        avl_adjust_balance_factor(parent, +1); 
    
    if(avl_get_balance_factor(parent) == 0)
        return;

    do
    {
        node = parent;
        parent = avl_get_parent(node);
        if(parent == NULL)
            return;

        if(node == parent->left)
            done = avl_handle_subtree_growth(node, parent, -1);
        else
            done = avl_handle_subtree_growth(node, parent, +1);
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
    *next->parent_balance = (uintptr_t)cur_ptr | 1;
    avl_tree_rebalance_after_insert(root, *next);
    return NULL;
}
