#include <bits/stdc++.h>

class Note
{
private:
  int id;
  std::string title, content, createdAt, updatedAt;

public:
  Note() {}
  Note(int id, std::string title, std::string content, std::string createdAt)
  {
    this->title = title;
    this->content = content;
    this->createdAt = createdAt;
    this->updatedAt = createdAt;
    this->id = id;
  }

  void setTitle(std::string title) { this->title = title; }

  void setContent(std::string content) { this->content = content; }
  void setUpdateAt(std::string time) { this->updatedAt = time; }

  int getId()
  {
    return this->id;
  }
  std::string getContent()
  {
    return this->content;
  }

  std::string getTitle() { return this->title; }

  std::string getCreatedAt()
  {
    return this->createdAt;
  }
  std::string getUpdatedAt()
  {
    return this->updatedAt;
  }
};

class Time
{
public:
  static std::string getCurrentTime()
  {
    auto t = time(nullptr);
    auto tm = *localtime(&t);
    std::stringstream ss;
    ss << std::put_time(&tm, "%d-%M-%Y");
    return ss.str();
  }
};

// Abstract Class
class Memory
{
public:
virtual ~ Memory()=default;
  virtual void save(std::string title, std::string content) = 0;
  virtual void update(int id, std::string title, std::string content) = 0;
  virtual std::vector<Note *> getAll() = 0;
  virtual Note *getById(int id) = 0;
  virtual std::vector<Note *> getByTitle(std::string title) = 0;
  virtual void remove(int id) = 0;
};

class INoteMomory : public Memory
{
private:
  std::map<int, std::unique_ptr<Note>> notes;
  int uniqueId;

public:
  INoteMomory()
  {
    uniqueId = 0;
  }
  void save(std::string title, std::string content)
  {

    auto note = std::make_unique<Note>(uniqueId, title, content, Time::getCurrentTime());
    notes[uniqueId] = std::move(note);
    uniqueId++;
  }
  void update(int id, std::string title, std::string content)
  {
    if (notes.find(id) == notes.end())
    {
      return;
    }
    notes[id]->setTitle(title);
    notes[id]->setContent(content);
    notes[id]->setUpdateAt(Time::getCurrentTime());
  }
  void remove(int id)
  {
    if (notes.find(id) == notes.end())
    {
      return;
    }
    notes.erase(id);
  }
  std::vector<Note *> getAll()
  {
    std::vector<Note *> res;
    for (auto &[i, note] : notes)
    {
      res.push_back(note.get());
    }
    return res;
  }
  Note *getById(int id)
  {
    if (notes.find(id) == notes.end())
    {
      return nullptr;
    }
    return notes[id].get();
  }
  std::vector<Note *> getByTitle(std::string title)
  {
    std::vector<Note *> res;
    for (auto &[i, note] : notes)
    {
      if (note->getTitle() == title)
        res.push_back(note.get());
    }
    return res;
  }
};

class NoteService
{
  Memory *memory;

public:
  NoteService(Memory *memory)
  {
    this->memory = memory;
  }

  void save(std::string title, std::string content)
  {
    memory->save(title, content);
  }
  void update(int id, std::string title, std::string content)
  {
    memory->update(id, title, content);
  }
  void remove(int id)
  {
    memory->remove(id);
  }
  Note *getById(int id)
  {
    return memory->getById(id);
  }
  std::vector<Note *> getAll()
  {
    return memory->getAll();
  }
  std::vector<Note *> getByTitle(std::string title)
  {
    return memory->getByTitle(title);
  }
};

int main()
{

  INoteMomory memory;
  NoteService nService(&memory);
  nService.save("Najir", "Najir is not happy.");
  std::vector<Note *> tem = nService.getAll();
  for (auto &i : tem)
  {
    std::cout << i->getTitle() << " " << i->getContent() << " " << i->getCreatedAt() << std::endl;
  }

  return 0;
}