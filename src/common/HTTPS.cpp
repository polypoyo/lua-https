#include "HTTPS.h"
#include "config.h"
#include "ConnectionClient.h"

#include <stdexcept>

#ifdef HTTPS_BACKEND_CURL
#	include "../generic/CurlClient.h"
#endif
#ifdef HTTPS_BACKEND_OPENSSL
#	include "../generic/OpenSSLConnection.h"
#endif
#ifdef HTTPS_BACKEND_SCHANNEL
#	include "../windows/SChannelConnection.h"
#endif
#ifdef HTTPS_BACKEND_NSURL
#	include "../macos/NSURLClient.h"
#endif
#ifdef HTTPS_BACKEND_ANDROID
#	include "../android/AndroidClient.h"
#endif

#ifdef HTTPS_BACKEND_CURL
	static CurlClient curlclient;
#endif
#ifdef HTTPS_BACKEND_OPENSSL
	static ConnectionClient<OpenSSLConnection> opensslclient;
#endif
#ifdef HTTPS_BACKEND_SCHANNEL
	static ConnectionClient<SChannelConnection> schannelclient;
#endif
#ifdef HTTPS_BACKEND_NSURL
	static NSURLClient nsurlclient;
#endif
#ifdef HTTPS_BACKEND_ANDROID
	static AndroidClient androidclient;
#endif

static HTTPSClient *clients[] = {
#ifdef HTTPS_BACKEND_CURL
	&curlclient,
#endif
#ifdef HTTPS_BACKEND_OPENSSL
	&opensslclient,
#endif
#ifdef HTTPS_BACKEND_SCHANNEL
	&schannelclient,
#endif
#ifdef HTTPS_BACKEND_NSURL
	&nsurlclient,
#endif
#ifdef HTTPS_BACKEND_ANDROID
	&androidclient,
#endif
	nullptr,
};

HTTPSClient::Reply request(const HTTPSClient::Request &req)
{
	for (size_t i = 0; clients[i]; ++i)
	{
		HTTPSClient &client = *clients[i];

		if (client.valid())
			return client.request(req);
	}

	throw std::runtime_error("No applicable HTTPS implementation found");
}
