## Design Documentation
This program uses a simple lexicon-based approach to classify tweets as positive (sentiment value 4) or negative (sentiment value 0). It is trained on the tweets in train.csv, then tested on the tweets in test.csv, and finally the results are compared to the known sentiment values in test_ground.csv. The DSString class is a custom string class that provides memory management (allocation and deallocation), string manipulation operations (concatenation and substring extraction, comparison operations, case conversion, and C-string compatibility. The TrainingTweet class contains tweet ID, date, query, username, text and sentiment value. The TestingTweet class contains the same information, but without the sentiment value. Several helper functions help clean and process the text, including tokenizer which splits the text into individual words. There is also a custom hash function which allows for the use of DSString in an unordered map. In the main program, a lexicon dictionary is built based on the training data, where each word has a sentiment score. The score is incremented if the word appears in a positive tweet and decremented if the word appears in a negative tweet. Then, the test tweets are classified based on the sum of the scores of the words they contain. If the score is non-negative, the tweet is classified as positive, and if the score is negative, the tweet is classified as negative. Each prediction is output to a csv file. Then, predictions are evaluated against the ground truth, and the accuracy, as well as a list of misclassified tweets are output to a text file. 

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

## Sources
1) https://chatgpt.com/c/67ba5084-4014-8001-b3ec-381ec8a3fa7e?model=o1
2) https://claude.ai/chat/4e6cd8d2-a82f-4a20-b51b-c1d1fe3ed052
3) https://www.cursor.com/en

I used ChatGPT to implement the DSString.cpp and sentiment.cpp programs, as well as debug build issues and learn about the time complexities. I used Cursor and Claude together to create a UML diagram in Mermaid. 


