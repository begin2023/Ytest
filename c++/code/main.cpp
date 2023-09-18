#include "src/testFrame/test_frame.h"

int main(int argc, char* argv[])
{
    if (argc == 1) {
        Frame::FrameWork::Instance().RunAllCases();
    } else {
        // 后续实现正则过滤
        for (int i = 1; i < argc; i++) {
            Frame::FrameWork::Instance().RunCase(argv[i]);
        }
    }
    return 0;
}