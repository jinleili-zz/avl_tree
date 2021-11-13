#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include "avl.h"


int max(int x,int y) {
    if(x==y){
        return x;
    }else{
        return x>y?x:y;
    }
}


struct avl_node *g_avl_root = NULL;

static int get_tree_height(struct avl_node *root)
{
    if(root==NULL)
    {
        return 0;
    }
    else
    {
        int x = get_tree_height(root->left);
        int y = get_tree_height(root->right); 
        return max(x,y);
    }
}

static int get_tree_balance_factor(struct avl_node *root)
{
    if(root==NULL)
    {
        return 0;
    }
    else
    {
        //return root->left->height - root->right->height;
        return get_tree_height(root->left) -  get_tree_height(root->right);
    }
}


static struct avl_node * tree_left_rotate(struct avl_node * node) 
{
    struct avl_node *right = node->right;

    node->right = right->left;
    right->left = node;
    
    return right;
}

static struct avl_node * tree_right_rotate(struct avl_node * node) 
{
    struct avl_node *left = node->left;
    struct avl_node *left_right_child = left->right;

    left->right = node;
    node->left = left_right_child;

    return left;    
}

static struct avl_node * tree_rebalance(struct avl_node *root) {
    int factor = get_tree_balance_factor(root);
    if(factor > 1 && get_tree_balance_factor(root->left) > 0) // LL
        return tree_right_rotate(root);
    else if(factor > 1 && get_tree_balance_factor(root->left) <= 0) { //LR
        root->left = tree_left_rotate(root->left);
        return tree_right_rotate(root);
    } else if(factor < -1 && get_tree_balance_factor(root->right) <= 0) // RR
        return tree_left_rotate(root);
    else if(factor < -1 && get_tree_balance_factor(root->right) > 0) { // RL
        root->right = tree_right_rotate(root->right);
        return tree_left_rotate(root);
    } else { // Nothing happened.
        return root;
    }
}




int insert_into_avl(struct avl_node **proot,int val)
{
    int ret;
    struct avl_node *root = *proot;

    if(root == NULL)
    {
        root =  (struct avl_node *)malloc(sizeof(struct avl_node));
        assert(root != NULL);
        memset(root,0,sizeof(struct avl_node));
        root->val = val;
        root->left = root->right = NULL;
    }
    else if(root->val == val)
    {
        return 0;
    }
    else 
    {
        if(root->val > val)
            ret = insert_into_avl(&root->left,val);
        else
            ret = insert_into_avl(&root->right,val);
    } 

    *proot = tree_rebalance(root);
    
    return 0;
}


void traverse_avl(struct avl_node *root)
{
    if(root != NULL)    
    {
        if(root->left!=NULL)
        {
            traverse_avl(root->left);            
        }
        printf("%d\n",root->val);
        if(root->right != NULL)
        {
            traverse_avl(root->right);
        }
    }
}

static int* generate_val_array(unsigned int count)
{
    int i = 0;
    int * array = (int*)malloc(sizeof(int)*count);
    assert(array);

    srand(time(0));

    for(i=0;i<count;i++)
    {
        array[i] = rand();
    }

    return array;
}


int main(int argc, char * argv[])
{
    int i,count;

    if(argc < 2)
    {
        exit(-1);
    }
    else
    {
        count = atoi(argv[1]);
        if(count <= 0)
        {
            exit(-2);
        }
    }

    int * data_array = generate_val_array(count);

    for(i=0;i<count;i++)
    {
        insert_into_avl(&g_avl_root,data_array[i]);
    }

    traverse_avl(g_avl_root);

    return 0;
}