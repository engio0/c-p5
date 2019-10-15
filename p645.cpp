#pragma once
#include <string>
#include <set>

class Message {
private:
    friend class Folder;
    std::string contents;
    std::set<Folder*> folders;
    void add_to_Folders(const Message&);
    void remove_from_Folders();
public:
    explicit Message(const std::string &str = ""):contents(str) {}
    Message(const Message&);
    Message& operator=(const Message&);
    ~Message();
    void save(Folder&);
    void remove(Folder&);
};

class Folder {
public:
    void addMsg(Message*);
    void remMsg(Message*);
};


void Message::save(Folder &f)
{
    folders.insert(&f);
    f.addMsg(this);
}

void Message::remove(Folder &f)
{
    folders.erase(&f);
    f.remMsg(this);
}
