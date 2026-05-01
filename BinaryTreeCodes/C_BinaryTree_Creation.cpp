#pragma
#include <stdio.h>
#include <stdlib.h>
#include <stack>
#include <iostream>

using namespace std;

typedef struct treeNode {
    treeNode* leftChild;
    int data;
    treeNode* rightChild;
}; treeNode;

typedef struct node {
    treeNode* treeval;
    node* next;
} Node;

typedef struct queue {
    Node* end;
    Node* front;
    int size;
} Queue;

Queue create_queue() {
    Queue q;
    q.end = NULL;
    q.front = NULL;
    q.size = 0;
    return q;
}

void push(Queue* q, treeNode* t) {
    Node* newnode = (Node*)(malloc(sizeof(Node)));
    if (newnode)
    {
        newnode->treeval = t;
        newnode->next = NULL;

    }
    if (q->size == 0)
    {
        q->end = q->front = newnode;
    }
    else
    {
        q->end->next = newnode;
        q->end = newnode;
    }
    q->size++;
}
treeNode* pop(Queue* q) {
    if (q->size == 0)
    {
        return NULL;
    }
    Node* temp = q->front;
    q->front = q->front->next;
    treeNode* val = temp->treeval;
    free(temp);
    q->size--;
    if (q->size == 0)
    {
        q->front = NULL;
        q->end = NULL;
    }
    return val;

}
void print(Queue* q) {
    for (Node* cur = q->front; cur; cur = cur->next)
    {
        printf("%d\n", cur->treeval->data);
    }
}

bool isEmpty(Queue* q)
{
    return (q->front == NULL && q->end == NULL);
}

treeNode* root = NULL;

void Create()
{
    queue q = create_queue();
    
    cout << "Please Enter Root value: " << endl;
    int x;
    cin >> x;
    root = (treeNode*)malloc(sizeof(treeNode));
    if (root)
    {
        root->data = x;
        root->leftChild = root->rightChild = NULL;
    }
    push(&q, root);


    treeNode* p, *t;
    while (!isEmpty(&q))
    {
        p = pop(&q);
        cout << "Please enter left child of: " << p->data << endl;
        int lval;
        cin >> lval;
        if (lval != -1)
        {
            t = (treeNode*)malloc(sizeof(treeNode));
            if (t)
            {
                t->data = lval;
                t->leftChild = t->rightChild = NULL;
                p->leftChild = t;
                push(&q, t);
            }
           
        }
        cout << "Please enter right child of: " << p->data << endl;
        int rval;
        cin >> rval;
        if (rval != -1)
        {
            t = (treeNode*)malloc(sizeof(treeNode));
            if (t)
            {
                t->data = rval;
                t->leftChild = t->rightChild = NULL;
                p->rightChild = t;
                push(&q, t);
            }

        }
    }



}

void PrintPreOrder(treeNode* current)
{
    if (!current) return;

    cout << current->data << " , ";
    PrintPreOrder(current->leftChild);
    PrintPreOrder(current->rightChild);
}

//for iterative
void PrintPreOrder_It(treeNode* current)
{
    stack<treeNode*> s;
    treeNode* t = current;
    while (!s.empty() || t)
    {
        if (t)
        {
            cout << t->data << ",";
            s.push(t);
            t = t->leftChild;
        }
        else
        {
            t = s.top();
            s.pop();
            t = t->rightChild;
        }

    }

}

void PrintInOrder_It(treeNode* current)
{
    stack<treeNode*> s;

    while (!s.empty() || current)
    {
        if (current)
        {
            s.push(current);
            current = current->leftChild;
        }
        else
        {
            current = s.top();
            s.pop();
            cout << current->data << ",";
            current = current->rightChild;
        }

    }

}

void PrintLevelOrder(treeNode* current)
{
    queue q = create_queue();
    cout << current->data<<",";
    push(&q, current);
    while (!isEmpty(&q))
    {
        current = pop(&q);
        if (current->leftChild)
        {
            cout << current->leftChild->data << ",";
            push(&q, current->leftChild);
        }
        if (current->rightChild)
        {
            cout << current->rightChild->data << ",";
            push(&q, current->rightChild);
        }
    }

}

int CountNodes(treeNode* current)
{
    if (!current) return 0;

    return CountNodes(current->leftChild) + CountNodes(current->rightChild) + 1;
}

int getHeight(treeNode* current)
{
    if (!current) return -1;

    int leftheight = getHeight(current->leftChild);
    int rightHeight = getHeight(current->rightChild);

    if (leftheight > rightHeight)
    {
        return leftheight + 1;
    }
    else
    {
        return rightHeight + 1;
    }

}


int main4()
{
    return 0;
    Create();
    PrintPreOrder(root);
    cout << endl;
    PrintPreOrder_It(root);
    cout << endl;
    PrintInOrder_It(root);
    cout << endl;
    PrintLevelOrder(root);
    cout << endl;
    cout<<CountNodes(root);
    cout << endl;
    cout << getHeight(root);
}