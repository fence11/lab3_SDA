#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct BinaryTreeNode
{
    int id;
    char track_name[100];
    int duration;
    struct BinaryTreeNode *left;
    struct BinaryTreeNode *right;
} BinaryTreeNode;

typedef struct BinaryTree
{
    BinaryTreeNode *root;
} BinaryTree;

BinaryTreeNode *create_binary_tree_node(int id, const char *track_name, int duration)
{
    BinaryTreeNode *tree_node = calloc(sizeof(BinaryTreeNode), 1);
    tree_node->id = id;
    strncpy(tree_node->track_name, track_name, sizeof(tree_node->track_name) - 1);
    tree_node->duration = duration;
    tree_node->left = NULL;
    tree_node->right = NULL;
    return tree_node;
}

BinaryTree *create_binary_tree()
{
    BinaryTree *local = calloc(sizeof(BinaryTree), 1);
    return local;
}

void delete_all_tree_nodes_from_node(BinaryTreeNode *current_node)
{
    if (current_node)
    {
        delete_all_tree_nodes_from_node(current_node->left);
        delete_all_tree_nodes_from_node(current_node->right);
        free(current_node);
    }
}

void clear_binary_tree(BinaryTree *tree)
{
    if (tree)
    {
        if (tree->root)
        {
            delete_all_tree_nodes_from_node(tree->root);
            tree->root = NULL;
        }
    }
}

void delete_binary_tree(BinaryTree *tree)
{
    if (tree)
    {
        clear_binary_tree(tree);
        free(tree);
    }
}

void insert_new_node_in_binary_tree(BinaryTreeNode *current_node, BinaryTreeNode *new_node)
{
    if (current_node)
    {
        if (current_node->id > new_node->id)
        {
            if (current_node->left)
            {
                insert_new_node_in_binary_tree(current_node->left, new_node);
            }
            else
            {
                current_node->left = new_node;
            }
        }
        else
        {
            if (current_node->right)
            {
                insert_new_node_in_binary_tree(current_node->right, new_node);
            }
            else
            {
                current_node->right = new_node;
            }
        }
    }
}

void insert_data_in_binary_tree(BinaryTree *tree, int id, const char *track_name, int duration)
{
    if (tree)
    {
        BinaryTreeNode *new_node = create_binary_tree_node(id, track_name, duration);
        if (tree->root)
        {
            insert_new_node_in_binary_tree(tree->root, new_node);
        }
        else
        {
            tree->root = new_node;
        }
    }
}

void print_binary_tree_node(BinaryTreeNode *node)
{
    if (node)
    {
        printf("ID: %3d, Track Name: %10s, Duration: %4d\n", node->id, node->track_name, node->duration);
    }
}

void print_binary_tree_inorder(BinaryTreeNode *root)
{
    if (root)
    {
        print_binary_tree_inorder(root->left);
        print_binary_tree_node(root);
        print_binary_tree_inorder(root->right);
    }
}

void print_binary_tree(BinaryTree *tree)
{
    if (tree && tree->root)
    {
        printf("Binary Tree (Inorder traversal):\n");
        print_binary_tree_inorder(tree->root);
        printf("\n");
    }
    else
    {
        printf("Binary Tree is empty.\n");
    }
}

int max(int a, int b)
{
    return (a > b) ? a : b;
}

int calculate_tree_depth(BinaryTreeNode *root)
{
    if (root == NULL)
    {
        return 0;
    }
    else
    {
        int left_depth = calculate_tree_depth(root->left);
        int right_depth = calculate_tree_depth(root->right);
        return 1 + max(left_depth, right_depth);
    }
}

BinaryTreeNode *search_node_by_id(BinaryTreeNode *root, int target_id)
{
    if (root == NULL || root->id == target_id)
    {
        return root;
    }

    if (target_id < root->id)
    {
        return search_node_by_id(root->left, target_id);
    }
    else
    {
        return search_node_by_id(root->right, target_id);
    }
}

void print_height_and_depth(BinaryTreeNode *root, int target_id, int current_depth)
{
    if (root == NULL)
    {
        printf("Node not found.\n");
        return;
    }
    if (root->id == target_id)
    {
        int height = calculate_tree_depth(root);
        printf("Height of node with ID %d: %d\n", target_id, height);
        printf("Depth of node with ID %d: %d\n", target_id, current_depth);
        return;
    }
    if (target_id < root->id)
    {
        print_height_and_depth(root->left, target_id, current_depth + 1);
    }
    else
    {
        print_height_and_depth(root->right, target_id, current_depth + 1);
    }
}

void print_leaves(BinaryTreeNode *root)
{
    if (root == NULL)
    {
        return;
    }

    if (root->left == NULL && root->right == NULL)
    {
        printf("ID: %d, Track Name: %s, Duration: %d\n", root->id, root->track_name, root->duration);
    }

    print_leaves(root->left);
    print_leaves(root->right);
}

int main()
{
    BinaryTree *tree = create_binary_tree();

    int id, duration;
    char track_name[100];
    char choice;

    int target_id = -1;

    printf("Enter elements to insert into the binary tree (ID Track_Name Duration, separated by spaces):\n");
    do
    {
        scanf("%d %s %d", &id, track_name, &duration);
        insert_data_in_binary_tree(tree, id, track_name, duration);
        printf("Do you want to insert another element? (y/n): ");
        scanf(" %c", &choice);
    } while (choice == 'y' || choice == 'Y');

    int menu_option = 0;
    do
    {
        printf("1 | Print binary tree\n");
        printf("2 | Depth of binary tree\n");
        printf("3 | Search for node by ID\n");
        printf("4 | Print the height and depth of a node\n");
        printf("5 | Print leaves of binary tree\n");
        printf("0 | Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &menu_option);
        switch (menu_option)
        {
        case 1:
            print_binary_tree(tree);
            break;
        case 2:
        {
            int depth = calculate_tree_depth(tree->root);
            printf("Depth of the binary tree: %d\n", depth);
        }
        break;
        case 3:
            printf("Insert search target ID:\n");
            scanf(" %d", &target_id);
            BinaryTreeNode *result_node = search_node_by_id(tree->root, target_id);
            if (result_node != NULL)
            {
                printf("Found node with ID %d: %s\n", result_node->id, result_node->track_name);
            }
            else
            {
                printf("Node with ID %d not found.\n", target_id);
            }
            break;
        case 4:
            printf("Enter the ID of the node to find its height and depth: ");
            scanf("%d", &target_id);

            print_height_and_depth(tree->root, target_id, 0);
            break;
        case 5:
            printf("Leaves of the binary tree:\n");
            print_leaves(tree->root);
            break;
        case 0:
            printf("==============\n||   EXIT   ||\n==============\n");
            break;
        default:
            printf("Invalid choice");
            break;
        }
    } while (menu_option != 0);

    delete_binary_tree(tree);

    return 0;
}
