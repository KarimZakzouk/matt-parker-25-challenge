// 🔍 Optimized Pangram Minus One Solver (Matt Parker Challenge)
// - Uses threads
// - Prunes unpromising paths
// - Avoids mutex in hot path
// - Buffers output per thread
// - ✅ Now with timing

#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <string>
#include <bitset>
#include <algorithm>
#include <cstdint>
#include <thread>
#include <mutex>
#include <sstream>
#include <chrono>

using namespace std;
using namespace std::chrono;

vector<uint32_t> wordMasks;
unordered_map<uint32_t, vector<string>> maskToWords;
mutex cout_mutex;

int charToBit(char c) {
    return 1 << (tolower(c) - 'a');
}

bool isValidWord(const string& word) {
    if (word.size() != 5) return false;
    int mask = 0;
    for (char c : word) {
        int bit = charToBit(c);
        if (mask & bit) return false; // duplicate letter
        mask |= bit;
    }
    return true;
}

uint32_t wordToMask(const string& word) {
    uint32_t mask = 0;
    for (char c : word) mask |= charToBit(c);
    return mask;
}

void loadWords(const string& filename) {
    ifstream file(filename);
    string word;
    while (file >> word) {
        if (!isValidWord(word)) continue;
        uint32_t mask = wordToMask(word);
        maskToWords[mask].push_back(word);
    }
    for (const auto& [mask, _] : maskToWords) {
        wordMasks.push_back(mask);
    }

    // Sort by decreasing number of unique letters to improve pruning
    sort(wordMasks.begin(), wordMasks.end(), [](uint32_t a, uint32_t b) {
        return __builtin_popcount(a) > __builtin_popcount(b);
    });
}

void findCombinations(int depth, int start, uint32_t used, uint32_t current[5], int& localCount, ostringstream& output) {
    if (depth == 5) {
        if (__builtin_popcount(used) == 25) {
            output << "Found: ";
            for (int i = 0; i < 5; ++i) {
                output << maskToWords[current[i]][0] << " ";
            }
            for (int i = 0; i < 26; ++i) {
                if ((used & (1 << i)) == 0) {
                    output << "(missing: " << (char)('a' + i) << ")";
                    break;
                }
            }
            output << '\n';
            localCount++;
        }
        return;
    }

    // Early pruning: not enough unique letters left
    if (__builtin_popcount(used) + (5 - depth) * 5 < 25) return;

    for (int i = start; i < (int)wordMasks.size(); ++i) {
        if (wordMasks[i] & used) continue;
        current[depth] = wordMasks[i];
        findCombinations(depth + 1, i + 1, used | wordMasks[i], current, localCount, output);
    }
}

void threadWorker(int startIndex, int endIndex, int& totalCount) {
    uint32_t current[5];
    int localCount = 0;
    ostringstream local_output;

    for (int i = startIndex; i < endIndex; ++i) {
        current[0] = wordMasks[i];
        findCombinations(1, i + 1, wordMasks[i], current, localCount, local_output);
    }

    // Safely print buffered output
    lock_guard<mutex> lock(cout_mutex);
    cout << local_output.str();
    totalCount += localCount;
}

int main() {
    auto start_time = high_resolution_clock::now();

    loadWords("words.txt");
    cout << "Loaded " << wordMasks.size() << " unique 5-letter words.\n";

    const int numThreads = thread::hardware_concurrency();
    vector<thread> threads;
    vector<int> counts(numThreads, 0);

    int total = wordMasks.size();
    int chunkSize = (total + numThreads - 1) / numThreads;

    for (int t = 0; t < numThreads; ++t) {
        int start = t * chunkSize;
        int end = min(total, (t + 1) * chunkSize);
        threads.emplace_back(threadWorker, start, end, ref(counts[t]));
    }

    for (auto& t : threads) t.join();

    int grandTotal = 0;
    for (int c : counts) grandTotal += c;

    auto end_time = high_resolution_clock::now();
    duration<double> elapsed = end_time - start_time;

    cout << "Done. Found " << grandTotal << " valid sets.\n";
    cout << "⏱️ Took " << elapsed.count() << " seconds.\n";
    return 0;
}
