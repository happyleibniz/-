#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <vector>
#include <windows.h>  // For MultiByteToWideChar and WideCharToMultiByte
#include <ctime> 

using namespace std;

string gb2312_to_utf8(const string& gb2312_str) {
    // Convert GB2312 to wide string
    int wlen = MultiByteToWideChar(CP_ACP, 0, gb2312_str.c_str(), -1, nullptr, 0);
    if (wlen == 0) return "";
    vector<wchar_t> wstr(wlen);
    MultiByteToWideChar(CP_ACP, 0, gb2312_str.c_str(), -1, wstr.data(), wlen);
    // Convert wide string to UTF-8
    int utf8_len = WideCharToMultiByte(CP_UTF8, 0, wstr.data(), -1, nullptr, 0, nullptr, nullptr);
    if (utf8_len == 0) return "";
    vector<char> utf8_str(utf8_len);
    WideCharToMultiByte(CP_UTF8, 0, wstr.data(), -1, utf8_str.data(), utf8_len, nullptr, nullptr);
    return string(utf8_str.data());
}

class Exam {
public:
    Exam() {
        cout << "<!>WARNING: YOU MUST install a C++ compiler! (if you have installed it, please ignore this warning)" << endl;
        cout << "INFO: initializing download process..." << endl;
    }

    void download(const string& url, const string& dest) {
        string command = "curl -o " + dest + " " + url;
        int result = system(command.c_str());

        if (result != 0) {
            cerr << "Failed to download file using curl command" << endl;
        }
    }

    void showFileContent(const string& filename) {
        ifstream file(filename, ios::binary);
        if (!file.is_open()) {
            cerr << "Failed to open file: " << filename << endl;
            return;
        }
        string content((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
        string utf8_content = gb2312_to_utf8(content);
        cout << utf8_content << endl;
        file.close();
    }

    void compileCode(const string& filename) {
        string command = "g++ " + filename + " -o compiled_program";
        int result = system(command.c_str());
        if (result != 0) {
            cerr << "Compilation failed" << endl;
        }
    }

    string runProgramWithInput(const string& input) {
        ofstream input_file("input.txt");
        if (!input_file) {
            cerr << "Failed to open file for writing input" << endl;
            return "";
        }
        input_file << input;
        input_file.close();
        string command = "compiled_program < input.txt";
        char buffer[128];
        string result = "";
        FILE* pipe = _popen(command.c_str(), "r");
        if (!pipe) return "ERROR";

        while (fgets(buffer, sizeof(buffer), pipe) != NULL) {
            result += buffer;
        }

        _pclose(pipe);
        return result;
    }

    bool checkOutput(const string& output, const string& expected) {
        // Trim any leading or trailing whitespace from both output and expected
        auto trim = [](const string& str) {
            size_t start = str.find_first_not_of(" \t\n\r");
            size_t end = str.find_last_not_of(" \t\n\r");
            return (start == string::npos) ? "" : str.substr(start, end - start + 1);
            };

        return trim(output) == trim(expected);
    }

    void enterCode() {
        cout << "Enter your C++ code (end with :wq):" << endl;
        string code;
        string line;
        while (getline(cin, line) && line != ":wq") {
            code += line + "\n";
        }
        ofstream code_file("foo.cpp");
        if (!code_file) {
            cerr << "Failed to open file for writing" << endl;
            return;
        }
        code_file << code;
        code_file.close();
        while (true) {
            compileCode("foo.cpp");
            ifstream test_file("test_cases.txt");
            if (!test_file) {
                cerr << "Failed to open test cases file" << endl;
                return;
            }

            string input, expected_output;
            bool all_tests_passed = true;
            while (getline(test_file, input)) {
                getline(test_file, expected_output);
                string output = runProgramWithInput(input);
                // cout << "Program output: " << output << endl;  //debug
                if (!checkOutput(output, expected_output)) {
                    cout << "Wrong Answer" << endl;
                    all_tests_passed = false;
                    break; 
                }
            }

            if (all_tests_passed) {
                cout << "Accepted" << endl;
                remove("compiled_program.exe");
                remove("foo.cpp");
                remove("exam_data.data");
                remove("test_cases.txt");
                remove("input.txt");
                break;
            }
        }
    }

    void beginner() {
        cout << "[INFO]: trying to connect to cdn.xyehr.cn ..." << endl;
        cout << "searching for exams... please wait..." << endl;
        string URL = "https://cdn.xyehr.cn/source/BlueBridgeCupNationalSoftwareandInformationTechnologyProfessionalTalentCompetition/get.search";
        string destination = "get.search";
        download(URL, destination);
        ifstream getsearchfile(destination);
        vector<pair<string, string>> exams; 
        string dataFile, testCaseFile;

        while (getline(getsearchfile, dataFile)) {
            getline(getsearchfile, testCaseFile);
            exams.push_back(make_pair(dataFile, testCaseFile));
        }
        getsearchfile.close();

        

        if (!exams.empty()) {
            srand(time(0)); 
            int randomIndex = rand() % exams.size();
            string selectedDataFile = exams[randomIndex].first;
            string selectedTestCaseFile = exams[randomIndex].second;
            cout << "Selected files: " << selectedDataFile << " and " << selectedTestCaseFile << endl;
            download("https://cdn.xyehr.cn/source/BlueBridgeCupNationalSoftwareandInformationTechnologyProfessionalTalentCompetition/" + selectedDataFile, "exam_data.data");
            download("https://cdn.xyehr.cn/source/BlueBridgeCupNationalSoftwareandInformationTechnologyProfessionalTalentCompetition/" + selectedTestCaseFile, "test_cases.txt");
            cout << "[INFO]: Download completed!" << endl;
            cout << "############################################################" << endl;
            cout << "\033[2J\033[1;1H";
            showFileContent("exam_data.data");

            cout << "####################[CODE AREA]#############################" << endl;
            enterCode();
        }
        else {
            cerr << "No exams found in the get.search file." << endl;
        }
    }




};

int main() {
    Exam exam;
    exam.beginner();
    return 0;
}
