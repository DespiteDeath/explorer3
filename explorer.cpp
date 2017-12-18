#include "explorer.hpp"

vector<pair<future<bool>, thread>> threads;

bool WriteInfo(string filename, string current_path){

    try{    
        
        // create new file "/info_<file_name>.txt" in current directory, and write filename info
        size_t nameSlPositionInFN = 0; // last position "/ "
        size_t nameDtPositionInFN = 0; // last position ".""
        
        for ( size_t i = filename.size(); i != 0; --i){
            
            if (filename[i] == '.'){
                nameDtPositionInFN = i;
            }
            
            if (filename[i] == '/'){
                nameSlPositionInFN = i;
                break;
            }
        }
        
        string name;
        name.append(filename, nameSlPositionInFN+1, nameDtPositionInFN-nameSlPositionInFN-1);
        cout << name << endl;
        
        string direction = current_path + "/info_" + name + ".txt";
        cout << direction << endl;
        
        ofstream fout;
    
        fout.open(direction);
        if (!fout.is_open())    // if the file didn't open
        {
            cout << "The file cannot be open or created" << endl;
            return false;
        }
        
        bf::path p(filename);
        bf::perms prm = bf::status(p).permissions();
        
        fout << "Full path: " << bf::absolute(p) << endl;
        fout << "File size: " << bf::file_size(p) << "byte" << endl;
        fout << "Access rights: " << endl << "File Owner ";
        fout << ((prm & bf::perms::owner_all) != bf::perms::no_perms ? "can " : "cannot ");
        fout << "to read, write down, run the file" << endl;
        fout << "Group of users of the file ";
        fout << ((prm & bf::perms::group_all) != bf::perms::no_perms ? "can " : "cannot ");
        fout << "to read, write down, run the file" << endl;
        fout << "Other users ";
        fout << ((prm & bf::perms::others_all) != bf::perms::no_perms ? "can " : "cannot ");
        fout << "to read, write down, run the file" << endl;
        fout << endl;
        fout.close();
        return true;
    }
    catch(bf::filesystem_error& e){ 
        cout << e.what() << endl;
        return false;
    }
}

void MakeOutputInfoThreads(int argc, char *argv[], string  current_pth){
    for (int i = 1; i < argc; ++i) {
        string filename = argv[i];

        packaged_task<bool(string, string)> task(WriteInfo); // set up packaged_task
        auto result = task.get_future();
        
        thread new_thr(move(WriteInfo), filename, current_pth);
        threads.push_back(pair<future<bool>, thread>(move(result), move(new_thr)));
    }
}

void StartKerr(){
    for (auto it = threads.begin(); it != threads.end(); ++it){
        it->second.detach();
    }
    
    for (auto it = threads.begin(); it != threads.end(); ++it){
        cout << "Data are taken: " << ( it->first.get() ? "true": "false" ) << endl;
    }
}
