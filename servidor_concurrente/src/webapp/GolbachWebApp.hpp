
#ifndef GOLBACHWEBAPP_HPP
#define GOLBACHWEBAPP_HPP

#include "HttpApp.hpp"




class GolbachWebApp : public HttpApp{

    DISABLE_COPY(GolbachWebApp);

    public:

    GolbachWebApp();
    ~GolbachWebApp();

    void start()override;

    bool handleHttpRequest(HttpRequest& httpRequest,
    HttpResponse& httpResponse)override;

    void stop() override;

    protected:

    bool serveHomepage(HttpRequest& httpRequest, HttpResponse& httpResponse);

    bool serveGolbach(HttpRequest& httpRequest, HttpResponse& httpResponse);



};

#endif