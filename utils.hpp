#ifndef UTILS_H
#define UTILS_H

bool isValid(int index, int size)
{
    return (index>=0 && index<size);
}

bool isValid(int left, int right, int size)
{
    return (left>=0 && left<size && right>=0 && right<size && left<=right);
}

int calculate_n(int size)
{
    int n = 1;
    while(n < size){
        n = n*2;
    }
    n = n*2;

    return n;
}
#endif
