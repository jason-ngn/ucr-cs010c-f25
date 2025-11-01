#include "bt.h"

#include <iostream>
#include <queue>
#include <stack>
#include <utility>

using namespace std;

// Make a type alias
using Node = BinaryTree<char>::Node;

// TODO: Q1.1
void PreorderIter(Node* root) {
  if (!root) return;

  cout << root->item << endl;
  PreorderIter(root->left.get());
  PreorderIter(root->right.get());
}

void LevelOrderRec(Node* root, int level, vector<vector<char>>& res) {
  if (root == nullptr) return;

  if (res.size() <= level) res.push_back({});

  res.at(level).push_back(root->item);

  LevelOrderRec(root->left.get(), level + 1, res);
  LevelOrderRec(root->right.get(), level + 1, res);
}

// TODO: Q1.2
void LevelIter(Node* root) {
  vector<vector<char>> res;

  LevelOrderRec(root, 0, res);

  for (auto v : res) {
    for (auto c : v) cout << c << endl;
  }
}

#ifndef NO_MAIN  // Only compile main if NO_MAIN is not defined
int main() {
  // Statically build a binary tree
  std::unique_ptr<Node> nj(new Node{'j'});
  std::unique_ptr<Node> ni(new Node{'i'});
  std::unique_ptr<Node> nh(new Node{'h'});
  std::unique_ptr<Node> ng(new Node{'g'});
  std::unique_ptr<Node> nf(new Node{'f', std::move(nj)});
  std::unique_ptr<Node> ne(new Node{'e'});
  std::unique_ptr<Node> nd(new Node{'d', std::move(nh), std::move(ni)});
  std::unique_ptr<Node> nc(new Node{'c', std::move(nf), std::move(ng)});
  std::unique_ptr<Node> nb(new Node{'b', std::move(nd), std::move(ne)});
  std::unique_ptr<Node> na(new Node{'a', std::move(nb), std::move(nc)});
  BinaryTree<char> bin_tree{std::move(na)};

  std::cout << "Iterative pre-order: \n";
  PreorderIter(bin_tree.root.get());
  std::cout << std::endl;

  std::cout << "Iterative level-order: \n";
  LevelIter(bin_tree.root.get());
  std::cout << std::endl;

  return 0;
}
#endif
