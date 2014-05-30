// sort_algoritm_experiment.cpp: îïğåäåëÿåò òî÷êó âõîäà äëÿ êîíñîëüíîãî ïğèëîæåíèÿ.
//

#include "stdafx.h"
#pragma once
#include <iostream>
#include <fstream>
#include <time.h>
#include <conio.h>
#include <omp.h>
#include <iomanip>

#define maxr 5000
#define n_time 12

int nVector[] = { 25, 50, 100, 200, 300, 400, 500, 600, 700, 800, 900, 1000 };
double result_buble[n_time];
double result_selection[n_time];
double result_quick[n_time];

using namespace std;

void bubbleSort(int n, int *a)
{
	int temp;
	for (int i = 0; i < n; i++)
		for (int j = n - 1; j > i; j--)
			if (a[j] < a[j - 1])
			{
				temp = a[j];
				a[j] = a[j - 1];
				a[j - 1] = temp;
			}
}

void selectionSort(int n, int *a)
{
	int max = a[0];
	int maxn = 0;
	for (int i = 0; i < n - 1; i++)
	{
		for (int j = i; j<n; j++)
			if (a[j] > max)
			{
				max = a[j];
				maxn = j;
			}
		int temp = a[i];
		a[i] = max;
		a[maxn] = temp;
	}
}

void quickSort(int N, int *a) {
	int i = 0, j = N - 1;
	int temp, p;
	p = a[N >> 1];
	do{
		while (a[i] < p) i++;
		while (a[j] > p) j--;
		if (i <= j)
		{
			temp = a[i]; a[i] = a[j]; a[j] = temp;
			i++; j--;
		}
	} while (i <= j);
	if (j > 0) quickSort(j + 1, a);
	if (N - 1 > i) quickSort(N - i, a + i);
}

void display_result()
{
	setlocale(LC_ALL, "C");
	cout << "ÚÄÄÄÄÄÄÄÂÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÂÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÂÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿\n";
	cout << "³   N   ³    Quick       ³      Bubble       ³       Selection     ³\n";
	cout << "ÃÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ´\n";
	for (int i = 0; i < n_time; i++)
	{
		if (i < n_time - 1)
		{
			cout << "³" << setw(7) << nVector[i] << "³" << setw(15) << result_quick[i] << " ³ " << setw(17) << result_buble[i] << " ³ " << setw(19) << result_selection[i] << " ³ " << endl;
			cout << "ÃÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ´\n";
		}
		else
		{
			cout << "³" << setw(7) << nVector[i] << "³" << setw(15) << result_quick[i] << " ³ " << setw(17) << result_buble[i] << " ³ " << setw(19) << result_selection[i] << " ³ " << endl;
			cout << "ÀÄÄÄÄÄÄÄÁÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÁÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÁÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ\n";
		}
	}
}

void generation(int *vector, int n)								//Ôóíêöèÿ ãåíåğàöèè 1000 ÷èñåë 0..5000
{
	srand(time(0));
	for (int i = 0; i < n; i++)
		vector[i] = rand() % maxr;
}

void calculateTime_bubble()
{
	for (int i = 0; i < n_time; i++)
	{
		int *mas = new int[nVector[i]];
		generation(mas, nVector[i]);
		double t1 = omp_get_wtime();
		bubbleSort(nVector[i], mas);
		result_buble[i] = (omp_get_wtime() - t1) * 1000;
	}
}

void calculateTime_selection()
{
	for (int i = 0; i < n_time; i++)
	{
		int *mas = new int[nVector[i]];
		generation(mas, nVector[i]);
		double t1 = omp_get_wtime();
		selectionSort(nVector[i], mas);
		result_selection[i] = (omp_get_wtime() - t1) * 1000;
	}
}

void calculateTime_quick()
{
	for (int i = 0; i < n_time; i++)
	{
		int *mas = new int[nVector[i]];
		generation(mas, nVector[i]);
		double t1 = omp_get_wtime();
		quickSort(nVector[i], mas);
		result_quick[i] = (omp_get_wtime() - t1) * 1000;
	}
}

void calculate()
{
	calculateTime_bubble();
	calculateTime_quick();
	calculateTime_selection();
}

void toFile()
{
	ofstream file_data;
	file_data.open("sorts.txt", ios::out);
	for (int i = 0; i < n_time; i++)
	{
		file_data << result_quick[i] << endl;
	}
	file_data << endl;
	for (int i = 0; i < n_time; i++)
	{
		file_data << result_selection[i] << endl;
	}
	file_data << endl;
	for (int i = 0; i < n_time; i++)
	{
		file_data << result_buble[i] << endl;
	}
	file_data.close();
}

void fromFile()
{
	ifstream file_data;
	file_data.open("sorts.txt");
	for (int i = 0; i < n_time; i++)
	{
		file_data >> result_quick[i];
	}
	for (int i = 0; i < n_time; i++)
	{
		file_data >> result_selection[i];
	}
	for (int i = 0; i < n_time; i++)
	{
		file_data >> result_buble[i];
	}
	file_data.close();
}

void menu()
{
	setlocale(0, "");
	printf(" 1.Ñãåíåğèğîâàòü äàííûå \n");
	printf(" 2.Â Ôàéë \n");
	printf(" 3.Èç Ôàéëà \n");
	printf(" 4.Ïîêàçàòü òàáëèöó \n");
	printf(" 5.Âûõîä \n");
	printf(" Ââåñòè íîìåğ: ");
}

int _tmain(int argc, _TCHAR* argv[])
{
	int ch;
	do
	{
		system("CLS");
		menu();
		cin >> ch;
		cin.sync();
		switch (ch)
		{
				case 1:
					calculate();
					break;
				case 2:
					toFile();
					break;
				case 3:
					fromFile();
					break;
				case 4:
						display_result();
					break;
		}
		cout << endl;
		system("pause");
	} while (ch != 5);

	return 0;
}