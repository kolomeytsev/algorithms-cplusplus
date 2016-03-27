#include <iostream>
#include <vector>

using namespace std;

template <class T>
class Queue {
    vector<T> heap;
    void heapify(int i);
    void up_heapify(int i);
    int Left(int i);
    int Right(int i);
    int Parent(int i);
public:
    void push(T t);
    T pop();
    void make_heap(vector<T> vect);
    void print();
};

template <class T>
int Queue<T>::Left(int i) {
    return 2*i;
}

template <class T>
int Queue<T>::Right(int i) {
    return 2*i+1;
}

template <class T>
int Queue<T>::Parent(int i) {
    return i/2;
}

template <class T>
void Queue<T>::heapify(int i) {
    int l, r, s, largest;
    int heap_size = heap.size();
    l = Left(i);
    r = Right(i);
    if ((l <= heap_size)&&(heap[l-1] > heap[i-1]))
        largest = l;
    else
        largest = i;
    if ((r <= heap_size)&&(heap[r-1] > heap[largest-1]))
        largest = r;
    if (largest != i) {
        s = heap[i-1];
        heap[i-1] = heap[largest-1];
        heap[largest-1] = s;
        heapify(largest);
    }
}

template <class T>
void Queue<T>::up_heapify(int i) {
    int p, s, largest;
    int heap_size = heap.size();
    if (i != 1) {
        p = Parent(i);
        if (heap[p-1] > heap[i-1])
            largest = p;
        else
            largest = i;
        if (largest == i) {
            s = heap[i-1];
            heap[i-1] = heap[p-1];
            heap[p-1] = s;
            up_heapify(p);
        }
    }
}

template <class T>
void Queue<T>::make_heap(vector<T> vect) {
    heap = vect;
}

template <class T>
void Queue<T>::print() {
    int i, n;
    n = heap.size();
    cout << "heap:  " << endl;
    for(i = 0; i < n; i++)
        cout << heap[i] << " ";
    cout << endl;
}

template <class T>
void Queue<T>::push(T t) {
    int n;
    heap.push_back(t);
    n = heap.size();
    //cout << n << " elem: " << heap[n-1] << endl;
    up_heapify(n);
}

template <class T>
T Queue<T>::pop() {
    int n = heap.size();
    if (n == 0) {
        throw "heap underflow!!!";
    }
    T s, x;
    s = heap[n-1];
    heap[n-1] = heap[0];
    heap[0] = s;
    x = heap.back();
    heap.pop_back();
    heapify(1);
    return x;
}



int main()
{
    Queue<int> q;
    vector<int> v;
    q.push(5);
    q.push(8);
    q.push(6);
    q.push(4);
    q.push(9);
    q.push(7);
    q.push(1);
    q.push(3);
    q.push(2);
    q.print();
    cout << "popping" << endl;
    cout << q.pop() << endl;
    cout << q.pop() << endl;
    cout << q.pop() << endl;
    cout << q.pop() << endl;
    cout << q.pop() << endl;
    cout << q.pop() << endl;
    cout << q.pop() << endl;
    cout << q.pop() << endl;
    cout << q.pop() << endl;

    Queue<int> q0;
    try {
        cout << q.pop() << endl;
    }
    catch (char* s) {
        cout << s << endl;
    }
    int x;
    cin >> x;
    return 0;
}