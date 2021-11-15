#ifndef __AVL_H__
#define __AVL_H__

struct avl_node{
    struct avl_node *left;
    struct avl_node *right;
    int height;
    int val;
};

int insert_into_avl(struct avl_node **root,int val);

int delete_from_avl(struct avl_node *root, int val);

void traverse_avl(struct avl_node *root);

int find_val_from_avl(struct avl_node *root, int val);

int search_in_avl(struct avl_node *root, int val);

#endif