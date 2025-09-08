
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
       search_node(node->left, key);
    }
    else
    {
        search_node(node->right, key);
    }