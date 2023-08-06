#include <glob.h>
#include <thread>

#include "KSVTable.h"

KSVTable::KSVTable(const KSVTable::TableCallback &c, const std::string& tableName)
    :KTable(tableName),
    log("KSVTable"),
    datacallback(c)
{
    log.info("Constructed KSVTable with name: " + tableName);
}

KSVTable::~KSVTable() 
{

}

void KSVTable::add_column(const std::string& colname, const std::string& coltype)
{
    log.info("Adding column '" + colname + "' of type " + coltype);
    m_columns[colname] = kdb_types::get_type(coltype);
}


void KSVTable::add_pattern(const std::string& p)
{
    m_patterns.push_back(p);
    log.info("For " + m_tableName + ", set added file pattern: " + p + "\n");

    // glob the pattern and get all the files
    glob_t files;
    int err = glob(&p[0], 0, NULL, &files);
    for (size_t i = 0; i < files.gl_pathc; i++)
    {
        m_files.push_back(files.gl_pathv[i]);
    }
    globfree(&files);
}

void KSVTable::process_file(const std::string& file)
{
    log.info("Processing file: " + file);

    rapidcsv::Document doc(file);
    for (const auto& col : m_columns)
    {
        log.info(col.first);
        // switch (col.second)
        // {
        //     case kdb_types::type::ksymbol:
        //     {
        //         std::vector<std::string> column;
        //         column = doc.GetColumn<std::string>(col.first);
        //         break;
        //     }
        //     case kdb_types::type::kint:
        //     {
        //         std::vector<std::string> column;
        //         column = doc.GetColumn<std::string>(col.first);
        //         break;
        //     }
        //     default:
        //     {
        //         std::vector<std::string> column;
        //         column = doc.GetColumn<std::string>(col.first);
        //     }
        // }
    }
}

void KSVTable::process_files()
{
    for (const auto& f : m_files) {
        process_file(f);
    }
}