#include<stdio.h>
#include<stdlib.h>
#include<math.h>
typedef struct node
{
    int value;
    int degree;
    struct node *left;
    struct node *right;
    struct node *parent;
    struct node *child;

}Heap_node;
Heap_node * find_min_in_circle(Heap_node * root);
Heap_node * move_childs_to_main_circle(Heap_node * root, Heap_node * child_root);
int count = 0;

Heap_node * insert(Heap_node *root,Heap_node *one)
{
    count++;
    if(root == NULL )
    {
        root = one;
        one->left = one;
        one->right = one;
    }
    else 
    {
        one->right = root->right;
        one->left = root;
        one->right->left = one;
        root->right = one;
    }
    if(one->value < root->value)
    {
        root = one;
    }
    return root;

}

Heap_node * delete(Heap_node *root)
{
    if(count >= 1)
    {
        count--;
    }
    if(root == NULL)
    {
        printf("there is no element to delete in the heap");
        return root;
    }
    else if(root->right == root)
    {
        if(root->child = NULL)
        {
            free(root);
            root = NULL;
        }
        else
        {
            Heap_node *temp = root;
            root = root->child;
            root->parent = NULL;
            free(temp);
            temp = NULL;
            root = find_min_in_circle(root);
        }
    }
    else
    {
        root->left->right = root->right;
        root->right->left = root->left;
        Heap_node *temp = root;
        if(root->child == NULL)
        {
            
            root = root->right;
            free(temp);
            temp = NULL;
            
        }
        else
        {
            Heap_node *child_root = root->child;
            if(child_root->right == child_root)
            {
                root = root->right;
                child_root->parent = NULL;
                root = insert(root,child_root);

            }
            else
            {
                // Heap_node *left_node = child_root;
                // Heap_node *right_node = child_root->right;
                root = root->right;
                child_root->parent = NULL;
                root = move_childs_to_main_circle(root, child_root);

            }

        }
        root = find_min_in_circle(root);
        

    }
    printf("%d \n",root->value);
    return root;
}

Heap_node * find_min_in_circle(Heap_node * root)
{
    Heap_node * min = root;
    Heap_node *temp = root;
    while(temp->right != root)
    {
        if(temp->value <= min->value)
        {
            min = temp;
            printf("%d \n",min->value);
        }
        temp = temp->right;
    }
    if(temp->value <= min->value)
    {
        min = temp;
    }
    return min;


}

Heap_node * move_childs_to_main_circle(Heap_node * root, Heap_node * child_root)
{
    Heap_node * left_node = child_root;
    Heap_node * right_node = child_root->right;
    left_node->right = root;
    right_node->left = root->right;
    root->right->left= right_node;
    root->right = left_node;
    return root;


}
Heap_node * same_degree_merge(Heap_node * parent,Heap_node * child)
{
    child->left->right = child->right;
    child->right->left = child->left;
    child->parent = parent;
    if(parent->degree == 0)
    {
        parent->child = child;
        parent->degree = 1;
    }
    else
    {
        parent->degree = 2 * parent->degree-1;
        Heap_node * temp = parent->child;
        child->right = temp->right;
        child->left = temp;
        child->right->left = child;
        temp->right = child;

    }
    return parent;

}

Heap_node * consolidate(Heap_node * root)
{
    int val = ceil(log(count));
    Heap_node * array = (Heap_node *)malloc(val*sizeof(Heap_node *));
    Heap_node * temp = root;
    while(temp->right != root)
    {
        if(array[temp->degree] != NULL)
        {
            if(array[temp->degree]->value <= temp->value)
            {
                // array[temp->degree] = NULL;
                array[2*temp->degree-1] = same_degree_merge(array[temp->degree],temp);
                temp = array[2*temp->degree-1];
            }
            else
            {
                array[2*temp->degree-1] = same_degree_merge(temp,array[temp->degree]);
                temp = array[2*temp->degree-1];
            }
            array[temp->degree] = NULL;
        }
        while(root->parent != NULL)
        {
            root = root->parent;
            
        }
    } 

}
void main()
{
    //reference before beginning
    /*
    Heap_node root = {10,NULL,NULL,NULL,NULL};
    Heap_node *one = (Heap_node *)malloc(sizeof(Heap_node));
    Heap_node *one ;
    one = &root;
    printf("%d",root.value);
    printf("%d",(*one).value);
    printf("%d",one->value);
    */

//    Heap_node *root = NULL;
//    int i = 0;
//    for(i = 0; i < 5; i++)
//    {
//        Heap_node *one = (Heap_node *)malloc(sizeof(Heap_node));
//        one->value = i;
       
//        root = insert(root,one);
//        printf("inserted %d \n",i);
//    }
//    i = 0;
//     Heap_node *temp = root;
//    for(i = 0; i < 5; i++)
//    {

//        printf("%d -> ",temp->value);
//        temp = temp->right;
//    }
//     printf("%d is going to be deleted \n",root->value);
//    root = delete(root);
//    printf("\n %d is the minimum value now : ",root->value);
    // Heap_node *one = (Heap_node *)malloc(sizeof(Heap_node));
    // one->value = 10;
    // one->left = one;
    // one->right = one;
    // printf("%d", one->value);
    // free(one);
    // if(one == NULL)
    // {
    //     printf("it's null");
    // }
    // else
    // {
    //     printf("I'ts not null");
    // }
    // printf("%d",one->value);
    // Heap_node root = {10,0,NULL,NULL,NULL,NULL};
    
    // int tot = ceil(log(10));
    // printf("%d",tot);
    // Heap_node * array[tot];
    // int i;
    // for(i = 0; i < 5; i++)
    // {
    //     array[i] = &root;
    // }
    // for(i = 0; i < 5; i++)
    // {
    //     printf("%d",array[i]->value);
    // }


}