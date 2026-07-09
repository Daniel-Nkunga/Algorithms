#include <vector>
#include <msort.hpp>
#include <graph.hpp>

// Merges array[l..m-1] and array[m..r-1]  (all indices exclusive on the right)
template <typename T>
void merge(std::vector<T> &array, int l, int m, int r) {
    std::vector<T> L(array.begin() + l, array.begin() + m);
    std::vector<T> R(array.begin() + m, array.begin() + r);

    int i = 0, j = 0, k = l;

    while (i < (int)L.size() && j < (int)R.size()) {
        if (L[i] <= R[j])
            array[k++] = L[i++];
        else
            array[k++] = R[j++];
    }

    while (i < (int)L.size())
        array[k++] = L[i++];

    while (j < (int)R.size())
        array[k++] = R[j++];
}

template <typename T>
void msort(std::vector<T> &array, int l, int r) {
    if (array.empty() || r - l <= 1)
        return;

    int mid = l + (r - l) / 2;

    msort(array, l, mid);
    msort(array, mid, r);

    merge(array, l, mid, r);
}

// Explicit instantiations
template void msort<Edge>(std::vector<Edge> &array, int l, int r);
template void msort<int>(std::vector<int> &array, int l, int r);