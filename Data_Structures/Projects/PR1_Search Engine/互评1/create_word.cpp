#include<iostream>
#include<string>
#include<fstream>
#include<unordered_map>
#include<map>
#include<math.h>
#include<iomanip>
#include <algorithm>
#include<string.h>
#include<ctype.h>
using namespace std;

typedef struct _word_position{
    int position;
    struct _word_position *next;
}word_position;
// this structure is used for contain the position
typedef struct _title_node{
    word_position *p_head;
    word_position *p_tail;
	double cnt;
	string title;
	float persent;
	struct _title_node *next;
}title_node;
// to establish the inverted index, we need
// a title node, which include the title of 
// article that contain the word, frequency
// of the word in this article, pointer to the 
// next article that contain the word and the
// position of the word in the article
typedef struct _word_num{
	double num;
	string title;
}word_num;

typedef struct _word_cnt{
	double cnt;
	title_node *head;
	title_node *tail;
}*word_cnt;
// every word appears in all article, then we divide
// it into stop words and interesting words.
word_cnt create(){
	word_cnt block = (word_cnt)malloc(sizeof(struct _word_cnt));
	block->cnt = 0;

	block->head = block->tail = NULL;
	return block;
}
// create a new linked list, set all members 
//to their defult.
void append(word_cnt block,string name){
	block->cnt++;
	if(block->head){                                    //不是空的
		if(block->tail->title != name){
			title_node *temp = new title_node;
            temp->p_head = temp->p_tail = NULL;
			temp->title = name;
			temp->persent = -1;
			temp->cnt = 0;
			temp->next = NULL;
			block->tail->next = temp;
			block->tail = temp;
		}
	} else {                                              //是空的
		block->head = new title_node;
		block->head->title = name;
		block->head->persent = -1;
        block->head->p_head =block->head->p_tail = NULL;
		block->cnt = 0;
		block->head->next = NULL;
		block->tail = block->head;
	}
}

void p_append(word_cnt block,int position){

	if(block->tail->p_head){
        word_position *temp = new word_position;                                    //不是空的
        temp->position = position;
        temp->next = NULL;
        block->tail->p_tail->next = temp;
        block->tail->p_tail = temp;
		
	} else {                                              //是空的
        block->tail->p_head = new word_position;
		block->tail->p_head->position = position;
        block->tail->p_head->next = NULL;
        block->tail->p_tail = block->tail->p_head;
	}
}
// remove all 's or 'S, normally, only
// proper nouns have this form, they shouldn't
// be treated to be stop words.
string cut_tail(string word){
	if(word.length() >= 2){
		if((word[word.length()-2] == '\'') && (word[word.length()-1]=='S' || word[word.length()-1]=='s')){
			word = word.erase(word.length()-2,2);
		}
	}
	return word;
}
// this is designed for select proper nouns,
// according to the custom of English writing,
// we list cases to select specific nouns.
bool IS_name(string word){
	bool flag = true;
	if((word.length() < 5) || (!isalnum(word[word.length()-1]))){
		flag = false;
		return flag;
	}
	for(int i = 0; i < word.length();i++){
		if(islower(word[i])){
			flag = false;
			break;
		}
	}
	return flag;
}
// this function is designed for making all
// words have the same case
string lowerString(string s){
    transform(s.begin(), s.end(), s.begin(),[](unsigned char c){ return tolower(c); });
    return s;
}
// this is designed for delete punctuation marks
// but punctuation marks inside don't have to be 
// removed since when querying, they're reserved
string alphanumize(string a){
	while(!isalnum(a[0])){
        a = a.erase(0, 1);
		if(a == "")
			break;
	}
	if(a != ""){
		while(!isalnum(a[a.length()-1])){
        a = a.erase(a.length()-1, 1);
		if(a == "")
			break;
		}
	}
    return a;
}
// this function is designed for replacing
// all ' ' of the title with "_".
// Then we can have convenience in reading
// and writing titles in files.
string change_title(string title){
	for(int i = 0; i < title.length(); i++){
		if(title[i] == ' '){
			title[i] = '_';
		}
	}
	return title;
}

int main(){
	word_num  array[42];
	int count = 0;
    ifstream titles("titles.txt");
    ofstream fw("./result/interesting_word.txt");
    ofstream show("./result/show.txt");
    map<string, word_cnt> word_bag;
    map<string, word_cnt> name;
	// open the file that stores all
    // titles, then read article with
    // the title we have read.
    // word_count is for marking the position 
    // of word appears in each article.
    if(titles){
        string line;
		string current_title;
        string word;
        while(getline(titles,line)){
            if(line != ""){
				current_title ="./articles/" + line + ".txt";
                ifstream article(current_title);
				array[count].title = line;
				array[count].num = 0;
                if(article){
                    int word_count = 0;
					double current_sum = 0;
                    cout << line << " begin,sir" << endl;
                    while (article >> word){ // line中不包括每行的换行符
                        //for each word, the position get increment.
						word_count++;
			            word = cut_tail(word);
			            if(word != ""){
				            if(IS_name(word)){
					            if(name.find(word) == name.end()){      //如果word不在name中
					                name[word] = create();
				                } 
								// when empty create a new link list
				                append(name[word],line);
                                p_append(name[word],word_count);
								name[word]->tail->cnt++;
								array[count].num++;
								// for word, no matter it is name or the orther
                                // we append them into corresponding map
				            } else {
					            word = alphanumize(word);
					            word = lowerString(word);
					            if(word != ""){
					                if(word_bag.find(word) == word_bag.end()){      //如果word不在name中
					                    word_bag[word] = create();
				                    } 
									// when empty create a new link list
				                    append(word_bag[word],line);
                                    p_append(word_bag[word],word_count);
									word_bag[word]->tail->cnt++;
									array[count].num++;
									// for word, no matter it is name or the orther
                                	// we append them into corresponding map
                                }     
				            }
			            }           	
		            }
                    article.close();
                    cout << line << " finish,sir" << endl;
					count++;
                } else {
					// these are used for notice,don't mind.
                    cout << "#" << line << "#" << "can't found" << endl;
                }
            }
        }
    } else {
		// when the file can't open, printout error.
        cout << "No Such File With Titles,Sir" << endl;
    }

	string temp_line;

    map<string, word_cnt>::iterator pointer = word_bag.begin( );
	// then we construct the file used for inverted index and 
    // searching. word_bag is used for store all distinct words
    // now we use it to write into these files.
	while(pointer!=word_bag.end()){
		if((pointer->first != "") && (pointer->second->cnt > 2)){
			int ccount = 0;
			title_node *ptr = pointer->second->head;
			while(ptr){
				ccount++;
				ptr = ptr->next;
			}
			// we suppose the thresholding to be less than 7
            // seven times appears in different article. (here, 
            //if a word appear in a article, we take one time.)
			if(ccount < 7){
				show << pointer->first << ":\n";
                fw << pointer->first << " $";
				ptr = pointer->second->head;
				while(ptr){
					for(int i = 0;i < 42; i++){
						if(array[i].title == ptr->title){
							ptr->persent = ptr->cnt/array[i].num;
							break;
						}
					}
					temp_line = change_title(ptr->title);
					show << " " << ptr->title << " cnt:" << ptr->cnt;
                    fw << " " << temp_line << " " <<ptr->persent;
                    word_position *q = ptr->p_head;
                    while(q){
                        show << " " << q->position;
                        q = q->next;
                    }
					// this is used for beautiful looking, for
					// your reading the content.
                    show << "\n";
					ptr = ptr->next;
				}
				show << "\n";
                fw << " #\n";
			}
        }
		pointer++;
	}
	map<string, word_cnt>::iterator point = name.begin( );
	while(point!=name.end()){
		if((point->first != "") && (point->second->cnt > 2)){
			title_node *ptr = point->second->head;
			int ccount = 0;
			while(ptr){
				ccount++;
				ptr = ptr->next;
			}
			// we suppose the thresholding to be less than 7
            // seven times appears in different article. (here, 
            // if a word appear in a article, we take one time.)
			// actually, the name and word_bag is so similar
			// just copy the same code and edit some varible.
			if(ccount < 7){
				show << point->first << ":\n";
                fw << point->first << " $";
				ptr = point->second->head;
				while(ptr){
					for(int i = 0;i < 42; i++){
						if(array[i].title == ptr->title){
							ptr->persent = ptr->cnt/array[i].num;
							break;
						}
					}
					// this is used for beautiful looking, for
					// your reading the content.
					temp_line = change_title(ptr->title);
					show << " " << temp_line << " cnt:" <<ptr->cnt;
                    fw << " " << temp_line << " " <<ptr->persent;
					word_position *q = ptr->p_head;
                    while(q){
                        show << " " << q->position;
                        q = q->next;
                    }
                    show << "\n";
                    ptr = ptr->next;
				}
				show << "\n";
                fw << " #\n";
			}
		}
		point++;
	}
    show.close();
    fw.close();
	// a sign for the completion.
    cout << "All tasks have been finished,sir";
    return 0;
}
