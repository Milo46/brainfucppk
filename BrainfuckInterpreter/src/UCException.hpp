#pragma once

class UCException
{
public:
    UCException(const char* message);

    virtual const char* What() const;

private:
    const char* m_Message;
};
