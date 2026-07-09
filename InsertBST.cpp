#include<iostream>
#include<queue>
using namespace std;

class Node{
    public:
    int data;
    Node* left;
    Node* right;
    Node(int val){
        data = val;
        left = NULL;
        right = NULL;
    }
};

Node* insertNode(Node* root,int val)
{
    if(root == nullptr)return new Node(val);
    if(root->data>=val)
    {
        root->left = insertNode(root->left,val);
    }
    else
    {
        root->right = insertNode(root->right,val);
    }
    return root;
}
void level(Node* root)
{
    queue<Node*> q;
    q.push(root);
    while(!q.empty())
    {
        int size = q.size();
        for(int i=0;i<size;i++)
        {
            Node* n = q.front();
            q.pop();
            cout<<n->data<<" ";
            
            if(n->left)q.push(n->left);
            if(n->right)q.push(n->right);
        }
        }
    }

void inorder(Node* root)
{
    if(root == nullptr)return;
    inorder(root->left);
    cout<<root->data<<" ";
    inorder(root->right);
}

int main()
{
    Node* root = nullptr;
    while(true)
    {
        int n;
        cin>>n;
        if(n==-1)break; 
        root = insertNode(root,n);
           
    }
    inorder(root) ;
}