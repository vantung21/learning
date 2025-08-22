#include <iostream>

using namespace std;

bool ascending(int l, int r){
    return l >r;
}
bool descending(int l, int r){
    return l < r;
}
void swap(int &x, int &y){
    int t = x; x = y; y = t;
}

//selectionSort
void selectionSort(int *arr, int n, bool cmp(int, int)){
    for(int i = 0; i<n-1; i++){
        int idx = i;
        for(int j =i+1; j<n; j++){
            if(cmp(arr[idx], arr[j])) idx = j;
        }
        swap(arr[i], arr[idx]);
    }
}

//insertionSort
void insertionSort(int *arr, int n, bool cmp(int, int)){
    for(int i=1; i<n; i++){
        int key = arr[i];
        int j = i-1;
        while(j >= 0 && cmp(arr[j], key)){
            arr[j+1] = arr[j];
            j--;
        }
        arr[j+1] = key;
    }
}

//BubbleSoft
void BubbleSoft(int *arr, int n, bool cmp(int , int)){
    for(int i =0 ; i<n-1; i++){
        for(int j=0; j< n-i-1; j++){
            if(cmp(arr[j], arr[j+1])) swap(arr[j], arr[j+1]);
        }
    }
}

//ShellSort
void ShellSort(int *arr, int n, bool cmp(int, int)){
    for(int gap = n/2; gap >= 1; gap/=2){
        for(int i = gap; i<n; i++){
            int key = arr[i];
            int j = i;
            while(j >= gap && cmp(arr[j-gap], key)){
                arr[j] = arr[j-gap];
                j -= gap;
            }
            arr[j] = key;
        }
    }
}

//QuickSort
int partition(int *arr, int l, int r, bool cmp(int, int)){
    int pivot = arr[r];
    int i = l-1;
    for(int j = l; j <= r; j++){
        if(!cmp(arr[j], pivot)){
            i++;
            swap(arr[i], arr[j]);
        }
    }
    return i;
}

void quickSort(int *arr, int l, int r, bool cmp(int, int)){
    if(l < r){
        int p = partition(arr, l, r, cmp);
        quickSort(arr, l, p-1, cmp);
        quickSort(arr, p+1, r, cmp);
    }
}

//HeapSort
void heapify(int *arr, int n, int i, bool cmp(int, int)){
    int key = i;
    int l = 2*i +1;
    int r = 2*i + 2;
    if(l<n && cmp(arr[l], arr[key])) key = l;
    if(r<n && cmp(arr[r], arr[key])) key = r;
    if(key != i){
        swap(arr[key], arr[i]);
        heapify(arr, n, key, cmp);
    }
}
void heapSort(int *arr, int n, bool cmp(int, int)){
    for(int i = n/2; i>= 0; i--){
        heapify(arr, n, i, cmp);
    }
    for(int i =n-1; i>=0; i--){
        swap(arr[i], arr[0]);
        heapify(arr, i, 0, cmp);
    }
}

//MergeSort
void merge(int *arr, int l, int m, int r, bool cmp(int, int)){
    int n1 = m-l+1;
    int n2 = r-m;
    int a1[n1], a2[n2];
    for(int i = 0; i<n1; i++){
        a1[i] = arr[l+i];
    }
    for(int i = 0; i<n2; i++){
        a2[i] = arr[m+1+i];
    }

    int i = 0, j = 0, k = l;
    while(i<n1 &&j <n2){
        if(cmp(a1[i], a2[j])) arr[k++] = a2[j++];
        else arr[k++] = a1[i++];
    }
    while(i < n1) arr[k++] = a1[i++];
    while(j <n2) arr[k++] = a2[j++];
}
void mergeSort(int *arr, int l, int r, bool cmp(int, int)){
    if(l<r){
        int m = l + (r-l)/2;
        mergeSort(arr, l, m, cmp);
        mergeSort(arr, m+1, r, cmp);
        merge(arr, l, m, r, cmp);
    }
}



void xuat(int *arr, int n){
    for(int i = 0; i < n; i++){
        cout << arr[i] << " ";
    }
    cout << endl;
}

void nhap(int* &arr, int &n){
    cout << "So luong phan tu cua mang la: ";
    cin >> n;
    while(n <= 0){
        cout << "So luong phan tu cua mang la: ";
        cin >> n;
    }
    if(arr != NULL) delete[] arr;
    arr = new int[n];
    cout << "nhap cac phan tu cua mang: \n";
    for(int i = 0; i< n; i++){
        cin >> arr[i];
    }
}
void menuSort(){
    cout << "Lua chon cach sap xep:\n";
    cout << "1-selectionSort\n";
    cout << "2-InsertionSort\n";
    cout << "3-BubbleSoft\n";
    cout << "4-ShellSort\n";
    cout << "5-QuickSort\n";
    cout << "6-HeapSort\n";
    cout << "7-MergeSort\n";
    cout<< "0-thoat\n";
    cout << "chon: ";
}
// SelectionSort, InsertionSort, BubbleSoft, ShellSort, QuickSort, HeapSort, MergeSort)

int binarySearch(int* arr, int l, int r, int x, bool (*cmp)(int, int)){
    while(l <= r){
        int m = l + (r-l)/2;
        if(arr[m] == x) return m;
        if(cmp(arr[m], x)) r = m-1;
        else l = m+1;
    }
    return -1;
}
int main(){
    int n;
    int *arr = NULL;
    nhap(arr, n);
    xuat(arr, n);

    void (*sort)(int* , int, bool(*)(int, int)) = NULL;
    bool (*order)(int, int) = NULL;
    
    while(1){
        menuSort();
        int choice, orderchoice;
        cin >> choice;
        if(choice == 0) break;

        cout << "chon thu tu sap xep (1-tang, 2-giam): ";
        cin >> orderchoice;
        order = (orderchoice==1)?ascending:descending;
        switch(choice){
            case 1:
            sort = selectionSort; break;
            case 2:
            sort = insertionSort; break;
            case 3:
            sort = BubbleSoft; break;
            case 4:
            sort = ShellSort; break;
            case 5:
            quickSort(arr, 0, n-1, order);
            cout << "da sap xep bang quickSort.\n"; 
            xuat(arr,n);
            continue;
            case 6:
            sort = heapSort; break;
            case 7:
            mergeSort(arr, 0, n-1, order);
            cout <<"da sap sep bang mergeSort.\n"; 
            xuat(arr, n);
            continue;
        }
        sort(arr, n,order);
        cout << "da sap xep:\n"; xuat(arr, n);
    }

    int x;
    cout << "nhap so can tim: "; cin >> x;
    int check = binarySearch(arr, 0, n-1, x, order);
    if(check != -1) cout << "tim thay so " << x << " o vi tri thu "<< check + 1<< " trong mang" << endl;
    else cout<< "khong tim thay " << x<< " trong mang!" << endl;
    delete[] arr;
    return 0;
}