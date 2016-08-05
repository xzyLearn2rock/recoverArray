#include <iostream>
#include <vector>

using namespace std;

void swap(int *first, int *second)
{
	int tmp = *first;
	*first = *second;
	*second = tmp;
}

int orderPairs(const vector<int> &data) 
{
	if (data.empty())
		return 0;
	int len = data.size();

	int count = 0;
	for (int i = 0; i < len - 1; ++i) 
	{
		for (int j = i + 1; j < len; ++j) 
		{
			if (data[i] < data[j])
				count++;
		}
	}
	return count;
}

void slurStatistic(const vector<int> &data, vector<int> &posVec, vector<int> &valueVec)
{
	int len = data.size();
	if (len <= 0)
		return;

	vector<int> tmpVec(len + 1, 0);
	for (int i = 0; i < len; ++i)
	{
		if (data[i] == 0)
			posVec.push_back(i);
		else
			tmpVec[data[i]] = 1;
	}

	for (int i = 1; i <= len; ++i)
	{
		if (tmpVec[i] == 0)
			valueVec.push_back(i);
	}
}

bool isSequence(vector<int> &data, vector<int> &posVec, vector<int> &valueVec, int pairs)
{
	int count = 0;
	for (int i = 0; i < valueVec.size(); ++i)
	{
		int pos = posVec[i];
		data[pos] = valueVec[i];
	}
	count = orderPairs(data);
	if (count == pairs)
		return true;
	return false;
}

void permutation(vector<int> &data, vector<int> &posVec, vector<int> &valueVec, int start, int pairs, int *pCounts)
{
	if (start == valueVec.size())
	{
		vector<int> tmpData = data;
		if (isSequence(tmpData, posVec, valueVec, pairs))
			(*pCounts)++;
	}
	else
	{
		for (int i = start; i < valueVec.size(); ++i)
		{
			swap(&valueVec[start], &valueVec[i]);
			permutation(data, posVec, valueVec, start + 1, pairs, pCounts);
			swap(&valueVec[start], &valueVec[i]);
		}
	}
}

int main()
{
	int numOfData = 0;
	int pairs = 0;
	vector<int> inputData;
	while (cin >> numOfData >> pairs)
	{
		while (numOfData--)
		{
			int tmpNum = 0;
			cin >> tmpNum;
			inputData.push_back(tmpNum);
		}
		vector<int> posVec;
		vector<int> valueVec;
		int counts = 0;
		slurStatistic(inputData, posVec, valueVec);
		permutation(inputData, posVec, valueVec, 0, pairs, &counts);
		cout << counts << endl;
	}

	return 0;
}