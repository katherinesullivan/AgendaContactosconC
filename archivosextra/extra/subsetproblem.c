// A Dynamic Programming solution
// for subset sum problem
#include <stdio.h>

// Returns true if there is a subset of set[]
// with sun equal to given sum
int isSubsetSum(int set[], int n, int sum)
{
	// The value of subset[i][j] will be true if
	// there is a subset of set[0..j-1] with sum
	// equal to i
	int subset[n + 1][sum + 1];

	// If sum is 0, then answer is true
	for (int i = 0; i <= n; i++) {
		subset[i][0] = 1;
    }

	// If sum is not 0 and set is empty,
	// then answer is false
	for (int i = 1; i <= sum; i++) {
		subset[0][i] = 0;
    }

	// Fill the subset table in botton up manner
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= sum; j++) {
			if (j < set[i - 1]) {
				subset[i][j] = subset[i - 1][j];
            }
			if (j >= set[i - 1]) {
				subset[i][j] = subset[i - 1][j] || subset[i - 1][j - set[i - 1]];
            }
		}
	}

	// uncomment this code to print table
    printf("   0   1   2   3   4   5   6   7   8   9\n");
    printf("-----------------------------------------\n");
	for (int i = 0; i <= n; i++)
	{
	for (int j = 0; j <= sum; j++)
		printf ("%4d", subset[i][j]);
	printf("\n");
	}

    int new_sum = sum;
    int i = n;
    /*for (;i > 0; i--) {
        printf("i is equal to %d\n", i);
        if (!subset[i-1][new_sum]) {
            printf("%d\n", set[i-1]);
            new_sum = new_sum - set[i-1];
        }
    }*/
    while (i > 0 && (new_sum != 0)) {
        if (!subset[i-1][new_sum]) {
            printf("%d\n", set[i-1]);
            new_sum = new_sum - set[i-1];
        }
        i--;
    }
    if (new_sum < 0) {
        printf("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\n");
    }

	return subset[n][sum];
}

// Driver code
int main()
{
	int set[] = {1,1,1, 2, 4, 5, 2};
	int sum = 6;
	int n = sizeof(set) / sizeof(set[0]);
	if (isSubsetSum(set, n, sum) == 1)
		printf("Found a subset with given sum\n");
	else
		printf("No subset with given sum\n");
	return 0;
}
// This code is contributed by Arjun Tyagi.
