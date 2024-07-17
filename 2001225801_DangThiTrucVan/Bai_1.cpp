#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

struct SinhVien {
	string hoTen;
	float diemTB;
	string xepLoai;
};

// Hàm tính xếp loại dựa vào điểm trung bình
string tinhXepLoai(float diemTB) {
	if (diemTB >= 8) return "Gioi";
	else if (diemTB >= 6.5) return "Kha";
	else if (diemTB >= 5.0) return "Trung binh";
	else return "Yeu";
}

// Hàm nhập thông tin sinh viên
void nhapSinhVien(SinhVien &sv) {
	cout << "Nhap ho ten: ";
	cin.ignore();
	getline(cin, sv.hoTen);
	cout << "Nhap diem trung binh: ";
	cin >> sv.diemTB;
	sv.xepLoai = tinhXepLoai(sv.diemTB);
}

// Hàm in thông tin sinh viên
void inSinhVien(const SinhVien &sv) {
	cout << "Ho ten: " << sv.hoTen << ", Diem TB: " << sv.diemTB << ", Xep loai: " << sv.xepLoai << endl;
}

// Hàm sắp xếp tăng dần theo điểm trung bình
bool sapXepTangDan(const SinhVien &a, const SinhVien &b) {
	return a.diemTB < b.diemTB;
}

// Hàm sắp xếp giảm dần theo điểm trung bình
bool sapXepGiamDan(const SinhVien &a, const SinhVien &b) {
	return a.diemTB > b.diemTB;
}

// Hàm tìm kiếm sinh viên có điểm trung bình cao nhất/thấp nhất
void timKiemSinhVien(const vector<SinhVien> &danhSach) {
	auto maxIt = max_element(danhSach.begin(), danhSach.end(), sapXepTangDan);
	auto minIt = min_element(danhSach.begin(), danhSach.end(), sapXepTangDan);

	cout << "Sinh vien co diem trung binh cao nhat:\n";
	inSinhVien(*maxIt);
	cout << "Sinh vien co diem trung binh thap nhat:\n";
	inSinhVien(*minIt);
}

// Hàm in danh sách sinh viên xếp loại giỏi và khá
void inSinhVienGioiKha(const vector<SinhVien> &danhSach) {
	cout << "Danh sach sinh vien xep loai Gioi:\n";
	for (const auto &sv : danhSach) {
		if (sv.xepLoai == "Gioi") inSinhVien(sv);
	}
	cout << "Danh sach sinh vien xep loai Kha:\n";
	for (const auto &sv : danhSach) {
		if (sv.xepLoai == "Kha") inSinhVien(sv);
	}
}

// Hàm đếm sinh viên họ Nguyễn
int demSinhVienHoNguyen(const vector<SinhVien> &danhSach) {
	int count = 0;
	for (const auto &sv : danhSach) {
		if (sv.hoTen.substr(0, 6) == "Nguyen") count++;
	}
	return count;
}

void menu() {
	vector<SinhVien> danhSach;
	int choice;

	do {
		cout << "\nMenu\n";
		cout << "1. Nhap danh sach sinh vien\n";
		cout << "2. In danh sach sinh vien\n";
		cout << "3. Sap xep danh sach tang dan theo diem TB\n";
		cout << "4. Sap xep danh sach giam dan theo diem TB\n";
		cout << "5. Tim sinh vien co diem TB cao nhat/thap nhat\n";
		cout << "6. In danh sach sinh vien xep loai Gioi va Kha\n";
		cout << "7. Dem sinh vien ho Nguyen\n";
		cout << "0. Thoat\n";
		cout << "Chon: ";
		cin >> choice;

		switch (choice) {
		case 1: {
					int n;
					cout << "Nhap so luong sinh vien: ";
					cin >> n;
					for (int i = 0; i < n; ++i) {
						SinhVien sv;
						nhapSinhVien(sv);
						danhSach.push_back(sv);
					}
					break;
		}
		case 2:{
				   for (const auto &sv : danhSach){
					   inSinhVien(sv);
				   }
				   break;
		}
		case 3:{
				   sort(danhSach.begin(), danhSach.end(), sapXepTangDan);
				   cout << "Danh sach da duoc sap xep tang dan theo diem TB.\n";
				   break;
		}
		case 4:{
				   sort(danhSach.begin(), danhSach.end(), sapXepGiamDan);
				   cout << "Danh sach da duoc sap xep giam dan theo diem TB.\n";
				   break;
		}
		case 5:{
				   timKiemSinhVien(danhSach);
				   break;
		}
		case 6:{
				   inSinhVienGioiKha(danhSach);
				   break;
		}
		case 7:{
				   int count = demSinhVienHoNguyen(danhSach);
				   cout << "So luong sinh vien ho Nguyen la: " << count << endl;
				   break;
		}
		case 0:{
				   cout << "Thoat chuong trinh.\n";
				   break;
		}
		default: {
					 cout << "Lua chon khong hop le. Vui long chon lai.\n";
					 break;
		}
		}
	} while (choice != 0);
}
int main(){
	menu();
	return 0;
}

