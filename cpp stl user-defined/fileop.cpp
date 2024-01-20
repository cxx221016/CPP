#include <fstream>
#include <string>
#include <iostream>

int main() {
    std::ifstream file("1.txt"); // 打开名为"1.txt"的文件以供读取
    if (!file) { // 如果文件不存在，输出错误信息并返回
        std::cerr << "Unable to open file";

        return 1;
    }
    std::string text((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>()); // 读取文件的全部内容
    int length = text.length(); // 计算文件内容的长度
    std::cout << length << std::endl; // 打印文件内容的长度
    system("pause");
    return 0;
}
