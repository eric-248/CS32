
int countIncludes(const string a1[], int n1, const string a2[], int n2)
{
    if (n1 < 0 || n2 < 0 || n2 > n1)
        return 0;
  
    if (n1 == 0)
        return 1;
    
    //base case
    if (a1[0] == a2[0]) {
        return countIncludes(a1 + 1, n1 - 1, a2 + 1, n2 - 1) + countIncludes(a1 + 1, n1 - 1, a2, n2);
    }
    else {
        return countIncludes(a1 + 1, n1 - 1, a2, n2);
    }
}

// Exchange two strings
void exchange(string& x, string& y)
{
    string t = x;
    x = y;
    y = t;
}

void separate(string a[], int n, string separator,
    int& firstNotLess, int& firstGreater)
{
    if (n < 0)
        n = 0;

    firstNotLess = 0;
    firstGreater = n;
    int firstUnknown = 0;
    while (firstUnknown < firstGreater)
    {
        if (a[firstUnknown] > separator)
        {
            firstGreater--;
            exchange(a[firstUnknown], a[firstGreater]);
        }
        else
        {
            if (a[firstUnknown] < separator)
            {
                exchange(a[firstNotLess], a[firstUnknown]);
                firstNotLess++;
            }
            firstUnknown++;
        }
    }
}

// Rearrange the elements of the array so that
// a[0] <= a[1] <= a[2] <= ... <= a[n-2] <= a[n-1]
// If n <= 1, do nothing.
void order(string a[], int n)
{
    if (n <= 1) {
        return;
    }

    //separate string
    int firstNotLess;
    int firstGreater;

    separate(a, n, a[n / 2], firstNotLess, firstGreater);

    //order string
    order(a, firstNotLess);
    order(a + firstGreater, n - firstGreater);
    
}
