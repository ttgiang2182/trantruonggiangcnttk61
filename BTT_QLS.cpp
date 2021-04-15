//Chuong trinh quan li sach

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


typedef struct {
	char Tensach[25],Theloai[25],Tentacgia[25];
	int Namxuatban,Gia;
}book_st;
void Nhap(book_st a[5]){
	for(int i=0; i < 5; i++){
		printf("\nNhap du lieu cua sach %d:\n", i +1);
		printf("+ Ten sach: ");
		gets(a[i].Tensach);
		printf("+ The loai: ");
		gets(a[i].Theloai);
		printf("+ Ten tac gia: ");
		gets(a[i].Tentacgia);
		printf("+ Nam xuat ban: ");
		scanf("%d",a[i].Namxuatban);
		printf("+ Gia: ");
		scanf("%d",a[i].Gia);
		fflush(stdin);
	}
}
void Tieude()
{
	printf("\n");
	printf("%-3s|", "Stt");
	printf("%-15s|", "Ten sach");
	printf("%-15s|", "Ten tac gia");
	printf("%-10s|", "The loai");
	printf("%-12s|", "Nam xuat ban");
	printf("%-8s|", "Gia");
	printf("\n");
}
void Hang(book_st a[5], int j )
{
	printf("%03d|", j + 1);
	printf("%-15s|", a[j].Tensach);
	printf("%-15s|", a[j].Tentacgia);
	printf("%-10s|", a[j].Theloai);
	printf("%-12d|", a[j].Namxuatban);
	printf("%-8d|\n", a[j].Gia);
}
void Hoanvi(book_st *book1, book_st *book2)
{
	book_st t = *book1;
	*book1 = *book2;
	*book2 = t;
}
void Sapxep(book_st a[5])
{
	int i, j;
	for (i = 0; i < 5 ; i++) {
		for (j = i + 1; j < 4; j++) {
			if(strcmp(a[i].Tensach, a[j].Tensach) > 0) {
				Hoanvi(&a[i], &a[j]);
			} else if(strcmp(a[i].Tensach, a[j].Tensach) == 0) {
				if (a[i].Tentacgia > a[j].Tentacgia) {
					Hoanvi(&a[i], &a[j]);
				}
		    }
        } 
    }
    Tieude();
	for(i = 0; i < 5; i++) {
		Hang(a, i);
	}
	
	// Find min year, max year
	int minNamxuatban = a[0].Namxuatban, maxNamxuatban = a[0].Namxuatban;
	for(i = 1; i < 3; i++) {
		if (a[i].Namxuatban < minNamxuatban) minNamxuatban = a[i].Namxuatban;
		if (a[i].Namxuatban > maxNamxuatban) maxNamxuatban = a[i].Namxuatban;
	}
	// Count statistic
	int* Thongke = (int*)calloc(maxNamxuatban + 1, sizeof(int));
	for(i = 0; i < 3; i++) {
		int Giatri = a[i].Namxuatban;
		Thongke[Giatri] += 1;
	}
		// Print statistic
	printf("\n");
	for(i = minNamxuatban; i <= maxNamxuatban; i++) {
		if (Thongke[i] == 1) {
			printf("Nam %d co %d sach\n", i, Thongke[i]);
		}
		else if (Thongke[i] > 1) {
			printf("Nam %d co %d sach\n", i, Thongke[i]);
		}
	}
	printf("\n");
	free(Thongke);
}
void Timkiem(book_st a[3])
{
	// Nhap tu ban phim
	char Theloai[25];
	printf("\nNhap the loai tim kiem : ");
	gets(Theloai);
	printf("\n");

	// Tim kiem
	int i = 0, dem = 0;
	for (i = 0; i < 5; i++) {
		if (strcmp(a[i].Theloai, Theloai) == 0) {
			Hang(a, i);
			dem++;
		}
	}
	if (dem == 0) {
		printf("\nKhong co quyen sach thuoc the loai nay\n");
	}
}

void Luu(book_st *p)
{
	FILE *fp = fopen("book.dat", "wb");

	int i;
	for (i = 0; i < 5; i++) {
		fwrite(p + i, sizeof(book_st), 1, fp);
	}

	fclose(fp);
}

int main()
{
	book_st bookList[5];
	int chon;

	while(1) {
		// Menu
		printf("\n");
		printf("1. Nhap du lieu cua sach\n");
		printf("2. Sap xep, thong ke va hien thi thong tin chi tiet cua tat ca quyen sach the loai\n");
		printf("3. Tim kiem sach theo the loai\n");
		printf("4. Luu vao tep nhi phan book.dat\n");
		printf("5. Thoat\n");

		// Nhap 1 so tuong ung voi menu:
		printf("\nNhap mot so tu 1 den 5: ");
		while(1) {
			if(!scanf("%d", &chon) || chon < 1 || chon > 5) {
				fflush(stdin);
				printf("Nhap mot so tu 1 den 5: ");
			} else {
				fflush(stdin);
				break;
			}
		}

		// Xu ly lua chon
		if (chon == 1) {
			Nhap(bookList);
		} else if (chon == 2) {
			Sapxep(bookList);
		} else if (chon == 3) {
			Timkiem(bookList);
		} else if (chon == 4) {
			Luu(bookList);
		} else {
			break;
		}
	}

	return 0;
}
