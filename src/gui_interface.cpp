#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Output.H>
#include <FL/Fl_Multiline_Output.H>
#include <FL/Fl_Text_Display.H>
#include <FL/Fl_Text_Buffer.H>
#include <FL/Fl_Native_File_Chooser.H>

#include "../inc/gui_interface.h"
#include "../inc/perms_serializer.h"

#include <iostream>
#include <string>

Fl_Input* filePathInput;
Fl_Input* passwordInput;
Fl_Button* browseButton;
Fl_Multiline_Output* outputArea;

void browse_callback(Fl_Widget* widget, void* data) {
    Fl_Native_File_Chooser fileChooser;
    fileChooser.title("Choose the file");
    fileChooser.type(Fl_Native_File_Chooser::BROWSE_FILE); // Choosing a file

    // Filters
    fileChooser.filter("DATENC files\t*.datenc\nAll files\t*.*");

    // Showing dialogue
    int result = fileChooser.show();

    if (result == 0) {  // Success
        filePathInput->value(fileChooser.filename());  // Input path setup
    }
}

void serialize_callback(Fl_Widget* widget, void* data) {
    std::string sourcePath = filePathInput->value();
    std::string password = passwordInput->value();

    if (sourcePath.empty() || password.empty()) {
        outputArea->value("Error: File path and password cannot be empty.");
        return;
    }

    int result = serialize(&sourcePath, &password);
    if(result == 0)
    {
        outputArea->value("File serialized successfully.");
    }
    else if (result == 1)
    {
        outputArea->value("ERROR: Failed to open file");
    }
    else if (result == 2)
    {
        outputArea->value("ERROR: Failed to encrypt file");
    }
}

void deserialize_callback(Fl_Widget* widget, void* data) {
    std::string sourcePath = filePathInput->value();
    std::string password = passwordInput->value();

    if (sourcePath.empty() || password.empty()) {
        outputArea->value("Error: File path and password cannot be empty.");
        return;
    }

    int result = deserialize(&sourcePath, &password);
    if (result == 0)
    {
        outputArea->value("File deserialized successfully.");
    }
    else if (result == 1)
    {
        outputArea->value("ERROR: Failed to open file");
    }
    else if (result == 2)
    {
        outputArea->value("ERROR: Decryption failed, data integrity corrupted");
    }
}

int run_gui(int argc, char** argv) {
    // Создание окна
    Fl_Window* window = new Fl_Window(400, 300, "Permissions Serializer");

    // Поле для ввода пути к файлу
    filePathInput = new Fl_Input(100, 20, 200, 30, "File Path:");

    browseButton = new Fl_Button(310, 20, 80, 30, "Browse...");
    browseButton->callback(browse_callback);

    // Поле для ввода пароля
    passwordInput = new Fl_Input(100, 60, 200, 30, "Password:");

    // Кнопка для сериализации
    Fl_Button* serializeButton = new Fl_Button(50, 100, 120, 30, "Serialize");
    serializeButton->callback(serialize_callback);

    // Кнопка для десериализации
    Fl_Button* deserializeButton = new Fl_Button(200, 100, 120, 30, "Deserialize");
    deserializeButton->callback(deserialize_callback);

    // Область для вывода сообщений
    outputArea = new Fl_Multiline_Output(50, 150, 300, 100, "Output:");
    outputArea->align(FL_ALIGN_TOP_LEFT);

    // Отображение окна
    window->end();
    window->show(argc, argv);

    // Запуск основного цикла обработки событий
    Fl::run();

    return 0;
}
