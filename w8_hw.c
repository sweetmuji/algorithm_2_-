#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

typedef struct TreeNode
{
    int data;
    struct TreeNode* left;
    struct TreeNode* right; 
} TreeNode;

TreeNode* new_node(int item) // 새로운 노드를 생성한 뒤 반환
{
    TreeNode* temp = (TreeNode*)malloc(sizeof(TreeNode));

    temp->data = item;
    temp->left = temp->right = NULL;

    return temp;
}

TreeNode* insert_node(TreeNode* node, int data) // 삽입 연산
{
    if (node == NULL) // 만약 공백 트리라면 새로운 노드를 생성 및 반환한다.
    {
        return new_node(data); 
    }

    // 만약 해당 노드가 비어있지 않다면 탐색 트리를 내려간다!
    if (data < node->data) 
    {
        node->left = insert_node(node->left, data);
    }
    else
    {
        node->right = insert_node(node->right, data);
    }

    return node; // 변경된 루트 포인터를 반환
}

TreeNode* search_node(TreeNode* node, int key)
{
    if(node == NULL) // 같은 것이 없을 때 
    { 
        return NULL;
    }

    printf("%d -> ", node->data); // 지나가는 노드 출력

    if(key == node->data) // 탐색 완료
    {
        return node;
    }
    else if(key < node->data)
    {
       return search_node(node->left, key);
    }
    else
    {
        return search_node(node->right, key);
    }
}

TreeNode* min_value_node(TreeNode* node) // 가장 작은 ( 가장 왼쪽으로 내려간 ) 노드를 찾는 
{
	TreeNode* current = node;
	
	while (current->left != NULL)
	{
		current = current->left;
	}
	
	return current;
}

TreeNode* delete_node(TreeNode* node, int key)
{ 
    if(node == NULL) // 해당 노드가 비어있다면 말단 노드
    {
        return node;
    }

    if(key < node->data) // 만약 탐색할 키가 왼쪽보다 작다면 왼쪽의 서브 트리 아래에 있다. 
    {
        node->left = delete_node(node->left, key);
    }
    else if(key > node->data)
    {
        node->right = delete_node(node->right, key);
    }
    else // 같을 경우. 즉 찾았을 때
    {
        if (node->left == NULL) // 왼쪽 노드가 비어있거나 두 노드가 모두 비어있어 말단 노드인 경우!
        {
            TreeNode* temp = node->right; // 오른쪽 노드를 다시 연결한다.
            free(node);
            return temp;
        }
        else if (node->right == NULL) // 오른쪽 노드가 비어있는 경우!! 
        {
            TreeNode* temp = node->left;
            free(node);
            return temp;
        }

        // 좌우 노드를 모두 가지고 있는 경우 ( 현재 노드보다 크면서 가장 작은, 즉 자신과 가장 비슷한 값으로 대체한다. )
        TreeNode* temp = min_value_node(node); 

        node->data = temp->data;
        node->right = delete_node(node, temp->data); // 옮긴 기존의 노드를 삭제한다. 
    }

    return node; // 변경된 루트 노드의 값 반환
}

void inorder(TreeNode* root) // 중위 순회 LVR
{
    if(root != NULL)
    {
        inorder(root->left);
        printf("[ %d ] ", root->data);
        inorder(root->right);
    }
}

void preorder(TreeNode* root) // 전위 순회 VLR 
{
    if(root != NULL)
    {
        printf("[ %d ] ", root->data);
        preorder(root->left);
        preorder(root->right);
    }
}

void postorder(TreeNode* root) // 후위 순회 LRV
{
    if (root != NULL)
    {
        postorder(root->left);
        postorder(root->right);
        printf("[ %d ] ", root->data);
    }
}

TreeNode* select_menu(int select, TreeNode* root) // 변화된 root 포인터 주소를 반환한다.
{
    int key;

    switch (select)
    {
    case 1:
        printf("\n삽입 : 트리에 넣을 키값을 입력하시오");
        scanf("%d", &key);
        root = insert_node(root, key);
        break;
    case 2:
        printf("\n삭제 : 트리에서 삭제할 키값을 입력하시오");
        scanf("%d", &key);
        root = delete_node(root, key);
        break;
    case 3:
        printf("\n전위순회 : 전위 순회를 진행힙니다. 방문되는 노드들은 다음과 같습니다.\n");
        preorder(root);
        printf("\n");
        break;
    case 4:
        printf("\n중위순회 : 중위 순회를 진행합니다. 방문되는 노드들은 다음과 같습니다.\n");
        inorder(root);
        printf("\n");
        break;
    case 5:
        printf("\n후위순회 : 후위 순회를 진행합니다. 방문되는 노드들은 다음과 같습니다.\n");
        postorder(root);
        printf("\n");
        break;
    case 6:
        printf("\n 노드 탐색 : 노드를 탐색합니다. 키 값을 입력하세요.\n");
        scanf("%d", &key);
        if(search_node(root, key) == NULL) // 만약 찾지 못 했다면 
        {
            printf("이진 탐색 트리에서 %d 를 발견하지 못 했습니다.\n", key);
        }
        else // 찾았다면 
        {
            printf("이진 탐색 트리에서 %d 를 발견했습니다.\n", key);
        }
        break;
    default:
        printf("잘못된 값을 입력했습니다.\n");
        break;
    }

    return root;
}

int main(void)
{
    TreeNode* root = NULL;

    while (1)
    {
        int select;

        printf("메뉴를 선택하시오 - 1: 삽입 / 2: 삭제 / 3: 전위순회 / 4: 중위순회 / 5: 후위순회 / 6: 노드 탐색");
        scanf("%d", &select);
        root = select_menu(select, root);
    }
    
    return 0;
}