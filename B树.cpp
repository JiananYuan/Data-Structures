/**
 * Created by andyjnyuan
 * Date: 2021/10/03
 * Project-name: B-Tree
 * Reference: https://www.cnblogs.com/nullzx/p/8729425.html
 */

#include <iostream>
using namespace std;

// data type in b_tree
typedef int key_type;
// b_tree's degree, (2-3 tree)
const int m = 3;

// b_tree node
typedef struct BTNode {
    // number of key
    int keynum;
    // key array
    key_type key[m+1];
    // node parent
    struct BTNode *parent;
    // ptr array
    struct BTNode *ptr[m+1];
    BTNode() {
        keynum = 0;
        parent = nullptr;
        for (int i = 0; i < m + 1; i += 1) {
            ptr[i] = nullptr;
        }
    }
} BTNode, *BTree;

// search result record
typedef struct {
    // current_node
    BTree pt;
    // index
    int i;
    // 1: found  0: not_found
    int tag;
} result;

// global b_tree
BTree T = nullptr;

/**
 * search key in a b_tree node
 * @param p BTree node
 * @param k key to be searched
 * @return the first element index greater than or equal to k
 */
int Search(BTree p, int k) {
    int i = 1;
    int keynum = p -> keynum;
    while (i <= keynum && p -> key[i] < k) {
        i += 1;
    }
    return i;
}

/**
 * search key in a b_tree
 * @param t BTree
 * @param k key to be searched
 * @param r search result refer
 */
void SearchBTree(BTree t, int k, result& r) {
    int i = 0, found = 0;
    BTree p = t, q = nullptr;
    while (p != nullptr && found == 0) {
        // search current node
        i = Search(p, k);
        // check whether find target
        if (i <= p -> keynum && p -> key[i] == k) {
            found = 1;
        }
        else {
            // record current node in q
            q = p;
            // search in the child node before i-th node
            p = p -> ptr[i-1];
        }
    }
    if (found == 1) {
        // record { current_node, index, found }
        r = { p, i, 1 };
    }
    else {
        // record { current_node, index, not_found }
        r = { q, i, 0 };
    }
}

/**
 * new a root node
 * @param t BTree
 * @param p left ptr
 * @param x first value
 * @param ap right ptr
 */
void newRoot(BTree& t, BTree p, int x, BTree ap) {
    t = new BTNode;
    t -> keynum = 1;
    t -> ptr[0] = p;
    t -> ptr[1] = ap;
    t -> key[1] = x;
    if (p != nullptr) {
        p -> parent = t;
    }
    if (ap != nullptr) {
        ap -> parent = t;
    }
    t -> parent = nullptr;
}

/**
 * split the node avg
 * @param q current_node
 * @param s middle_number
 * @param ap next node after spliting
 */
void split(BTree& q, int s, BTree& ap) {
    int i, j, n = q -> keynum;
    ap = new BTNode;
    ap -> ptr[0] = q -> ptr[s];
    for (i = s + 1, j = 1; i <= n; i += 1, j += 1) {
        ap -> key[j] = q -> key[i];
        ap -> ptr[j] = q -> ptr[i];
    }
    ap -> keynum = n - s;
    ap -> parent = q -> parent;
    for (i = 0; i <= n - s; i += 1) {
        if (ap -> ptr[i] != nullptr) {
            ap -> ptr[i] -> parent = ap;
        }
    }
    q -> keynum = s - 1;
}

/**
 * insert an element into a b_tree node named q
 * @param q target insert node
 * @param i target insert index
 * @param x target value
 * @param ap target gap ptr
 */
void Insert(BTree& q, int i, int x, BTree ap) {
    int j, n = q -> keynum;
    for (j = n; j >= i; j -= 1) {
        q -> key[j+1] = q -> key[j];
        q -> ptr[j+1] = q -> ptr[j];
    }
    q -> key[i] = x;
    q -> ptr[i] = ap;
    if (ap != nullptr) {
        ap -> parent = q;
    }
    q -> keynum  = q -> keynum + 1;
}

/**
 * insert an element into b_tree
 * @param t BTree
 * @param k element to insert
 * @param q target node
 * @param i target index
 */
void InsertBTree(BTree& t, int k, BTree q, int i) {
    // first insert, the root node has not existed
    if (q == nullptr) {
        newRoot(t, nullptr, k, nullptr);
    }
    else {
        int x = k, finished = 0, needNewRoot = 0;
        BTree ap = nullptr;
        while (needNewRoot == 0 && finished == 0) {
            // try to insert k at i-th index in q node
            Insert(q, i, x, ap);
            // enough space to insert, ready to finish this function
            if (q -> keynum < m) {
                finished = 1;
            }
            // not enough space, try split node averagely
            else {
                int s = (m + 1) / 2;
                split(q, s, ap);
                // improve middle_number x into father node
                x = q -> key[s];
                if (q -> parent != nullptr) {
                    q = q -> parent;
                    i = Search(q, x);
                }
                else {
                    needNewRoot = 1;
                }
            }
        }
        // if reach root node, then new a new_root node
        if (needNewRoot == 1) {
            newRoot(t, q, x, ap);
        }
    }
}

/**
 * remove i-th index in node p
 * @param p current_node
 * @param i index to be removed
 */
void Remove(BTree& p, int i) {
    int j, n = p -> keynum;
    for (j = i; j < n; j += 1) {
        p -> key[j] = p -> key[j+1];
        p -> ptr[j] = p -> ptr[j+1];
    }
    p -> keynum = p -> keynum - 1;
}

/**
 * restore b_tree after changes caused by deleting
 * @param p target node (changed)
 * @param i target index (changed)
 * @param T BTree
 */
void Restore(BTree& p, int i, BTree& T) {
    int j;
    BTree ap = p -> parent;
    if (ap == nullptr) {
        T = p;
        p = p -> parent;
        return;
    }
    BTree lc, rc, pr;
    int finished = 0, r = 0;
    while (!finished) {
        r = 0;
        while (ap -> ptr[r] != p) {
            r += 1;
        }
        if (r == 0) {
            r += 1;
            lc = nullptr;
            rc = ap -> ptr[r];
        }
        else if (r == ap -> keynum) {
            lc = ap -> ptr[r-1];
            rc = nullptr;
        }
        else {
            lc = ap -> ptr[r-1];
            rc = ap -> ptr[r+1];
        }
        // borrow one key from left node
        if (r > 0 && lc != nullptr && (lc -> keynum > (m-1)/2)) {
            p -> keynum = p -> keynum + 1;
            for (j = p -> keynum; j > 1; j -= 1) {
                p -> key[j] = p -> key[j-1];
                p -> ptr[j] = p -> ptr[j-1];
            }
            p -> key[1] = ap -> key[r];
            p -> ptr[1] = p -> ptr[0];
            p -> ptr[0] = lc -> ptr[lc -> keynum];
            if (p -> ptr[0] != nullptr) {
                p -> ptr[0] -> parent = p;
            }
            ap -> key[r] = lc -> key[lc -> keynum];
            lc -> keynum = lc -> keynum - 1;
            finished = 1;
            break;
        }
        // borrow one key from right node
        else if (ap -> keynum > r && rc != nullptr && (rc -> keynum > (m-1)/2)) {
            p -> keynum = p -> keynum + 1;
            p -> key[p -> keynum] = ap -> key[r];
            p -> ptr[p -> keynum] = rc -> ptr[0];
            if (p -> ptr[p -> keynum] != nullptr) {
                p -> ptr[p -> keynum] -> parent = p;
            }
            ap -> key[r] = rc -> key[1];
            rc -> ptr[0] = rc -> ptr[1];
            for (j = 1; j < rc -> keynum; j += 1) {
                rc -> key[j] = rc -> key[j+1];
                rc -> ptr[j] = rc -> ptr[j+1];
            }
            rc -> keynum = rc -> keynum - 1;
            finished = 1;
            break;
        }
        r = 0;
        while (ap -> ptr[r] != p) {
            r += 1;
        }
        // combine with left brother
        if (r > 0 && (ap -> ptr[r-1] -> keynum <= (m-1)/2)) {
            lc = ap -> ptr[r-1];
            p -> keynum = p -> keynum + 1;
            for (j = p -> keynum; j > 1; j -= 1) {
                p -> key[j] = p -> key[j-1];
                p -> ptr[j] = p -> ptr[j-1];
            }
            p -> key[1] = ap -> key[r];
            p -> ptr[1] = p -> ptr[0];
            ap -> ptr[r] = lc;
            for (j = 1; j <= lc -> keynum + p -> keynum; j += 1) {
                lc -> key[lc -> keynum + j] = p -> key[j];
                lc -> ptr[lc -> keynum + j] = p -> ptr[j];
            }
            if (p -> ptr[0]) {
                for (j = 1; j <= p -> keynum; j += 1) {
                    if (p -> ptr[p -> keynum + j]) {
                        p -> ptr[p -> keynum + j] -> parent = lc;
                    }
                }
            }
            lc -> keynum = lc -> keynum + p -> keynum;
            for (j = r; j < ap -> keynum; j += 1) {
                ap -> key[j] = ap -> key[j+1];
                ap -> ptr[j] = ap -> ptr[j+1];
            }
            ap -> keynum = ap -> keynum - 1;
            delete pr;
            pr = nullptr;
            p = lc;
        }
        // combine with right brother
        else {
            rc = ap -> ptr[r+1];
            if (r == 0) {
                r += 1;
            }
            p -> keynum = p -> keynum + 1;
            p -> key[p -> keynum] = ap -> key[r];
            p -> ptr[p -> keynum]  = rc -> ptr[0];
            rc -> keynum = p -> keynum + rc -> keynum;
            ap -> ptr[r-1] = rc;
            for (j = 1; j <= rc -> keynum - p -> keynum; j += 1) {
                rc -> key[p -> keynum + j] = rc -> key[j];
                rc -> ptr[p -> keynum + j] = rc -> ptr[j];
            }
            for (j = 1; j <= p -> keynum; j += 1) {
                rc -> key[j] = p -> key[j];
                rc -> ptr[j] = p -> ptr[j];
            }
            rc -> ptr[0] = p -> ptr[0];
            if (p -> ptr[0]) {
                for (j = 1; j <= p -> keynum; j += 1) {
                    if (p -> ptr[p -> keynum + j]) {
                        p -> ptr[p -> keynum + j] -> parent = rc;
                    }
                }
            }
            for (j = r; j < ap -> keynum; j += 1) {
                ap -> key[j] = ap -> key[j+1];
                ap -> ptr[j] = ap -> ptr[j+1];
            }
            ap -> keynum = ap -> keynum - 1;
            delete pr;
            pr = nullptr;
            p = lc;
        }
        ap = ap -> parent;
        if (p -> parent -> keynum >= (m-1) / 2 || (ap == nullptr && p -> parent -> keynum > 0)) {
            finished = 1;
        }
        else if (ap == nullptr) {
            T = p;
            free(pr);
            pr = nullptr;
            finished = 1;
        }
        p = p -> parent;
    }
}

/**
 * re-arrange p->key[i]
 * @param p current_node
 * @param i target_index
 */
void Successor(BTree& p, int i) {
    BTree child = p -> ptr[i];
    while (child -> ptr[0] != nullptr) {
        child = child -> ptr[0];
    }
    p -> key[i] = child -> key[1];
    p = child;
}

/**
 * delete an element from a b_tree
 * @param p target node
 * @param i target index
 * @param T BTree
 */
void DeleteBTree(BTree& p, int i, BTree& T) {
    // use the successor to replace it
    if (p -> ptr[i] != nullptr) {
        // notice that p will change to the successor node after calling this function
        Successor(p, i);
        // delete the successor recursively
        DeleteBTree(p, 1, T);
    }
    // no successor
    else {
        // first remove i-th value directly
        Remove(p, i);
        // not enough to (m-1)/2, then need to restore b_tree
        if (p -> keynum < (m-1)/2) {
            Restore(p, i, T);
        }
    }
}

/**
 * print b_tree
 * @param p BTree
 */
void show_btree(BTree& p) {
   if (p == nullptr) {
       cout << "B-Tree is nullptr" << endl;
       return;
   }
   bool have_child = false;
   cout << "[";
   for (int i = 1; i <= p -> keynum; i += 1) {
       if (i != 1) {
           cout << " ";
       }
       cout << p -> key[i];
   }
   cout << "]";
   for (int i = 0; i <= p -> keynum; i += 1) {
       if (p -> ptr[i] != nullptr) {
           if (i == 0) {
               cout << "<";
           }
           else {
               cout << ",";
           }
           show_btree(p -> ptr[i]);
           have_child = true;
       }
   }
   if (have_child) {
       cout << ">";
   }
}


/**
 * destory b_tree
 * @param t BTree
 */
void Destory(BTree& t) {
    int i = 0;
    if (t != nullptr) {
        while (i < t -> keynum) {
            Destory(t -> ptr[i]);
            delete t -> ptr[i];
            i += 1;
        }
    }
    delete t;
    t = nullptr;
}


// api: create a new B_tree
void create_btree() {
    T = new BTNode;
    cout << "create B-Tree successfully" << endl;
}


// api: insert
void insert_key_type() {
    cout << "Enter an element to insert: ";
    key_type tmp;
    cin >> tmp;
    result p;
    SearchBTree(T, tmp, p);
    // not existed, then insert
    if (p.tag == 0) {
        // param: BTree, insert_value, target_node, target_index
        InsertBTree(T, tmp, p.pt, p.i);
        cout << "Insert successfully" << endl;
        show_btree(T);
        cout << endl;
    }
    else {
        cout << "The element is already in B-Tree" << endl;
    }
}


// api: search element
void find_key_type() {
    cout << "Enter an element to find: " << endl;
    key_type tmp;
    cin >> tmp;
    result p;
    SearchBTree(T, tmp, p);
    if (p.tag) {
        cout << "The element exists in B-Tree" << endl;
    }
    else {
        cout << "Lookup failure" << endl;
    }
}

// api: delete element
void delete_key_type() {
    cout << "Enter an element to be deleted: " << endl;
    key_type tmp;
    cin >> tmp;
    result p;
    SearchBTree(T, tmp, p);
    if (p.tag) {
        DeleteBTree(p.pt, p.i, T);
        cout << "Delete successfully" << endl;
        show_btree(T);
        cout << endl;
    }
    else {
        cout << "The element does not exist in B-Tree" << endl;
    }
}


int main()
{
    int order = 1;
    while (order) {
        cout << "********** Operation Menu **********" << endl;
        cout << "1: Create a 3-B-Tree" << endl;
        cout << "2: Insert an element" << endl;
        cout << "3: Find an element" << endl;
        cout << "4: Delete an element" << endl;
        cout << "5: Print B-Tree" << endl;
        cout << "6: Exit" << endl;
        cout << "7: Continue execution" << endl;
        cout << "********** Operation Menu **********" << endl;
        cin >> order;
        switch (order) {
            // Create a 3-B-Tree
            case 1:
                Destory(T);
                create_btree();
                break;
            // Insert an element
            case 2:
                insert_key_type();
                break;
            // Find an element
            case 3:
                find_key_type();
                break;
            // Delete an element
            case 4:
                delete_key_type();
                break;
            // Print B-Tree
            case 5:
                show_btree(T);
                cout << endl;
                break;
            // Exit
            case 6:
                cout << "Good Bye!" << endl;
                return 0;
            default:
                cout << "Invalid input, try again!" << endl;
        }
    }

    return 0;
}

/***** output: exist bug!!
C:\Users\Jiananyuan\CLionProjects\b_tree\cmake-build-debug\b_tree.exe
********** Operation Menu **********
1: Create a 3-B-Tree
2: Insert an element
3: Find an element
4: Delete an element
5: Print B-Tree
6: Exit
7: Continue execution
********** Operation Menu **********
2
Enter an element to insert:39
 Insert successfully
[39]
********** Operation Menu **********
1: Create a 3-B-Tree
2: Insert an element
3: Find an element
4: Delete an element
5: Print B-Tree
6: Exit
7: Continue execution
********** Operation Menu **********
2
Enter an element to insert:22
 Insert successfully
[22 39]
********** Operation Menu **********
1: Create a 3-B-Tree
2: Insert an element
3: Find an element
4: Delete an element
5: Print B-Tree
6: Exit
7: Continue execution
********** Operation Menu **********
2
Enter an element to insert:97
 Insert successfully
[22 39 97]
********** Operation Menu **********
1: Create a 3-B-Tree
2: Insert an element
3: Find an element
4: Delete an element
5: Print B-Tree
6: Exit
7: Continue execution
********** Operation Menu **********
2
Enter an element to insert:41
 Insert successfully
[22 39 41 97]
********** Operation Menu **********
1: Create a 3-B-Tree
2: Insert an element
3: Find an element
4: Delete an element
5: Print B-Tree
6: Exit
7: Continue execution
********** Operation Menu **********
2
Enter an element to insert:53
 Insert successfully
[41]<[22 39],[53 97]>
********** Operation Menu **********
1: Create a 3-B-Tree
2: Insert an element
3: Find an element
4: Delete an element
5: Print B-Tree
6: Exit
7: Continue execution
********** Operation Menu **********
2 
Enter an element to insert:13
 Insert successfully
[41]<[13 22 39],[53 97]>
********** Operation Menu **********
1: Create a 3-B-Tree
2: Insert an element
3: Find an element
4: Delete an element
5: Print B-Tree
6: Exit
7: Continue execution
********** Operation Menu **********
2
Enter an element to insert:21
 Insert successfully
[41]<[13 21 22 39],[53 97]>
********** Operation Menu **********
1: Create a 3-B-Tree
2: Insert an element
3: Find an element
4: Delete an element
5: Print B-Tree
6: Exit
7: Continue execution
********** Operation Menu **********
2
Enter an element to insert:40
 Insert successfully
[22 41]<[13 21],[39 40],[53 97]>
********** Operation Menu **********
1: Create a 3-B-Tree
2: Insert an element
3: Find an element
4: Delete an element
5: Print B-Tree
6: Exit
7: Continue execution
********** Operation Menu **********
2
Enter an element to insert:30
 Insert successfully
[22 41]<[13 21],[30 39 40],[53 97]>
********** Operation Menu **********
1: Create a 3-B-Tree
2: Insert an element
3: Find an element
4: Delete an element
5: Print B-Tree
6: Exit
7: Continue execution
********** Operation Menu **********
2
Enter an element to insert:27
 Insert successfully
[22 41]<[13 21],[27 30 39 40],[53 97]>
********** Operation Menu **********
1: Create a 3-B-Tree
2: Insert an element
3: Find an element
4: Delete an element
5: Print B-Tree
6: Exit
7: Continue execution
********** Operation Menu **********
2
Enter an element to insert:33
 Insert successfully
[22 33 41]<[13 21],[27 30],[39 40],[53 97]>
********** Operation Menu **********
1: Create a 3-B-Tree
2: Insert an element
3: Find an element
4: Delete an element
5: Print B-Tree
6: Exit
7: Continue execution
********** Operation Menu **********
2
Enter an element to insert:36
 Insert successfully
[22 33 41]<[13 21],[27 30],[36 39 40],[53 97]>
********** Operation Menu **********
1: Create a 3-B-Tree
2: Insert an element
3: Find an element
4: Delete an element
5: Print B-Tree
6: Exit
7: Continue execution
********** Operation Menu **********
2
Enter an element to insert:35
 Insert successfully
[22 33 41]<[13 21],[27 30],[35 36 39 40],[53 97]>
********** Operation Menu **********
1: Create a 3-B-Tree
2: Insert an element
3: Find an element
4: Delete an element
5: Print B-Tree
6: Exit
7: Continue execution
********** Operation Menu **********
2
Enter an element to insert:34
 Insert successfully
[22 33 36 41]<[13 21],[27 30],[34 35],[39 40],[53 97]>
********** Operation Menu **********
1: Create a 3-B-Tree
2: Insert an element
3: Find an element
4: Delete an element
5: Print B-Tree
6: Exit
7: Continue execution
********** Operation Menu **********
2 
Enter an element to insert:24
 Insert successfully
[22 33 36 41]<[13 21],[24 27 30],[34 35],[39 40],[53 97]>
********** Operation Menu **********
1: Create a 3-B-Tree
2: Insert an element
3: Find an element
4: Delete an element
5: Print B-Tree
6: Exit
7: Continue execution
********** Operation Menu **********
2
Enter an element to insert:29
 Insert successfully
[22 33 36 41]<[13 21],[24 27 29 30],[34 35],[39 40],[53 97]>
********** Operation Menu **********
1: Create a 3-B-Tree
2: Insert an element
3: Find an element
4: Delete an element
5: Print B-Tree
6: Exit
7: Continue execution
********** Operation Menu **********
2
Enter an element to insert:26
 Insert successfully
[33]<[22 27]<[13 21],[24 26],[29 30]>,[36 41]<[34 35],[39 40],[53 97]>>
********** Operation Menu **********
1: Create a 3-B-Tree
2: Insert an element
3: Find an element
4: Delete an element
5: Print B-Tree
6: Exit
7: Continue execution
********** Operation Menu **********
2
Enter an element to insert:17
 Insert successfully
[33]<[22 27]<[13 17 21],[24 26],[29 30]>,[36 41]<[34 35],[39 40],[53 97]>>
********** Operation Menu **********
1: Create a 3-B-Tree
2: Insert an element
3: Find an element
4: Delete an element
5: Print B-Tree
6: Exit
7: Continue execution
********** Operation Menu **********
2
Enter an element to insert:28
 Insert successfully
[33]<[22 27]<[13 17 21],[24 26],[28 29 30]>,[36 41]<[34 35],[39 40],[53 97]>>
********** Operation Menu **********
1: Create a 3-B-Tree
2: Insert an element
3: Find an element
4: Delete an element
5: Print B-Tree
6: Exit
7: Continue execution
********** Operation Menu **********
2
Enter an element to insert:29
 The element is already in B-Tree
********** Operation Menu **********
1: Create a 3-B-Tree
2: Insert an element
3: Find an element
4: Delete an element
5: Print B-Tree
6: Exit
7: Continue execution
********** Operation Menu **********
2
Enter an element to insert:31
 Insert successfully
[33]<[22 27]<[13 17 21],[24 26],[28 29 30 31]>,[36 41]<[34 35],[39 40],[53 97]>>
********** Operation Menu **********
1: Create a 3-B-Tree
2: Insert an element
3: Find an element
4: Delete an element
5: Print B-Tree
6: Exit
7: Continue execution
********** Operation Menu **********
22
Enter an element to insert:32
 Insert successfully
[33]<[22 27 30]<[13 17 21],[24 26],[28 29],[31 32]>,[36 41]<[34 35],[39 40],[53 97]>>
********** Operation Menu **********
1: Create a 3-B-Tree
2: Insert an element
3: Find an element
4: Delete an element
5: Print B-Tree
6: Exit
7: Continue execution
********** Operation Menu **********
2
Enter an element to insert:23
 Insert successfully
[33]<[22 27 30]<[13 17 21],[23 24 26],[28 29],[31 32]>,[36 41]<[34 35],[39 40],[53 97]>>
********** Operation Menu **********
1: Create a 3-B-Tree
2: Insert an element
3: Find an element
4: Delete an element
5: Print B-Tree
6: Exit
7: Continue execution
********** Operation Menu **********
4
Enter an element to be deleted:
21
Delete successfully
[33]<[22 27 30]<[13 17],[23 24 26],[28 29],[31 32]>,[36 41]<[34 35],[39 40],[53 97]>>
********** Operation Menu **********
1: Create a 3-B-Tree
2: Insert an element
3: Find an element
4: Delete an element
5: Print B-Tree
6: Exit
7: Continue execution
********** Operation Menu **********
4
Enter an element to be deleted:
27
Delete successfully
[33]<[22 26 30]<[13 17],[23 24],[28 29],[31 32]>,[36 41]<[34 35],[39 40],[53 97]>>
********** Operation Menu **********
1: Create a 3-B-Tree
2: Insert an element
3: Find an element
4: Delete an element
5: Print B-Tree
6: Exit
7: Continue execution
********** Operation Menu **********
4
Enter an element to be deleted:
32  // error!

Process finished with exit code 3

*****/
