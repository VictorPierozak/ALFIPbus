#include "AlfIPbus.h"

std::atomic<bool> AlfIPbus::s_running{false};

AlfIPbus::AlfIPbus(const AlfConfig& cfg)
  : m_cfg(cfg)
{
  BOOST_LOG_TRIVIAL(info) << "Created ALF IPbus named " << m_cfg.name;
  s_running.store(true);
}

AlfIPbus::~AlfIPbus() {
  BOOST_LOG_TRIVIAL(info) << "ALF IPbus " << m_cfg.name << " shutting down";
  s_running.store(false);
}

void AlfIPbus::initLinks()
{
  for (size_t i = 0; i < m_cfg.links.size(); i++) {
    std::string serviceName = m_cfg.name + "/SERIAL_0/LINK_" + std::to_string(i) + "/SWT_SEQUENCE";
    BOOST_LOG_TRIVIAL(debug) << "Creating service " + serviceName;
    m_swtLinks.emplace_back(serviceName, m_ioContext, m_cfg.links[i].address, m_cfg.links[i].rport, 0);
    BOOST_LOG_TRIVIAL(info) << "Created service " + serviceName;
  }
}

void AlfIPbus::startServer()
{
  DimServer::start(m_cfg.name.c_str());
  mainLoop();
}

void AlfIPbus::stop(int)
{
  s_running.store(false);
}

void AlfIPbus::mainLoop()
{
  while (AlfIPbus::s_running.load()) {
    pause();
  }
}
