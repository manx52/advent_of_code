#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
using namespace std;


namespace detail {
    template <typename T, typename... Tail>
    void print_impl(const T& t, const Tail&... tail) {
        using namespace std::literals;
        std::cout << t;
        (..., (std::cout << " "sv << tail));
    }
}  // namespace detail

template <typename... Tail>
void print(const Tail&... tail) {
    if constexpr (sizeof...(tail) != 0) {
        detail::print_impl(tail...);
    }
    std::cout << std::endl;
}
string trim(const string& str)
{
    size_t first = str.find_first_not_of(' ');
    if (string::npos == first)
    {
        return str;
    }
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, (last - first + 1));
}

int main() {
    string myText;
    ifstream MyReadFile("input.txt");
    string list[] = {"blue", "red", "green"};
    vector<int> failed;
    while (getline (MyReadFile, myText)) {
        // Output the text from the file
        const int index_space = myText.find(' '), index_colon = myText.find(':');
        int id = stoi(myText.substr(index_space,(index_colon - index_space)));
        vector<string> pulls;
        vector<int> indexes;

        bool pass = true;
        stringstream  ss(myText.substr(index_colon + 1));
        string str;
        while (getline(ss, str, ';')) {
            pulls.push_back(trim(str));
        }


        for (const auto& i: pulls) {
            stringstream  ss2(i);
            string str2;

            while (getline(ss2, str2, ',')) {
                // print(trim(str2));
                int j = -1;
                for (const auto & color: list) {
                    j+=1;
                    int temp = str2.find(color);
                    if (temp == -1){
                        continue;
                    }

                    // print(trim(str2.substr(0, temp)));

                    int num = stoi(trim(str2.substr(0, temp)));
                    // print(color, str2, j, num);
                    switch (j) {
                        case 0: // blue
                            if (num > 14) {
                                print("h1", num);
                                // failed.push_back(id);
                                pass = false;
                            }
                            break;
                        case 1: // red
                            if (num > 12) {
                                // print("h2", num, j);
                                // failed.push_back(id);
                                pass = false;
                            }
                            break;
                        case 2: // green
                            if (num > 13) {
                                print("h3", num);
                                // failed.push_back(id);
                                pass = false;
                            }
                            break;
                        // default:
                        //     break;

                    }


                }

            }

        }
        if (pass) {
            // print(id);
            failed.push_back(id);
        }


    }
    int sum = 0;
    for (const auto& i: failed) {
        sum+= i;
        // print(i);
    }

    print(sum);
    // Close the file
    MyReadFile.close();
    return 0;
}