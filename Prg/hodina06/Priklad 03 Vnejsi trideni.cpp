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
#include "heapsort.hxx"

constexpr int MERGE_PAGE_SIZE{ 4 };

int bufferReadInts(std::ifstream& input, int *buffer, int runSize, int &bufferElCount)
{
    for (int i{ 0 }; i < runSize && !input.eof(); i++)
        input >> buffer[bufferElCount++];

    return buffer[bufferElCount];
}

void bufferWrite(std::ostream& fout, int *buffer, int runSize, int &bufferElCount)
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
        else if (f2lastval >= f1lastval)
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

int main()
{
    externalMerge("f1.txt", "f2.txt", "fout.txt", asc);
}