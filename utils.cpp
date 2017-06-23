#include <QUrl>
#include <QJsonDocument>

#include <progbase.h>
#include <progbase/net.h>

#include "utils.h"

#define BUFFER_LEN 1024

#define HTTP "http"
#define HTTPS "https"

#define USER_AGENT "lab7"

#define HEAD_SEPARATOR "\r\n\r\n"

QByteArray WebGet(QString sUrl)
{
    char buffer[BUFFER_LEN];

    QByteArray result;

    QUrl url(sUrl);
    if (url.scheme() != HTTP && url.scheme() != HTTPS)
        return "ERROR: invalid scheme";

    char host[255] = "";
    strcpy(host, url.host().toLocal8Bit());

    char path[255] = "";
    strcpy(path, url.path().toLocal8Bit());

    int port = url.port();
    if (port == -1)
        port = url.scheme() == HTTP ? 80 : 443;

    Ssl ssl;
    TcpClient client;
    TcpClient_init(&client);

    char ipv4[20] = "";
    if (!Ip_resolveHostname(ipv4, host))
        return "ERROR: resolve address";

    IpAddress ipAddress;
    IpAddress_init(&ipAddress, ipv4, port);

    NetMessage message;
    NetMessage_init(&message, buffer, BUFFER_LEN);

    if (url.scheme() == HTTP)
    {
        if (!TcpClient_connect(&client, &ipAddress))
            return ("ERROR: tcp connect");
    }
    else // HTTPS
    {
        Ssl_init(&ssl);
        client.ssl = &ssl;
        if (!TcpClient_connectSecure(&client, &ipAddress, &ssl))
                return ("ERROR: tcp connect");
    }

    char httpRequest[255] = "";
    sprintf(httpRequest,
        "GET %s HTTP/1.0\r\n"
        "Host: %s\r\n"
        "User-Agent: " USER_AGENT "\r\n"
        "\r\n",
        path,
        host);
    NetMessage_setDataString(&message, httpRequest);

    if(!TcpClient_send(&client, &message))
        return ("ERROR: send");

    while (1)
    {
        if(!TcpClient_receive(&client, &message))
            return ("ERROR: receive");
        if (NetMessage_dataLength(&message) == 0)
            break;
        result.append(message.buffer, message.dataLength);
    }

    TcpClient_close(&client);

    char* pos = strstr(result.data(), HEAD_SEPARATOR);

    if (pos != NULL)
    {
        result.remove(0, pos - result.data() + strlen(HEAD_SEPARATOR));
        return result;
    }
    else
        return "ERROR: no data";
}

QString TestJsonResult(QString s)
{
    QJsonDocument doc = QJsonDocument::fromJson(s.toUtf8());
    if (doc.isNull())
        return "ERROR: parsing JSON result";

    return doc.toJson();
}
