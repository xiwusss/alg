void swap(int arr[], int index_x, int index_y) 
{
	int temp;
	temp = arr[index_x];
	arr[index_x] = arr[index_y];
	arr[index_y] = temp;
}
