
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

class HttpApp;
class HttpServer;


class HttpConnectionHandler: public Consumer<Socket>{
    DISABLE_COPY(HttpConnectionHandler);


    protected:

    size_t numberOfSockets = 0;

    std::vector<HttpApp*> applications;
    
    virtual bool handleHttpRequest(HttpRequest& httpRequest,
    HttpResponse& httpResponse);

    bool route(HttpRequest& httpRequest, HttpResponse& httpResponse);
      bool serveNotFound(HttpRequest& httpRequest, HttpResponse& httpResponse);
    public:


   // HttpConnectionHandler();
    //~HttpConnectionHandler();

    explicit HttpConnectionHandler(std::vector<HttpApp*> applications);

    int run()override;

    void consume(Socket client) override;

};



















#endif