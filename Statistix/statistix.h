///Bartlomiej Stepek

void merge(int *array, int left, int middle, int right){
    int arr2[right + 1], i = left, j = middle + 1;

    for(int a = left; a <= right; a++)
        arr2[a] = array[a];

    for(int k = left; k <= right; k++) {
        if(i <= middle){
            if(j <= R){
                if(arr2[j] < arr2[i]){
                    array[k] = arr2[j];
                    j++;
                }
                else{
                    array[k] = arr2[i];
                    i++;
                }
            }
            else{
                array[k] = arr2[i];
                i++;
            }
        }
        else{
            array[k] = arr2[j];
            j++;
        }
    }
}

void sort(int *array, int left, int right){
    if(right <= left)
        return;
    int middle = (right + left)/2;
    sort(array, left, middle);
    sort(array, middle+1, right);
    merge(array, left, middle, right);
}


bool expval(unsigned int n, const double* x, const double* p, double(*f)(double), double& r){
    float sum = 0, s = 1;
    r = 0;
    for(int i = 0; i < n; i++){
        sum += p[i];
        if(p[i]<0 || sum >= 1) return false;
    }
    for(int i=0; i<n; i++){
        r+= f(x[i]) * p[i];
        s-= p[i];
    }
    r += f(x[n]) * s;
    return true;
}

bool median(unsigned int n, const int* t, int(*f)(int), bool(*p)(int), double& r){
    int counter = 0, counter2 = 0;
    int* Z = new int[n];
    for(int i=0; i<n; i++)
        if(p(t[i]))
            Z[counter++] = f(t[i]);

    if(counter == 0)
        return false;

    else {
        sort(Z, 0, counter-1);
        for(int i=0; i < counter; i++)
            if(Z[i] > Z[i-1] || i == 0)
                Z[counter2++] = Z[i];

        if(counter2 % 2 == 0)
            r = (double)(Z[counter2/2 - 1] + Z[counter2/2])/2;
        else
            r = Z[counter2/2];
        delete[] Z;
        return true;
    }
}

unsigned int gcd(unsigned int n, const int* t, int* r = nullptr){
    unsigned int max = 1;
    int* Z = new int[n];
    int counter = 0;
    for(int i=0; i < n; i++)
        if(t[i]!=0)
            Z[counter++]=t[i];

    if(counter == 0) {
        delete[] Z;
        return 0;
    }
    else {
        unsigned int the_smallest = Z[0];
        for(int i = 1; i<counter; i++)
            if(Z[i]>0){
                if(Z[i] < the_smallest)
                    the_smallest = Z[i];
            }
            else{
                if(-Z[i] < the_smallest)
                    the_smallest = -Z[i];
            }

        unsigned int amount_of_dividers;
        for(int i = 2; i <= the_smallest; i++){
            amount_of_dividers = 0;
            for(int j=0; j < counter; j++){
                if(Z[j] % i == 0)
                    amount_of_dividers++;

            if(amount_of_dividers==counter)
                max = i;
        }
    if(r!= nullptr)
        for(int i=0; i < n; i++)
            r[i] = t[i]/max;

    delete []Z;
    return max;
    }
}

unsigned int count(unsigned int n, const int* t, bool(*p)(int,int)=nullptr){
    unsigned int counter = 0, counter2 = 0;
    int* Z = new int[n];
    for(int i = 0; i < n; i++)
        Z[i]=t[i];

    sort(Z, 0, n-1);
    if(p == nullptr){
        for(int i=0; i<n; i++)
            if(Z[i]>Z[i-1] || i==0)
                counter++;

        delete[] Z;
        return counter*counter;
    }
    else{
        int* array = new int[n];
        for(int i=0; i<n; i++)
            if(Z[i]>Z[i-1] || i==0)
                array[counter2++] = Z[i];

        for(int i=0; i<counter2; i++)
            for(int j=0; j<counter2; j++)
                if(p(array[i],array[j]))
                    counter++;

        delete[] array;
        delete[] Z;
        return counter;
    }
}
