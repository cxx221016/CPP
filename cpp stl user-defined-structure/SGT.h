#pragma once

struct Node
{
    int val,add;
    Node* left;Node* right;
    Node()=default;
    Node(int _val,int _add,Node* _left=nullptr,Node* _right=nullptr)
    {
        val=_val;
        add=_add;
        left=_left;
        right=_right;
    }
};

class SGT
{
    Node* root;
    static constexpr int N=1e9+7;
public:
    SGT()
    {
        root=new Node();
    }
    
    void insert(Node* root,int cl,int cr,int l,int r,int val)
    {
        int len=cr-cl+1;
        if(cl>=l&&cr<=r)
        {
            root->val= val==1?len:0 ;
            root->add=val;
            return;
        }
        pushdown(root,len);
        int mid=(cl+cr)>>1;
        if(l<=mid) insert(root->left,cl,mid,l,r,val);
        if(r>mid) insert(root->right,mid+1,cr,l,r,val);
        pushup(root);
    }
    
    int query(Node* root,int cl,int cr,int l,int r)
    {
        int len=cr-cl+1;
        if(l<=cl&&cr<=r) return root->val;
        pushdown(root,len);
        int mid=(cl+cr)>>1,res=0;
        if(l<=mid) res=query(root->left,cl,mid,l,r);
        if(r>mid)  res+=(res,query(root->right,mid+1,cr,l,r));
        return res;
    }

    void pushdown(Node* root,int len)
    {
        if(!root->left) root->left=new Node();
        if(!root->right) root->right=new Node();
        if(root->add==0) return;
        int add=root->add;
        if (add == -1) 
        {
            root->left->val=root->right->val=0;
        } else {
            root->left->val= len - len / 2;
            root->right->val = len / 2;
        }
        root->left->add=add;root->right->add=add;
        root->add = 0;
    }

    void pushup(Node* root)
    {
        root->val=root->left->val+root->right->val;
    }
};