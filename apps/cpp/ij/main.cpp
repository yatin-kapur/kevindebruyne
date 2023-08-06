#include <iostream>
#include "lib/logger/log.h"
#include "lib/k/k.h"

int main()
{
    Log log("table");
    log.info("Starting app");

    auto host = (S)"localhost";
    auto port = (I)12345;
    auto user = (S)"";

    auto handle = khpu(host, port, user);

    auto t1 = k(handle, (S)"t1", (K)0);
    auto t2 = k(handle, (S)"t2", (K)0);
    auto t3 = k(handle, (S)"t3", (K)0);

    // this takes the first element of the table, which is the list of columns
    // and takes it's length
    auto ncols = kK(t1->k)[0]->n;

    for(int col=0; col < ncols; col++)
    {
        jv(&kK(kK(t1->k)[1])[col], kK(kK(t2->k)[1])[col]);
    }

    // this takes all the values, first element of table
    // it then finds the first column
    // and then we find it's length
    auto nrows = kK(kK(t1->k)[1])[1]->n;
    std::cout << "Rows: " << nrows << std::endl;
    for(int row=0; row<nrows; row++)  {
        for(int col=0; col<ncols; col++) {
            std::cout << "Row: " << row <<  ", Col: " << col << ", value: " << kI(kK(kK(t1->k)[1])[col])[row] << std::endl;
        }
    }

    for(int col=0; col < ncols; col++)
    {
        jv(&kK(kK(t1->k)[1])[col], kK(kK(t3->k)[1])[col]);
    }

    // this takes all the values, first element of table
    // it then finds the first column
    // and then we find it's length
    nrows = kK(kK(t1->k)[1])[1]->n;
    std::cout << "Rows: " << nrows << std::endl;
    for(int row=0; row<nrows; row++)  {
        for(int col=0; col<ncols; col++) {
            std::cout << "Row: " << row <<  ", Col: " << col << ", value: " << kI(kK(kK(t1->k)[1])[col])[row] << std::endl;
        }
    }

    r0(t1);
    r0(t2);
    return 0;
}