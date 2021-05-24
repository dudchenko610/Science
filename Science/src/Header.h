//#include <unistd.h> 
//#include <sys/types.h> 
//#include <fcntl.h> 
//#include <iostream>
//#include <cstring>
//
//using namespace std;
//
//const char* data = "ќдним из вариантов предыдущего способа €вл€етс€ хранение указателей не в дисковых блоках, а в индекс";
//
//int main(int argc, char** argv)
//{
//
//    if (argc != 4)
//    {
//        cout << "Wrong argument number" << endl;
//        return -1;
//    }
//
//    char* sourceFileName = argv[1];
//    char* receiverFileName = argv[2];
//    char* hardLinkName = argv[3];
//
//    int fd1 = open(sourceFileName, O_RDWR | O_CREAT, 777);
//    if (fd1 <= 0)
//    {
//        cout << "Unable to open / create source file" << endl;
//        return -1;
//    }
//
//    write(fd1, data, 100);
//
//
//    int hardLinkRes = link(sourceFileName, hardLinkName);
//    if (hardLinkRes != 0)
//    {
//        cout << "Unable to create hard link for source file" << endl;
//        return -1;
//    }
//
//
//
//    int fd2 = open(hardLinkName, O_RDONLY, 0);
//    lseek(fd2, -20, SEEK_END);
//    char buf[20];
//    read(fd2, &buf, sizeof(buf));
//
//    int fd3 = open(receiverFileName, O_RDWR | O_CREAT, 777);
//    write(fd3, &buf, sizeof(buf));
//
//    // Output data from files
//
//    int fd4 = open(hardLinkName, O_RDONLY, 0);
//    char sfBuf[100];
//    read(fd4, &sfBuf, 100);
//
//    int fd5 = open(receiverFileName, O_RDONLY, 0);
//    char rfBuf[20];
//    read(fd5, &rfBuf, 20);
//
//
//
//    cout << "Content of " << sourceFileName << " file:" << endl;
//    cout << sfBuf << endl;
//    cout << endl;
//
//    cout << "Content of " << receiverFileName << " file:" << endl;
//    cout << rfBuf << endl;
//    cout << endl;
//
//
//
//
//    cout << "[ls -li] Before removing hard link: " << hardLinkName << endl;
//    system("ls -li");
//
//    int unHardLinkRes = unlink(hardLinkName);
//    if (unHardLinkRes != 0)
//    {
//        cout << "Unable to destroy hard link for source file" << endl;
//        return -1;
//    }
//
//    cout << "[ls -li] After removing hard link: " << hardLinkName << endl;
//    system("ls -li");
//
//    return 0;
//}