#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define RED 1
#define BLACK 0
#define NIL "zzzzzzzzzzzzzzzzzzzzzzzzzzzzzz"
//------------------------------------------BLACK AND RED TREES---------------------------------------------------------------
struct  RB_Trees {
    char key[32];
    int color;
    struct RB_Trees *parent;
    struct RB_Trees *left;
    struct RB_Trees *right;
};
//--------------------------------------------ASSING NILL----------------------------------------------------------------------
struct RB_Trees *Assing_Nil() {
    struct RB_Trees *z;
    z = (struct RB_Trees *)malloc(sizeof(struct RB_Trees));
    z->parent = NULL;
    z->right = NULL;
    z->left = NULL;
    strcpy(z->key,NIL);
    z->color = BLACK;

    return z;
}
//------------------------------------------------PRINT------------------------------------------------------------------------
void RBInorderTreeWalk(struct RB_Trees *root) {
    if(strcmp(root->key,NIL) != 0)
    {
        RBInorderTreeWalk(root->left);
        if(root->color == RED)
            printf("[%s | RED] ", root->key);
        else
            printf("[%s | BLACK] ", root->key);
        RBInorderTreeWalk(root->right);
    }
}
//---------------------------------------------------SEARCH--------------------------------------------------------------------
//-----------------------------------------------RECURSIVE TREE SEARCH---------------------------------------------------------
struct RB_Trees *RB_TreeSearch(struct RB_Trees *root, char element[]) {
    if((strcmp((root->key),NIL) == 0) || (strcmp(element,(root->key)) == 0))
        return root;
    if(strcmp(element,(root->key)) < 0)
        return RB_TreeSearch((root->left), element);
    else
        return RB_TreeSearch((root->right), element);
}
//----------------------------------------------ITERATIVE TREE SEARCH----------------------------------------------------------
struct RB_Trees *RB_IterativeTreeSearch(struct RB_Trees *root, char element[]) {
    while((strcmp((root->key),NIL) != 0) && (strcmp(element,(root->key)) != 0))
    {
        if(strcmp(element,(root->key)) < 0)
            root = root->left;
        else
            root = root->right;
    }
    return root;
}
//-----------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------ROTATIONS--------------------------------------------------------------------
//----------------------------------------------LEFT ROTATION------------------------------------------------------------------
struct RB_Trees *RB_LeftRotate(struct RB_Trees *root, struct RB_Trees *node) {
    struct RB_Trees *y;
    y = node->right;
    node->right = y->left;
    if(strcmp((y->left->key),NIL) != 0)
        y->left->parent = node;
    y->parent = node->parent;
    if(strcmp((node->parent->key),NIL) == 0)
        root = y;
    else if(node == (node->parent->left))
        node->parent->left = y;
    else
         node->parent->right = y;
    y->left = node;
    node->parent = y;
    return root;
}
//------------------------------------------------RIGHT ROTATION---------------------------------------------------------------
struct RB_Trees *RB_RightRotate(struct RB_Trees *root, struct RB_Trees *node) {
    struct RB_Trees *y;
    y = node->left;
    node->left = y->right;
    if(strcmp((y->right->key),NIL) != 0)
        y->right->parent = node;
    y->parent = node->parent;
    if(strcmp((node->parent->key),NIL) == 0)
        root = y;
    else if( node == (node->parent->right))
        node->parent->right = y;
    else
        node->parent->left = y;
    
    y->right = node;
    node->parent = y;
    return root;
}
//-----------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------MINIMUN & MAXIMUN-----------------------------------------------------
//-------------------------------------------------------MINIMUN---------------------------------------------------------------
struct RB_Trees *RB_TreeMinimun(struct RB_Trees *root) {
    while(strcmp((root->left->key),NIL) != 0)
    {
        root = root->left;
    }
    return root;
}
//--------------------------------------------------------MAXIMUN--------------------------------------------------------------
struct RB_Trees *RB_Maximun(struct RB_Trees *root) {
    while(strcmp((root->right->key),NIL) != 0)
    {
        root = root->right;
    }
    return root;
}

//-----------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------SUCCESSOR & PREDECCESSOR---------------------------------------------------------
//-------------------------------------------------SUCCESSOR-------------------------------------------------------------------
struct RB_Trees *RB_TreeSuccessor(struct RB_Trees *node) {
    struct RB_Trees *y;
    if(strcmp((node->right->key),NIL) != 0)
        return RB_TreeMinimun(node->right);
    y = node->parent;
    while((strcmp((y->key),NIL) != 0) && (node == (y->right)))
    {
        node = y;
        y = y->parent;
    }
    return y;
}
//-------------------------------------------------------PREDECCESSOR----------------------------------------------------------
struct RB_Trees *RB_TreePredeccessor(struct RB_Trees *node) {
    struct RB_Trees *y;
    if(strcmp((node->left->key),NIL) != 0)
        return RB_Maximun(node->left);
    y = node->parent;
    while((strcmp((y->key),NIL) != 0) && (node == (y->left)))
    {
        node = y;
        y = y->parent;
    }
    return y;
}
//-----------------------------------------------------------------------------------------------------------------------------
//-----------------------------------------FIX UP FUCTIONS---------------------------------------------------------------------
//-----------------------------------------Insert Fix Up-----------------------------------------------------------------------
struct RB_Trees *RB_InsertFixUp(struct RB_Trees *root, struct RB_Trees *node) {
    struct RB_Trees *y;
    while((node->parent->color) == RED)
    {
        if((node->parent) == (node->parent->parent->left))
        {
            y = node->parent->parent->right;
            if((y->color) == RED)//-------------------------------------CASE 1-------------------------------------------------
            {
                node->parent->color = BLACK;
                y->color = BLACK;
                node->parent->parent->color = RED;
                node = node->parent->parent; 
            }
            else
            {
                if(node == (node->parent->right))//-----------------------------------CASE 2----------------------------------
                {
                    node = node->parent;
                    root = RB_LeftRotate(root,node);
                }
                node->parent->color = BLACK;   
                node->parent->parent->color = RED;
                root = RB_RightRotate(root,(node->parent->parent));
            }
        }
        else
        {
            y = node->parent->parent->left;
            if((y->color) == RED)
            {
                node->parent->color = BLACK;
                y->color = BLACK;
                node->parent->parent->color = RED;
                node = node->parent->parent;
            }
            else
            {
                if(node == (node->parent->left))
                {
                    node = node->parent;
                    root = RB_RightRotate(root,node);
                }
                node->parent->color = BLACK;
                node->parent->parent->color = RED;
                root = RB_LeftRotate(root,(node->parent->parent));
            }
        }
    }
    root->color = BLACK;
    return root;
}
//--------------------------------------------------------Delete Fix Up--------------------------------------------------------
struct RB_Trees *RB_DeleteFixUp(struct RB_Trees *root, struct RB_Trees *node) {
    struct RB_Trees *w;
    while((node != root) && ((node->color) == BLACK))
    {
        if(node == (node->parent->left))
        {
            w = node->parent->right;
            if((w->color) == RED)
            {
                w->color = BLACK;
                node->parent->color = RED;
                root = RB_LeftRotate(root,(node->parent));
                w = node->parent->right;
            }

            if(((w->left->color) == BLACK) && ((w->right->color) == BLACK))
            {
                w->color =  RED;
                node = node->parent;
            }
            else
            {
                if((w->right->color) == BLACK)
                {
                    w->left->color == BLACK;
                    w->color = RED;
                    root = RB_RightRotate(root, w);
                    w = node->parent->right;
                }
                w->color = node->parent->color;
                node->parent->color = BLACK;
                w->right->color = BLACK;
                root = RB_LeftRotate(root,(node->parent));
                node = root;
            }
        }
        else
        {
            w = node->parent->left;
            if((w->color) == RED)
            {
                w->color = BLACK;
                node->parent->color = RED;
                root = RB_RightRotate(root,(node->parent));
                w = node->parent->left;
            }

            if(((w->left->color) == BLACK) && ((w->right->color) == BLACK))
            {
                w->color = RED;
                node = node->parent;
            }
            else
            {
                if((w->left->color) == BLACK)
                {
                    w->right->color =BLACK;
                    w->color = RED;
                    root = RB_LeftRotate(root,w);
                    w = node->parent->left;
                }
                w->color = node->parent->color;
                node->parent->color = BLACK;
                w->left->color = BLACK;
                root = RB_RightRotate(root,(node->parent));
                node = root;
            }
        }
    }
    node->color = BLACK;
    return root;
}
//-----------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------RB INSERT & DELETE----------------------------------------------------------------
//----------------------------------------------RB INSERT----------------------------------------------------------------------
struct RB_Trees *RB_Insert(struct RB_Trees *root, char element[]) {
	struct RB_Trees *x, *y, *z;
    z = (struct RB_Trees *) malloc(sizeof(struct RB_Trees));
    strcpy(z->key,element);
    z->color = RED;
    z->left = Assing_Nil();
    z->left->parent = z;
    z->right = Assing_Nil();
    z->right->parent = z;

	if(strcmp(root->key,NIL) != 0)
        y = root->parent;
    else
        y = root;

	x = root;
	while(strcmp(x->key,NIL) != 0)
    {
		y = x;
		if(strcmp(z->key,x->key) < 0)
			x = x->left;
        else
			x = x->right;
	}
	z->parent = y;
	if(strcmp(y->key,NIL) == 0)
		root = z;
	else
    {
		if(strcmp(z->key,y->key) < 0)
        {
            free(y->left);
			y->left = z;

        }
		else
        {
            free(y->right);
			y->right = z;
        }
	}
	return RB_InsertFixUp(root, z);
}
//------------------------------------------------RB DELETE--------------------------------------------------------------------
struct RB_Trees *RB_Delete(struct RB_Trees *root, struct RB_Trees *node) {
	struct RB_Trees *x, *y;
	if((strcmp((node->left->key),NIL) == 0) || (strcmp((node->right->key),NIL) == 0))
		y = node;
	else
		y = RB_TreeSuccessor(node);

	if(strcmp((y->left->key),NIL) != 0)
		x = y->left;
    else
		x = y->right;

	x->parent = y->parent;
	if(strcmp((y->parent->key),NIL) == 0)
		root = x;
	else
    {
		if(y == y->parent->left)
			y->parent->left = x;
        else
			y->parent->right = x;
	}

	if(y != node) {
		strcpy(node->key,y->key);
        //copy all information  camps
    }

	if(y->color == BLACK) {
		root = RB_DeleteFixUp(root, x);
  }

	if(y->left->parent == y)
		free(y->left);

	if(y->right->parent == y)
		free(y->right);

	free(y);
	return root;
}
//-----------------------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------------------
int main() {
  struct RB_Trees *T = Assing_Nil(), *x, *y, *z;
  char word1[32], word2[32];
  int i, j, k, len;
  char words[32];
  while(scanf("%s",words) && (strcmp(words,".") != 0)) {
    z = RB_IterativeTreeSearch(T,words);
    if(strcmp(z->key,NIL) == 0) {
      T = RB_Insert(T,words);
    }
  }
  scanf("%s", words);
  z = RB_IterativeTreeSearch(T,words);
  len = strlen(z->key);
  for(i = 1; i < len; i++) {
    for(j = 0; j < i; j++) {
      word1[j] = z->key[j];
    }
    word1[j] = '\0';
    for(k = 0, j = i; j < len; j++, k++) {
      word2[k] = z->key[j];
    }
    word2[k] = '\0';
    y = RB_IterativeTreeSearch(T, word1);
    x = RB_IterativeTreeSearch(T, word2);
    if(strcmp(y->key,NIL) != 0) {
      if(strcmp(x->key,NIL) != 0) {
        printf("%s\n",z->key);
      }
    }
  }
  return 0;
}
