#pragma once

#include <vector>
#include <queue>
#include <random>

#include "TreeNode.h"

std::vector<int> GenerateValues(size_t count)
{
    std::vector<int> result;
    result.reserve(count);

    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> distr(1, count);

    for(auto i = 0; i < count; ++i)
        result.push_back(distr(rng));

    return result;
}

TreeNode* GenerateTree(std::vector<int>& values)
{    
    auto result = new TreeNode(0);
    std::queue<TreeNode*> lastNodes;
    lastNodes.push(result);
    for (auto i = 0; i < values.size(); i += 2)
    {
        auto currentNode = lastNodes.front();
        auto leftNode = new TreeNode(values[i]);
        auto rightNode = new TreeNode(i + 1 < values.size() ? values[i + 1] : 0);
        currentNode->left = leftNode;
        currentNode->right = rightNode;
        lastNodes.pop();
        lastNodes.push(leftNode);
        lastNodes.push(rightNode);
    }
    return result;
}

TreeNode* GenerateTree(size_t count)
{
    auto values = GenerateValues(count);
    return GenerateTree(values);
}
