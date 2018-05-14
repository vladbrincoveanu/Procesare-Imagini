// OpenCVApplication.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "common.h"


//static int arrayFinal[1000][64];

uchar array[] = { 16,11,10,16,24,40,51,61,
12,12,14,19,26,58,60,55,
14,13,16,24,40,57,69,56,
14,17,22,29,51,87,80,62,
18,22,37,56,68,109,103,77,
24,35,55,64,81,104,113,92,
49,64,78,87,103,121,120,101,
72,92,95,98,112,100,103,99
};

Mat_<uchar> quantize(8, 8, array);

int RATIO,HEIGHT,WIDTH,NBBLOCK;

int* zigZagMatrix(int arr[][8], int n, int m)
{
	int array[64];
	int i = 0;
	int row = 0, col = 0;

	// Boolean variable that will true if we
	// need to increment 'row' value otherwise
	// false- if increment 'col' value
	bool row_inc = 0;

	// Print matrix of lower half zig-zag pattern
	int mn = min(m, n);
	for (int len = 1; len <= mn; ++len) {
		for (int i = 0; i < len; ++i) {
			array[i] = arr[row][col];
			printf("%d ", arr[row][col]);
			i++;
			if (i + 1 == len)
				break;
			// If row_increment value is true
			// increment row and decrement col
			// else decrement row and increment
			// col
			if (row_inc)
				++row, --col;
			else
				--row, ++col;
		}

		if (len == mn)
			break;

		// Update row or col vlaue according
		// to the last increment
		if (row_inc)
			++row, row_inc = false;
		else
			++col, row_inc = true;
	}

	// Update the indexes of row and col variable
	if (row == 0) {
		if (col == m - 1)
			++row;
		else
			++col;
		row_inc = 1;
	}
	else {
		if (row == n - 1)
			++col;
		else
			++row;
		row_inc = 0;
	}

	// Print the next half zig-zag pattern
	int MAX = max(m, n) - 1;
	for (int len, diag = MAX; diag > 0; --diag) {

		if (diag > mn)
			len = mn;
		else
			len = diag;

		for (int i = 0; i < len; ++i) {
			array[i] = arr[row][col];
			printf("%d ", arr[row][col]);
			i++;
			if (i + 1 == len)
				break;

			// Update row or col vlaue according
			// to the last increment
			if (row_inc)
				++row, --col;
			else
				++col, --row;
		}

		// Update the indexes of row and col variable
		if (row == 0 || col == m - 1) {
			if (col == m - 1)
				++row;
			else
				++col;

			row_inc = true;
		}

		else if (col == 0 || row == n - 1) {
			if (row == n - 1)
				++col;
			else
				++row;

			row_inc = false;
		}
	}

	return array;
}

char* zigZag(Mat_<int> rez) {
	char* result = (char*)calloc(64,sizeof(char));

	result[0] = rez(0, 0);
	result[1] = rez(0, 1);
	result[2] = rez(1, 0);
	result[3] = rez(2, 0);
	result[4] = rez(1, 1);
	result[5] = rez(0, 2);
	result[6] = rez(0, 3);


	result[7] = rez(1, 2);
	result[8] = rez(2, 1);
	result[9] = rez(3, 0);
	result[10] = rez(4, 0);
	result[11] = rez(3, 1);
	result[12] = rez(2, 2);
	result[13] = rez(1, 3);


	result[14] = rez(0, 4);
	result[15] = rez(0, 5);
	result[16] = rez(1, 4);
	result[17] = rez(2, 3);
	result[18] = rez(3, 2);
	result[19] = rez(4, 1);
	result[20] = rez(5, 0);


	result[21] = rez(6, 0);
	result[22] = rez(5, 1);
	result[23] = rez(4, 2);
	result[24] = rez(3, 3);
	result[25] = rez(2, 4);
	result[26] = rez(1, 5);
	result[27] = rez(0, 6);


	result[28] = rez(0, 7);
	result[29] = rez(1, 6);
	result[30] = rez(2, 5);
	result[31] = rez(3, 4);
	result[32] = rez(4, 3);
	result[33] = rez(5, 2);
	result[34] = rez(6, 1);


	result[35] = rez(7, 0);
	result[36] = rez(7, 1);
	result[37] = rez(6, 2);
	result[38] = rez(5, 3);
	result[39] = rez(4, 4);
	result[40] = rez(3, 5);
	result[41] = rez(2, 6);


	result[42] = rez(1, 7);
	result[43] = rez(2, 7);
	result[44] = rez(3, 6);
	result[45] = rez(4, 5);
	result[46] = rez(5, 4);
	result[47] = rez(6, 3);
	result[48] = rez(7, 2);

	result[49] = rez(7, 3);
	result[50] = rez(6, 4);
	result[51] = rez(5, 5);
	result[52] = rez(4, 6);
	result[53] = rez(3, 7);
	result[54] = rez(4, 7);
	result[55] = rez(5, 6);

	result[56] = rez(6, 5);
	result[57] = rez(7, 4);
	result[58] = rez(7, 5);
	result[59] = rez(6, 6);
	result[60] = rez(5, 7);
	result[61] = rez(6, 7);
	result[62] = rez(7, 6);
	result[63] = rez(7, 7);

	return result;

}

Mat_<int> revZigZag(char* result) {

	Mat_<int> rez(8,8);

	rez(0, 0) = result[0];
	rez(0, 1) = result[1];
	rez(1, 0) = result[2];
	rez(2, 0) = result[3];
	rez(1, 1) = result[4];
	rez(0, 2) = result[5];
	rez(0, 3) = result[6];


	rez(1, 2) = result[7];
	rez(2, 1) = result[8];
	rez(3, 0) = result[9];
	rez(4, 0) = result[10];
	rez(3, 1)= result[11];
	rez(2, 2)= result[12];
	rez(1, 3)= result[13];


	rez(0, 4) = result[14];
	rez(0, 5) = result[15];
	rez(1, 4) = result[16];
	rez(2, 3) = result[17];
	rez(3, 2) = result[18];
	rez(4, 1) = result[19]; 
	rez(5, 0) = result[20];


	rez(6, 0) = result[21];
	rez(5, 1) = result[22];
	rez(4, 2) = result[23];
	rez(3, 3) = result[24];
	rez(2, 4) = result[25];
	rez(1, 5) = result[26];
	rez(0, 6) = result[27];


	rez(0, 7) = result[28];
	rez(1, 6) = result[29];
	rez(2, 5) = result[30];
	rez(3, 4) = result[31];
	rez(4, 3) = result[32];
	rez(5, 2) = result[33];
	rez(6, 1) = result[34];


	rez(7, 0) = result[35];
	rez(7, 1) = result[36];
	rez(6, 2) = result[37];
	rez(5, 3) = result[38];
	rez(4, 4) = result[39];
	rez(3, 5) = result[40];
	rez(2, 6) = result[41];


	rez(1, 7) = result[42];
	rez(2, 7) = result[43];
	rez(3, 6) = result[44];
	rez(4, 5) = result[45];
	rez(5, 4) = result[46];
	rez(6, 3) = result[47];
	rez(7, 2) = result[48];
	rez(7, 3) = result[49];
	rez(6, 4) = result[50];
	rez(5, 5) = result[51];
	rez(4, 6) = result[52];
	rez(3, 7) = result[53];
	rez(4, 7) = result[54];
	rez(5, 6) = result[55];

	rez(6, 5) = result[56];
	rez(7, 4) = result[57];
	rez(7, 5) = result[58];
	rez(6, 6) = result[59];
	rez(5, 7) = result[60];
	rez(6, 7) = result[61];
	rez(7, 6) = result[62];
	rez(7, 7) = result[63];

	return rez;
}

Mat_<int> dct(Mat_<int> signedMatrix, int xoffset, int yoffset, int n, int m) {
	Mat_<int> rezPartial(8, 8);

	int N = 8;
	int i, j, x, y = 0;
	double temp;
	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			temp = 0.0;
			for (x = 0; x < N; x++) {
				for (y = 0; y < N; y++) {
					temp += cos(((2 * y + 1)*i*PI) / (float)(2 * N)) *
						cos(((2 * x + 1)*j*PI) / (float)(2 * N)) *
						signedMatrix(y, x);
				}
			}

			if (i == 0)
				if (j == 0) {
					temp *= 0.125;
				}
				else {
					temp *= 0.1767;
				}
			else {
				if (j == 0) {
					temp *= 0.1767;
				}
				else {
					temp *= 0.25;
				}

			}
			rezPartial(i, j) = round(temp / quantize(i, j));
		}
	}

	return rezPartial;

}

Mat_<int> idct(Mat_<int> signedMatrix, int xoffset, int yoffset, int n, int m) {
	Mat_<int> rezPartial(8, 8);

	int N = 8;
	int i, j, x, y = 0;
	double temp;
	double sum;


	for (x = 0; x < N; x++) {
		for (y = 0; y < N; y++) {
			temp = 0.0;
			sum = 0.0;
			for (i = 0; i < N; i++) {
				for (j = 0; j < N; j++) {
					temp = ((float)cos(((2 * y + 1)*i*PI) / (float)(2 * N)) *
						(float)cos(((2 * x + 1)*j*PI) / (float)(2 * N)) *
						signedMatrix(j, i));

					if (i == 0) {
						if (j == 0) {
							temp *= 0.125;
						}
						else {
							temp *= 0.1767;
						}
					}
					else {
						if (j == 0) {
							temp *= 0.1767;
						}
						else {
							temp *= 0.25;
						}

					}

					sum += temp;
				}
			}
			rezPartial(x, y) = round(sum);
		}
	}

	return rezPartial;

}

Mat_<int> matrixAt(Mat_<int> matrix, int offsetx, int offsety, int m, int n) {
	Mat_<int> da(m, n);
	for (int x = offsetx; x < offsetx + m; x++) {
		for (int y = offsety; y < offsety + n; y++) {
			da(x - offsetx, y - offsety) = matrix(x, y);
			//	printf("%d ", da(x - offsetx, y - offsety));
		}

			//printf("\n ");
	}
	return da;
}

void matrixTo(Mat_<int> matrix, Mat_<int>* matRez,int offsetx, int offsety, int m, int n) {
	for (int x = offsetx; x < offsetx + m; x++) {
		for (int y = offsety; y < offsety + n; y++) {
			(*matRez)(x, y) = matrix(x - offsetx, y - offsety);
			//printf("%d ", (*matRez)(x - offsetx, y - offsety));
		}
		//printf("\n ");
	}
}

void compr() {
	Mat test = Mat(8, 8, CV_LOAD_IMAGE_GRAYSCALE);
	uchar* dataTest = test.data;

	Mat_<char> rez1(8, 8);

	Mat_<int> rez(8, 8);

	test.at<uchar>(0, 0) = 52;
	test.at<uchar>(0, 1) = 55;
	test.at<uchar>(0, 2) = 61;
	test.at<uchar>(0, 3) = 66;
	test.at<uchar>(0, 4) = 70;
	test.at<uchar>(0, 5) = 61;
	test.at<uchar>(0, 6) = 64;
	test.at<uchar>(0, 7) = 73;
	test.at<uchar>(1, 0) = 64;
	test.at<uchar>(1, 1) = 59;
	test.at<uchar>(1, 2) = 55;
	test.at<uchar>(1, 3) = 90;
	test.at<uchar>(1, 4) = 109;
	test.at<uchar>(1, 5) = 85;
	test.at<uchar>(1, 6) = 69;
	test.at<uchar>(1, 7) = 72;
	test.at<uchar>(2, 0) = 62;
	test.at<uchar>(2, 1) = 59;
	test.at<uchar>(2, 2) = 68;
	test.at<uchar>(2, 3) = 113;
	test.at<uchar>(2, 4) = 144;
	test.at<uchar>(2, 5) = 104;
	test.at<uchar>(2, 6) = 66;
	test.at<uchar>(2, 7) = 73;
	test.at<uchar>(3, 0) = 63;
	test.at<uchar>(3, 1) = 58;
	test.at<uchar>(3, 2) = 71;
	test.at<uchar>(3, 3) = 122;
	test.at<uchar>(3, 4) = 154;
	test.at<uchar>(3, 5) = 106;
	test.at<uchar>(3, 6) = 70;
	test.at<uchar>(3, 7) = 69;
	test.at<uchar>(4, 0) = 67;
	test.at<uchar>(4, 1) = 61;
	test.at<uchar>(4, 2) = 68;
	test.at<uchar>(4, 3) = 104;
	test.at<uchar>(4, 4) = 126;
	test.at<uchar>(4, 5) = 88;
	test.at<uchar>(4, 6) = 68;
	test.at<uchar>(4, 7) = 70;
	test.at<uchar>(5, 0) = 79;
	test.at<uchar>(5, 1) = 65;
	test.at<uchar>(5, 2) = 60;
	test.at<uchar>(5, 3) = 70;
	test.at<uchar>(5, 4) = 77;
	test.at<uchar>(5, 5) = 68;
	test.at<uchar>(5, 6) = 58;
	test.at<uchar>(5, 7) = 75;
	test.at<uchar>(6, 0) = 85;
	test.at<uchar>(6, 1) = 71;
	test.at<uchar>(6, 2) = 64;
	test.at<uchar>(6, 3) = 59;
	test.at<uchar>(6, 4) = 55;
	test.at<uchar>(6, 5) = 61;
	test.at<uchar>(6, 6) = 65;
	test.at<uchar>(6, 7) = 83;
	test.at<uchar>(7, 0) = 87;
	test.at<uchar>(7, 1) = 79;
	test.at<uchar>(7, 2) = 69;
	test.at<uchar>(7, 3) = 68;
	test.at<uchar>(7, 4) = 65;
	test.at<uchar>(7, 5) = 76;
	test.at<uchar>(7, 6) = 78;
	test.at<uchar>(7, 7) = 94;

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			rez1(i,j) = test.at<uchar>(i, j) - 128;
		}
	}

	printf("Rez 1\n");
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			printf("%d ", rez1(i,j));
		}
		printf("\n");
	}

	rez = dct(rez1, 0, 0, 8, 8);
	int N = 8;
	int i, j ,x,y= 0;
	float temp;
	//for (i = 0; i < N; i++) {
	//	for (j = 0; j < N; j++) {
	//		temp = 0.0;
	//		for (x = 0; x < N; x++) {
	//			for (y = 0; y < N; y++) {
	//				temp += cos(((2 * y + 1)*i*PI) / (float)(2 * N)) *
	//					cos(((2 * x + 1)*j*PI) / (float)(2 * N)) *
	//					rez1(y,x);
	//			}
	//		}
	//
	//		if (i == 0)
	//			if(j == 0) {
	//				temp *= (1 / (float)N);
	//			}
	//			else {
	//				temp *= (sqrt(1 / (float)N)*sqrt(2 / (float)N));
	//			}
	//		else {
	//			if (j == 0) {
	//				temp *= (sqrt(1 / (float)N)*sqrt(2 / (float)N));
	//			}
	//			else {
	//				temp *= (2 / (float)N);
	//			}
	//			
	//		}
	//		//printf("%d ", temp);
	//		rez(i,j) = round(round(temp)/quantize(i,j));
	//	}
	//}

	printf("\n\n");
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			printf("%d ", ((int*)rez.data)[i * 8 + j]);
		}
		printf("\n");
	}

	char* result = zigZag(rez);



	for (int i = 0; i < 64; i++) {
		printf("%d ", result[i]);
	}

	rez = revZigZag(result);

	printf("\n\n");
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			printf("%d ", ((int*)rez.data)[i * 8 + j]);
		}
		printf("\n");
	}

	Mat_<int> darez(8, 8);

	for (x = 0; x < N; x++) {
		for (y = 0; y < N; y++) {
			darez(x, y) = rez(x, y)*quantize(x, y);
		}
	}

	printf("\n\n");
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			printf("%d ", ((int*)darez.data)[i * 8 + j]);
		}
		printf("\n");
	}

	rez = idct(darez, 0, 0,8, 8);
	/*float sum;
	for (x = 0; x < N; x++) {
		for (y = 0; y < N; y++) {
			temp = 0.0;
			sum = 0.0;
			for (i = 0; i < N; i++) {
				for (j = 0; j < N; j++) {
					temp = ((float)cos(((2 * y + 1)*i*PI) / (float)(2 * N)) *
						(float)cos(((2 * x + 1)*j*PI) / (float)(2 * N)) *
						darez(i,j));

					if (i == 0) {
						if (j == 0) {
							temp *= 0.125;
						}
						else {
							temp *= 0.1767;
						}
					}else {
						if (j == 0) {
							temp *= 0.1767;
						}
						else {
							temp *= 0.25;
						}

					}

					sum += temp;
				}
			} 

			printf("%f ", sum);
			rez(x,y) = round(sum);
		}
	}*/

	printf("\n\n");
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			((int*)rez.data)[i * 8 + j] += 128;
			printf("%d ", ((int*)rez.data)[i * 8 + j]);
		}
		printf("\n");
	}	

}

void printMatrix(Mat_<int> a) {
	for (int i = 0; i < 8; i ++) {
		for (int j = 0; j < 8; j ++) {
			printf("%d ", a.at<int>(i, j));
		}

		printf("\n");
	}
}

void compression1(){
	char frame[MAX_PATH];
	openFileDlg(frame);
	Mat img = imread(frame, CV_LOAD_IMAGE_COLOR);
	int height = img.rows;
	int width = img.cols;
	HEIGHT = height;
	WIDTH = width;

	int nbOfBlocks = height * width / 64;
	NBBLOCK = nbOfBlocks;
	Mat arrayB[1000];
	//printf("%d", nbOfBlocks);1

	uchar *srcData = img.data;
	
	printf("COMPRESSION RATIO 1 - 64\n");
	scanf("%d", &RATIO);

	FILE *f = fopen("file.bin", "wb");
	if (f == NULL)
	{
		printf("Error opening file!\n");
		exit(1);
	}


	Mat_<int> resultat(nbOfBlocks, nbOfBlocks);

	Mat_<int> signedMatrixR(height, width);
	Mat_<int> signedMatrixG(height, width);
	Mat_<int> signedMatrixB(height, width);

	uchar* signedMatrixDataR = signedMatrixR.data;
	uchar* signedMatrixDataG = signedMatrixG.data;
	uchar* signedMatrixDataB = signedMatrixB.data;
	int k = 0;
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			signedMatrixR(i,j) = srcData[3 * (i*width + j) + 2] - 128;
			signedMatrixG(i,j) = srcData[3 * (i*width + j) + 1] - 128;
			signedMatrixB(i,j) = srcData[3 * (i*width + j) + 0] - 128;
		}
	}

	char* bitStream1;
	char* bitStream2;
	char* bitStream3;

	Mat_<int> matrix1;
	Mat_<int> matrix2;
	Mat_<int> matrix3;
	int contor = 0;
	boolean a = true;
	char counter = 0;

	double t = (double)getTickCount(); // Găsește timpul curent [ms]
									   // … Procesarea propriu-zisă …
									   // Găsește timpul current din nou și calculează timpul scurs [ms]

	for (int i = 0; i < height-7; i += 8) {
		for (int j = 0; j < width-7; j += 8) {
		/*	matrix1 = ;
			matrix2 = ;
			matrix3 = ;*/
		
			matrix1 = dct(matrixAt(signedMatrixR, i, j, 8, 8), 0, 0, 8, 8);
			matrix2 = dct(matrixAt(signedMatrixG, i, j, 8, 8), 0, 0, 8, 8);
			matrix3 = dct(matrixAt(signedMatrixB, i, j, 8, 8), 0, 0, 8, 8);

		/*	bitStream1 = ;
			bitStream2 = ;
			bitStream3 = ;*/

		
			fwrite(zigZag(matrix1), sizeof(char), RATIO, f);
			fwrite(zigZag(matrix2), sizeof(char), RATIO, f);
			fwrite(zigZag(matrix3), sizeof(char), RATIO, f);
		
		}
		
	}
	t = ((double)getTickCount() - t) / getTickFrequency();
	// Afișarea la consolă a timpului de procesare [ms]
	printf("Time = %.8f [ms]\n", t * 1000 / nbOfBlocks);

	fclose(f);

	//END PROGRAM////
}

void decompression() {
	
	printf("Decompression started..... \n");

	char* bitStream1 = (char*)calloc(64, sizeof(char));
	char* bitStream2 = (char*)calloc(64, sizeof(char));
	char* bitStream3 = (char*)calloc(64, sizeof(char));

	Mat_<int> matR(8, 8);
	Mat_<int> matG(8, 8);
	Mat_<int> matB(8, 8);

	FILE *fileptr;
	int size;
	fileptr = fopen("file.bin", "rb");

	int k = 0;
	Mat img(HEIGHT, WIDTH, CV_8UC3);
	uchar* data = img.data;
	Mat_<int> rezultatR(HEIGHT, WIDTH);
	Mat_<int> rezultatG(HEIGHT, WIDTH);
	Mat_<int> rezultatB(HEIGHT, WIDTH);
	boolean a = true;


	Mat_<int> matR1(8, 8);
	Mat_<int> matG1(8, 8);
	Mat_<int> matB1(8, 8);

	double t = (double)getTickCount(); // Găsește timpul curent [ms]
									   // … Procesarea propriu-zisă …
									   // Găsește timpul current din nou și calculează timpul scurs [ms]

	int x, y = 0;
	for (int i = 0; i < HEIGHT - 7; i += 8) {
		for (int j = 0; j < WIDTH  - 7; j += 8) {

			bitStream1 = (char*)calloc(64, sizeof(char));
			bitStream2 = (char*)calloc(64, sizeof(char));
			bitStream3 = (char*)calloc(64, sizeof(char));
		
			fread(bitStream1, sizeof(char), RATIO, fileptr);
			fread(bitStream2, sizeof(char), RATIO, fileptr);
			fread(bitStream3, sizeof(char), RATIO, fileptr);
		
			//	fscanf(fileptr, "%c%c%c", &bitStream1[k], &bitStream2[k], &bitStream3[k]);

			matR = revZigZag(bitStream1);
			matG = revZigZag(bitStream2);
			matB = revZigZag(bitStream3);
		
			for (x = 0; x < 8; x++) {
				for (y = 0; y < 8; y++) {
					matR1(x, y) = matR(x, y)*quantize(x, y);
					matG1(x, y) = matG(x, y)*quantize(x, y);
					matB1(x, y) = matB(x, y)*quantize(x, y);
				}
			}

			/*matR = ;
			matG = ;
			matB = ;*/

			matrixTo(idct(matR1, 0, 0, 8, 8), &rezultatR, i, j, 8, 8);
			matrixTo(idct(matG1, 0, 0, 8, 8), &rezultatG, i, j, 8, 8);
			matrixTo(idct(matB1, 0, 0, 8, 8), &rezultatB, i, j, 8, 8);

			free(bitStream1);
			free(bitStream2);
			free(bitStream3);
		}
	}

	t = ((double)getTickCount() - t) / getTickFrequency();
	// Afișarea la consolă a timpului de procesare [ms]
	printf("Time = %.8f [ms]\n", t * 1000/ NBBLOCK);

	for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j < WIDTH; j++) {
			int R = (rezultatR(i, j) + 128);
			int G = (rezultatG(i, j) + 128);
			int B = (rezultatB(i, j) + 128);
			uchar r = (uchar)R;
			uchar g = (uchar)G;
			uchar b = (uchar)B;

			if (R > 255) {
				r = 255;
			}
			else if (R < 0) {
				r = 0;
			}

			if (G > 255) {
				g = 255;
			}
			else if (G < 0) {
				g = 0;
			}

			if (B > 255) {
				b = 255;
			}
			else if (B < 0) {
				b = 0;
			}

			data[3 * (i * WIDTH + j) + 2] = r;
			data[3 * (i * WIDTH + j) + 1] = g;
			data[3 * (i * WIDTH + j) + 0] = b;
		}
		imshow("Compressed img ", img);
		waitKey(10);
	}
	waitKey();
	fclose(fileptr);
	
	
}


int main()
{
	int op;
	do
	{
		system("cls");
		destroyAllWindows();
		printf("Menu:\n");
		printf(" 1 - Open image\n");
		printf(" 2 - Open BMP images from folder\n");
		printf(" 3 - Image negative - diblook style\n");
		printf(" 4 - BGR->HSV\n");
		printf(" 5 - Resize image\n");
		printf(" 6 - Canny edge detection\n");
		printf(" 7 - Edges in a video sequence\n");
		printf(" 8 - Snap frame from live video\n");
		printf(" 9 - Mouse callback demo\n");
		printf(" 0 - Exit\n\n");
		printf("Option: ");
		scanf("%d",&op);
		switch (op)
		{
			case 1:
				compression1();
				system("pause");
				break;
			case 2:
				decompression();
				break;
			case 3:
				compr();
				system("pause");
				break;
	
		}
	}
	while (op!=0);
	return 0;
}