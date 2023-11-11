#include<unistd.h>
#include<fcntl.h>
#include<string>
#include<vector>
namespace cc{
    using namespace std;
    struct CCRecord{
        char* data;
        unsigned int count;
    };
    class CCDB{
        int fd;
    public:
        CCDB(string path);
        ~CCDB();
        void flush();
        void addRecord(CCRecord& record);
        cc::CCRecord* operator [](int index);
    };

    template<typename T>
    class CCFileArray{
        int fd;
    public:
        CCFileArray(string path){
            fd = open(path.c_str(),O_RDWR | O_NONBLOCK | O_TRUNC 
            | O_CREAT);
        }
        ~CCFileArray(){
            close(fd);
        }
        T operator [](int index){
            T c;
            auto result = pread(this->fd,&c,sizeof(T),index * sizeof(T));
            if (0 > result){
                throw std::to_string(result);
            }
            return c;
        }
        void write(T t,int index){
            auto result = pwrite(fd,&t,sizeof(t),index * sizeof(t));
            if (0 > result){
                throw std::to_string(result);
            }
        }
        void wlock(int index,int whence,int len){
            struct flock fl;   
            fl.l_type = F_RDLCK;
            fl.l_start = index;
            fl.l_whence = whence;
            fl.l_len = len;
            auto result = fcntl(this->fd,F_SETLK,&fl);
            if (0 != result){
                throw std::to_string(result);
            }
        }
        void rlock(int index,int whence,int len){
            struct flock fl;   
            fl.l_type = F_WRLCK;
            fl.l_start = index;
            fl.l_whence = whence;
            fl.l_len = len;
            auto result = fcntl(this->fd,F_SETLKW,&fl);
            if (0 != result){
                throw std::to_string(result);
            }
        }
        void unlock(int index,int whence,int len){
            struct flock fl;   
            fl.l_type = F_UNLCK;
            fl.l_start = index;
            fl.l_whence = whence;
            fl.l_len = len;
            auto result = fcntl(this->fd,F_SETLKW,&fl);
            if (0 != result){
                throw std::to_string(result);
            }
        }
    };
};