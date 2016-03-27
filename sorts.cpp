#include <iostream>
#include <vector>
#include <ctime>
#include <algorithm>
#include <climits>

using namespace std;

int gen() {
    return rand() % 10000;
}

bool check(vector<int> v) {
    int i;
    for(i = 0; i < v.size()-1; i++)
        if (v[i] > v[i+1])
            return false;
    return true;
}

class Sorts {
public:
    void start_insert(int n);
    void start_qsort(int n);
    void start_heap(int n);
    void start_merge(int n);
};

void insert_sort(vector<int> & A) {
    int j, i, key, n;
    n = A.size();
    for(j = 1; j < n; j++) {
        key = A[j];
        i = j - 1;
        while ((i >=0)&&(A[i] >= key)) {
            A[i+1] = A[i];
            i--;
        }
        i++;
        A[i] = key;
    }
}

int partition(vector<int> & A, int p, int r) {
    int x, i, j, s;
    x = A[r-1];
    i = p - 1;
    for(j = p; j <= r - 1; j++) {
        if (A[j-1] <= x) {
            i++;
            s = A[j-1];
            A[j-1] = A[i-1];
            A[i-1] = s;
        }
    }
    s = A[r-1];
    A[r-1] = A[i];
    A[i] = s;
    return i+1;
}

void qsort(vector<int> & A, int p, int r) {
    int q;
    if (p < r) {
        q = partition(A, p, r);
        qsort(A, p, q-1);
        qsort(A, q+1, r);
    }
}

int Left(int i) {
    return 2*i;
}

int Right(int i) {
    return 2*i+1;
}

void Max_heapify(vector<int> & A, int i, int heap_size) {
    int l, r, s;
    int largest;
    l = Left(i);
    r = Right(i);
    if ((l <= heap_size)&&(A[l-1] > A[i-1]))
        largest = l;
    else
        largest = i;
    if ((r <= heap_size)&&(A[r-1] > A[largest-1]))
        largest = r;
    if (largest != i) {
        s = A[i-1];
        A[i-1] = A[largest-1];
        A[largest-1] = s;
        Max_heapify(A, largest, heap_size);
    }
}

void Build_heap(vector<int> & A) {
    int i, n;
    n = A.size()/2;
    for(i = n; i > 0; i--)
        Max_heapify(A, i, A.size());
}

void Heap_sort(vector<int> & A) {
    Build_heap(A);
    int heap_size = A.size();
    int i, s;
    for(i = A.size(); i > 1; i--) {
        s = A[0];
        A[0] = A[i-1];
        A[i-1] = s;
        heap_size--;
        Max_heapify(A, 1, heap_size);
    }
}

void merge(vector<int> & A, int p, int q, int r, vector<int> & L, vector<int> & R) {
    int n1, n2, i, j, k;
    n1 = q - p + 1;
    n2 = r - q;
    for(i = 0; i < n1; i++)
        L[i] = A[p + i - 1];
    for(i = 0; i < n2; i++)
        R[i] = A[q + i];
    L[n1] = INT_MAX;
    R[n2] = INT_MAX;
    i = 0;
    j = 0;
    for(k = p; k <= r; k++) {
        if (L[i] <= R[j]) {
            A[k-1] = L[i];
            i++;
        } else {
            A[k-1] = R[j];
            j++;
        }
    }
}

void merge_sort2(vector<int> & A, int p, int r, vector<int> & L, vector<int> & R) {
    int q;
    if (p < r) {
        q = (p+r)/2;
        merge_sort2(A, p, q, L, R);
        merge_sort2(A, q+1, r, L, R);
        merge(A, p, q, r, L, R);
    }
}

void merge_sort(vector<int> & A) {
    int n = A.size();
    vector<int> L(n/2+2);
    vector<int> R(n/2+2);
    merge_sort2(A, 1, n, L, R);
}

void Sorts::start_insert(int n) {
    int i;
    vector<int> v(n);
    double time1, time2, time3;

    for(i = 0; i < n; i++)
        v[i] = i;
    time_t t1 = clock();
    insert_sort(v);
    t1 = clock() - t1;
    time1 = t1 / CLOCKS_PER_SEC;

    cout << check(v) << endl;

    for(i = 0; i < n; i++)
        v[i] = n - i;
    time_t t2 = clock();
    insert_sort(v);
    t2 = clock() - t2;
    time2 = t2 / CLOCKS_PER_SEC;

    cout << check(v) << endl;

    srand(time(NULL));
    generate(v.begin(), v.end(), gen);
    time_t t3 = clock();
    insert_sort(v);
    t3 = clock() - t3;
    time3 = t3 / CLOCKS_PER_SEC;

    cout << check(v) << endl;

    cout << "insert_sort :  " << time1 << "     " << time2 << "     " << time3 << endl;

}

void Sorts::start_qsort(int n) {
    int i;
    vector<int> v(n);
    double time1, time2, time3;
    
    for(i = 0; i < n; i++)
        v[i] = i;
    time_t t1 = clock();
    qsort(v, 1, n);
    t1 = clock() - t1;
    time1 = t1 / CLOCKS_PER_SEC;

    cout << check(v) << endl;

    for(i = 0; i < n; i++)
        v[i] = n - i;
    time_t t2 = clock();
    qsort(v, 1, n);
    t2 = clock() - t2;
    time2 = t2 / CLOCKS_PER_SEC;

    cout << check(v) << endl;
    

    srand(time(NULL));
    generate(v.begin(), v.end(), gen);
    time_t t3 = clock();
    qsort(v, 1, n);
    t3 = clock() - t3;
    time3 = t3 / CLOCKS_PER_SEC;

    cout << check(v) << endl;

    cout << "qsort :        " << time1 << "     " << time2 << "     " << time3 << endl;

}

void Sorts::start_heap(int n) {
    int i;
    vector<int> v(n);
    double time1, time2, time3;
    
    for(i = 0; i < n; i++)
        v[i] = i;
    time_t t1 = clock();
    Heap_sort(v);
    t1 = clock() - t1;
    time1 = t1 / CLOCKS_PER_SEC;

    cout << check(v) << endl;
    
    for(i = 0; i < n; i++)
        v[i] = n - i;
    time_t t2 = clock();
    Heap_sort(v);
    t2 = clock() - t2;
    time2 = t2 / CLOCKS_PER_SEC;

    cout << check(v) << endl;

    srand(time(NULL));
    generate(v.begin(), v.end(), gen);
    time_t t3 = clock();
    Heap_sort(v);
    t3 = clock() - t3;
    time3 = t3 / CLOCKS_PER_SEC;

    cout << check(v) << endl;

    cout << "heap sort :    " << time1 << "     " << time2 << "     " << time3 << endl;

}

void Sorts::start_merge(int n) {
    int i;
    vector<int> v(n);
    double time1, time2, time3;
    
    for(i = 0; i < n; i++)
        v[i] = i;
    time_t t1 = clock();

    merge_sort(v);

    t1 = clock() - t1;
    time1 = t1 / CLOCKS_PER_SEC;

    cout << check(v) << endl;
    
    for(i = 0; i < n; i++)
        v[i] = n - i;
    time_t t2 = clock();

    merge_sort(v);

    t2 = clock() - t2;
    time2 = t2 / CLOCKS_PER_SEC;

    cout << check(v) << endl;

    srand(time(NULL));
    generate(v.begin(), v.end(), gen);
    time_t t3 = clock();

    merge_sort(v);

    t3 = clock() - t3;
    time3 = t3 / CLOCKS_PER_SEC;

    cout << check(v) << endl;

    cout << "merge sort:    " << time1 << "     " << time2 << "     " << time3 << endl;

}


int main()
{
    int n, i, x;
    Sorts sort;

    cout << "n = 8" << endl;
    cout << "       sorted->    sorted<-    unsorted" << endl;
    sort.start_insert(8);
    sort.start_qsort(8);
    sort.start_heap(8);
    sort.start_merge(8);
    cout << endl;

    cout << "n = 16" << endl;
    cout << "       sorted->    sorted<-    unsorted" << endl;
    sort.start_insert(16);
    sort.start_qsort(16);
    sort.start_heap(16);
    sort.start_merge(16);
    cout << endl;

    cout << "n = 32"<< endl;
    cout << "       sorted->    sorted<-    unsorted" << endl;
    sort.start_insert(32);
    sort.start_qsort(32);
    sort.start_heap(32);
    sort.start_merge(32);
    cout << endl;

    cout << "n = 256"<< endl;
    cout << "       sorted->    sorted<-    unsorted" << endl;
    sort.start_insert(256);
    sort.start_qsort(256);
    sort.start_heap(256);
    sort.start_merge(256);
    cout << endl;

    cout << "n = 1000"<< endl;
    cout << "       sorted->    sorted<-    unsorted" << endl;
    sort.start_insert(1000);
    sort.start_qsort(1000);
    sort.start_heap(1000);
    sort.start_merge(1000);
    cout << endl;

    cout << "n = 10000"<< endl;
    cout << "       sorted->    sorted<-    unsorted" << endl;
    sort.start_insert(10000);
    //sort.start_qsort(10000);
    sort.start_heap(10000);
    sort.start_merge(10000);
    cout << endl;

    cout << "n = 1 000 000"<< endl;
    cout << "       sorted->    sorted<-    unsorted" << endl;
    //sort.start_qsort(1000000);
    sort.start_heap(1000000);
    sort.start_merge(1000000);
    cout << endl;

    cin >> x;
    return 0;
}