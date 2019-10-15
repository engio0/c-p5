#pragma once
#include <string>
#include <set>

class Message {
    friend class Folder;

public:
    explicit Message(const std::string &str = ""):contents(str) {}
    Message(const Message&);
    ~Message();
    Message& operator=(const Message&);
    void save(Folder&);
    void remove(Folder&);

private:
    std::string contents;
    std::set<Folder*> folders;

    void add_to_Folders(const Message&);
    void remove_from_Folders();
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
