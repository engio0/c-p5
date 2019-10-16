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
    friend class Message;

public:
    explicit Folder(const std::string &str = "") : title(str) {}
    void addMsg(Message*);
    void remMsg(Message*);

private:
    std::string title;
    std::set<Message*> messages;
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

void Message::add_to_Folders(const Message& msg)
{
    for (auto f : msg.folders)
        f->addMsg(this);
}

Message::Message(const Message& msg):
    contents(msg.contents), folders(msg.folders)
{
    add_to_Folders(msg);
}

void Message::remove_from_Folders()
{
    for (auto f : folders)
        f->remMsg(this);
}

Message::~Message()
{
    remove_from_Folders();
}

Message& Message::operator=(const Message& rhs)
{
    remove_from_Folders();
    contents = rhs.contents;
    folders = rhs.folders;
    add_to_Folders(rhs);
    return *this;
}
