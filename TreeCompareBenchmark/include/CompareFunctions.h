#pragma once

#include "TreeNode.h"

bool isSameTreeAGZ(TreeNode* p, TreeNode* q)
{
    if (p == nullptr &&
        q == nullptr)
        return true;
    if ((p != nullptr &&
         q == nullptr) ||
        (p == nullptr &&
         q != nullptr))
        return false;
    if (p->val != q->val)
        return false;
    return isSameTreeAGZ(p->left, q->left) &&
        isSameTreeAGZ(p->right, q->right);
}

bool isSameTreeLeetCode(TreeNode* p, TreeNode* q)
{
    if (p == nullptr &&
        q == nullptr)
        return true;
    else if (p == nullptr ||
        q == nullptr)
        return false;
    else if (p->val != q->val)
        return false;
    else
        return isSameTreeLeetCode(p->left, q->left) && 
        isSameTreeLeetCode(p->right, q->right);
}
