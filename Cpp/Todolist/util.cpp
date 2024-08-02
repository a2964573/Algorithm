#include "main.h"

int showTitle() noexcept
{
    // system("cls");
    std::cout << TODOLIST << std::endl;
std::cout << "00" << std::endl;
    return 0;
}

int showList(GLOBAL& _global)
{
    LIST* lists = new LIST[_global.list_lastId];
    memset(lists, 0x00, sizeof(LIST) * _global.list_lastId);

    int rtn = getListAll(_global, lists);
    if(rtn < 0) {
        std::cout << "Error: Get List All Failed" << std::endl << std::endl;
    }
    else
    if(rtn == 0) {
        std::cout << "표시할 리스트가 없습니다." << std::endl << std::endl;
    }
    else {
        std::cout << std::setw(10) << std::left << "ID"    << '|';
        std::cout << std::setw(1 ) << std::left << "S"     << '|';
        std::cout <<                  std::left << "Title" << std::endl;

        int pos;
        for(pos = 0; pos < rtn; pos++) {
            if(lists[pos].index <= 0) {
                continue;
            }

            std::cout << std::setw(10                          )  << std::left << (lists[pos].id                ) << '|';
            std::cout << std::setw(1                           )  << std::left << (lists[pos].status ? 'V' : 'O') << '|';
            std::cout << std::setw(std::strlen(lists[pos].title)) << std::left << (lists[pos].title             ) << std::endl << std::endl;
        }
    }
    delete[] lists;

    return rtn;
}

int getListAll(GLOBAL& _global, LIST* output)
{
    int  pos    = 0;
    int  tpos   = 0;
    int  start  = 0;
    int  end    = 0;
    char target = ',';
    LIST list   = {0,};
    TAG  tag    = {0,};
    std::ifstream inTodoFile(_global.filename);
    std::string todoLine;
    std::string result;
    while(std::getline(inTodoFile, todoLine)) {
        start = 0;
        end   = 0;
        memset(&list, 0x00, sizeof(list));
        memset(&tag , 0x00, sizeof(tag ));

        end = findString(todoLine, end    , target, result);
        if(end == 0) {
            continue;
        }
        list.id        = std::stoi(result        );

        end = findString(todoLine, end + 1, target, result);
        if(end == 0) {
            continue;
        }
        list.index     = std::stoi(result        );

        end = findString(todoLine, end + 1, target, result);
        if(end == 0) {
            continue;
        }
        list.status    = std::stoi(result        );

        end = findString(todoLine, end + 1, target, result);
        if(end == 0) {
            continue;
        }
        std::strcpy(list.in_date , result.c_str());

        end = findString(todoLine, end + 1, target, result);
        if(end == 0) {
            continue;
        }
        std::strcpy(list.in_time , result.c_str());

        end = findString(todoLine, end + 1, target, result);
        if(end == 0) {
            continue;
        }
        std::strcpy(list.title   , result.c_str());

        end = findString(todoLine, end + 1, target, result);
        if(end == 0) {
            std::strcpy(list.desc, result.c_str());
        }

        end = findString(todoLine, end + 1, target, result);
        if(end == 0) {
            continue;
        }
        std::strcpy(list.clr_date, result.c_str());

        end = findString(todoLine, end + 1, target, result);
        if(end == 0) {
            continue;
        }
        std::strcpy(list.clr_time, result.c_str());

        end = findString(todoLine, end + 1, target, result);
        if(end == 0) {
            continue;
        }
        list.tag_cnt   = std::stoi(result        );

        for(tpos = 0; tpos < list.tag_cnt; tpos++) {
            end = findString(todoLine, end + 1, target, result);
            if(end == 0) {
                continue;
            }
            tag.id    = std::stoi(result         );

            end = findString(todoLine, end + 1, target, result);
            if(end == 0) {
                continue;
            }
            std::strcpy(tag.name, result.c_str() );

            list.tags[tpos] = tag;
        }

        output[pos] = list;
        pos++;
    }
    inTodoFile.close();

    return pos;
}

int parseCSVLine(const LIST& list, char* output)
{
    int len = sprintf(output, "%d,%d,%d,%s,%s,%s,%s,%s,%s,%d"
                , list.id      , list.index   , list.status
                , list.in_date , list.in_time , list.title
                , list.desc    , list.clr_date, list.clr_time
                , list.tag_cnt);
    int pos = 0;
    while(true) {
        if(pos >= list.tag_cnt) {
            break;
        }

        len += sprintf(&output[len], ",%d,%s", list.tags[pos].id, list.tags[pos].name);
        pos++;
    }

    return len;
}

int printList(const LIST& list) noexcept
{
    std::cout << "ID         : " << list.id       << std::endl;
    std::cout << "Index      : " << list.index    << std::endl;
    std::cout << "Status     : " << list.status   << std::endl;
    std::cout << "Input Date : " << list.in_date  << std::endl;
    std::cout << "Input Time : " << list.in_time  << std::endl;
    std::cout << "Title      : " << list.title    << std::endl;
    std::cout << "Description: " << list.desc     << std::endl;
    std::cout << "Clear Date : " << list.clr_date << std::endl;
    std::cout << "Clear Time : " << list.clr_time << std::endl;
    std::cout << "Tag Count  : " << list.tag_cnt  << std::endl;
    int pos;
    for(pos = 0; pos < list.tag_cnt; pos++) {
        std::cout << "Tag        : #" << list.tags[pos].id << " " << list.tags[pos].name << std::endl;
    }
    std::cout << std::endl;

    return 0;
}

int onClickKeyEvent(const char* message) noexcept
{
    if(message != NULL) {
        std::cout << message << std::endl;
    }

    int key = static_cast<int>(getch());
    if(65 <= key && key <= 90) {
        key += 32;
    }

    return key;
}

int confirm(const char* message) noexcept
{
    int rtn;
    int key;
    while(true) {
        key = onClickKeyEvent(message);
        if(key == ANSWER_YES) {
            rtn = 1;
            break;
        }
        else
        if(key == ANSWER_NO) {
            rtn = 0;
            break;
        }
        else {
            std::cout << "Invalid input. Please try again." << std::endl << std::endl;
        }
    }

    return rtn;
}

int inputValueUInt(const char* message, uint& output) noexcept
{
    if(message != NULL) {
        std::cout << message << std::endl;
    }
    std::string input;
    std::getline(std::cin, input);

    try {
        int rtn = std::stoi(input.substr(0, input.find(' ')));
        output = static_cast<uint>(rtn);
    } catch(const std::invalid_argument& e) {
        std::cout << "ID를 입력해주세요" << std::endl << std::endl;
    }

    return output;
}

int inputValueWord(const char* message, int max_size, char* output) noexcept
{
    if(message != NULL) {
        std::cout << message << std::endl;
    }

    int size = 0;
    std::string input;
    while(true) {
        std::getline(std::cin, input);
        input = input.substr(0, input.find(' '));
        size = input.size();
        if(size >= max_size) {
            std::cout << "Input value too long: " << input << "(" << size << "byte)" << std::endl;
            std::cout << "Please try again." << std::endl << std::endl << std::endl;
            continue;
        }
        break;
    }
    strcpy(output, input.c_str());

    return size;
}

int inputValueString(const char* message, int max_size, char* output) noexcept
{
    if(message != NULL) {
        std::cout << message << std::endl;
    }

    int size = 0;
    std::string input;
    while(true) {
        std::getline(std::cin, input);
        size = input.size();
        if(size >= max_size) {
            std::cout << "Input value too long: " << input << "(" << size << "byte)" << std::endl;
            std::cout << "Please try again." << std::endl << std::endl;
            continue;
        }
        break;
    }
    strcpy(output, input.c_str());

    return size;
}

int getNowDate(char* format, int size, char* output) noexcept
{
    char dformat[32] = {0,};
    if(format == NULL) {
        std::strcpy(dformat, "%Y%m%d");
    } else {
        std::strcpy(dformat, format);
    }

    auto now = std::chrono::system_clock::now();
    std::time_t now_time = std::chrono::system_clock::to_time_t(now);
    std::tm* now_tm = std::localtime(&now_time);

    std::strftime(output, size, dformat, now_tm);
    return 0;
}

int getNowTime(char* format, int size, char* output) noexcept
{
    char dformat[32] = {0,};
    if(format == NULL) {
        std::strcpy(dformat, "%H%M%S");
    } else {
        std::strcpy(dformat, format);
    }

    auto now = std::chrono::system_clock::now();
    std::time_t now_time = std::chrono::system_clock::to_time_t(now);
    std::tm* now_tm = std::localtime(&now_time);

    std::strftime(output, size, dformat, now_tm);
    return 0;
}

int showAllTags() noexcept
{
    std::ifstream inTagConf(TAG_FILE_NAME);
    if(!inTagConf.good()) {
        std::cerr << "Error: Failed to open '" << TAG_FILE_NAME << "'" << std::endl << std::endl;
        return -1;
    }

    TAG tag = {0,};
    std::string tagLine;
    while(std::getline(inTagConf, tagLine)) {
        tag.id = std::stoi(tagLine.substr(0, tagLine.find(',')));
        std::strcpy(tag.name, tagLine.substr(tagLine.find(',') + 1).c_str());
        std::cout << '#' << tag.id << ' ' << tag.name << std::endl;
    }
    inTagConf.close();

    return 0;
}

int findTag(int tag_id, TAG& output)
{
    std::ifstream inTagConf(TAG_FILE_NAME);
    if(!inTagConf.good()) {
        std::cerr << "Error: Failed to open '" << TAG_FILE_NAME << "'" << std::endl << std::endl;
        return -1;
    }

    std::string tagLine;
    while(std::getline(inTagConf, tagLine)) {
        output.id = std::stoi(tagLine.substr(0, tagLine.find(',')));
        if(output.id == tag_id) {
            std::strcpy(output.name, tagLine.substr(tagLine.find(',') + 1).c_str());
            break;
        }
    }
    inTagConf.close();

    if(output.name[0] == 0x00) {
        output.id = 0x00;
    }

    return output.id == 0x00 ? 0 : 1;
}

int findString(std::string str, int start, char target, std::string& output)
{
    int end = str.find(target, start);
    if(end == std::string::npos) {
        end = str.length();
    }

    output = str.substr(start, end - start);

    return end;
}