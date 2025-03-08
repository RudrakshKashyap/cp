#include <iostream>
using namespace std;

struct Node {
    int start, end; // Range represented by the node
    int value = 0;  // Sum of the range
    int lazy = 0;   // Pending lazy value
    Node* left = nullptr;
    Node* right = nullptr;

    Node(int s, int e) : start(s), end(e) {}
};

class SegmentTree {
private:
    Node* root;

    // Propagate pending lazy updates to children
    void propagate(Node* node) {
        if (node->lazy != 0 && node->start != node->end) {
            int mid = node->start + (node->end - node->start) / 2;

            // Create children if they don't exist
            if (!node->left) node->left = new Node(node->start, mid);
            if (!node->right) node->right = new Node(mid + 1, node->end);

            // Apply lazy value to children
            node->left->lazy += node->lazy;
            node->right->lazy += node->lazy;
            
            // Update children values
            node->left->value += node->lazy * (mid - node->start + 1);
            node->right->value += node->lazy * (node->end - mid);

            // Clear parent's lazy value
            node->lazy = 0;
        }
    }

    void updatePoint(Node* node, int index, int value) {
        if (node->start == node->end) {
            node->value = value;
            return;
        }

        propagate(node); // Ensure any pending updates are applied

        int mid = node->start + (node->end - node->start) / 2;
        if (index <= mid) {
            if (!node->left) node->left = new Node(node->start, mid);
            updatePoint(node->left, index, value);
        } else {
            if (!node->right) node->right = new Node(mid + 1, node->end);
            updatePoint(node->right, index, value);
        }

        // Update current value based on children
        node->value = (node->left ? node->left->value : 0) + 
                     (node->right ? node->right->value : 0);
    }

    void rangeUpdate(Node* node, int l, int r, int value) {
        if (node->end < l || node->start > r) return;

        if (l <= node->start && node->end <= r) {
            node->value += value * (node->end - node->start + 1);
            node->lazy += value;
            return;
        }

        propagate(node);

        int mid = node->start + (node->end - node->start) / 2;
        if (l <= mid) {
            if (!node->left) node->left = new Node(node->start, mid);
            rangeUpdate(node->left, l, r, value);
        }
        if (r > mid) {
            if (!node->right) node->right = new Node(mid + 1, node->end);
            rangeUpdate(node->right, l, r, value);
        }

        node->value = (node->left ? node->left->value : 0) + 
                     (node->right ? node->right->value : 0);
    }

    int queryRange(Node* node, int l, int r) {
        if (node->end < l || node->start > r) return 0;

        if (l <= node->start && node->end <= r) {
            return node->value;
        }

        propagate(node);

        return (node->left ? queryRange(node->left, l, r) : 0) + 
               (node->right ? queryRange(node->right, l, r) : 0);
    }

public:
    SegmentTree(int start, int end) {
        root = new Node(start, end);
    }

    // Point update (set value at index)
    void update(int index, int value) {
        updatePoint(root, index, value);
    }

    // Range update (add value to range [l, r])
    void rangeAdd(int l, int r, int value) {
        rangeUpdate(root, l, r, value);
    }

    // Range query (sum from l to r)
    int query(int l, int r) {
        return queryRange(root, l, r);
    }
};

int main() {
    SegmentTree st(0, 5); // Covers range [0, 5]

    st.update(2, 5);       // Set index 2 to 5
    st.rangeAdd(1, 3, 2);  // Add 2 to indices 1-3
    st.rangeAdd(2, 4, 1);  // Add 1 to indices 2-4

    cout << "Sum 1-3: " << st.query(1, 3) << endl; // 2 + (5+2+1) + (0+2+1) = 2+8+3 = 13
    cout << "Sum 0-5: " << st.query(0, 5) << endl; // 0 + 2 + 8 + 3 + 1 + 0 = 14
}
