#include "FileManager.h"
#include <fstream>

template <typename T>
static bool saveBin(const std::string& path, const T* ptr, int n) {
    std::ofstream out(path, std::ios::binary);
    if (!out) return false;
    out.write(reinterpret_cast<const char*>(&n), sizeof(int));
    if (n > 0) out.write(reinterpret_cast<const char*>(ptr), sizeof(T) * n);
    return out.good();
}

template <typename T>
static bool loadBin(const std::string& path, std::vector<T>& ds) {
    std::ifstream in(path, std::ios::binary);
    int n = 0;
    if (!in || !in.read(reinterpret_cast<char*>(&n), sizeof(int)) || n < 0) return false;
    ds.resize(n);
    if (n > 0) in.read(reinterpret_cast<char*>(ds.data()), sizeof(T) * n);
    return in.good();
}

bool FileManager::saveBooks(const std::vector<Sach>& ds) { return saveBin("data/books.dat", ds.data(), ds.size()); }
bool FileManager::loadBooks(std::vector<Sach>& ds) { return loadBin("data/books.dat", ds); }
bool FileManager::saveReaders(const std::vector<DocGia>& ds) { return saveBin("data/readers.dat", ds.data(), ds.size()); }
bool FileManager::loadReaders(std::vector<DocGia>& ds) { return loadBin("data/readers.dat", ds); }
bool FileManager::saveTickets(const std::vector<PhieuMuon>& ds) { return saveBin("data/tickets.dat", ds.data(), ds.size()); }
bool FileManager::loadTickets(std::vector<PhieuMuon>& ds) { return loadBin("data/tickets.dat", ds); }
bool FileManager::saveHistory(const GiaoDich* arr, int n) { return saveBin("data/history.dat", arr, n); }
bool FileManager::loadHistory(std::vector<GiaoDich>& ds) { return loadBin("data/history.dat", ds); }

void FileManager::log(const std::string& msg) {
    std::ofstream f("data/log.txt", std::ios::app);
    if (f) f << msg << "\n";
}
