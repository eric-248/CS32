
bool allTrue(const string a[], int n)
{
    if (n < 0) {
        return false;
    }
    //base case
    if (n == 0) {
        return true;
    }
    return (somePredicate(a[n - 1]) && allTrue(a, n - 1));
}

int countTrue(const string a[], int n)
{
    //base case
    if (n <= 0) {
        return 0;
    }

    if (somePredicate(a[n - 1])) {
        return countTrue(a, n - 1) + 1;
    }
    
    return countTrue(a, n - 1);

}

int firstTrue(const string a[], int n)
{
    if (n <= 0) {
        return -1;
    }

    if (somePredicate(a[0])) {
        return 0;
    }
    
    return firstTrue(a + 1, n) + 1;
}

int positionOfMax(const string a[], int n)
{
    if (n <= 0) {
        return -1;
    }

    if (n == 1) {
        return 0;
    }

    //split array
    int mid = n / 2;
    int max1 = positionOfMax(a, mid);
    int max2 = positionOfMax(a + mid, n - mid) + mid;

    if (max1 > max2) {
        return max1;
    }
    else {
        return max2;
    }


}

bool contains(const string a1[], int n1, const string a2[], int n2)
{
    if (n1 < 0 || n2 < 0 || n2 > n1) {
        return false;
    }

    if (n2 == 0) {
        return true;
    }

    if (a1[0] == a2[0] && contains(a1 + 1, n1 - 1, a2 + 1, n2 - 1)) {
        return true;
    }
    else {
        return contains(a1 + 1, n1 - 1, a2, n2);
    }
}
