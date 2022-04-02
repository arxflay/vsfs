#ifndef ASTRING_H
#define ASTRING_H

#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>

#define ASTRING_SUCCESS 1
#define ASTRING_ERROR -1

struct tagastring
{
    char *m_buffer;
    size_t m_len;
    size_t m_rlen;
};

typedef struct tagastring *astring;
typedef const struct tagastring *const_astring;

#define astrStatic(text) { .m_buffer = text, .m_len = sizeof(text) - 1, .m_rlen = sizeof(text) }

#define astr_cstr(astr) ((astr)->m_buffer)
#define astrLen(astr) ((astr)->m_len)
#define astrRLen(astr) ((astr)->m_rlen)

#define astrAlloc() ((astring)calloc(1, sizeof(struct tagastring)))
#define astrBufferAlloc(n) ((char*)calloc(n, sizeof(char)))
void astrDestroy(astring astr);

astring astrFromCstrn(const char *text, size_t n);
astring astrFromCstr(const char *text);
astring astrFromCstron(const char *text, size_t offset, size_t n);
astring astrFromCstro(const char *text, size_t offset);
astring astrSubstro(const_astring astr, size_t offset, size_t n);
astring astrSubstr(const_astring astr, size_t n);
astring astrCreateCopy(const_astring astr);

int astrSetFromCstr(astring astr, const char *cstr);

int astrConcat(astring astr, const_astring astr2);
int astrConcatCstr(astring astr, const char *cstr);

int astrInsert(astring astr, size_t pos, const_astring bstr);
int astrInsertCstr(astring astr, size_t pos, const char *cstr);

int astrTrunc(astring astr, size_t end);

int astrCmp(const_astring astr, const_astring astr2);

size_t astrFind(const_astring astr, const_astring astr2, size_t start, bool *found);
size_t astrFindFirst(const_astring astr, const_astring astr2, bool *found);
bool astrContains(const_astring astr, const_astring astr2);

size_t astrFindCstr(const_astring astr, const char *cstr, size_t start, bool *found);
size_t astrFindFirstCstr(const_astring astr, const char *cstr, bool *found);
bool astrContainsCstr(const_astring astr, const char *cstr);

bool astrContainsChar(const_astring astr, char c);

int astrTrimStart(astring astr);
int astrTrimEnd(astring astr);
int astrTrim(astring astr);

int astrToLowerASCII(astring astr);
int astrToUpperASCII(astring astr);

struct tagastringList
{
    astring *m_astrs;
    size_t m_count;
};

typedef struct tagastringList *astringList;

#define astrListAlloc() ((astringList)calloc(1, sizeof(struct tagastringList)))
#define astrListAstrsAlloc(list) ((astring*)calloc(astrListCount(list), sizeof(astring)))
void astrListDestroy(astringList list);

#define astrListCount(list) ((list)->m_count)
#define astrListGet(list, i) ((list)->m_astrs[i])

astringList astrSplit(const_astring astr, const char *delimiters);

#endif