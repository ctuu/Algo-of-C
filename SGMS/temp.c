void quicksort(int i, int j)
{
    int a = i;
    int b = j - 1;
    int temp;
    if (a < b)
    {
        while (a < b)
        {
            while (num[a] <= num[j] && a < b)
                a++;
            while (num[b] > num[j] && a < b)
                b--;
            if (num[a] >= num[j] && num[b] <= num[j])
            {
                temp = num[a];
                num[a] = num[b];
                num[b] = temp;
            }
        }
        if (num[a] > num[j])
        {
        swap();
        }
        quicksort(i, a);
        quicksort(b, j);
    }
    else if (a == b)
    {
        if (num[i] > num[j])
        {
            temp = num[i];
            num[i] = num[j];
            num[j] = temp;
        }
    }
}