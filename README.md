## Design Documentation
This program is a search engine for documents in JSON format. Only sample data is included here because the full dataset is too large to inlcude in the repository. The full dataset can be found at https://www.kaggle.com/jeet2016/us-financial-news-articles. To run the program as is, you need to include a data/archive folder, but you can leave it empty to run with sample data. The program indexes each file by reading the text, removing stopwords, and applying the Porter2 stemming algorithm, then builds data structures (AVL trees, hash tables) that map from words or entity names (people, organizations) to the documents where they appear. This allows for fast lookups of relevant documents when a user enters a query. When the user runs the program, they can parse an entire directory of .json files to build an index, save that index to a file so it can be reused later, load the index back in without re‐parsing all files, and query for specific search terms. The query engine supports normal words, excluded terms (prefixed by -), and special tags for organizations (ORG:) and persons (PERSON:). It then ranks the matching documents (using a simple tf–idf style metric) and prints the most relevant results, with an option to view each document’s text. 

## UML Diagram

```mermaid
classDiagram
    class SearchEngine {
        -IndexHandler ih
        -DocumentParser dp
        -UserInterface ui
        -QueryProcessor qp
        +input(int, char**)
    }
    
    class UserInterface {
        -chrono::duration<double> elapsedTrain
        -IndexHandler ih
        -QueryProcessor qp
        -DocumentParser dp
        +initialQuestion()
    }
    
    class DocumentParser {
        -IndexHandler ih
        -vector<string> titles
        +parseDocument(const string&)
        +printDocument(const string&)
        +setIndex(IndexHandler)
        +getIndex() IndexHandler
        +traverseSubdirectory(const string&)
        +printInfo(const string&)
        +getTitle(int) string
    }
    
    class IndexHandler {
        -DSAvlTree<string, string> words
        -Hash<string, string> people
        -Hash<string, string> orgs
        -vector<string> docs
        -map<string, int> wordCount
        +getWords(string) map<string, int>
        +getPeople(string) map<string, int>
        +getOrgs(string) map<string, int>
        +getWordCount(string) int
        +addWords(string, string)
        +addPeople(string, string)
        +addOrgs(string, string)
        +addDocument(string)
        +addWordCount(string, int)
        +getDocSize() int
        +createPersistence()
        +readPersistence()
        +returnSize() int
    }
    
    class QueryProcessor {
        -vector<string> storage
        -map<string, int> relevantDocuments
        -map<string, int> relDocs
        -map<string, int> sendTo
        -IndexHandler indexObject
        -vector<string> printVector
        +getPrintVector() vector<string>
        +getPrintVectorSize() int
        +getPrint(int) string
        +clearPrintVector()
        +parsingAnswer(string) map<string, int>
        +disectAnswer() map<string, int>
        +intersection(map<string, int>, map<string, int>) map<string, int>
        +complement(map<string, int>, map<string, int>) map<string, int>
        +setIndexHandler(IndexHandler)
        +Relevancy(map<string, int>) vector<string>
        +quickSort(map<string, int>&, int, int)
        +partition(map<string, int>, int, int) int
    }
    
    class DSAvlTree~Comparable, Value~ {
        -struct DSAvlNode
        -DSAvlNode* root
        -int size
        +DSAvlTree()
        +~DSAvlTree()
        +contains(const Comparable&) map<Value, int>
        +isEmpty() bool
        +makeEmpty()
        +insert(const Comparable&, const Value&)
        +insert(const Comparable&, const Value&, const int&)
        +remove(const Comparable&)
        +getSize() int
        +printTree(ostream&)
    }
    
    class Hash~Comparable, Value~ {
        -struct HashNode
        -int capacity
        -int size
        -HashNode** table
        +Hash()
        +~Hash()
        +getSize() int
        +clear()
        +createHash(int)
        +clone(const Hash&)
        +insert(Comparable, Value)
        +insert(Comparable, Value, int)
        +printHash(ostream&)
        -secondInsert(Comparable, map<Value, int>)
        -rehash()
        -hash(Comparable) int
    }
    
    SearchEngine --> IndexHandler
    SearchEngine --> DocumentParser
    SearchEngine --> UserInterface
    SearchEngine --> QueryProcessor
    
    UserInterface --> IndexHandler
    UserInterface --> QueryProcessor
    UserInterface --> DocumentParser
    
    DocumentParser --> IndexHandler
    QueryProcessor --> IndexHandler
    
    IndexHandler --> "1" DSAvlTree~string, string~ : words
    IndexHandler --> "1" Hash~string, string~ : people
    IndexHandler --> "1" Hash~string, string~ : orgs
```

## Collaborators
William Bjorndahl

## Sources
1) https://chatgpt.com/c/67ba5084-4014-8001-b3ec-381ec8a3fa7e?model=o1
2) https://claude.ai/chat/4e6cd8d2-a82f-4a20-b51b-c1d1fe3ed052
3) https://www.cursor.com/en
4) https://github.com/msappel4/cs5393-002_project4/blob/main/howtorun.txt
