int prem_root(int P)
{
    int e1 = 0;
    for (int i = 2; i < P; i++)
    {
        bool checker = true;
        for (int j = 1; j < P - 1; j++)
        {
            int mod = 1, k = j;
            while (k--)
            {
                mod = (mod * i) % P;
            }
            if (mod == 1)
            {
                checker = false;
                break;
            }
        }
        if (checker)
        {
            e1 = i;
            break;
        }
    }
    return e1;
}