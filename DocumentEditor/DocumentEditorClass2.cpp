#include <bits/stdc++.h>
using namespace std;

class DocumentElement {
public:
  virtual string render() = 0;
};

// Document Elemenets
class TextElement : public DocumentElement {
private:
  string text;

public:
  TextElement(string text) { this->text = text; }
  string render() { return text; }
};

class ImageElement : public DocumentElement {
private:
  string path;

public:
  ImageElement(string path) { this->path = path; }
  string render() { return "[Image: " + path + "]\n"; }
};
class NewLineElement : public DocumentElement {
public:
  string render() { return "\n"; }
};
class TabSpaceElement : public DocumentElement {
public:
  string render() { return "\t"; }
};

// Document Class responsible for holding collections of element
class Document {
  vector<DocumentElement *> docs;
  public :
    void addElement(DocumentElement* doc){
        docs.push_back(doc);
    }
    string render(){
        string result="";
        for(auto&element: docs){
            result+= element->render();
        }
        return result;
    }


};

class Persistance{
    public:
        virtual void save(string renderDocs)=0;
};

class SaveToFile: public Persistance{
    public:
        virtual void save(string renderDocs){
             ofstream file("document.txt");
        if (file.is_open())
        {
            file << renderDocs;
            file.close();
            cout << "Document save to document.txt" << endl;
        }
        else
        {
            cout << "Error: Unable to open the file for save" << endl;
        }
        }
};
class SaveToDB: public Persistance{
public:
void save(string renderDocs){
    cout<<"Document Save to DB"<<endl;
}


};

class DocumentEditor{
    Document* document;
    Persistance* storage;
    string renderedDocument;
    public: 
    DocumentEditor(Document* document, Persistance* storage){
        this->document=document;
        this->storage = storage;
    }
    void addText(string text){
        document->addElement(new TextElement(text));
    }
    void addImage(string path){
        document->addElement(new ImageElement(path));
    }
    void addNewLine(){
        document->addElement(new NewLineElement());
    }
    void addTabSpace(){
        document->addElement(new TabSpaceElement());

    }
    string renderDocument(){

        if(renderedDocument.empty()) renderedDocument= document->render();
        return renderedDocument;
    }

    void save(){
        storage->save(renderDocument());
    }






};

int main() {

    Document* document = new Document();
    Persistance* storage = new SaveToFile();
    DocumentEditor * editor = new DocumentEditor( document, storage);
    editor->addText("Hello World!!");
    editor->addTabSpace();
    editor->addText("This is my first LLD Project.");
    editor->addNewLine();
    editor->addImage("profile.jpg");
    editor->addText("Time to take a coffie");
    editor->addNewLine();
    editor->save();
    cout<<editor->renderDocument();

    
    
    
    
    
    return 0; }