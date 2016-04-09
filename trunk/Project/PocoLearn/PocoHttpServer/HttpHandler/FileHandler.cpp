#include "stdafx.h"
#include "FileHandler.h"


CFileHandler::CFileHandler()
{
}

CFileHandler::~CFileHandler()
{
    if (!m_fileName.empty())
    {
        Poco::File tempFile(m_fileName);
        if (tempFile.exists())
        {
            tempFile.remove();
        }
    }
}

void CFileHandler::handlePart(const Poco::Net::MessageHeader& header, std::istream& stream)
{
    if (header.has("Content-Disposition"))
    {
        std::string disp;
        NameValueCollection params;
        MessageHeader::splitParameters(header["Content-Disposition"], disp, params);
        auto name = params.get("name", "(unnamed)");
        if (name == "file")
        {
            Poco::Random rnd;
            rnd.seed();
            m_fileName = Poco::Path::temp() + Poco::NumberFormatter::format(rnd.next()) + ".file";
            Poco::File tempFileName(m_fileName);
            std::ofstream of(tempFileName.path(), std::ios::binary);
            if (of.is_open())
            {
                m_isReady = true;
                Poco::StreamCopier::copyStream(stream, of);
                of.close();
            }
            else
            {
                m_isReady = false;
            }
        }
    }
}

bool CFileHandler::isReady() const
{
    return m_isReady;
}

std::string CFileHandler::getFileName() const
{
    return m_fileName;
}
