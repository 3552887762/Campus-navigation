#include "Graph.hpp" 
#include <easyx.h> -
#include <conio.h> 
#include <graphics.h> 
#pragma comment(lib,"winmm.lib") 

void Start()
{
    IMAGE img1;
    const char* str = "E:\\����\\У԰����\\��ͼ.jpg";
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
        if (InputBox(inputBuffer, 100, "��������ʼ������(��0��ʼ): \n����\"end\"�˳�����"))
        {
            string inputStr(inputBuffer);
            if (inputStr == "end") {
                break;
            }
            try {
                int src_vertex = std::stoi(inputBuffer);
                if (src_vertex >= 13 || src_vertex < 0)
                {
                    MessageBox(NULL, "��������ֲ��ڷ�Χ��\n����������", "У԰����", MB_OKCANCEL);
                    continue;
                }
                myg.DijkstraShortestPath(src_vertex);
                cout << '\n';
                cout << '\n';
            }
            catch (const std::invalid_argument& e) {
                MessageBox(NULL, "����Ĳ�������\n����������", "У԰����", MB_OKCANCEL);
                continue;
            }
        }
    }

    MessageBox(NULL, "�������˳�", "У԰����", MB_OKCANCEL);
    closegraph();
    return 0;
}