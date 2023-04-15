#include "KSV.h"

KSV::KSV(const std::string& file)
    : m_configFile(file),
    log("KSV")
{
    log.info("constructed KSV for config file at: " + m_configFile);
    m_config.load_file(m_configFile.c_str());
}

KSV::~KSV()
{

}

void KSV::run()
{
    log.info("called KSV::run()");

    // parse config file and get kdb connections
    const std::string& qhost = m_config.child("KDB").attribute("host").as_string();
    const std::string& userpass = m_config.child("KDB").attribute("userpass").as_string();
    const int qport = m_config.child("KDB").attribute("port").as_int();

    log.info("KDB service passed as: " + qhost + ":" + std::to_string(qport));

    // send test message to kdb service just for fun
    I handle;
    K result;

    handle= khpu(const_cast<char *>(qhost.c_str()), qport, const_cast<char *>(userpass.c_str()));
    printf("Handle value is %d\n", handle);
    result= k(handle, const_cast<char *>("2.0+3.0"), (K)0);
    printf("Value returned is %f\n", result->f);

    r0(result);
    kclose(handle);
}