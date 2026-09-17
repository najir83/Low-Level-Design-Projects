#include <bits/stdc++.h>
using namespace std;
class DocumentEditor
{
private:
    vector<string> docs;
    string renderDocs;

public:
    void addText(string s)
    {
        docs.push_back(s);
    }

    // Path will be given .jpg or .png format
    void addImage(string path)
    {
        docs.push_back(path);
    }
    string renderedDocument()
    {
        if (renderDocs.empty())
        {
            string result;
            for (auto &i : docs)
            {
                if (i.size() >= 4 and (i.substr(i.size() - 4, 4) == ".jpg" or i.substr(i.size() - 4, 4) == ".png"))
                {
                    result += "[Image : " + i + "]\n";
                }
                else
                {
                    result += i + "\n";
                }
            }
            renderDocs = result;
        }
        return renderDocs;
    }

    void saveToFile()
    {
        ofstream file("document.txt");
        if (file.is_open())
        {
            file << renderedDocument();
            file.close();
            cout << "Document save to document.txt" << endl;
        }
        else
        {
            cout << "Error: Unable to open the file for save" << endl;
        }
    }
};

int main()
{
    DocumentEditor editor;
    editor.addText("My name is Sk Najir");
    editor.addImage("profileImage.jpg");
    editor.addText("This is a docs editor");
    editor.saveToFile();



    return 0;
}