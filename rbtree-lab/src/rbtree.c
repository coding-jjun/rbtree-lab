#include "rbtree.h"

#include <stdio.h>
#include <stdlib.h>

rbtree *new_rbtree(void) {
  // TODO: initialize struct if needed
  rbtree *p = (rbtree *)calloc(1, sizeof(rbtree));
  node_t *nilNode = (node_t *)calloc(1, sizeof(node_t));

  nilNode->color = RBTREE_BLACK;
  p->nil = nilNode;
  p->root = nilNode;

  return p;
}

void delete_node(rbtree *t, node_t *node) {
    if (node->left != t->nil)
    {
        delete_node(t, node->left);
    }
    if (node->right != t->nil)
    {
        delete_node(t, node->right);
    }
    free(node);
    node = NULL;
}

void delete_rbtree(rbtree *t) {
  // TODO: reclaim the tree nodes's memory
  if (t->root != t->nil)
    delete_node(t, t->root);

  free(t->nil);
  free(t);
}


void left_rotate(rbtree *t, node_t *node) {
    node_t *r_node = node->right;
    node->right = r_node->left;
    
    if (r_node->left != t->nil)
        r_node->left->parent = node;
    
    r_node->parent = node->parent;

    if (node->parent == t->nil)
        t->root = r_node;
    else if (node == node->parent->left)
        node->parent->left = r_node;
    else
        node->parent->right = r_node;

    r_node->left = node;
    node->parent = r_node;
}

void right_rotate(rbtree *t, node_t *node) {
    node_t *l_node = node->left;
    node->left = l_node->right;

    if (l_node->right != t->nil)
        l_node->right->parent = node;

    l_node->parent = node->parent;

    if (node->parent == t->nil)
        t->root = l_node;
    else if (node == node->parent->left)
        node->parent->left = l_node;
    else
        node->parent->right = l_node;

    l_node->right = node;
    node->parent = l_node;
}

void rbtree_insert_fix(rbtree *t, node_t *node) {
    node_t *uncle;

    while (node->parent->color == RBTREE_RED) {  // double-red
        if (node->parent == node->parent->parent->left) {   // uncle is red
            uncle = node->parent->parent->right;
            if (uncle->color == RBTREE_RED) {
                node->parent->color = RBTREE_BLACK;
                uncle->color = RBTREE_BLACK;
                node->parent->parent->color = RBTREE_RED;
                node = node->parent->parent;
            }
            else {
                if (node == node->parent->right) {
                    node = node->parent;
                    left_rotate(t, node);
                }
                node->parent->color = RBTREE_BLACK;
                node->parent->parent->color = RBTREE_RED;
                right_rotate(t, node->parent->parent);
            }
        }
        else {   // uncle is black
            uncle = node->parent->parent->left;
            if (uncle->color == RBTREE_RED) {
                node->parent->color = RBTREE_BLACK;
                uncle->color = RBTREE_BLACK;
                node->parent->parent->color = RBTREE_RED;
                node = node->parent->parent;
            }
            else {
                if (node == node->parent->left) {
                    node = node->parent;
                    right_rotate(t, node);
                }
                node->parent->color = RBTREE_BLACK;
                node->parent->parent->color = RBTREE_RED;
                left_rotate(t, node->parent->parent);
            }
        }
    }
    t->root->color = RBTREE_BLACK;
}

node_t *rbtree_insert(rbtree *t, const key_t key) {
  // TODO: implement insert
  node_t *node = (node_t *)malloc(sizeof(node_t));
  node->key = key;
  node_t *cur = t->nil;
  node_t *x = t->root;
  while (x != t->nil) {
    cur = x;
    if (key < x->key)
        x = x->left;
    else
        x = x->right;
  }
  
  node->parent = cur;
  if (cur == t->nil)
    t->root = node;
  else if (key < cur->key)
    cur->left = node;
  else
    cur->right = node;
  
  node->left = t->nil;
  node->right = t->nil;
  node->color = RBTREE_RED;
  rbtree_insert_fix(t, node);

  return t->root;
}

node_t *rbtree_find(const rbtree *t, const key_t key) {
  // TODO: implement find
  node_t *cur = t->root;

  while (cur != t->nil) {
    if (cur->key == key)
        return cur;

    if (key < cur->key)
        cur = cur->left;
    else
        cur = cur->right;
  }    
  return NULL;
}

node_t *rbtree_min(const rbtree *t) {
  // TODO: implement find
  node_t *cur = t->root;

  while (cur != t->nil) {
    if (cur->left != t->nil)
        cur = cur->left;
    else
        return cur;
  }
  return cur;
}

node_t *rbtree_max(const rbtree *t) {
  // TODO: implement find
  node_t *cur = t->root;

  while (cur != t->nil) {
    if (cur->right != t->nil)
        cur = cur->right;
    else
        return cur;
  }
  return cur;
}

void rbtree_replace(rbtree *t, node_t *x, node_t *y) {  // replacing erase_node
    if (x->parent == t->nil)
        t->root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;

    y->parent = x->parent;
}

void rbtree_erase_fix(rbtree *t, node_t *p) {
    if (p->color == RBTREE_RED)
        p->color = RBTREE_BLACK;
    else {
        while (p != t->root && p->color == RBTREE_BLACK) {
            if (p == p->parent->left) {
                node_t *q = p->parent->right;
                if (q->color == RBTREE_RED) {
                    q->parent->color = RBTREE_RED;
                    q->color = RBTREE_BLACK;
                    left_rotate(t, p->parent);
                    q = p->parent->right;
                }
                if (q->left->color == RBTREE_BLACK && q->right->color == RBTREE_BLACK) {
                    q->color = RBTREE_RED;
                    p = q->parent;
                }
                else {
                    if (q->right->color == RBTREE_BLACK) {
                        q->left->color = RBTREE_BLACK;
                        q->color = RBTREE_RED;
                        right_rotate(t, q);
                        q = q->parent;
                    }
                    q->color = q->parent->color;
                    q->right->color = RBTREE_BLACK;
                    q->parent->color = RBTREE_BLACK;
                    left_rotate(t, q->parent);
                    p = t->root;
                }
            }
            else {
                node_t *q = p->parent->left;
                if (q->color == RBTREE_RED) {
                    q->parent->color = RBTREE_RED;
                    q->color = RBTREE_BLACK;
                    right_rotate(t, p->parent);
                    q = p->parent->left;
                }
                if (q->right->color == RBTREE_BLACK && q->left->color == RBTREE_BLACK) {
                    q->color = RBTREE_RED;
                    p = q->parent;
                }
                else {
                    if (q->left->color == RBTREE_BLACK) {
                        q->right->color = RBTREE_BLACK;
                        q->color = RBTREE_RED;
                        left_rotate(t, q);
                        q = q->parent;
                    }
                    q->color = q->parent->color;
                    q->left->color = RBTREE_BLACK;
                    q->parent->color = RBTREE_BLACK;
                    right_rotate(t, q->parent);
                    p = t->root;
                }
            }
        }
        p->color = RBTREE_BLACK;
    }
}

int rbtree_erase(rbtree *t, node_t *p) {
  // TODO: implement erase
  node_t *x;
  node_t *replace_node = p;
  color_t replace_node_org_color = p->color;

  if (replace_node->left == t->nil) {  // erased_node has one child(right)
    x = p->right;
    rbtree_replace(t, p, p->right);
  }
  else if (replace_node->right == t->nil) {  // erased_node has one child(left)
    x = p->left;
    rbtree_replace(t, p, p->left);
  }
  else {  // erased_node has two child
    replace_node = p->right;
    while (replace_node->left != t->nil) {  // find successor (replace node which is the smallest among the bigger group)
        replace_node = replace_node->left;
    }
    replace_node_org_color = replace_node->color;  // update replace node's color
    x = replace_node->right;
    if (replace_node->parent == p)
        x->parent = replace_node;
    else { 
        rbtree_replace(t, replace_node, replace_node->right);
        replace_node->right = p->right;
        replace_node->right->parent = replace_node;
    }
    rbtree_replace(t, p, replace_node);
    replace_node->left = p->left;
    replace_node->left->parent = replace_node;
    replace_node->color = p->color;
  }

  if (replace_node_org_color == RBTREE_BLACK)   // double-black
    rbtree_erase_fix(t, x);   // x node is double-black
  
  free(p);
    
  return 0;
}

void subtree_to_array(const rbtree *t, node_t *cur, key_t *arr, size_t n, size_t *count) {
    if (cur == t->nil) 
        return;

    subtree_to_array(t, cur->left, arr, n, count);
    if (*count < n) {
        arr[(*count)++] = cur->key;
    }
    else return;
    subtree_to_array(t, cur->right, arr, n, count);
}

int rbtree_to_array(const rbtree *t, key_t *arr, const size_t n) {
  // TODO: implement to_array
  if (t->root == t->nil)
    return 0;
  
  size_t cnt = 0;
  subtree_to_array(t, t->root, arr, n, &cnt);
  
  return 0;
}