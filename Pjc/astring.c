#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

#include "debug.h"
#include "astring.h"

void astrDestroy(astring astr)
{
    if (astr)
        free(astr->m_buffer);

    free(astr);
}

astring astrFromCstrn(const char *text, size_t n)
{
    if (text == NULL)
        return NULL;

    astring astr = astrAlloc();
    check_mem(astr);

    size_t length = strlen(text);

    astr->m_len = (n > length) ? length : n;
    astr->m_rlen = astr->m_len + 1;
    astr->m_buffer = (char*)calloc(astr->m_rlen, sizeof(char));
    check_mem(astr->m_buffer);

    memcpy(astr->m_buffer, text, astr->m_len);

    return astr;

error:
    if (astr)
        free(astr);

    return NULL;
}

astring astrFromCstr(const char *text)
{
    return astrFromCstrn(text, strlen(text));
}

astring astrFromCstron(const char *text, size_t offset, size_t n)
{
    if (text == NULL)
        return NULL;

    astring astr = astrAlloc();
    check_mem(astr);

    size_t length = strlen(text);

    if (length <= offset)
        return astr;
    
    astr->m_len = (length - offset < n) ? length - offset : n;
    astr->m_rlen = astr->m_len + 1;
    astr->m_buffer = (char*)calloc(astr->m_rlen, sizeof(char));
    check_mem(astr->m_buffer);

    memcpy(astr->m_buffer, text + offset, n);

    return astr;

error:
    if (astr)
        free(astr);

    return NULL;
}

astring astrFromCstro(const char *text, size_t offset)
{
    return astrFromCstron(text, offset, strlen(text));
}

astring astrSubstro(const_astring astr, size_t offset, size_t n)
{
    if (astr == NULL)
        return NULL;

    astring newstr = astrAlloc();
    check_mem(newstr);

    if (astrLen(astr) <= offset)
        return newstr;

    newstr->m_len = (astrLen(astr) - offset < n) ? astrLen(astr) - offset : n;
    newstr->m_rlen = astr->m_len + 1;
    newstr->m_buffer = (char*)calloc(astr->m_rlen, sizeof(char));
    check_mem(newstr->m_buffer);

    memcpy(newstr->m_buffer, astr_cstr(astr) + offset, n);

    return newstr;

error:
    if (newstr)
        free(newstr);
    
    return NULL;
}

astring astrSubstr(const_astring astr, size_t n)
{
    return astrSubstro(astr, 0, n);
}

astring astrCreateCopy(const_astring astr)
{
    return astrSubstro(astr, 0, astrLen(astr));
}

int astrSetFromCstr(astring astr, const char *cstr)
{
    if (astr == NULL)
        return ASTRING_ERROR;

    size_t cstrLen = strlen(cstr);
    astr->m_len = cstrLen;
    astr->m_rlen = astrLen(astr) + 1;

    if (astr_cstr(astr) == NULL)
    {
        astr->m_buffer = strdup(cstr);
        check_mem(astr_cstr(astr));

        return ASTRING_SUCCESS;
    }

    astr->m_buffer = (char*)realloc((void*)astr->m_buffer, astrRLen(astr) * sizeof(char));
    check_mem(astr_cstr(astr));

    memset(astr->m_buffer, 0, astrRLen(astr));
    memcpy(astr->m_buffer, cstr, astrLen(astr));

    return ASTRING_SUCCESS;

error:
    return ASTRING_ERROR;
}

int astrConcat(astring astr, const_astring astr2)
{
    if (astr == NULL || astr2 == NULL || astr_cstr(astr2) == NULL)
        return ASTRING_ERROR;
        
    size_t oldLen = astrLen(astr);
    astr->m_len += astrLen(astr2);
    astr->m_rlen += astrRLen(astr2);

    if (astr_cstr(astr) == NULL)
    {
        astr->m_buffer = strdup(astr2->m_buffer);
        check_mem(astr->m_buffer);

        return ASTRING_SUCCESS;
    }

    astr->m_buffer = (char*)realloc((void*)astr->m_buffer, astrRLen(astr) * sizeof(char));
    check_mem(astr->m_buffer);
    
    memcpy(astr->m_buffer + oldLen, astr2->m_buffer, astrLen(astr2));
    astr->m_buffer[astrLen(astr)] = '\0';


    return ASTRING_SUCCESS;
    
error:
    return ASTRING_ERROR;
}

int astrConcatCstr(astring astr, const char *cstr)
{
    if (astr == NULL || cstr == NULL)
        return ASTRING_ERROR;

    size_t cstrLen = strlen(cstr);
    size_t oldLen = astrLen(astr);
    astr->m_len += cstrLen;
    astr->m_rlen += cstrLen;

    if (astr_cstr(astr) == NULL)
    {
        astr->m_rlen++;
        astr->m_buffer = strdup(cstr);
        check_mem(astr->m_buffer);

        return ASTRING_SUCCESS;
    }

    astr->m_buffer = (char*)realloc((void*)astr->m_buffer, astrRLen(astr) * sizeof(char));
    check_mem(astr->m_buffer);
    
    memcpy(astr->m_buffer + oldLen, cstr, cstrLen);
    astr->m_buffer[astrLen(astr)] = '\0';
    

    return ASTRING_SUCCESS;

error:
    return ASTRING_ERROR;
}

int astrInsert(astring astr, size_t pos, const_astring bstr)
{
    if (astr == NULL || 
        bstr == NULL || 
        astr_cstr(astr) == NULL || 
        astr_cstr(bstr) == NULL ||
        pos >= astrLen(astr))
        return ASTRING_ERROR;
    else if (pos + 1 == astrLen(astr))
        return astrConcat(astr, bstr);

    size_t oldStrLen = astrLen(astr) - pos;
    
    astr->m_len += astrLen(bstr);
    astr->m_rlen += astrLen(bstr);
    astr->m_buffer = (char*)realloc((void*)astr->m_buffer, sizeof(char) * astrRLen(astr));
    check_mem(astr->m_buffer);

    memmove(astr->m_buffer + pos + astrLen(bstr), astr->m_buffer + pos, oldStrLen + 1);
    memcpy(astr->m_buffer + pos, bstr->m_buffer, astrLen(bstr));

    return ASTRING_SUCCESS;

error:

    return ASTRING_ERROR;
}

int astrInsertCstr(astring astr, size_t pos, const char *cstr)
{
    if (astr == NULL || 
        cstr == NULL || 
        astr_cstr(astr) == NULL ||
        pos >= astrLen(astr))
        return ASTRING_ERROR;
    else if (pos + 1 == astrLen(astr))
        return astrConcatCstr(astr, cstr);

    size_t cstrLength = strlen(cstr);
    size_t oldStrLen = astrLen(astr) - pos;

    astr->m_len += cstrLength;
    astr->m_rlen += cstrLength;
    astr->m_buffer = (char*)realloc((void*)astr->m_buffer, sizeof(char) * astrRLen(astr));
    check_mem(astr->m_buffer);

    memmove(astr->m_buffer + pos + cstrLength, astr->m_buffer + pos, oldStrLen + 1);
    memcpy(astr->m_buffer + pos, cstr, cstrLength);

    return ASTRING_SUCCESS;

error:
    return ASTRING_ERROR;
}

int astrTrunc(astring astr, size_t end)
{
    if (astr == NULL || astr_cstr(astr) == NULL || end >= astrLen(astr))
        return ASTRING_ERROR;
    else if (end + 1 == astrLen(astr))
        return ASTRING_SUCCESS;

    astr->m_len -= (astrLen(astr) - end);
    astr->m_rlen = astrLen(astr) + 1;
    astr->m_buffer = (char*)realloc((void*)astr->m_buffer, astrRLen(astr) * sizeof(char));
    check_mem(astr->m_buffer);

    astr->m_buffer[astrLen(astr)] = '\0';
    
    return ASTRING_SUCCESS;

error:
    return ASTRING_ERROR;
}

int astrCmp(const_astring astr, const_astring astr2)
{
    if (astr_cstr(astr) == NULL && astr_cstr(astr2) == NULL)
        return 0;
    else if (astr_cstr(astr) == NULL)
        return -1;
    else if (astr_cstr(astr2) == NULL)
        return 1;

    size_t aLen = astrLen(astr);
    size_t bLen = astrLen(astr2);

    size_t minLen = (aLen < bLen) ? aLen : bLen;

    const char *acstr = astr_cstr(astr);
    const char *bcstr = astr_cstr(astr2);

    for (size_t i = 0; i < minLen; i++)
    {
        if (acstr[i] > bcstr[i])
            return 1;
        else if (acstr[i] < bcstr[i])
            return -1;
    }

    if (aLen == bLen)
        return 0;

    return (aLen > bLen) ? 1 : -1; 
}

size_t astrFind(const_astring astr, const_astring astr2, size_t start, bool *found)
{
    if (found != NULL)
        *found = false;

    if ((astr == NULL) || (astr2 == NULL) || (astr_cstr(astr) == NULL) || (astr_cstr(astr2) == NULL))
        return 0;

    const char *acstr = astr_cstr(astr);
    const char *bcstr = astr_cstr(astr2);

    size_t aLen = astrLen(astr) ;
    size_t bLen = astrLen(astr2);

    if ((start > aLen) || (aLen - start < bLen) || bLen == 0)
    {
        if (aLen == 0 && bLen == 0 && found != NULL)
            *found = true;

        return 0;
    }
    
    size_t shift = 0;
    size_t pos = 0;

    for (size_t i = start; i < aLen; i++)
    {
        if (acstr[i] == bcstr[shift])
        {
            if (shift == 0)
                pos = i;
            
            shift++;
        }
        else if (shift != 0)
            shift = 0;

        if (shift == bLen)
        {
            if (found != NULL)
                *found = true;

            return pos;
        }
    }

    return 0;
}

size_t astrFindFirst(const_astring astr, const_astring astr2, bool *found)
{
    return astrFind(astr, astr2, 0, found);
}

bool astrContains(const_astring astr, const_astring astr2)
{
    bool found = false;
    astrFindFirst(astr, astr2, &found);

    return found;
}

size_t astrFindCstr(const_astring astr, const char *cstr, size_t start, bool *found)
{
    if (found != NULL)
        *found = false;

    if ((astr == NULL) || (cstr == NULL) || (astr_cstr(astr) == NULL))
        return 0;

    const char *acstr = astr_cstr(astr);

    size_t astrLen = astrLen(astr);
    size_t cstrLen = strlen(cstr);

    if ((start > astrLen) || (astrLen - start < cstrLen) || cstrLen == 0)
    {
        if (astrLen == 0 && cstrLen == 0 && found != NULL)
            *found = true;

        return 0;
    }
    
    size_t shift = 0;
    size_t pos = 0;

    for (size_t i = start; i < astrLen; i++)
    {
        if (acstr[i] == cstr[shift])
        {
            if (shift == 0)
                pos = i;
            
            shift++;
        }
        else if (shift != 0)
            shift = 0;

        if (shift == cstrLen)
        {
            if (found != NULL)
                *found = true;

            return pos;
        }
    }

    return 0;
}

size_t astrFindFirstCstr(const_astring astr, const char *cstr, bool *found)
{
    return astrFindCstr(astr, cstr, 0, found);
}

bool astrContainsCstr(const_astring astr, const char *cstr)
{
    bool found = false;
    astrFindFirstCstr(astr, cstr, &found);

    return found;
}

bool astrContainsChar(const_astring astr, char c)
{
    const char *acstr = astr_cstr(astr);

    for (size_t i = 0; i < astrLen(astr); i++)
        if (acstr[i] == c)
            return true;

    return false;
}

int astrTrimStart(astring astr)
{
    if (astr == NULL || astr_cstr(astr) == NULL)
        return ASTRING_ERROR;

    size_t count = 0;
    char *cstr = astr_cstr(astr);

    for (; count < astrLen(astr); count++)
        if (!isblank(cstr[count]))
            break;

    if (count != 0)
    {
        memmove(astr->m_buffer, astr->m_buffer + count, astrLen(astr) - count);
        memset(astr->m_buffer + astrLen(astr) - count, 0, count);
        astr->m_len = astrLen(astr) - count;
        astr->m_rlen = astr->m_len + 1;
        astr->m_buffer = (char*)realloc((void*)astr->m_buffer, astrRLen(astr) * sizeof(char));
        check_mem(astr_cstr(astr));
    }

    return ASTRING_SUCCESS;

error:
    return ASTRING_ERROR;
}

int astrTrimEnd(astring astr)
{
    if (astr == NULL || astr_cstr(astr) == NULL)
        return ASTRING_ERROR;

    size_t count = 0;
    char *cstr = astr_cstr(astr);

    for (; astrLen(astr) - count - 1 >= 0; count++)
    {
        if (!isblank(cstr[astrLen(astr) - count - 1]))
            break;

        if (astrLen(astr) - count - 1 == 0)
            break;
    }

    if (count != 0)
    {
        astr->m_len = astrLen(astr) - count;
        astr->m_rlen = astr->m_len + 1;
        astr->m_buffer = (char*)realloc((void*)astr->m_buffer, astrRLen(astr));
        check_mem(astr_cstr(astr));
        astr->m_buffer[astrLen(astr)] = '\0';
    }

    return ASTRING_SUCCESS;

error:
    return ASTRING_ERROR;
}

int astrTrim(astring astr)
{
    int success = astrTrimStart(astr);

    if (success == ASTRING_ERROR)
        return ASTRING_ERROR;

    return astrTrimEnd(astr);
}

int astrToLowerASCII(astring astr)
{
    if (astr == NULL || astr_cstr(astr) == NULL)
        return ASTRING_ERROR;

    for (size_t i = 0; i < astrLen(astr); i++)
        if (isupper(astr->m_buffer[i]))
            astr->m_buffer[i] = tolower(astr->m_buffer[i]);

    return ASTRING_SUCCESS;
}

int astrToUpperASCII(astring astr)
{
    if (astr == NULL || astr_cstr(astr) == NULL)
        return ASTRING_ERROR;

    for (size_t i = 0; i < astrLen(astr); i++)
        if (islower(astr->m_buffer[i]))
            astr->m_buffer[i] = toupper(astr->m_buffer[i]);

    return ASTRING_SUCCESS;
}

void astrListDestroy(astringList list)
{
    if (list)
    {
        if (list->m_astrs != NULL)
        {
            for (size_t i = 0; i < astrListCount(list); i++)
                astrDestroy(astrListGet(list, i));

            free(list->m_astrs);
        }

        free(list);
    }
}

static inline int splitCount(const_astring astr, const char *delimiters, size_t delimitersCount)
{
    bool validSplit = false;
    size_t count = 0;
    const char *acstr = astr_cstr(astr);

    for (size_t i = 0; i < astrLen(astr); i++)
    {
        for (size_t j = 0; j < delimitersCount; j++)
        {
            if(acstr[i] == delimiters[j])
            {
                if (validSplit)
                    count++;

                validSplit = false;

                break;
            }

            if (j + 1 == delimitersCount)
                validSplit = true;
        }
    }

    if (validSplit)
        count++;

    return count;
}

astringList astrSplit(const_astring astr, const char *delimiters)
{
    if (astr_cstr(astr) == NULL || delimiters == NULL)
        return NULL;
    
    astringList list = astrListAlloc();
    check_mem(list);

    const char *acstr = astr_cstr(astr);
    size_t delimitersCount = strlen(delimiters);

    list->m_count = splitCount(astr, delimiters, delimitersCount);
    list->m_astrs = astrListAstrsAlloc(list);

    if (list->m_count == 1)
    {
        list->m_astrs[0] = astrFromCstr(astr->m_buffer);
        return list;
    }

    size_t len = 0;
    size_t count = 0;

    for (size_t i = 0; i < astrLen(astr) && count != astrListCount(list); i++)
    {
        if (i + 1 == astrLen(astr))
        {
            list->m_astrs[count++] = astrFromCstron(acstr, (i - len), len + 1);
            break;
        }

        for (size_t j = 0; j < delimitersCount; j++)
        {
            if(acstr[i] == delimiters[j])
            {
                if (len != 0)
                    list->m_astrs[count++] = astrFromCstron(acstr, (i - len), len);

                len = 0;

                break;
            }

            if (j + 1 == delimitersCount)
                len++;
        }
    }
    
    return list;

error:
    return NULL;
}

int main()
{
    astring str = astrFromCstr(" Hello world ");
    astrTrim(str);
    astrToLowerASCII(str);
    astrTrunc(str, 5);
    struct tagastring str2 = astrStatic(" shitty");
    astrInsert(str, 4, &str2);
    log("%s", astr_cstr(str));
    astrDestroy(str);

    return 0;
}