#include <iostream>
#include <vector>

using namespace std;

int getSum(int BITree[], int index)
{
    int sum = 0; // Initialize result

    // index in BITree[] is 1 more than the index in arr[]
    index = index + 1;

    // Traverse ancestors of BITree[index]
    while (index>0)
    {
        // Add current element of BITree to sum
        sum += BITree[index];

        // Move index to parent node in getSum View
        index -= index & (-index);
    }
    return sum;
}

// Updates a node in Binary Index Tree (BITree) at given index
// in BITree. The given value 'val' is added to BITree[i] and
// all of its ancestors in tree.
void updateBIT(int BITree[], int n, int index, int val)
{
    // index in BITree[] is 1 more than the index in arr[]
    index = index + 1;

    // Traverse all ancestors and add 'val'
    while (index <= n)
    {
        // Add 'val' to current node of BI Tree
        BITree[index] += val;

        // Update index to that of parent in update View
        index += index & (-index);
    }
}

// Constructs and returns a Binary Indexed Tree for given
// array of size n.
int *constructBITree(int arr[], int n)
{
    // Create and initialize BITree[] as 0
    int *BITree = new int[n+1];
    for (int i=1; i<=n; i++)
        BITree[i] = 0;

    // Store the actual values in BITree[] using update()
    // for (int i=0; i<n; i++)
    //     updateBIT(BITree, n, i, arr[i]);

    return BITree;
}

int main() {

    int N, K;
    cin >> N >> K;

    int computer[N];
    for (int i = 0; i < N; i++)
        computer[i] = 0;

    int* BITree = constructBITree(computer, N);


    for (int k = 0; k < K; k++) {
        // Uncomment below lines to see contents of BITree[]
        char op;
        cin >> op;
        if (op == 'F') {
            int index;
            cin >> index;
            index -= 1;
            // Let use test the update operation
            if (computer[index] == 0) {
                computer[index] = 1;
                updateBIT(BITree, N, index, 1); //Update BIT for above change in arr[]
            }
            else {
                computer[index] = 0;
                updateBIT(BITree, N, index, -1); //Update BIT for above change in arr[]
            }
        }
        else {
            int start_index, end_index;
            cin >> start_index >> end_index;

            start_index -= 1;
            end_index -= 1;

            int wholeSum = getSum(BITree, end_index);
            int partialSum = 0;
            if (start_index != 0) {
                partialSum = getSum(BITree, start_index - 1);
            }
            cout << wholeSum - partialSum << endl;
        }
    }

}
/*
8 5
F 3
F 5
F 4
F 4
F 4

*/