#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

struct SinhVien {
	string hoTen;
	float diemTB;
	string xepLoai;
};

struct LopHoc {
	string tenLop;
	int siSo;
	vector<SinhVien> danhSachSV;
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

// Hàm in thông tin lớp học
void inLopHoc(const LopHoc &lop) {
	cout << "Ten lop: " << lop.tenLop << ", Si so: " << lop.siSo << endl;
	cout << "Danh sach sinh vien:\n";
	for (const auto &sv : lop.danhSachSV) {
		inSinhVien(sv);
	}
}

// Hàm đọc thông tin từ file
void docFile(vector<LopHoc> &danhSachLop) {
	ifstream file("dslop.txt");
	if (!file) {
		cout << "Khong the mo file.\n";
		return;
	}
	int n;
	file >> n;
	danhSachLop.resize(n);
	for (int i = 0; i < n; ++i) {
		file >> danhSachLop[i].tenLop >> danhSachLop[i].siSo;
		danhSachLop[i].danhSachSV.resize(danhSachLop[i].siSo);
		for (int j = 0; j < danhSachLop[i].siSo; ++j) {
			file.ignore();
			getline(file, danhSachLop[i].danhSachSV[j].hoTen);
			file >> danhSachLop[i].danhSachSV[j].diemTB;
			danhSachLop[i].danhSachSV[j].xepLoai = tinhXepLoai(danhSachLop[i].danhSachSV[j].diemTB);
		}
	}
	file.close();
}

// Hàm xuất thông tin ra file
void xuatFile(const vector<LopHoc> &danhSachLop) {
	ofstream file("dslop_out.txt");
	if (!file) {
		cout << "Khong the mo file.\n";
		return;
	}
	for (const auto &lop : danhSachLop) {
		file << "Ten lop: " << lop.tenLop << ", Si so: " << lop.siSo << endl;
		file << "Danh sach sinh vien:\n";
		for (const auto &sv : lop.danhSachSV) {
			file << "Ho ten: " << sv.hoTen << ", Diem TB: " << sv.diemTB << ", Xep loai: " << sv.xepLoai << endl;
		}
	}
	file.close();
}

// Hàm in các lớp có trên 5 sinh viên giỏi
void inLopCoSinhVienGioi(const vector<LopHoc> &danhSachLop) {
	for (const auto &lop : danhSachLop) {
		int count = count_if(lop.danhSachSV.begin(), lop.danhSachSV.end(), [](const SinhVien &sv) {
			return sv.xepLoai == "Gioi";
		});
		if (count > 5) {
			inLopHoc(lop);
		}
	}
}

// Hàm tìm lớp có nhiều sinh viên nhất
void timLopNhieuSinhVienNhat(const vector<LopHoc> &danhSachLop) {
	auto maxIt = max_element(danhSachLop.begin(), danhSachLop.end(), [](const LopHoc &a, const LopHoc &b) {
		return a.siSo < b.siSo;
	});
	cout << "Lop co nhieu sinh vien nhat:\n";
	inLopHoc(*maxIt);
}

// Hàm tìm sinh viên có điểm trung bình cao nhất trong các lớp
void timSinhVienDiemTBMax(const vector<LopHoc> &danhSachLop) {
	SinhVien *maxSV = nullptr;
	for (const auto &lop : danhSachLop) {
		for (const auto &sv : lop.danhSachSV) {
			if (maxSV == nullptr || sv.diemTB > maxSV->diemTB) {
				maxSV = const_cast<SinhVien *>(&sv);
			}
		}
	}
	if (maxSV) {
		cout << "Sinh vien co diem trung binh cao nhat:\n";
		inSinhVien(*maxSV);
	}
}

int main() {
	vector<LopHoc> danhSachLop;

	// Đọc danh sách lớp từ file
	docFile(danhSachLop);

	// Xuất danh sách lớp vừa đọc ra file mới
	xuatFile(danhSachLop);

	// In danh sách các lớp có trên 5 sinh viên giỏi
	cout << "Danh sach cac lop co tren 5 sinh vien gioi:\n";
	inLopCoSinhVienGioi(danhSachLop);

	// Tìm lớp có nhiều sinh viên nhất
	cout << "Lop co nhieu sinh vien nhat:\n";
	timLopNhieuSinhVienNhat(danhSachLop);

	return 0;
}
