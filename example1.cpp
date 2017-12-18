#include "explorer.hpp"

int main(int argc, char *argv[]) {
    
    if(argc < 2){
        cout << "There is no transferred parameter - there is no information on the file" << endl;
        return 0;
    }
    
    bf::path currentPath(bf::current_path());
    string curr_p = currentPath.string();
    
    MakeOutputInfoThreads(argc, argv, curr_p);
    StartKerr();
    
    return 0;
}