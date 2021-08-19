#include <memory>
#include <string>
#include <vector>

using namespace std;

struct avl_node {
    int protocol;
    unsigned int source;
    unsigned int dest;
    int count;
    shared_ptr<avl_node> parent;
    shared_ptr<avl_node> left;
    shared_ptr<avl_node> right;
};

class AVL {
public:
    AVL();
    ~AVL();
    shared_ptr<avl_node> InitNode(int protocol, int source, int dest);
    bool Contains(int data);
    void InsertNode(shared_ptr<avl_node> new_node);
    int GetHeight(shared_ptr<avl_node> node);
    int HeightDifference(shared_ptr<avl_node> node);
    int PacketsRecvd(shared_ptr<avl_node> node, int count);
    void Print(shared_ptr<avl_node> node);
    void TraverseTreeUp(shared_ptr<avl_node> node);
    void TraversalInsert(shared_ptr<avl_node> new_node);
    void BalanceTree(shared_ptr<avl_node> root);
    void RotateLeft(shared_ptr<avl_node> node);
    void RotateRight(shared_ptr<avl_node> node);
    shared_ptr<avl_node> GetRoot();
    void SetRoot(shared_ptr<avl_node> root);
    void TestTraverseTreeInorder(shared_ptr<avl_node> node);
private:
    shared_ptr<avl_node> root_ptr;
};
