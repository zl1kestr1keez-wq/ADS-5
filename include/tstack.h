// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TSTACK_H_
#define INCLUDE_TSTACK_H_

template<typename T, int kSize>
class TStack {
 private:
    T data[kSize];
    int topIndex;

 public:
    TStack() : topIndex(-1) {}

    void addToStack(const T& value) {
        if (stackIsFull()) return;
        data[++topIndex] = value;
    }

    T takeFromStack() {
        if (stackIsEmpty()) return T();
        return data[topIndex--];
    }

    T lookAtTop() const {
        if (stackIsEmpty()) return T();
        return data[topIndex];
    }

    bool stackIsEmpty() const {
        return topIndex == -1;
    }

    bool stackIsFull() const {
        return topIndex == kSize - 1;
    }

    void clearStack() {
        topIndex = -1;
    }
};

#endif  // INCLUDE_TSTACK_H_
