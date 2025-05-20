#pragma once
#include <gtkmm.h>
#include "Calculator.h"
#include "Database.h"
#include <iostream>

class FiestaWindow : public Gtk::Window {
public:
    FiestaWindow()
        : db("data/fiesta.db"),
        main_box(Gtk::ORIENTATION_VERTICAL, 10),
        btn_calculate("Calcular"),
        btn_save("Guardar"),
        btn_export("Exportar a CSV") {

        set_title("Калькулятор Фиесты Делюкс");
        set_default_size(500, 400);

        setupInputs();
        setupButtons();
        setupResults();

        add(main_box);
        show_all_children();
    }

private:
    Database db;
    FiestaCalculator<double> calculator;

    Gtk::Box main_box;
    Gtk::Entry entry_ingredient, entry_quantity;
    Gtk::ComboBoxText combo_operation;
    Gtk::Button btn_calculate, btn_save, btn_export;
    Gtk::Label label_result;
    Gtk::ScrolledWindow scroll_results;
    Gtk::TextView text_results;

    void setupInputs() {
        entry_ingredient.set_placeholder_text("Ingrediente");
        entry_quantity.set_placeholder_text("Cantidad");

        combo_operation.append("Sumar");
        combo_operation.append("Restar");
        combo_operation.append("Multiplicar");
        combo_operation.append("Dividir");
        combo_operation.set_active(0);

        main_box.pack_start(entry_ingredient, Gtk::PACK_SHRINK);
        main_box.pack_start(entry_quantity, Gtk::PACK_SHRINK);
        main_box.pack_start(combo_operation, Gtk::PACK_SHRINK);
    }

    void setupButtons() {
        btn_calculate.signal_clicked().connect([this]() {
            try {
                double value = std::stod(entry_quantity.get_text());
                std::vector<double> vec = { 1.0, 2.0, 3.0 };

                std::string op = combo_operation.get_active_text();
                std::vector<double> result;

                if (op == "Sumar") result = calculator.add(vec, { value, value, value });
                else if (op == "Restar") result = calculator.subtract(vec, { value, value, value });
                else if (op == "Multiplicar") result = calculator.multiply(vec, value);
                else if (op == "Dividir") result = calculator.divide(vec, value);

                text_results.get_buffer()->set_text("Resultado: " + vectorToString(result));
            }
            catch (const std::exception& e) {
                text_results.get_buffer()->set_text("?Error! " + std::string(e.what()));
            }
            });

        btn_save.signal_clicked().connect([this]() {
            try {
                db.saveIngredient(
                    entry_ingredient.get_text(),
                    std::stod(entry_quantity.get_text())
                );
                updateResults();
            }
            catch (...) {
                text_results.get_buffer()->set_text("Error al guardar");
            }
            auto ingredients = db.getIngredients();
            if (ingredients.empty()) {
                std::cout << "БД пуста! Нет данных для экспорта." << std::endl;
            }
            });

        btn_export.signal_clicked().connect([this]() {
            std::string csv_path = "exports/ingredients.csv";
            std::cout << "Путь экспорта: " << std::filesystem::absolute(csv_path) << std::endl;
            db.exportToCSV(csv_path);
            text_results.get_buffer()->set_text("Datos exportados a: " + csv_path);
            });

        main_box.pack_start(btn_calculate, Gtk::PACK_SHRINK);
        main_box.pack_start(btn_save, Gtk::PACK_SHRINK);
        main_box.pack_start(btn_export, Gtk::PACK_SHRINK);
    }

    void setupResults() {
        text_results.set_editable(false);
        scroll_results.add(text_results);
        scroll_results.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
        main_box.pack_start(scroll_results);
    }

    void updateResults() {
        auto ingredients = db.getIngredients();
        std::string text;
        for (const auto& ingredient : ingredients) {
            text += ingredient.first + ": " + std::to_string(ingredient.second) + "\n";
        }
        text_results.get_buffer()->set_text(text.empty() ? "No hay datos" : text);
    }

    std::string vectorToString(const std::vector<double>& vec) {
        std::string result;
        for (double v : vec) {
            result += std::to_string(v) + " ";
        }
        return result;
    }
};