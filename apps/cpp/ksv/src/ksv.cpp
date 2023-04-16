#include <filesystem>
#include <thread>

#include "KSV.h"

KSV::KSV(const std::string& file)
    : log("KSV"),
    m_configFile(file)
{
    log.info("Constructed KSV for config file at: " + m_configFile);
    m_config.load_file(m_configFile.c_str());
}

KSV::~KSV()
{

}

void KSV::run()
{
    log.info("Called KSV::run()");

    auto cfg = m_config.child("KSV");

    // parse config file and get kdb connections
    const std::string& qhost = cfg.child("KDB").attribute("host").as_string();
    const std::string& userpass = cfg.child("KDB").attribute("userpass").as_string();
    const int qport = cfg.child("KDB").attribute("port").as_int();

    log.info("KDB service defined: " + qhost + ":" + std::to_string(qport));

    // get all file patterns
    std::vector<std::string> patterns;
    auto data = cfg.child("Data");
    for (const auto &csv : data)
    {
        const std::string& dir = csv.child("Directory").child_value();
        auto subd = csv.child("Subdirectories");
        for (const auto &fp: subd) // find all subdirectory patterns
        {
            const std::string& filepattern = fp.child_value();
            const std::string& table = fp.attribute("table").as_string();

            auto pattern = dir + filepattern;

            // check if this table exists in the map
            if (m_KSVTables.find(table) == m_KSVTables.end())
            {
                m_KSVTables[table] = std::make_unique<KSVTable>(
                        std::bind(&KSV::callback, this, std::placeholders::_1, std::placeholders::_2), 
                        table
                    );
            }
            m_KSVTables[table]->add_pattern(pattern);
        }
    }

    // send test message to kdb service just for fun
    auto handle = khpu(const_cast<char *>(qhost.c_str()), qport, const_cast<char *>(userpass.c_str()));
    printf("Handle value is %d\n", handle);
    auto result = k(handle, const_cast<char *>("2.0+3.0"), (K)0);
    printf("Value returned is %f\n", result->f);
    r0(result);
    kclose(handle);
    // finish and close handle

    start_tables();
    
    // TODO: graceful closing on sigterm
    while (true) {}
}

void KSV::start_tables() 
{
    // each table to process all their files
    for (const auto &tbl : m_KSVTables)
    {
        auto t = std::thread(std::bind(&KSVTable::process_files, tbl.second.get()));
        t.detach();
    }
}

void KSV::callback(const std::string& tbl, std::unique_ptr<KRow> row)
{
    // add row to buffer with table name
    log.info("Got row for table: " + tbl);
}