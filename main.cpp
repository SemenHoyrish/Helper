#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;


enum colors
{
    Black,
    Red,
    Green,
    Yellow,
    Blue,
    Magenta,
    Cyan,
    White,
    Bright_Black,
    Bright_Red,
    Bright_Green,
    Bright_Yellow,
    Bright_Blue,
    Bright_Magenta,
    Bright_Cyan,
    Bright_White
};
const std::map<colors, std::string> fg_colors = {
    {Black, "30"},
    {Red, "31"},
    {Green, "32"},
    {Yellow, "33"},
    {Blue, "34"},
    {Magenta, "35"},
    {Cyan, "36"},
    {White, "37"},
    {Bright_Black, "90"},
    {Bright_Red, "91"},
    {Bright_Green, "92"},
    {Bright_Yellow, "93"},
    {Bright_Blue, "94"},
    {Bright_Magenta, "95"},
    {Bright_Cyan, "96"},
    {Bright_White, "97"}
};
const std::map<colors, std::string> bg_colors = {
    {Black, "40"},
    {Red, "41"},
    {Green, "42"},
    {Yellow, "43"},
    {Blue, "44"},
    {Magenta, "45"},
    {Cyan, "46"},
    {White, "47"},
    {Bright_Black, "100"},
    {Bright_Red, "101"},
    {Bright_Green, "102"},
    {Bright_Yellow, "103"},
    {Bright_Blue, "104"},
    {Bright_Magenta, "105"},
    {Bright_Cyan, "106"},
    {Bright_White, "107"}
};
enum styles
{
    normal,
    bold,
    italic,
    dark
};
const std::map<styles, int> font_styles = {
    {normal, 0},
    {bold, 1},
    {dark, 2},
    {italic, 3}
};

void write_line(std::string text)
{
    std::cout << text << std::endl;
}
void write(std::string text)
{
    std::cout << text;
}

void color_write(std::string text, colors fg, colors bg, styles style)
{
    write_line("\033[" + std::to_string(font_styles.at(style)) + ";" + fg_colors.at(fg) + ";" + bg_colors.at(bg) + "m"+ text +"\033[0m");
}

void default_write(string text)
{
    color_write(text, White, Black, normal);
}

void log(string text)
{
    color_write("[INFO] " + text, White, Black, normal);
}

void log_warning(string text)
{
    color_write("[WARN] " + text, Yellow, Black, normal);
}

void log_error(string text)
{
    color_write("[ERROR] " + text, Red, Black, normal);
}



// typedef struct {
//     map<string, Information> values = {};
//     string value = "";

//     string get()
//     {
//         if (value != "")
//         {
//             return value;
//         }
//         else
//         {
//             return "";
//         }
//     }
//     map<string, Information> get_values()
//     {
//         if (values.size() > 0)
//         {
//             return values;
//         }
//     }

// } Information;

map<string, map<string, string>> info = {
    {
        "math",
        {
            {"_", "Some math information such as formulas, theorems, etc."},
            {"area_triangle", "The area of the triangle is \n 1/2 * a * h"},
            {"area_right_triangle", "The area of the right triangle (one angle is 90 deg) is \n 1/2 * a * b"},
            {"area_parallelogram", "The area of the parallelogram is \n a * h"},
        }
    },
};

std::vector<std::string> split (std::string s, std::string delimiter) {
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    std::string token;
    std::vector<std::string> res;

    while ((pos_end = s.find (delimiter, pos_start)) != std::string::npos) {
        token = s.substr (pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        res.push_back (token);
    }

    res.push_back (s.substr (pos_start));
    return res;
}

void inf(string request)
{
    auto info_path = split(request, "/");
    string message = "";

    if (info.count(info_path[0]) == 0)
    {
        log_error("Can`t find " + info_path[0]);
        exit(0);
    }

    if (info.at(info_path[0]).size() == 1 && info.at(info_path[0]).count("_") == 1 )
    {
        message = info.at(info_path[0]).at("_");
    }
    else
    {
        if (info_path.size() == 1 && info.at(info_path[0]).count("_") == 1)
        {
            message = info.at(info_path[0]).at("_");
        }
        else if (info_path.size() == 1)
        {
            log_error("Can`t find " + info_path[0] + "/_");
            exit(0);
        }
        else if (info.at(info_path[0]).count(info_path[1]) == 0)
        {
            log_error("Can`t find " + info_path[0] + "/" + info_path[1]);
            exit(0);
        }
        else
        {
            message = info.at(info_path[0]).at(info_path[1]);
        }
    }


    default_write(message);
}

int main(int argc, char *argv[])
{
    // for (int i = 0; i < argc; i++)
    // {
    //     cout << argv[i] << endl;
    // }

    if (argc != 3)
    {
        log_error("Incorrect number of arguments! Got " + std::to_string(argc) + ", expected 3");
        exit(1);
    }

    // math/area_triangle
    // -> inf math/area_triangle
    //  +++ 
    // calc нок
    // calc нод
    // etc

    string s = "inf";
    if ( s.compare(argv[1]) == 0)
    {
        inf(argv[2]);
    }
    else
    {
        log_error("????");
    }
    

    return 0;
}
