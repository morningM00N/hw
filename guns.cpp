
#include <iostream>
#include <vector>
#define INPUT_SIZE 8

#ifdef _WIN32
void DP(bool b) {
	if (b==false) {
		int a = 3;
	}
}
#else
#define DP(b)
#endif

using namespace std;

static int seed = 10;

int pseudo_rand() {
	seed = seed * 214013 + 2531011;
	return (seed >> 16) & 0x7FFF;
}

struct Location {
	int row;
	int col;
};

int countEmpties(const int MAP[INPUT_SIZE][INPUT_SIZE], const int mNumOfRows, const int nNumOfCols,
	Location t1,
	Location t2,
	Location t3
	) {

	int newMAP[INPUT_SIZE][INPUT_SIZE] = { 0, };
	for (int i = 0; i < mNumOfRows; i++)
	{
		for (int j = 0; j < nNumOfCols; j++)
		{
			newMAP[i][j] = MAP[i][j];
		}
	}

	DP(newMAP[t1.row][t1.col] == 0);
	DP(newMAP[t2.row][t2.col] == 0);
	DP(newMAP[t3.row][t3.col] == 0);

	newMAP[t1.row][t1.col] = 2;
	newMAP[t2.row][t2.col] = 2;
	newMAP[t3.row][t3.col] = 2;


	int tempRow, tempCol;

	{
		tempRow = t1.row + 1;
		while (tempRow < mNumOfRows && newMAP[tempRow][t1.col] != 1) {
			newMAP[tempRow][t1.col] = 2;
			++tempRow;
		}

		tempRow = t1.row - 1;
		while (tempRow >= 0 && newMAP[tempRow][t1.col] != 1) {
			newMAP[tempRow][t1.col] = 2;
			--tempRow;
		}

		tempCol = t1.col + 1;
		while (tempCol < nNumOfCols && newMAP[t1.row][tempCol] != 1) {
			newMAP[t1.row][tempCol] = 2;
			++tempCol;
		}

		tempCol = t1.col - 1;
		while (tempCol >= 0 && newMAP[t1.row][tempCol] != 1) {
			newMAP[t1.row][tempCol] = 2;
			--tempCol;
		}
	}

	{
		tempRow = t2.row + 1;
		while (tempRow < mNumOfRows && newMAP[tempRow][t2.col] != 1) {
			newMAP[tempRow][t2.col] = 2;
			++tempRow;
		}

		tempRow = t2.row - 1;
		while (tempRow >= 0 && newMAP[tempRow][t2.col] != 1) {
			newMAP[tempRow][t2.col] = 2;
			--tempRow;
		}
		
	}

	{
		tempCol = t3.col + 1;
		while (tempCol < nNumOfCols && newMAP[t3.row][tempCol] != 1) {
			newMAP[t3.row][tempCol] = 2;
			++tempCol;
		}

		tempCol = t3.col - 1;
		while (tempCol >= 0 && newMAP[t3.row][tempCol] != 1) {
			newMAP[t3.row][tempCol] = 2;
			--tempCol;
		}
	}


	//
	//

	int ret = 0;
	for (int i = 0; i < mNumOfRows; i++)
	{
		for (int j = 0; j < nNumOfCols; j++)
		{
			if (newMAP[i][j] == 0) {
				++ret;
			}
		}
	}
	return ret;


}



int getSolution(const int MAP[INPUT_SIZE][INPUT_SIZE], const int mNumOfRows, const int nNumOfCols) {
	vector<Location> loc;
	for (int i = 0; i < mNumOfRows; i++)
	{
		for (int j = 0; j < nNumOfCols; j++)
		{
			if (MAP[i][j] == 0) {
				loc.push_back({i,j});
			}
		}
	}

	int ret = mNumOfRows * nNumOfCols;
	for (int i = 0; i < loc.size(); i++)
	{
		for (int j = 0; j < loc.size(); j++)
		{
			if (i == j) {
				continue;
			}
			for (int k = 0; k < loc.size(); k++)
			{
				if (i == k || j == k) {
					continue;
				}
				int temp = countEmpties(MAP, mNumOfRows, nNumOfCols,
					loc.at(i),
					loc.at(j),
					loc.at(k)
				);
				if (temp < ret) {
					ret = temp;
				}

			}
		}
	}
	

	return ret;
}

int main()
{
	int T = 100;
	for (int i = 1; i < T + 1; ++i) {
		int mNumOfRows = (pseudo_rand() % (INPUT_SIZE / 2) + INPUT_SIZE / 2);  // rows 값
		int nNumOfCols = (pseudo_rand() % (INPUT_SIZE / 2) + INPUT_SIZE / 2);  // columns 값
		int MAP[INPUT_SIZE][INPUT_SIZE]; // 지형을 표현하는 2차원 배열
		while (true) {
			int numOfEmpties = 0;
			for (int r = 0; r < mNumOfRows; ++r) {
				for (int c = 0; c < nNumOfCols; ++c) {
					if (pseudo_rand() % 3 == 0) {
						MAP[r][c] = 0;  // 빈공간
						numOfEmpties += 1;
					}

					else {
						MAP[r][c] = 1;  // 벽
					}
				}
			}
			if (numOfEmpties >= 3) break;
		}

		printf("#%d:%d\n", i, getSolution(MAP, mNumOfRows, nNumOfCols));
	}
	return 0;
}

