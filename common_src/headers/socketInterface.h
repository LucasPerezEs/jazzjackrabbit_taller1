#ifndef SOCKETINTERFACE_H_
#define SOCKETINTERFACE_H_

class SocketInterface {
public:
    virtual int sendsome(const void *data, unsigned int sz, bool *was_closed) = 0;
    virtual int recvsome(void *data, unsigned int sz, bool *was_closed) = 0;

    virtual int sendall(const void *data, unsigned int sz, bool *was_closed) = 0;
    virtual int recvall(void *data, unsigned int sz, bool *was_closed) = 0;

    virtual SocketInterface *accept() = 0;

    virtual void shutdown(int how) = 0;

    virtual int close() = 0;

    virtual ~SocketInterface() {}
};

#endif
