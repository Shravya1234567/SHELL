typedef struct pData *data;
struct pData
{
    int pid;
    int sno;
    char* pName;
    char *procName;
    data next;
};

struct pData *root, *tail ;