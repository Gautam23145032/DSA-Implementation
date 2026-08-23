#include <bits/stdc++.h>
using namespace std;

int booth(string s) {

    int n = s.size();

    // Create s + s.
    //
    // Why?
    // Every rotation of s will appear as a substring of length n.
    //
    // Example:
    // s = "acab"
    // ss = "acabacab"
    //
    // rotations:
    // starting at 0 -> "acab"
    // starting at 1 -> "caba"
    // starting at 2 -> "abac"
    // starting at 3 -> "baca"
    string ss = s + s;

    // i and j are the starting positions of two
    // candidate rotations that we are currently comparing.
    //
    // Initially:
    // i = 0 -> rotation starting from index 0
    // j = 1 -> rotation starting from index 1
    int i = 0;
    int j = 1;

    // k tells us how many characters of the two
    // rotations have matched so far.
    int k = 0;

    // We only need to consider starting positions
    // from 0 to n-1 because there are n rotations.
    //
    // k < n because we only need to compare at most
    // n characters of two rotations.
    while (i < n && j < n && k < n) {

        // Compare the kth character of the two rotations.
        //
        // Rotation i:
        // ss[i], ss[i+1], ss[i+2], ...
        //
        // Rotation j:
        // ss[j], ss[j+1], ss[j+2], ...
        //
        // If they are equal, we cannot decide which
        // rotation is smaller yet.
        if (ss[i + k] == ss[j + k]) {

            // Move to the next character.
            k++;

            // Continue comparing.
            continue;
        }

        // If we reach here, the characters are different.
        //
        // Case 1:
        //
        // ss[i+k] > ss[j+k]
        //
        // Example:
        //
        // rotation i: ... c ...
        // rotation j: ... a ...
        //
        // Since a < c, rotation j is smaller.
        //
        // Therefore rotation i cannot be the answer.
        //
        // Moreover, because the first k characters were equal,
        // we can eliminate not only i but also the next k
        // possible starting positions.
        //
        // Therefore jump:
        //
        // i -> i + k + 1
        if (ss[i + k] > ss[j + k]) {
            i = i + k + 1;
        }

        // Case 2:
        //
        // ss[i+k] < ss[j+k]
        //
        // Then rotation i is smaller.
        //
        // Therefore rotation j cannot be the answer.
        //
        // We can skip j and the next k candidates.
        else {
            j = j + k + 1;
        }

        // It is possible that after jumping,
        // i and j become equal.
        //
        // We need two different candidate rotations,
        // so move j one step forward.
        if (i == j) {
            j++;
        }

        // We are comparing a new pair of rotations,
        // so we start comparing from their first character.
        k = 0;
    }

    // At this point, all other possible rotations
    // have been eliminated.
    //
    // The answer starts at either i or j.
    //
    // Take the smaller starting index.
    return min(i, j);
}


int main() {

    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Read the string.
    string s;
    cin >> s;

    int n = s.size();

    // Find the starting index of the
    // lexicographically smallest rotation.
    int pos = booth(s);

    // Print the rotation starting from pos.
    //
    // We use % n because after reaching the end
    // of the string, we need to continue from index 0.
    //
    // Example:
    //
    // s = "acab"
    // pos = 2
    //
    // i = 0 -> s[2] = a
    // i = 1 -> s[3] = b
    // i = 2 -> s[0] = a
    // i = 3 -> s[1] = c
    //
    // Output = "abac"
    for (int i = 0; i < n; i++) {
        cout << s[(pos + i) % n];
    }

    cout << '\n';

    return 0;
}