// file.h
#pragma once


#include <filesystem>
#include <fstream>

#include "common/common.h"
#include "serialization/json_serializers.h"


namespace accounting {
template <typename T>
// Добавить индексирование
// Исправить include write/read
class File {
 private:
  std::filesystem::path file_path_;

  // Enforce using File<T> only for T = Account or Transfer
  static_assert(
      std::is_same<T, Account>::value || std::is_same<T, Transfer>::value,
      "File class can only be instantiated with Account or Transfer types");

  template <typename R, typename F>
  R with_istream(F&& func);
  template <typename R, typename F>
  R with_ostream(F&& func, std::ios::openmode mode = std::ios::out |
                                                          std::ios::trunc);

 public:
  File(const string& file_path) : file_path_(file_path) {}

  ~File() = default;

  bool file_exists() const { return std::filesystem::exists(file_path_); }

  //bool write(const T& obj);
  bool write(const std::vector<T>& objs);

  //std::optional<T> read_one();
  std::vector<T> read_all();

  bool append(const T& obj);
  bool append(const std::vector<T>& objs);
};
} // namespace accounting


namespace accounting {
// Добавить проверку сигнатуры лямбды
// Добавить свои типы для ошибок
template <typename T>
template <typename R, typename F>
R File<T>::with_istream(F&& func) {
  try {
    std::ifstream in(file_path_);
    if (!in.is_open())
      throw std::runtime_error("Failed to open file for reading: "s +
                               file_path_.string());
    in.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    return func(in);
  } catch (const std::ios::failure& e) {
    throw std::runtime_error("I/O error while reading from "s +
                             file_path_.string() + ": " + e.what());
  } catch (const std::exception& e) {
    throw std::runtime_error("Unexpected error while reading from "s +
                             file_path_.string() + ": " + e.what());
  }
}

template <typename T>
template <typename R, typename F>
R File<T>::with_ostream(F&& func, std::ios::openmode mode) {
  try {
    std::ofstream out(file_path_, mode);
    if (!out.is_open())
      throw std::runtime_error("Failed to open file for writing: "s +
                               file_path_.string());
    out.exceptions(std::ofstream::badbit | std::ofstream::failbit);
    func(out);
    if constexpr (std::is_same_v<void, R>)
      R();
    else
      return R();
  } catch (std::ios::failure& ex) {
    throw std::runtime_error("I/O error while reading from "s +
                             file_path_.string() + ": " + ex.what());
  } catch (std::exception& ex) {
    throw std::runtime_error("Unexpected error while reading from "s +
                             file_path_.string() + ": " + ex.what());
  }
}


template <typename T>
bool File<T>::write(const std::vector<T>& objs) {
  return with_ostream<bool>([&](std::ofstream& out) {
    nlohmann::json json_array = nlohmann::json::array();
    for (const T& obj : objs) json_array.push_back(obj);
    out << json_array.dump(4);
    return true;
  });
}


// Сделать возвращаемый вектор ссылкой?
template <typename T>
std::vector<T> File<T>::read_all() {
  return with_istream<std::vector<T>>([&](std::ifstream& in) {
    std::vector<T> result;
    nlohmann::json j;
    in >> j;
    if (j.is_array())
      for (const auto& item : j) result.push_back(item.get<T>());
    else
      result.push_back(j.get<T>());
    return result;
  });
}

template <typename T>
bool File<T>::append(const T& obj) {
  std::vector<T> existing_data;
  if (file_exists()) existing_data = read_all();
  existing_data.push_back(obj);
  return write(existing_data);
}

template <typename T>
bool File<T>::append(const std::vector<T>& objs) {
  std::vector<T> existing_data;
  if (file_exists()) existing_data = read_all();
  existing_data.insert(existing_data.end(), objs.begin(), objs.end());
  return write(existing_data);
}
} // namespace accounting