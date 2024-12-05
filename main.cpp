#include <cstdio>
#include <cstring>
#include <climits>

int arr[] = {1,2,3,4,2,1,5,6,2,1,2,3,7,6,3,2,1,2,3,6};
int n = 20;

int calcPageFaults(int* arr, int n, int frameNum, const char* algorithm);

int main() {
    for (int i = 1; i <= 7; i++) {
        printf("%d Frame Page Fault # using FIFO : \t\t\t\t %d\n", i, calcPageFaults(arr, n, i, "FIFO"));
        printf("%d Frame Page Fault # using LRU : \t\t\t\t %d\n", i, calcPageFaults(arr, n, i, "LRU"));
        printf("%d Frame Page Fault # using Optimal Replacement : %d\n", i, calcPageFaults(arr, n, i, "Optimal Replacement"));
        printf("\n");
    }

    return 0;
}

int calcPageFaults(int* arr, int n, int frameNum, const char* algorithm) {
    int result = 0;
    int frame[frameNum];
    memset(frame, -1, sizeof(frame));

    if (strcmp(algorithm, "LRU") == 0) {
        int lastUsed[frameNum];
        for (int i = 0; i < frameNum; i++) lastUsed[i] = -1;

        for (int i = 0; i < n; i++) {
            bool found = false;
            for (int j = 0; j < frameNum; j++) {
                if (frame[j] == arr[i]) {
                    found = true;
                    lastUsed[j] = i;
                    break;
                }
            }
            if (!found) {
                result++;
                int lruIndex = 0;
                for (int j = 1; j < frameNum; j++) {
                    if (lastUsed[j] < lastUsed[lruIndex]) {
                        lruIndex = j;
                    }
                }
                frame[lruIndex] = arr[i];
                lastUsed[lruIndex] = i;
            }
        }

    } else if (strcmp(algorithm, "FIFO") == 0) {
        int oldest = 0;

        for (int i = 0; i < n; i++) {
            bool found = false;

            for (int j = 0; j < frameNum; j++) {
                if (frame[j] == arr[i]) {
                    found = true;
                    break;
                }
            }
            if (!found) {
                result++;
                frame[oldest] = arr[i];
                oldest = (oldest + 1) % frameNum;
            }
        }

    } else if (strcmp(algorithm, "Optimal Replacement") == 0) {
        for (int i = 0; i < n; i++) {
            bool found = false;

            for (int j = 0; j < frameNum; j++) {
                if (frame[j] == arr[i]) {
                    found = true;
                    break;
                }
            }

            if (!found) {
                result++;
                int replaceIndex = -1;
                int farthest = -1;

                for (int j = 0; j < frameNum; j++) {
                    int nextUse = INT_MAX;
                    for (int k = i + 1; k < n; k++) {
                        if (frame[j] == arr[k]) {
                            nextUse = k;
                            break;
                        }
                    }
                    if (nextUse > farthest) {
                        farthest = nextUse;
                        replaceIndex = j;
                    }

                    if (nextUse == INT_MAX) {
                        replaceIndex = j;
                        break;
                    }
                }
                frame[replaceIndex] = arr[i];
            }
        }
    }
    return result;
}
