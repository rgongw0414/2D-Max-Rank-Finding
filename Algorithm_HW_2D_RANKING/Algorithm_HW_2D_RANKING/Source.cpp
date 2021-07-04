#include <iostream>
#include <string>
#include <vector>
#include <random>

using namespace std;

class coordinate
{
public:
	int x;
	int y;
	int rank = 0;
	int index;
	void print();	
};

void coordinate::print()
{
	cout << "x = " << x << ", y = " << y << ", rank = " << rank << ", index = " << index << endl;
}

void QuickSort(vector<coordinate> &coor_arr, int f, int l);
void QuickSortByIndex(vector<coordinate> &coor_arr, int f, int l);
void RankFinding(vector<coordinate> &coor_arr, int begin, int end);

int main()
{
	random_device rd;
	cout << "請決定有幾個座標(輸入0則自動產生隨機10個座標) : ";
	int num;
	cin >> num;
	string s;
	getline(cin, s);

	coordinate coor;
	vector<coordinate> coor_arr;
	if (num == 0)
	{
		num = 10;
		for (int i = 0; i < num; i++)
		{
			coor.x = rd() % 100;
			coor.y = rd() % 100;
			coor.index = i;
			coor_arr.push_back(coor);
		}
		cout << "\nThe random 10 coordinates : \n";
		for (int i = 0; i < num; i++)
		{
			coor_arr[i].print();
		}
	}
	else
	{			
		char Xi;
 		for (int i = 0; i < num; i++)
		{
			int index = 0;
			while ((Xi = getchar()) != '\n')
			{						
				if ((Xi != ' ') && (index == 0))
				{										
					ungetc(Xi, stdin);
					cin >> coor.x;					
					index++;
				}
				else if ((Xi != ' ') && (index != 0))
				{
					ungetc(Xi, stdin);
					cin >> coor.y;
					index++;
				}				
			}
			coor.index = i;
			coor_arr.push_back(coor);
		}		
	}
	
	QuickSort(coor_arr, 0, num - 1);
	cout << "\nBefore 2-D rank finding, the sorted coordinates(sorted by x, using quick sort) : \n";
	for (int i = 0; i < num; i++)
	{		
		coor_arr[i].print();
	}
	cout << endl;

	cout << "\nAfter 2-D rank finding, the sorted coordinates(sorted by x) : \n";
	RankFinding(coor_arr, 0, num - 1);	
	for (int i = 0; i < num; i++)
	{
		coor_arr[i].print();
	}

	cout << "\nAfter 2-D rank finding, the sorted coordinates(sorted by original index) : \n";
	QuickSortByIndex(coor_arr, 0, num - 1);
	for (int i = 0; i < num; i++)
	{
		coor_arr[i].print();
	}

	system("PAUSE");
}

void QuickSort(vector<coordinate> &coor_arr, int f, int l)
{
	if (f > l) return;
	int X = coor_arr[f].x;
	int i = f;
	int j = l;

	while (i < j)
	{
		while (coor_arr[j].x >= X && i != j)
		{
			j--;
		}
		swap(coor_arr[i], coor_arr[j]);
		while (coor_arr[i].x <= X && i != j)
		{
			i++;
		}
		swap(coor_arr[i], coor_arr[j]);
	}
	QuickSort(coor_arr, f, j - 1);
	QuickSort(coor_arr, j + 1, l);
}

void QuickSortByIndex(vector<coordinate> &coor_arr, int f, int l)
{
	if (f > l) return;
	int X = coor_arr[f].index;
	int i = f;
	int j = l;

	while (i < j)
	{
		while (coor_arr[j].index >= X && i != j)
		{
			j--;
		}
		swap(coor_arr[i], coor_arr[j]);
		while (coor_arr[i].index <= X && i != j)
		{
			i++;
		}
		swap(coor_arr[i], coor_arr[j]);
	}
	QuickSortByIndex(coor_arr, f, j - 1);
	QuickSortByIndex(coor_arr, j + 1, l);
}

void RankFinding(vector<coordinate> &coor_arr, int begin, int end)
{
	if ((end - begin) == 0) return;

	int median_index = (begin + end) / 2;	
	
	RankFinding(coor_arr, begin, median_index);	
	RankFinding(coor_arr, median_index + 1, end);
	
	for (int i = median_index + 1; i <= end; i++)
	{
		for (int j = begin; j <= median_index; j++)
		{
			if (i > j && coor_arr[i].y > coor_arr[j].y)
			{
				coor_arr[i].rank++;
			}
		}
	}
}