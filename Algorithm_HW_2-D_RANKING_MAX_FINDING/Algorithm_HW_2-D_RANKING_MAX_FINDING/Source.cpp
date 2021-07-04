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
	int index;
	bool max = false;
	bool dominant_flag = false;  // 若被dominant則設為true
	void print();
};

void coordinate::print()
{
	cout << "x = " << x << ", y = " << y << ", index = " << index
		<< ", max = " << max << endl;
}

void QuickSort(vector<coordinate> &coor_arr, int f, int l);
void MaximaFinding(vector<coordinate> &coor_arr, int begin, int end);

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
	cout << "\nSort the coordinates by x (quick sort) : \n";
	for (int i = 0; i < num; i++)
	{
		coor_arr[i].print();
	}
	cout << endl;

	cout << "\nAfter 2-D maxima finding, the MAX coordinates are : \n";
	MaximaFinding(coor_arr, 0, num - 1);
	
	int tmp; // 由大到小排序SR
	for (int i = num / 2 ; i < num - 1; i++)
	{
		tmp = i;
		for (int j = i + 1; j < num; j++)
		{
			if (coor_arr[j].y >= coor_arr[tmp].y)
			{
				tmp = j;
			}
		}
		swap(coor_arr[i], coor_arr[tmp]);
	}
	int biggest_num_in_SR = coor_arr[num / 2].y;  // 找出SR中的最大值
	cout << "\n(biggest y-value in SR is : " << biggest_num_in_SR << ")\n";

	for (int i = 0; i < num / 2; i++)  // FINDING FINAL MAXIMA IN SL(其y值必須大於SR的最大值)
	{
		if (coor_arr[i].max == true && coor_arr[i].y <= biggest_num_in_SR)
		{
			coor_arr[i].max = false;
		}
	}

	QuickSort(coor_arr, 0, num - 1);
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

void MaximaFinding(vector<coordinate> &coor_arr, int begin, int end)
{
	if ((end - begin) == 0) return;

	int median_index = (begin + end) / 2;

	MaximaFinding(coor_arr, begin, median_index);
	MaximaFinding(coor_arr, median_index + 1, end);


	for (int i = begin; i <= median_index; i++)
	{
		for (int j = begin; j <= median_index; j++)
		{
			if (coor_arr[j].dominant_flag == true) // 若被dominant則設為"非max"
			{
				coor_arr[j].max = false;
			}

			if (i > j && coor_arr[i].y > coor_arr[j].y 
						&& coor_arr[i].dominant_flag == false)
			{
				coor_arr[j].dominant_flag = true;  // 若被dominant則flag設為true
				coor_arr[i].max = true;
			}
			else if (i < j && coor_arr[i].y > coor_arr[j].y) // 無法互相dominant
			{				
				if (coor_arr[i].dominant_flag == false)  // 彼此都設為max
				{
					coor_arr[i].max = true;
				}
				if (coor_arr[j].dominant_flag == false)
				{
					coor_arr[j].max = true;
				}
			}
		}
	}

	for (int i = median_index + 1; i <= end; i++)
	{
		for (int j = median_index + 1; j <= end; j++)
		{
			if (coor_arr[j].dominant_flag == true) // 若被dominant則設為"非max"
			{
				coor_arr[j].max = false;
			}

			if (i > j && coor_arr[i].y > coor_arr[j].y
				&& coor_arr[i].dominant_flag == false)
			{
				coor_arr[j].dominant_flag = true;  // 若被dominant則flag設為true
				coor_arr[i].max = true;
			}
			else if (i < j && coor_arr[i].y > coor_arr[j].y) // 無法互相dominant
			{
				if (coor_arr[i].dominant_flag == false)  // 彼此都設為max
				{
					coor_arr[i].max = true;
				}
				if (coor_arr[j].dominant_flag == false)
				{
					coor_arr[j].max = true;
				}
			}
		}
	}
}