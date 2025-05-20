#include <gtest/gtest.h>
#include "../src/Database.h"
#include <filesystem>

class DatabaseTest : public ::testing::Test {
protected:
  void SetUp() override {
    db_path = "test_fiesta.db";
    db = new Database(db_path);
  }

  void TearDown() override {
    delete db;
    std::remove(db_path.c_str());
  }

  std::string db_path;
  Database* db;
};

// Тест сохранения ингредиента
TEST_F(DatabaseTest, SaveIngredient) {
  db->saveIngredient("Сальса", 100.0);
  auto ingredients = db->getIngredients();
  ASSERT_FALSE(ingredients.empty());
  EXPECT_EQ(ingredients[0].first, "Сальса");
}

// Тест экспорта в CSV
TEST_F(DatabaseTest, ExportToCSV) {
  db->saveIngredient("Кукуруза", 50.0);
  std::string csv_path = "test_export.csv";
  db->exportToCSV(csv_path);

  std::ifstream file(csv_path);
  std::string line;
  std::getline(file, line);
  EXPECT_EQ(line, "name,quantity");
  std::getline(file, line);
  EXPECT_TRUE(line.find("Кукуруза,50.0") != std::string::npos);

  std::remove(csv_path.c_str());
}