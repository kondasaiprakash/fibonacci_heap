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
Heap_node * create_random_nodes(int num);
Heap_node * insert(Heap_node *root,Heap_node *one);
Heap_node * delete(Heap_node *root);
Heap_node * find_min_in_circle(Heap_node * root);
Heap_node * move_childs_to_main_circle(Heap_node * root, Heap_node * child_root);
Heap_node * same_degree_merge(Heap_node * parent,Heap_node * child);
Heap_node * consolidate(Heap_node * root);
void print_nodes_in_main_circle(Heap_node * root);
void make_child_parent_null(Heap_node *root);


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
        if(root->child == NULL)
        {
            free(root);
            root = NULL;
        }
        else
        {
            Heap_node *temp = root;
            root = root->child;
            // create a method which makes all the parents of the child null  pending pending.....
            make_child_parent_null(root);

            // root->parent = NULL;

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
                // child_root->parent = NULL;
                make_child_parent_null(child_root);
                root = move_childs_to_main_circle(root, child_root);

            }

        }
        root = consolidate(root);
        root = find_min_in_circle(root);
        

    }
    // printf("%d \n",root->value);
    return root;
}
void make_child_parent_null(Heap_node *root)
{
    Heap_node *temp = root;
    while(temp->right != root)
    {
        temp->parent = NULL;
        temp = temp->right;
    }
    temp->parent = NULL;
}
Heap_node * find_min_in_circle(Heap_node * root)
{
    if(root == NULL)
    {
        return root;

    }
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
        child->right = child;
        child->left = child;
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
    if(root == NULL)
    {
        return root;

    }

    int val = ceil(log(count));
    Heap_node **array = malloc(val*sizeof(Heap_node *));
    Heap_node * temp = root;
    int chance = 1;
    while(temp->right != root)
    {
        
        if(array[temp->degree] != NULL && array[temp->degree] != temp)
        {
            int deg = temp->degree;
            if(array[temp->degree]->value <= temp->value)
            {
                // array[temp->degree] = NULL;
                // array[2*temp->degree-1] = same_degree_merge(array[temp->degree],temp);
                // temp = array[2*temp->degree-1];
                temp = same_degree_merge(array[temp->degree],temp);
            }
            else
            {
                // array[2*temp->degree-1] = same_degree_merge(temp,array[temp->degree]);
                // temp = array[2*temp->degree-1];
                temp = same_degree_merge(temp,array[temp->degree]);
                root = temp;
            }
            chance = 0;
            array[deg] = NULL;
        }
        else
        {
            array[temp->degree] = temp;
            temp = temp->right;

        }
        if(temp->right == root && chance == 0)
        {
            chance = 1;
            root = root->right;
        }
        
        // while(root->parent != NULL)
        // {
        //     root = root->parent;
            
        // }
    } 
    return root;

}

void print_nodes_in_main_circle(Heap_node * root)
{
    if(root == NULL)
    {
        printf("\n  all the nodes were deleted ");
        printf("\n**************enter 0 to exit **********\n");
        return;
    }
    int i;
//    Heap_node *temp = root;
//    for(i = 0; i < 5; i++)
//    {

//        printf("%d -> ",temp->value);
//        temp = temp->right;
//    }
    Heap_node *temp = root;
    while(temp->right != root)
    {
        printf("%d ->",temp->value);
        temp = temp->right;
    }
    printf("%d->",temp->value);
    
}

Heap_node * create_random_nodes(int num)
{
    Heap_node *root = NULL;
   int i = 0;
   for(i = 0; i < num; i++)
   {
       Heap_node *one = (Heap_node *)malloc(sizeof(Heap_node));
       one->value = i;
       
       root = insert(root,one);
       printf("inserted %d \n",i);
   }
   return root;

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

   Heap_node *root = NULL;
   int num;
   printf("\n enter number of nodes to create :");
   scanf("%d",&num);
   root = create_random_nodes(num);
   print_nodes_in_main_circle(root);

   printf("\n enter 1 to delete the element");
   int check;
   scanf("%d",&check);
   while(check)
   {
       printf(" \n deleting element : %d\n",root->value);
        root = delete(root);
        print_nodes_in_main_circle(root);
        printf("\n enter 1 to delete the element");
        scanf("%d",&check);
   }
   
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