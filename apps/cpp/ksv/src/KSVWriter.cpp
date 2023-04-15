#include "KSVWriter.h"

KSVWriter::KSVWriter(std::string file): 
    m_csvFile(file),
    log("KSVWriter", 2)
{
    log.info("constructed KSVWriter for CSV file: " + m_csvFile);
}

KSVWriter::~KSVWriter() 
{

}