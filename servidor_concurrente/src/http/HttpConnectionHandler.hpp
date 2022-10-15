
#ifndef HTTPCONNECTIONHANDLER_HPP
#define HTTPCONNECTIONHANDLER_HPP

#include <vector>
#include "Consumer.hpp"
#include "Socket.hpp"
#include "TcpServer.hpp"
#include "HttpRequest.hpp"
#include "HttpResponse.hpp"
#include "HttpConnectionHandler.hpp"
#include "Queue.hpp"
#include "HttpServer.hpp"
#include "HttpApp.hpp"
#include "HttpPackage.hpp"

class HttpApp;
class HttpServer;


class HttpConnectionHandler: public Consumer<Socket>{
    DISABLE_COPY(HttpConnectionHandler);


    protected:

    size_t numberOfSockets = 0;

    std::vector<HttpApp*> applications;
    
    virtual bool handleHttpRequest(HttpPackage& httpPackage);

    bool route(HttpPackage& httpPackage);
      bool serveNotFound(HttpPackage& httpPackage);
    public:


   // HttpConnectionHandler();
    //~HttpConnectionHandler();

    explicit HttpConnectionHandler(std::vector<HttpApp*> applications);

    int run()override;

    void consume(Socket client) override;

};

#endif