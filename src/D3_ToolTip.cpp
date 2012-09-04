#include "D3_ToolTip.h"
#include <stdio.h>

const char *D3_ToolTip::type_string[ENUM_END] = {
    "D3_NAME", "D3_TYPE", "D3_SLOT", "D3_RATING", "D3_RATING_LABEL", "D3_SPECIAL_STATS",
    "D3_STATS", "D3_REQUIRED_LEVEL", "D3_COST", "D3_DURABILITY", "D3_REQUIRED_CLASS",
    "D3_SOCKET_0", "D3_SOCKET_1", "D3_SOCKET_2", "D3_SOCKET_COST", "D3_ITEM_LEVEL",
    "D3_FLAVOR", "D3_SET_ITEM", "D3_ENHANCEMENT", "D3_INSTRUCTION"
};

const unsigned char D3_ToolTip::hash[20][8] = {
    {0x4A, 0x29, 0x53, 0x8B, 0x28, 0x38, 0xE9, 0x74}, //D3_NAME             Root.TopLayer.item 2.stack.top_wrapper.stack.name
    {0xBC, 0x10, 0x71, 0x65, 0x71, 0xC7, 0x88, 0x2D}, //D3_TYPE             Root.TopLayer.item 2.stack.frame body.stack.main.stack.wrapper.col1.type
    {0x8F, 0xC5, 0xBD, 0x7C, 0x42, 0xFE, 0x7B, 0xA6}, //D3_SLOT             Root.TopLayer.item 2.stack.frame body.stack.main.stack.wrapper.col2.slot
    {0xE7, 0x8F, 0x7B, 0xD0, 0x71, 0x49, 0xB4, 0x77}, //D3_RATING           Root.TopLayer.item 2.stack.frame body.stack.main.stack.wrapper.col1.stack.rating
    {0x16, 0xE7, 0xFA, 0x91, 0xB5, 0xC3, 0xD0, 0xEF}, //D3_RATING_LABEL     Root.TopLayer.item 2.stack.frame body.stack.main.stack.wrapper.col1.stack.rating_label
    {0xB7, 0xAB, 0xAD, 0xB5, 0x84, 0xD3, 0xFB, 0xFC}, //D3_SPECIAL_STATS    Root.TopLayer.item 2.stack.frame body.stack.main.stack.special_stats
    {0xE0, 0xDE, 0x5B, 0x80, 0xDB, 0x4D, 0x93, 0x1F}, //D3_STATS            Root.TopLayer.item 2.stack.frame body.stack.stats
    {0x3B, 0x90, 0x94, 0x12, 0x32, 0x86, 0x03, 0xED}, //D3_REQUIRED_LEVEL   Root.TopLayer.item 2.stack.frame body.stack.wrapper.reqs
    {0xD2, 0xDC, 0xFB, 0x17, 0xF5, 0xF9, 0x05, 0xC4}, //D3_COST             Root.TopLayer.item 2.stack.frame_cost.cost
    {0x8C, 0x3E, 0x4F, 0xB1, 0xF3, 0xC7, 0xD3, 0xAB}, //D3_DURABILITY       Root.TopLayer.item 2.stack.frame_cost.durability
    {0x8F, 0x0B, 0x3C, 0x67, 0x8E, 0x3B, 0xDF, 0x4E}, //D3_REQUIRED_CLASS   Root.TopLayer.item 2.stack.frame body.stack.main.stack.wrapper.col2.class_reqs
    {0x61, 0xC5, 0xE9, 0xF9, 0x0D, 0x6A, 0xCD, 0x5E}, //D3_SOCKET_0         Root.TopLayer.item 2.stack.frame body.stack.socket 0.text
    {0x20, 0x82, 0x50, 0x8A, 0xF5, 0x26, 0x4C, 0xC6}, //D3_SOCKET_1         Root.TopLayer.item 2.stack.frame body.stack.socket 1.text
    {0x9F, 0xC2, 0xA8, 0x09, 0x10, 0x77, 0x7B, 0x89}, //D3_SOCKET_2         Root.TopLayer.item 2.stack.frame body.stack.socket 2.text
    {0xD6, 0x62, 0x04, 0xA6, 0xBA, 0xD3, 0x84, 0x1F}, //D3_SOCKET_COST      Root.TopLayer.item 2.stack.frame_cost.socket_cost
    {0x81, 0x1C, 0x33, 0x40, 0xC3, 0x30, 0x58, 0x90}, //D3_ITEM_LEVEL       Root.TopLayer.item 2.stack.frame body.stack.wrapper.itemLevel
    {0xB5, 0x10, 0x06, 0x11, 0x24, 0x70, 0xCB, 0x25}, //D3_FLAVOR           Root.TopLayer.item 2.stack.frame body.stack.flavor
    {0x87, 0x0F, 0x11, 0x37, 0x93, 0x9F, 0x39, 0x30}, //D3_SET_ITEM         Root.TopLayer.item 2.stack.frame body.stack.set_item
    {0xF5, 0x1C, 0x98, 0xC2, 0x3F, 0xFD, 0x22, 0xDB}, //D3_ENHANCEMENT      Root.TopLayer.item 2.stack.frame body.stack.enhancement
    {0x0D, 0x53, 0x98, 0xDF, 0x78, 0x46, 0xCE, 0xF7}  //D3_INSTRUCTION      Root.TopLayer.item 2.stack.frame_instruction.stack.text
}; // begin with

const unsigned char D3_ToolTip::parent_hash[20][8] = {
    {0xC5, 0xC0, 0xC5, 0x06, 0xD7, 0x8B, 0xF9, 0x58}, //D3_NAME             Root.TopLayer.item 2.stack.top_wrapper.stack
    {0xF2, 0x33, 0xF7, 0xCA, 0x08, 0xF5, 0xB3, 0x9C}, //D3_TYPE             Root.TopLayer.item 2.stack.frame body.stack.main.stack.wrapper.col1
    {0x3F, 0x32, 0xF7, 0xCA, 0x08, 0xF4, 0xB3, 0x9C}, //D3_SLOT             Root.TopLayer.item 2.stack.frame body.stack.main.stack.wrapper.col2
    {0xDC, 0xDF, 0xD2, 0x7B, 0x83, 0xCF, 0x99, 0xB3}, //D3_RATING           Root.TopLayer.item 2.stack.frame body.stack.main.stack.wrapper.col1.stack
    {0xDC, 0xDF, 0xD2, 0x7B, 0x83, 0xCF, 0x99, 0xB3}, //D3_RATING_LABEL     Root.TopLayer.item 2.stack.frame body.stack.main.stack.wrapper.col1.stack
    {0x7E, 0x4E, 0xD4, 0x05, 0xEE, 0x32, 0x5C, 0x37}, //D3_SPECIAL_STATS    Root.TopLayer.item 2.stack.frame body.stack.main.stack
    {0xC5, 0x34, 0x83, 0xCF, 0x13, 0x78, 0xCC, 0x6F}, //D3_STATS            Root.TopLayer.item 2.stack.frame body.stack
    {0x28, 0xE3, 0xDD, 0xFA, 0x7A, 0xB5, 0x7A, 0x4F}, //D3_REQUIRED_LEVEL   Root.TopLayer.item 2.stack.frame body.stack.wrapper
    {0x67, 0xE7, 0x0B, 0x68, 0xE9, 0x4C, 0xB4, 0x33}, //D3_COST             Root.TopLayer.item 2.stack.frame_cost
    {0x67, 0xE7, 0x0B, 0x68, 0xE9, 0x4C, 0xB4, 0x33}, //D3_DURABILITY       Root.TopLayer.item 2.stack.frame_cost
    {0x3F, 0x32, 0xF7, 0xCA, 0x08, 0xF4, 0xB3, 0x9C}, //D3_REQUIRED_CLASS   Root.TopLayer.item 2.stack.frame body.stack.main.stack.wrapper.col2
    {0x40, 0x2B, 0xCC, 0x5E, 0x36, 0x97, 0x56, 0xBE}, //D3_SOCKET_0         Root.TopLayer.item 2.stack.frame body.stack.socket 0
    {0xF3, 0x2C, 0xCC, 0x5E, 0x36, 0x98, 0x56, 0xBE}, //D3_SOCKET_1         Root.TopLayer.item 2.stack.frame body.stack.socket 1
    {0xA6, 0x2E, 0xCC, 0x5E, 0x36, 0x99, 0x56, 0xBE}, //D3_SOCKET_2         Root.TopLayer.item 2.stack.frame body.stack.socket 2
    {0x67, 0xE7, 0x0B, 0x68, 0xE9, 0x4C, 0xB4, 0x33}, //D3_SOCKET_COST      Root.TopLayer.item 2.stack.frame_cost
    {0x28, 0xE3, 0xDD, 0xFA, 0x7A, 0xB5, 0x7A, 0x4F}, //D3_ITEM_LEVEL       Root.TopLayer.item 2.stack.frame body.stack.wrapper
    {0xC5, 0x34, 0x83, 0xCF, 0x13, 0x78, 0xCC, 0x6F}, //D3_FLAVOR           Root.TopLayer.item 2.stack.frame body.stack
    {0xC5, 0x34, 0x83, 0xCF, 0x13, 0x78, 0xCC, 0x6F}, //D3_SET_ITEM         Root.TopLayer.item 2.stack.frame body.stack
    {0xC5, 0x34, 0x83, 0xCF, 0x13, 0x78, 0xCC, 0x6F}, //D3_ENHANCEMENT      Root.TopLayer.item 2.stack.frame body.stack
    {0xF4, 0xCA, 0x04, 0x11, 0xFD, 0xBA, 0x44, 0xAC}  //D3_INSTRUCTION      Root.TopLayer.item 2.stack.frame_instruction.stack
}; // at {0x210}

const unsigned char D3_ToolTip::unik0[4] = {
    0x0D, 0xF0, 0x0D, 0x60
};// at {0x458, 0x490, 0xAD8, 0xB10, 0xB60, 0xBB0}

const unsigned char D3_ToolTip::unik1[24] = {
    0x00, 0x00, 0x00, 0xFF, 0x7F, 0x7F, 0x7F, 0xFF,
    0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};// at {0xBEC}

D3_ToolTip::D3_ToolTip()
{
    this->ptr = (int *)malloc(ENUM_END*sizeof(int));
    this->ptr_count = (char *)malloc(ENUM_END*sizeof(char));
    this->resetPtr();
    this->model = new QStandardItemModel();

    QStringList headerNames;
    headerNames.append("custom");
    for (char e = 0; e < ENUM_END; e++)
    {
        headerNames.append(type_string[e]);
    }
    model->setHorizontalHeaderLabels(headerNames);
}

void D3_ToolTip::resetPtr()
{
    for(unsigned char i = 0; i < ENUM_END; i++)
    {
        this->ptr[i] = NULL;
        this->ptr_count[i] = 0;
    }
}

char *D3_ToolTip::init()
{
    long pid = this->getProcID();
    if (pid == 0) return "'Diablo III' PID not found. Start the game and retry.";
    this->hndl = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, pid);
    if (this->hndl == INVALID_HANDLE_VALUE) return "Unable to open D3 process. Do you have enough privilege ?";
    return NULL;
}

void D3_ToolTip::run()
{
    this->resetPtr();
    size_t s, reg;
    char *buffer, *prevbuff = NULL;
    unsigned int offset, prevlen = 0, bound;
    MEMORY_BASIC_INFORMATION mbi;
    SYSTEM_INFO si;
    GetSystemInfo(&si);
    unsigned int min = 0x06000000; //(unsigned int)si.lpMinimumApplicationAddress; //0x06000000
    unsigned int max = 0x30000000; //(unsigned int)si.lpMaximumApplicationAddress; //0x30000000



    for(unsigned int i = min; i < max;)
    {
        emit progress(i);
        s = VirtualQueryEx(this->hndl, (void *)i, &mbi, sizeof(MEMORY_BASIC_INFORMATION));
        if(s != 0 && (mbi.Type == MEM_PRIVATE) && (mbi.State == MEM_COMMIT) && (mbi.Protect == PAGE_READWRITE))
        {
            reg = (unsigned int)mbi.RegionSize;
            buffer = (char *)malloc(prevlen + reg);
            if (prevlen > 0) memcpy(buffer, prevbuff, prevlen);

            if (buffer == NULL) exit(1);
            if (! ReadProcessMemory(this->hndl, (LPVOID)mbi.BaseAddress, buffer + prevlen, reg, NULL))
            {
                i += (unsigned int)mbi.RegionSize;
                continue;
            }
            for(offset = 0; offset < prevlen + reg - 0xD00; offset+=4)
            {
                for(unsigned char e = 0; e < ENUM_END; e++)
                {
                    if((memcmp(this->hash[e], (buffer + offset), 8) == 0) && (memcmp(this->parent_hash[e], (buffer + offset + 0x208), 8) == 0) && this->chkUnik(buffer, offset))
                    {
                        this->ptr[e] = (int)mbi.BaseAddress - prevlen + offset + 0xA98;
                        this->ptr_count[e]++;
                        break;
                    }
                }
            }
            if (prevbuff != NULL) free(prevbuff);
            bound = prevlen + reg;
            prevlen = 8;
            for(;offset < bound - 4; offset+=4) //segmentation aware
            {
               for(unsigned char e = 0; e < ENUM_END; e++)
               {
                   if((memcmp(this->hash[e], (buffer + offset), 8) == 0))
                   {
                       prevlen = bound - offset;
                       break;
                   }
               }
            }
            prevbuff = (char *)malloc(prevlen);
            memcpy(prevbuff, buffer + bound - prevlen, prevlen);
            free(buffer);
        }
        i += (unsigned int)mbi.RegionSize;
    }
}

bool D3_ToolTip::chkUnik(char *buffer, int offset)
{
    int addr[] = {0x458, 0x490, 0xAD8, 0xB10, 0xB60, 0xBB0};
    for (int i = 0; i < 6; i++)
    {
        if (memcmp(unik0, ((char *)buffer + offset + addr[i]), 4) != 0) return false;
    }
    if (memcmp(unik1, ((char *)buffer + offset + 0xBEC), 24) != 0) return false;
    return true;
}

long D3_ToolTip::getProcID()
{
    HANDLE snapshot = (0);
    snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (snapshot == INVALID_HANDLE_VALUE) return 0;
    PROCESSENTRY32 pe32;
    pe32.dwSize = sizeof(PROCESSENTRY32);
    if (!Process32First(snapshot, &pe32))
    {
        CloseHandle(snapshot);
        return 0;
    }
    long pid = 0;
    do
    {
        if (wcscmp(pe32.szExeFile, L"Diablo III.exe")==0)
        {
            pid = pe32.th32ProcessID;
            break;
        }
    } while (Process32Next(snapshot, &pe32));
    CloseHandle(snapshot);
    return pid;
}

bool D3_ToolTip::makeItem(QString custom)
{
    unsigned int target = 0, show = 0;
    char *sluged;
    char *str = (char *)malloc(2048 * sizeof(char));
    QStandardItem *si;
    QList<QStandardItem *> l;
    if (str == NULL) return false;

    l.append(new QStandardItem(custom));
    for(unsigned char e = 0; e < ENUM_END; e++)
    {
        si = new QStandardItem();
        if (this->ptr[e] == NULL) return false;
        if (ptr_count[e] != 1) return false;
        //if (! ReadProcessMemory(this->hndl, (LPVOID) (this->ptr[e] - 0x5DC), &show, sizeof(int), NULL))
        if (! ReadProcessMemory(this->hndl, (LPVOID) (this->ptr[e] - 0xAA0), &show, sizeof(int), NULL))
        {
            si->setText("");
            si->setData("{Qt:DEBUG:RPM1Failed}", Qt::UserRole);
            l.append(si);
            continue;
        }
        if (! ReadProcessMemory(this->hndl, (LPVOID) this->ptr[e], &target, sizeof(int), NULL))
        {
            si->setText("");
            si->setData("{Qt:DEBUG:RPM2Failed}", Qt::UserRole);
            l.append(si);
            continue;
        }
        if (target == 0)
        {
            si->setText("");
            si->setData("{Qt:DEBUG:notfound}", Qt::UserRole);
            l.append(si);
            continue;
        }
        if (! ReadProcessMemory(this->hndl, (LPVOID) target, str, 2047, NULL))
        {
            si->setText("");
            si->setData("{Qt:DEBUG:RPM3Failed}", Qt::UserRole);
            l.append(si);
            continue;
        }
        str[2047] = '\0';

        sluged = slug(str);
        si->setText(QString::fromUtf8(sluged));
        if (show == 0) si->setData(QString("{Qt:DEBUG:hidden}") + QString::fromUtf8(str), Qt::UserRole);
        else si->setData(QString::fromUtf8(str), Qt::UserRole);
        l.append(si);
        free(sluged);
    }
    model->appendRow(l);
    free(str);
    return true;
}

char *D3_ToolTip::slug(char *str)
{
    if (str == NULL) return NULL;
    int pos = -1, len = strlen(str);
    char state = 0, *res = (char*)malloc(1+len*sizeof(char));
    res[0] = '\0';

    for(int i = 0; i < len; i++)
    {
        switch(state)
        {
        case 0: //text
            if(str[i] == '{') state = 1;
            else
            {
                res[++pos] = str[i];
            }
            break;
        case 1: //style
            if(str[i] == '}') state = 0;
            break;
        default:
            break;
        }
    }
    res[++pos] = '\0';
    return res;
}


