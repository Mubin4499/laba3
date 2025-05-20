#pragma once
#include <sqlite3.h>
#include <string>
#include <vector>
#include <filesystem>
#include <fstream>
#include <iostream>

class Database {
public:
    Database(const std::string& db_path) {
        std::filesystem::create_directory("data");
        if (sqlite3_open(db_path.c_str(), &db) != SQLITE_OK) {
            throw std::runtime_error("Error opening database: " + std::string(sqlite3_errmsg(db)));
        }
        createTables();
    }

    ~Database() { sqlite3_close(db); }

    void saveIngredient(const std::string& name, double quantity) {
        std::string sql = "INSERT INTO Ingredients (name, quantity) VALUES (?, ?);";
        sqlite3_stmt* stmt;
        sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
        sqlite3_bind_text(stmt, 1, name.c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_double(stmt, 2, quantity);
        sqlite3_step(stmt);
        sqlite3_finalize(stmt);
    }

    std::vector<std::pair<std::string, double>> getIngredients() {
        std::vector<std::pair<std::string, double>> ingredients;
        sqlite3_stmt* stmt;
        const char* sql = "SELECT name, quantity FROM Ingredients;";
        sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);

        while (sqlite3_step(stmt) == SQLITE_ROW) {
            ingredients.emplace_back(
                reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0)),
                sqlite3_column_double(stmt, 1)
            );
        }
        sqlite3_finalize(stmt);
        return ingredients;
    }

    void exportToCSV(const std::string& filename) {
        std::filesystem::create_directory("exports");

        std::ofstream file(filename);
        if (!file.is_open()) {
            throw std::runtime_error("Не удалось открыть файл для записи: " + filename);
        }

        file << "name,quantity\n";
        auto ingredients = getIngredients();
        for (const auto& [name, qty] : ingredients) {
            file << name << "," << qty << "\n";
        }
        file.close();
        std::cout << "Файл успешно создан: " << filename << std::endl;
    }

private:
    sqlite3* db;

    void createTables() {
        const char* sql =
            "CREATE TABLE IF NOT EXISTS Ingredients ("
            "id INTEGER PRIMARY KEY AUTOINCREMENT,"
            "name TEXT NOT NULL,"
            "quantity REAL NOT NULL);";
        sqlite3_exec(db, sql, nullptr, nullptr, nullptr);
    }
};