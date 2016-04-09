#ifndef _FILE_HANDLER_H_
#define _FILE_HANDLER_H_


class CFileHandler : public Poco::Net::PartHandler
{
public:
    CFileHandler();
    ~CFileHandler();

    void handlePart(const Poco::Net::MessageHeader& header, std::istream& stream) override final;

    bool isReady() const;
    std::string getFileName() const;

private:
    bool m_isReady = false;
    std::string m_fileName;
};

#endif // CFileHandler_H
