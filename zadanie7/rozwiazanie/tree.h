#ifndef TREE_H
#define TREE_H

#include <memory>
#include <climits>
#include <limits>
#include <list>

template<typename T>
class Tree {
private:
    class NodeDef {
        typedef std::shared_ptr<NodeDef> Node;
    public:
        T value;
        Node left;
        Node right;

        NodeDef(T val, Node l, Node r) :
                value(val), left(l), right(r) { }

        template<typename Operation, typename U>
        U fold(Operation fun, U init) const {
            if (this == nullptr) {
                return init;
            }
            return fun(value, left->fold(fun, init), right->fold(fun, init));
        }

        std::list<T> inorder() const {
            if (this == nullptr) {
                return std::list<T>();
            }
            std::list<T> ret = left->inorder();
            ret.splice(ret.end(), std::list<T> {this->value});
            ret.splice(ret.end(), right->inorder());
            return ret;
        }

        std::list<T> postorder() const {
            if (this == nullptr) {
                return std::list<T>();
            }
            std::list<T> ret = left->postorder();
            ret.splice(ret.end(), right->postorder());
            ret.splice(ret.end(), std::list<T> {this->value});

            return ret;
        }

        std::list<T> preorder() const {
            if (this == nullptr) {
                return std::list<T>();
            }
            std::list<T> ret = std::list<T> {this->value};
            ret.splice(ret.end(), left->preorder());
            ret.splice(ret.end(), right->preorder());
            return ret;
        }
    };

    typedef std::shared_ptr<NodeDef> Node;
    Node root;
public:
    Tree() :
            root(createEmptyNode()) { }

    Tree(Node _root) :
            root(_root) { }

    Tree(Tree const &tree) {
        (*this) = tree.map([](T e) {return e;});
    }

    static Node createEmptyNode() {
        return nullptr;
    }

    static Node createValueNode(T value) {
        return std::make_shared<NodeDef>(NodeDef(value, createEmptyNode(), createEmptyNode()));
    }

    static Node createValueNode(T value, Node left, Node right) {
        return std::make_shared<NodeDef>(NodeDef(value, left, right));
    }

    int size() const {
        return root->fold([](T, int l, int r) -> int { return l + r + 1; }, 0);
    }

    int height() const {
        return root->fold([](T, int l, int r) -> int { return std::max(l, r) + 1; }, 0);
    }

    bool is_bst() const {
        typedef std::tuple<bool, T, T> data;
        const int MAX_T = std::numeric_limits<T>::max();
        const int MIN_T = std::numeric_limits<T>::min();
        static const int BST = 0;
        static const int MIN = 1;
        static const int MAX = 2;
        data res = root->fold([](T val, data l, data r) -> data {
            T min_l = std::get<MIN>(l);
            T max_l = std::get<MAX>(l);
            T min_r = std::get<MIN>(r);
            T max_r = std::get<MAX>(r);
            bool bst_l = std::get<BST>(l);
            bool bst_r = std::get<BST>(r);
            bool is_bst = bst_l && max_l <= val && val <= min_r && bst_r;
            return std::make_tuple(is_bst, std::min(min_l, val), std::max(val, max_r));
        }, std::make_tuple(true, MAX_T, MIN_T));
        return std::get<BST>(res);
    }

    template<typename Operation, typename U>
    U fold(Operation fun, U init) const {
        return root->fold(fun, init);
    }

    Tree filter(std::function<bool(T)> predicate) const {
        typedef std::pair<Node, Node> data; //first - parent, second - rightmost child
        data res = root->fold([&predicate](T val, data left, data right) -> data {
            if (predicate(val)) {
                return std::make_pair(createValueNode(val, left.first, right.first), right.second);
            }
            else {
                if (left.first == nullptr) {
                    return right;
                }
                left.second = right.first;
                return std::make_pair(left.first, right.second);
            }
        }, std::make_pair(createEmptyNode(), createEmptyNode()));
        return Tree(res.first);
    }

    Tree map(std::function<T(T)> transformer) const {
        return Tree<T>(root->fold([&transformer](T val, Node left, Node right) -> Node {
            return createValueNode(transformer(val), left, right);
        }, createEmptyNode()));
    }

    Tree lazy_map(std::function<T(T)> transformer) const {
        return Tree<T>(root->fold([&transformer](T val, Node left, Node right) -> Node {
            return createValueNode(transformer(val), left, right);
        }, createEmptyNode()));
    }

    void apply(std::function<void(T)> operation,
               std::function<std::list<T>(Node)> traversal) const {
        std::list<T> order = traversal(root);
        for (T e : order) {
            operation(e);
        }
    }

    void print(std::function<std::list<T>(Node)> traversal = inorder) const {
        apply([](T e) { std::cout << e << " "; }, traversal);
        std::cout << std::endl;
    }

    T accumulate(std::function<T(T, T)> operation, T init,
                 std::function<std::list<T>(Node)> traversal) const {
        T ret = init;
        apply([&](T e) { ret = operation(ret, e); }, traversal);
        return ret;
    }

    static std::list<T> inorder(Node root) {
        return root->inorder();
    }

    static std::list<T> postorder(Node root) {
        return root->postorder();
    }

    static std::list<T> preorder(Node root) {
        return root->preorder();
    }
};


#endif //TREE_H