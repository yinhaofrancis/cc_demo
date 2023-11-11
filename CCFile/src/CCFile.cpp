#include "CCFile.h"
#include <iostream>
cc::CCDB::CCDB(string path)
{
    this->fd = open(path.c_str(), O_RDWR | O_CREAT | O_TRUNC);
}

cc::CCDB::~CCDB()
{
    close(fd);
}

void cc::CCDB::addRecord(CCRecord &record)
{
    write(this->fd, &record.count, sizeof(record.count));
    write(this->fd, record.data, record.count);
}
void cc::CCDB::flush()
{
    fsync(this->fd);
}

cc::CCRecord *cc::CCDB::operator[](int index)
{
    lseek(this->fd, 0, SEEK_SET);
    int c = 0;
    if (index > 0)
    {
        for (size_t i = 0; i < index; i++)
        {
            read(this->fd, &c, sizeof(unsigned int));
            lseek(this->fd, c, SEEK_CUR);
        }
        read(this->fd, &c, sizeof(unsigned int));
        CCRecord *rc = new CCRecord();
        rc->count = c;
        char *content = (char *)malloc(c);
        read(this->fd, content, c);
        rc->data = content;
        return rc;
    }else{
        read(this->fd, &c, sizeof(unsigned int));
        CCRecord *rc = new CCRecord();
        rc->count = c;
        char *content = (char *)malloc(c);
        read(this->fd, content, c);
        rc->data = content;
        return rc;
    }
}