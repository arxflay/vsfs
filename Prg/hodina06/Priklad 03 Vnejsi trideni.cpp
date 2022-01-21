// Tento zdrojovy kod jsem vypracoval zcela samostatne bez cizi pomoci
// Neokopiroval jsem ani neopsal jsem cizi zdrojove kody
// Nikdo mi pri vypracovani neradil
// Pokud nektery radek porusuje toto pravidlo je oznacen komentarem
// NENI MOJE TVORBA
// Poruseni techto pravidel se povazuje za podvod, ktery lze potrestat VYLOUCENIM ZE STUDIA
// Alexej Fedorenko, učo 37676 

#include <fstream>
#include <string>
#include <sstream>
#include <iostream>
#include <cstdio>
#include "heapsort.hxx"

constexpr int MERGE_PAGE_SIZE{ 4 };

//returns last read int
int bufferReadInts(std::ifstream &input, int *buffer, int runSize, int &bufferElCount)
{
    for (int i{ 0 }; i < runSize && !input.eof(); i++)
        input >> buffer[bufferElCount++];
    
    return buffer[bufferElCount - 1];
}

void bufferWrite(std::ostream &fout, int *buffer, int runSize, int &bufferElCount)
{
    for (int i { 0 }; i < runSize && bufferElCount > 0; i++)
    {
        if (bufferElCount == 1)
            fout << buffer[--bufferElCount];
        else
            fout << buffer[--bufferElCount] << ' ';
    }
}

compFunc changeComp(compFunc func)
{
    if (func == asc)
        return desc;
    else
        return asc;
}

/*
    Speed 3.1GB/min
    Tested on Ryzen 2600 with 16GB RAM and NVME SSD with speed 1GB/s
*/

void externalMerge(const std::string &f1, const std::string &f2, const std::string &output, compFunc comp) //a)
{
    comp = changeComp(comp);

    int f1lastval{ 0 };
    int f2lastval{ 0 };
    int buffer[MERGE_PAGE_SIZE * 2]{};
    int bufferElCount{ 0 };
    std::ifstream f1Input{};
    std::ifstream f2Input{};
    std::ofstream fout{};
    
    f1Input.exceptions(f1Input.failbit | f1Input.badbit);
    f2Input.exceptions(f2Input.failbit | f2Input.badbit);
    f1Input.open(f1);
    f2Input.open(f2);
    fout.open(output);
    f1Input.peek();
    f2Input.peek();
    
    while (!f1Input.eof() && !f2Input.eof())
    {
        if (bufferElCount == 0)
        {
            f1lastval = bufferReadInts(f1Input, buffer, MERGE_PAGE_SIZE, bufferElCount);
            f2lastval = bufferReadInts(f2Input, buffer, MERGE_PAGE_SIZE, bufferElCount);
        }
        else if (comp(f1lastval, f2lastval))
            f1lastval = bufferReadInts(f1Input, buffer, MERGE_PAGE_SIZE, bufferElCount);
        else
            f2lastval = bufferReadInts(f2Input, buffer, MERGE_PAGE_SIZE, bufferElCount);

        heapsort(buffer, bufferElCount - 1, comp);
        bufferWrite(fout, buffer, MERGE_PAGE_SIZE, bufferElCount);
    }

    while(!f1Input.eof())
    {
        bufferReadInts(f1Input, buffer, MERGE_PAGE_SIZE, bufferElCount);
        heapsort(buffer, bufferElCount - 1, comp);
        bufferWrite(fout, buffer, MERGE_PAGE_SIZE, bufferElCount);
    }
    f1Input.close();

    while(!f2Input.eof())
    {
        bufferReadInts(f2Input, buffer, MERGE_PAGE_SIZE, bufferElCount);
        heapsort(buffer, bufferElCount - 1, comp);
        bufferWrite(fout, buffer, MERGE_PAGE_SIZE, bufferElCount);
    }
    f2Input.close();

    if (bufferElCount > 0)
        bufferWrite(fout, buffer, MERGE_PAGE_SIZE, bufferElCount);

    fout.close();
}

//K-way using iterative 2-way approach
void externalMergeK(const std::string *filenames, size_t k, const std::string &output, compFunc comp)
{
    if (k < 2)
        std::cerr << "ERROR: number of files must be 2 or greater" << '\n';

    static const std::string mergetag{ "mergefile" };
    std::string curtag{ mergetag + std::to_string(1) };
    externalMerge(filenames[0], filenames[1], curtag, comp);

    for (size_t i{ 2 }; i < k; i++)
    {
        std::string newtag{ mergetag + std::to_string(i) };
        externalMerge(curtag, filenames[i], newtag, comp);
        remove(curtag.c_str());
        curtag = newtag;
    }

    rename(curtag.c_str(), output.c_str());
}

int createRuns(const std::string &filename, int ways, size_t runSize, compFunc comp)
{
    comp = changeComp(comp);

    std::ifstream inputFile{};
    inputFile.exceptions(inputFile.failbit | inputFile.badbit);
    std::ofstream page{};
    int *buffer{ new int[runSize]{} };
    int runCount{ 0 };

    inputFile.open(filename);
    inputFile.peek();

    for (; runCount < ways && !inputFile.eof(); runCount++)
    {
        int bufferCount{ 0 };
        page.open(std::to_string(runCount));

        bufferReadInts(inputFile, buffer, runSize, bufferCount);
        heapsort(buffer, bufferCount - 1, comp);
        bufferWrite(page, buffer, runSize, bufferCount);

        page.close();
    }

    inputFile.close();

    delete[] buffer;

    return runCount;
}

void externalSortFile(const std::string &filename, const std::string &output, int ways, size_t runSize, compFunc comp)
{
    int runCount{ createRuns(filename, ways, runSize, comp ) };

    if (runCount == 0)
        return;

    std::string *filenames{ new std::string[runCount]{} };

    for (int i{ 0 }; i < runCount; i++)
        filenames[i] = std::to_string(i);

    if (runCount == 1)
        rename(filenames[0].c_str(), output.c_str());
    else
        externalMergeK(filenames, runCount, output, comp);

    for (int i{ 0 }; i < runCount; i++)
        remove(filenames[i].c_str());

    delete[] filenames;
}

int main()
{
    srand(time(NULL));
    size_t count{ 10000000 };
    std::ofstream testfile{};
    testfile.open("ff1.txt");

    for (size_t i{ 0 }; i < count; i++)
    {
        if (i == count - 1)
            testfile << rand() % 1000000;
        else
            testfile << rand() % 1000000 << ' ';  
    }
    testfile.close();
    
    externalSortFile("ff1.txt", "fout.txt", 10, count / 10, asc);
}