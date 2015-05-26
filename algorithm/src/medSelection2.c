/*
 * medSelection2.c
 *
 *  Created on: May 25, 2015
 *      Author: hunglv
 */


int med_of_five(int a, int b, int c, int d, int e){
	int _array[5] = {a,b,c,d,e};
	int i = 0,j = 0;
	for(i = 0 ; i < 5; i++){
		int smaller = 0;
		int bigger = 0;
		for(j = 0; j < 5; j++)
		if(j != i){
			if(_array[j] < _array[i]) smaller++;
			if(_array[j] > _array[i]) bigger++;
		}
		if(smaller < 3 && bigger  < 3) return _array[i];
	}
  return -1;
}
int main(void){
//	int a[16] = {2,10,13,4,12,6,7,15,9,5,11,1,3,14,15,16};
//	int x = 0, y = 15;
//	int m = (y-x+1)/5 + ((y-x+1)%5 > 0? 1 : 0);
//	printf("%d\n",m);
//	int b[m];
//	int n = m;
//	if(m*5 > (y-x)+1){
//		b[m-1] = a[y];
//		 n = n-1;
//	}
//	int i = 0;
//	for (i = 0 ; i < n ; i++){
//		b[i] = med_of_five(a[5*i], a[5*i+1],a[5*i+2], a[5*i+3], a[5*i+4]);
//	}
//	printArr(b,m);
	//printf("\nexhaustive: %d\n", med_exhaustive(a, x, y, 0));
	//printArr(a,16);
	//printf("med: %d", quick_select(a,x,y,2));
	test_test();


}
void test_test(){

	int i = 0;
	for ( i = 0; i < 100; i++){
		int size = (rand()%10000)+1;
		int k = rand()%size+1;
		if (k == 0) k = 1;
		printf("testnum:  %d\n", i);
		printf("size: %d   k:%d \n", size, k);
		if(test(size,k,i) == -1){
			break;
		}//else printf("pass\n");
	}
}
int test(int size, int k, int test_num){
		int _array[size];
		memset(_array, 0, sizeof(_array));
		random_array(_array, size, 10000);
		int r = quick_select_2(_array, 0, size-1, k-1);
		buble_sort(_array, size);
		if(r == _array[k-1]) {
			printf("Pass\n");
			return r;
		}
		else {

			printf("Fail\n");
			printf("r: %d\n",r);
			printArr(_array, size);
			return -1;
		}

}

int quick_select_2(int _array[], int x, int y, int k){
	if(y - x <= 24) {
		return med_exhaustive(_array, x, y ,k);
	}
	else {
		int m = (y-x+1)/5 + ((y-x+1)%5 > 0? 1 : 0); // m = ceiling(n/5)
		int _brray[m];
        int n = m;
        if(m*5 > (y-x)+1){
            _brray[m-1] = _array[y];
            n = n-1;
        }
        int i = 0;
        for (i = 0 ; i < n ; i++){
        	_brray[i] = med_of_five(_array[5*i+x], _array[5*i+1+x],_array[5*i+2+x], _array[5*i+3+x], _array[5*i+4+x]);
        }
        int med_of_brray = quick_select_2(_brray, 0, m-1, m/2-1);
        int p  =  0;
        for( i = x ; i <= y  ; i++){
        	if (_array[i] == med_of_brray) p = i;
        }
        //printf("p=%d--x=%d--y=%d\n", p ,x ,y);
        int r = partition(_array, x, y, p);
		if ( k < r){
			return quick_select_2(_array, x, r-1, k);
		}else if (k > r) {
			return quick_select_2(_array, r+1, y, k);
		}else {
			return _array[r];
		}
	}
}


int med_exhaustive(int _array[], int x, int y, int k){
	if(k < x || k > y) printf("impossible\n");
	int i = x, j = x;
	for (i = x; i <= y; i++){
		for (j = i+1; j <= y; j++){
			if(_array[i] > _array[j]) swap(&_array[i], &_array[j]);
		}
	}
	return _array[k];
}


