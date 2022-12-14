#include <stdio.h>
#include "string.h"
#include "time.h"
#include "conio.h"
#include <stdlib.h>

struct date {
	int ngay;
	int thang;
	int nam;
};
struct SinhVien {
	date ngaysinh;
	float diemdv;
	float dtl;
	char ten[50];
	char gioitinh[20];
	char quequan[100];

};
typedef SinhVien SV;
///
void nhapSinhVien(SV &sv);
void xoaXuongDong(char x[]);
void inSinhVien(SV sv);
void nhapdanhsachsv(SV ds[], int& n);
void capNhatSinhVien(SV &sv);
void getany();

int searchbyname(SV ds[], int n, char ten[]);
void sapXepDanhSachSinhVienTheodtl(SV ds[], int n);
void sapXepDanhSachSinhVienTheoddv(SV ds[], int n);
void searchbypoint(SV ds[], int n, float diem);
int searchbysex(SV ds[], int n, char gioitinh[]);
void xoaSinhVienTheostt(SV ds[], int& n, int stt);
void set_File(SV ds[], int n);
void get_File(SV ds[], int& n);
//////////////////////////
void xoaXuongDong(char x[]) {
	size_t len = strlen(x);
	if (x[len - 1] == '\n') {
		x[len - 1] = '\0';
	}
}

void nhapSinhVien(SV &sv) {
	char readnewline[10];
	fgets(readnewline, sizeof(readnewline), stdin); // line nay de xoa /n khi nhap scanf 
	printf("\nTen: ");fflush(stdin);fgets(sv.ten, sizeof(sv.ten), stdin); /*scanf("%s", sv.gioitinh);*/xoaXuongDong(sv.ten);
	printf("\nGioi tinh: ");fflush(stdin); fgets(sv.gioitinh, sizeof(sv.gioitinh), stdin); /*scanf("%s", sv.gioitinh);*/xoaXuongDong(sv.gioitinh);
	printf("\nQue Quan: "); fflush(stdin); fgets(sv.quequan, sizeof(sv.quequan), stdin);xoaXuongDong(sv.quequan);

	printf("\nNgay sinh: "); scanf("%d%d%d", &sv.ngaysinh.ngay, &sv.ngaysinh.thang, &sv.ngaysinh.nam);
	printf("\nDiem dv: "); scanf("%f", &sv.diemdv);
	printf("\nDiem tl: "); scanf("%f", &sv.dtl);
	//char readnewline[10];
	//fgets(readnewline, sizeof(readnewline), stdin); // line nay de xoa /n khi nhap scanf 
}
void inSinhVien(SV sv) {
	printf(" %20s \t %10s \t %2d/%d/%d \t %6.2f \t %6.2f \t %10s",  sv.ten, sv.gioitinh, sv.ngaysinh.ngay, sv.ngaysinh.thang, sv.ngaysinh.nam, sv.diemdv, sv.dtl,sv.quequan);
}
int searchbyname(SV ds[], int n, char ten[])
{
	for (int i = 0; i < n; i++) {
		if (strstr(ds[i].ten, ten)) {
			printf("Sinh vien can tim la: \n");
			inSinhVien(ds[i]);
		}
	}
	return 0;
}
void nhapdanhsachsv(SV ds[], int& n) {
	do {
		printf("\nNhap vao n:");
		scanf("%d", &n); fflush(stdin);
		
	} while (n <= 0);
	for (int i = 0; i < n; i++) {
		printf("Nhap vao sinh vien thu %d:\n ", i);
		nhapSinhVien(ds[i]);
	}
}
void capNhatSinhVien(SV& sv) {
	nhapSinhVien(sv);
}
void xuatDanhSachSinhVien(SV ds[], int n) {
	printf("%15s \t %10s \t %10s \t %10s \t %6s \t %6s \t %10s", "Ten", "Gioi Tinh", "Ngay Sinh", "Diem dv", "Diem tl", "Que Quan");
	printf("\n");
	for (int i = 0; i < n; i++) {
		inSinhVien(ds[i]);
		printf("\n");
	}
}
int searchbysex(SV ds[], int n, char gioitinh[])
{
	for (int i = 0; i < n; i++) {
		if (strstr(ds[i].gioitinh, gioitinh)) {
			printf("Sinh vien can tim la: \n");
			inSinhVien(ds[i]);
		}
	}
	return 0;
}
void sapXepDanhSachSinhVienTheodtl(SV ds[], int n) {
	for (int i = 0; i < n - 1; i++) {
		for (int j = i + 1; j < n; j++) {
			if (ds[i].dtl > ds[j].dtl) {
				SV temp;
				temp = ds[i];
				ds[i] = ds[j];
				ds[j] = temp;
			}
		}
	}
}
void sapXepDanhSachSinhVienTheoddv(SV ds[], int n) {
	for (int i = 0; i < n - 1; i++) {
		for (int j = i + 1; j < n; j++) {
			if (ds[i].diemdv > ds[j].diemdv) {
				SV temp;
				temp = ds[i];
				ds[i] = ds[j];
				ds[j] = temp;
			}
		}
	}
}
void searchbypoint(SV ds[], int n, float diem) {
	
		for (int i = 0; i < n; i++) {
			if (ds[i].diemdv >= diem) {
				printf("Sinh vien can tim la: \n");
				inSinhVien(ds[i]);
			}
		}	
}
void getany() {
	printf("\nNhap cai gi do di cuc cung ");
	_getch();
}
void xoaSinhVienTheostt(SV ds[], int& n, int stt) {
	for (int i = 0; i < n; i++) {
		if (i == stt) {
			for (int j = i; j < n; j++) {
				ds[j] = ds[j + 1];
			}
			n -= 1;
			return;
		}
	}
}
void get_File(SV ds[], int& n) {
	char tenFile[100];
	printf("\nNhap vao duong dan va ten file: ");
	fflush(stdin); fgets(tenFile, sizeof(tenFile), stdin); xoaXuongDong(tenFile);

	FILE* f;
	f = fopen(tenFile, "rb");
	if (f == NULL) {
		printf("\nLoi moi file de doc!");
		return;
	}
	fread(&n, sizeof(n), 1, f);
	for (int i = 0; i < n; i++) {
		fread(&ds[i], sizeof(SV), 1, f);
	}
	fclose(f);
}
void set_File(SV ds[], int n) {
	char tenFile[100];
	printf("\nNhap vao duong dan va ten file: ");
	fflush(stdin); fgets(tenFile, sizeof(tenFile), stdin); xoaXuongDong(tenFile);

	FILE* f;
	f = fopen(tenFile, "wb");
	if (f == NULL) {
		printf("\nLoi moi file de ghi!");
		return;
	}
	fwrite(&n, sizeof(n), 1, f);
	for (int i = 0; i < n; i++) {
		fwrite(&ds[i], sizeof(SV), 1, f);
	}
	fclose(f);

}


int main() {
	//SV sv1, arr[10];
	//int n = 10; int i;
	//for (i = 0; i < n; i++) {
	//	nhapSinhVien(arr[i]);
	//}
	///*nhapSinhVien(sv1);*/
	//printf("%15s \t %10s \t %10s \t %10s \t %6s \t %6s \t %10s", "Ten", "Gioi Tinh", "Ngay Sinh", "Diem dv", "Diem tl", "Que Quan");
	//for (i = 0; i < n; i++) {
	//	inSinhVien(arr[i]);

	//inSinhVien(sv1);
	SV ds[100]; int n; float diem; int chon;
		//int n; char name[50];
		//nhapdanhsachsv(ds, n);
		//xuatDanhSachSinhVien(ds, n);
		//printf("Nhap diem can tim: \n");
		//float diem = 8.3;
		///*scanf("%f", &name);*/
		//searchbypoint(ds, n, diem);
	do {
		printf("\nMENU:");
		printf("\n1- Nhap danh sach sinh vien");
		printf("\n2- Xuat danh sach sinh vien");
		printf("\n3- Xuat danh sach sinh vien loai");
		printf("\n- Sap xep sinh vien theo Dtl");
	
		printf("\n4- Tim sinh vien theo ten");
		printf("\n5- Xoa sinh vien theo Stt");
		printf("\n0- Thoat\n");
		scanf("%d", &chon);
	switch (chon) {
	case 1:
		printf("Nhap so luong sinh vien");
		
		nhapdanhsachsv(ds, n);
		getany();
		break;
	case 2:
		xuatDanhSachSinhVien(ds, n);
		getany();
		break;
	case 3:
		printf("\nDanh sach theo Dtl\n");
		printf("Nhap diem san`");
		scanf("%d", &diem);
		searchbypoint(ds, n,diem);
		getany();
		break;
	case 4:
		char tensv[20];
		char readnewline[10];
		fgets(readnewline, sizeof(readnewline), stdin);
		printf("\nNhap ten sinh vien can tim: "); fflush(stdin); fgets(tensv, sizeof(tensv), stdin); xoaXuongDong(tensv);
		searchbyname(ds, n, tensv);
		getany();
		break;
	case 5:
		int stt;
		printf("\nNhap stt can xoa"); scanf("%d", &stt);
		printf("\nDanh sach sau khi xoa\n");
		xoaSinhVienTheostt(ds, n, stt);
		xuatDanhSachSinhVien(ds, n);
		getany();
		break;
	}
} while (n != 0);
}


	


