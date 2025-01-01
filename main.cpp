#include "Graph.hpp" 
#include <easyx.h> -
#include <conio.h> 
#include <graphics.h> 
#pragma comment(lib,"winmm.lib") 

void Start()
{
    IMAGE img1;
    const char* str = "E:\\桌面\\校园导航\\地图.jpg";
    loadimage(&img1, str, 1040, 680, true);
    putimage(0, 0, &img1);
}

int main()
{
    initgraph(1040, 680, SHOWCONSOLE);
    Start();

    Graph myg;
    myg.PrintGraph();

    while (true) {
        char inputBuffer[100];
        if (InputBox(inputBuffer, 100, "请输入起始顶点编号(从0开始): \n输入\"end\"退出程序"))
        {
            string inputStr(inputBuffer);
            if (inputStr == "end") {
                break;
            }
            try {
                int src_vertex = std::stoi(inputBuffer);
                if (src_vertex >= 13 || src_vertex < 0)
                {
                    MessageBox(NULL, "输入的数字不在范围内\n请重新输入", "校园导航", MB_OKCANCEL);
                    continue;
                }
                myg.DijkstraShortestPath(src_vertex);
                cout << '\n';
                cout << '\n';
            }
            catch (const std::invalid_argument& e) {
                MessageBox(NULL, "输入的不是数字\n请重新输入", "校园导航", MB_OKCANCEL);
                continue;
            }
        }
    }

    MessageBox(NULL, "程序已退出", "校园导航", MB_OKCANCEL);
    closegraph();
    return 0;
}