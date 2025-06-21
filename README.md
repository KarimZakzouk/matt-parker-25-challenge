# 🧩 Matt Parker's 5-Word Alphabet Challenge

Inspired by Matt Parker’s brilliant linguistic puzzle, this project explores the challenge of finding **five English words** that together use **25 unique letters** — every letter of the alphabet **except one**.

---

## 🎯 The Goal

Find sets of **five valid English words** that:
- Use a total of **25 different letters**
- Have **no repeated letters across the words**
- Miss **exactly one letter** from A–Z

This is also known as a **"Pangram Minus One"**.

---

## ✅ Example

Example 5-word set (missing letter: **Q**):

```
fjord
blanket
chimp
vex
swag
```

These words together use all letters except **Q**.

---

## 🚀 How to Run

### 1. 🛠️ Prerequisites

- A C++ compiler that supports C++17 or later (e.g., `g++`)
- A terminal (Linux, macOS, or WSL on Windows)
- A word list file like `words.txt` (one word per line, 5-letter words recommended)

### 2. 🧾 Compile the Program

From your project folder:

```bash
g++ solution.cpp -o solution -O2 -std=c++17 -pthread
```

### 3. ▶️ Run the Program

Assuming your `words.txt` file is in the same folder:

```bash
./solution
```

> The program automatically reads `words.txt`.

You’ll see output like:

```
Found: fjord blanket chimp vex swag (missing: q)
...
Done. Found 163 valid sets.
```

---

## 🗂️ Folder Structure

- `words.txt` – input dictionary file (you can replace this with any word list)
- `solution.cpp` – main C++ program to find valid 5-word sets

---

## 🤝 Contributions

Pull requests welcome! You can contribute by:
- Adding new optimized search strategies (e.g., GPU, distributed)
- Improving speed/memory efficiency
- Adding visualizations or statistics

---

## 📚 Credits

- Inspired by [Matt Parker (Stand-up Maths)](https://www.youtube.com/user/standupmaths)
- Word list: [SCOWL](http://wordlist.aspell.net/) and others

---

## 🧩 License

MIT — free to use, modify, and share.
